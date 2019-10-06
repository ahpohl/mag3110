#include <iostream>
#include <cmath>
#include <cstdint>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include "mag3110.hpp"

using namespace std;

MAG3110::MAG3110(void)
{
	m_xoffset = 0;
	m_yoffset = 0;
	x_scale = 0.0f;
	y_scale = 0.0f;
}

bool MAG3110::initialize(void)
{
  m_i2cbus = "/dev/i2c-1";
  if ((m_fd = open(m_i2cbus, O_RDWR)) < 0) {
    throw runtime_error("Failed to open the bus.");
  }
  if ((ioctl(m_fd, I2C_SLAVE, MAG3110_I2C_ADDRESS)) < 0) {
    throw runtime_error("Failed to access the bus.");
  }
	if(readRegister(MAG3110_WHO_AM_I) != MAG3110_WHO_AM_I_RSP) {
		cout << "Could not find MAG3110 connected!" << endl;
		return false;
	} else {
		reset();
		return true;
	}
}

uint8_t MAG3110::readRegister(uint8_t t_addr)
{
  uint8_t res;
  write(m_fd, &t_addr, 1);
  read(m_fd, &res, 1);

  return res;
}

void MAG3110::writeRegister(uint8_t addr, uint8_t val)
{
  /*
  Wire.beginTransmission(MAG3110_I2C_ADDRESS);
  Wire.write(address);
  Wire.write(value);
  Wire.endTransmission();
  */
}

bool MAG3110::dataReady(void)
{
	return ((readRegister(MAG3110_DR_STATUS) & 0x8) >> 3);
}

void MAG3110::readMag(int* t_x, int* t_y, int* t_z)
{
  /*
	Wire.beginTransmission(MAG3110_I2C_ADDRESS);
	Wire.write(MAG3110_OUT_X_MSB);
	Wire.endTransmission();
	delayMicroseconds(2);
	Wire.requestFrom(MAG3110_I2C_ADDRESS, 6);
	
  uint16_t values[3];
	for(uint8_t idx = 0; idx <= 2; idx++)
	{
		values[idx]  = Wire.read() << 8;	// MSB
		values[idx] |= Wire.read();       // LSB
	}
	*x = (int) values[0];
	*y = (int) values[1];
	*z = (int) values[2];
  */
}

void MAG3110::readMicroTeslas(float* t_x, float* t_y, float* t_z)
{
  /*
	int x_int, y_int, z_int;
	readMag(&x_int, &y_int, &z_int);
	*x = (float) x_int * 0.1f;
	*y = (float) y_int * 0.1f;
	*z = (float) z_int * 0.1f;
  */
}

float MAG3110::readHeading(void)
{
  /*
	int x, y, z;
	readMag(&x, &y, &z);
	float xf = (float) x * 1.0f;
	float yf = (float) y * 1.0f;
	return (atan2(-y*y_scale, x*x_scale) * DEG_PER_RAD);
  */
  return 0;
}

void MAG3110::setDR_OS(uint8_t t_DROS)
{
  /*
	bool wasActive = activeMode;	
	if(activeMode) {
		enterStandby();
  }	
	delay(100);
	uint8_t current = readRegister(MAG3110_CTRL_REG1) & 0x07;
	writeRegister(MAG3110_CTRL_REG1, (current | DROS));
	delay(100);
	if(wasActive) {
		exitStandby();
  }
  */
}

void MAG3110::triggerMeasurement(void)
{	
  /*
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (current |  0x02));
  */
}

void MAG3110::rawData(bool t_raw)
{
  /*
	if (raw) {
		rawMode = true;
		writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN | (0x01 << 5) );
	} else {
		rawMode = false;
		writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN & ~(0x01 << 5));
	}
  */
}

void MAG3110::setOffset(uint8_t t_axis, int t_offset)
{
  /*
	offset = offset << 1;	
	uint8_t msbAddress = axis + 8;
	uint8_t lsbAddress = msbAddress + 1;
	writeRegister(msbAddress, (uint8_t)((offset >> 8) & 0xFF));
	delay(15);
	writeRegister(lsbAddress, (uint8_t) offset & 0xFF);
  */
}

int MAG3110::readOffset(uint8_t t_axis)
{
  /*
	return (readAxis(axis+8)) >> 1;
  */
  return 0;
}

void MAG3110::start(void)
{
  /*
	exitStandby();
  */
}

void MAG3110::enterStandby(void)
{
  /*
	activeMode = false;
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (current & ~(0x3)));
  */
}

void MAG3110::exitStandby(void)
{
  /*
	activeMode = true;
	uint8_t current = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (current | MAG3110_ACTIVE_MODE));
  */
}

bool MAG3110::isActive(void)
{
	return m_activeMode;
}

bool MAG3110::isRaw(void)
{
	return m_rawMode;
}

bool MAG3110::isCalibrated(void)
{
	return calibrated;
}

bool MAG3110::isCalibrating(void)
{
	return m_calibrationMode;
}

uint8_t MAG3110::getSysMode(void)
{
	return readRegister(MAG3110_SYSMOD);
}

void MAG3110::enterCalMode(void)
{
	m_calibrationMode = true;
	m_xmin = 32767;
	m_xmax = 0x8000;
	m_ymin = 32767;
	m_ymax = 0x8000;
	
  /*
	rawData(true);	
	calibrated = false;
	
	setDR_OS(MAG3110_DR_OS_80_16);
	if(!activeMode) {
		start();
  }
  */
}

void MAG3110::calibrate(void)
{
  /*
	int x, y, z;
	readMag(&x, &y, &z);
	
	bool changed = false;
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
  */
}

void MAG3110::exitCalMode(void)
{
  /*
	x_offset = (x_min + x_max)/2;
	y_offset = (y_min + y_max)/2;
	x_scale = 1.0/(x_max - x_min);
	y_scale = 1.0/(y_max - y_min);
	setOffset(MAG3110_X_AXIS, x_offset);
	setOffset(MAG3110_Y_AXIS, y_offset);
	rawData(false);
	calibrationMode = false;
	calibrated = true;
  */
	//enterStandby();
}

void MAG3110::reset(void)
{
  /*
	enterStandby();
	writeRegister(MAG3110_CTRL_REG1, 0x00);
	writeRegister(MAG3110_CTRL_REG2, 0x80);	
	calibrationMode = false;
	activeMode = false;
	rawMode = false;
	calibrated = false;
	setOffset(MAG3110_X_AXIS, 0);
	setOffset(MAG3110_Y_AXIS, 0);
	setOffset(MAG3110_Z_AXIS, 0);
  */
}

int MAG3110::readAxis(uint8_t t_axis)
{
  /*
	uint8_t lsbAddress, msbAddress;
	uint8_t lsb, msb;
	msbAddress = axis;
	lsbAddress = axis+1;
	msb = readRegister(msbAddress);
	delayMicroseconds(2);
	lsb = readRegister(lsbAddress);
	int16_t out = (lsb | (msb << 8));
	return (int)out;
  */
  return 0;
}
