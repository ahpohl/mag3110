#include "mag3110.hpp"
#include <cmath>

#define CALIBRATION_TIMEOUT 5000 //timeout in milliseconds
#define DEG_PER_RAD (180.0/3.14159265358979)

MAG3110::MAG3110()
{
	x_offset = 0;
	y_offset = 0;
	x_scale = 0.0f;
	y_scale = 0.0f;
}

bool MAG3110::initialize() {

	if(readRegister(MAG3110_WHO_AM_I) != MAG3110_WHO_AM_I_RSP) {
		cout << "Could not find MAG3110 connected!" << endl;;
		return false;
	} else {
		reset();
		return true;
	}
}

uint8_t MAG3110::readRegister(uint8_t address)
{
  uint8_t output;
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  delayMicroseconds(2);
  Wire.requestFrom(MAG3110_I2C_ADDRESS, 1);
  while(Wire.available())
  {
	  output = Wire.read();
  }
  return output;
}

void MAG3110::writeRegister(uint8_t address, uint8_t value)
{
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
}

bool MAG3110::dataReady()
{
	return ((readRegister(MAG3110_DR_STATUS) & 0x8) >> 3);
}

void MAG3110::readMag(int* x, int* y, int* z)
{
	Wire.beginTransmission(MAG3110_I2C_ADDRESS);
	Wire.write(MAG3110_OUT_X_MSB);
	Wire.endTransmission();
	delayMicroseconds(2);
	Wire.requestFrom(MAG3110_I2C_ADDRESS, 6);
 	// Combine registers
	uint16_t values[3];
	for(uint8_t idx = 0; idx <= 2; idx++)
	{
		values[idx]  = Wire.read() << 8;	// MSB
		values[idx] |= Wire.read();       // LSB
	}
	*x = (int) values[0];
	*y = (int) values[1];
	*z = (int) values[2];
}

void MAG3110::readMicroTeslas(float* x, float* y, float* z)
{
	int x_int, y_int, z_int;
	readMag(&x_int, &y_int, &z_int);
	*x = (float) x_int * 0.1f;
	*y = (float) y_int * 0.1f;
	*z = (float) z_int * 0.1f;
}

// Note: Must be calibrated to use readHeading!!!
float MAG3110::readHeading()
{
	int x, y, z;
	readMag(&x, &y, &z);
	float xf = (float) x * 1.0f;
	float yf = (float) y * 1.0f;
	return (atan2(-y*y_scale, x*x_scale) * DEG_PER_RAD);
}

void MAG3110::setDR_OS(uint8_t DROS)
{
	bool wasActive = activeMode;	
	if(activeMode) {
		enterStandby(); //Must be in standby to modify CTRL_REG1
  }	
	delay(100);
	uint8_t current = readRegister(MAG3110_CTRL_REG1) & 0x07; //And chop off the 5 MSB
	writeRegister(MAG3110_CTRL_REG1, (current | DROS)); //Write back the register with new DR_OS set	
	delay(100);
	if(wasActive) {
		exitStandby();
  }
}

void MAG3110::triggerMeasurement()
{	
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (current |  0x02));
}

//Note that AUTO_MRST_EN will always read back as 0
//Therefore we must explicitly set this bit every time we modify CTRL_REG2
void MAG3110::rawData(bool raw){
	if(raw) //Turn on raw (non-user corrected) mode
	{
		rawMode = true;
		writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN | (0x01 << 5) );
	}
	else //Turn off raw mode
	{
		rawMode = false;
		writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN & ~(0x01 << 5));
	}
}

void MAG3110::setOffset(uint8_t axis, int offset)
{	
	offset = offset << 1;	
	uint8_t msbAddress = axis + 8;
	uint8_t lsbAddress = msbAddress + 1;
	writeRegister(msbAddress, (uint8_t)((offset >> 8) & 0xFF));
	delay(15);
	writeRegister(lsbAddress, (uint8_t) offset & 0xFF);
}

int MAG3110::readOffset(uint8_t axis)
{
	return (readAxis(axis+8)) >> 1;
}

void MAG3110::start()
{
	exitStandby();
}

void MAG3110::enterStandby()
{
	activeMode = false;
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	//Clear bits 0 and 1 to enter low power standby mode
	writeRegister(MAG3110_CTRL_REG1, (current & ~(0x3)));
}

void MAG3110::exitStandby()
{
	activeMode = true;
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (current | MAG3110_ACTIVE_MODE));	
}

bool MAG3110::isActive()
{
	return activeMode;
}

bool MAG3110::isRaw()
{
	return rawMode;
}

bool MAG3110::isCalibrated()
{
	return calibrated;
}

bool MAG3110::isCalibrating()
{
	return calibrationMode;
}

uint8_t MAG3110::getSysMode()
{
	return readRegister(MAG3110_SYSMOD);
}

void MAG3110::enterCalMode()
{
	calibrationMode = true;
	//Starting values for calibration
	x_min = 32767;
	x_max = 0x8000;
	y_min = 32767;
	y_max = 0x8000;
	
	//Read raw readings for calibration
	rawData(true);	
	calibrated = false;
	
	//Set to active mode, highest DROS for continous readings
	setDR_OS(MAG3110_DR_OS_80_16);
	if(!activeMode) {
		start();
  }
}

void MAG3110::calibrate()
{
	int x, y, z;
	readMag(&x, &y, &z);
	
	bool changed = false; //Keep track of if a min/max is updated
	if (x < x_min) {
    x_min = x;
    changed = true;
  }
  if (x > x_max) {
    x_max = x;
    changed = true;
  }
  if (y < y_min) {
    y_min = y;
    changed = true;
  }
  if (y > y_max) {
    y_max = y;
    changed = true;
  }
	if (changed) {
    timeLastChange = millis();
  }
  if (millis() > 5000 && millis() - timeLastChange > CALIBRATION_TIMEOUT) {
	  exitCalMode();
  }
}

void MAG3110::exitCalMode()
{
	x_offset = (x_min + x_max)/2;
	y_offset = (y_min + y_max)/2;
	x_scale = 1.0/(x_max - x_min);
	y_scale = 1.0/(y_max - y_min);
	setOffset(MAG3110_X_AXIS, x_offset);
	setOffset(MAG3110_Y_AXIS, y_offset);
	rawData(false);
	calibrationMode = false;
	calibrated = true;
	//enterStandby();
}

void MAG3110::reset()
{
	enterStandby();
	writeRegister(MAG3110_CTRL_REG1, 0x00); //Set everything to 0
	writeRegister(MAG3110_CTRL_REG2, 0x80); //Enable Auto Mag Reset, non-raw mode	
	calibrationMode = false;
	activeMode = false;
	rawMode = false;
	calibrated = false;
	setOffset(MAG3110_X_AXIS, 0);
	setOffset(MAG3110_Y_AXIS, 0);
	setOffset(MAG3110_Z_AXIS, 0);
}

int MAG3110::readAxis(uint8_t axis){
	uint8_t lsbAddress, msbAddress;
	uint8_t lsb, msb;
	msbAddress = axis;
	lsbAddress = axis+1;
	msb = readRegister(msbAddress);
	delayMicroseconds(2);
	lsb = readRegister(lsbAddress);
	int16_t out = (lsb | (msb << 8));
	return (int)out;
}
