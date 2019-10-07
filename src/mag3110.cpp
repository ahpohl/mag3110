#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstring>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "mag3110.hpp"

using namespace std;

MAG3110::MAG3110(void)
{
  m_debug = false;
	m_xoffset = 0;
	m_yoffset = 0;
	x_scale = 0.0f;
	y_scale = 0.0f;
}

MAG3110::~MAG3110(void)
{
  if (m_fd) {
    close(m_fd);
  }
}

void MAG3110::setDebug(void)
{
  m_debug = true;
}

void MAG3110::initialize(const char* t_bus)
{
  int res = 0, rsp = 0;
  if ((m_fd = open(t_bus, O_RDWR)) < 0) {
    throw runtime_error(string("Failed to open I2C bus ") + t_bus + ": "
      + strerror(errno) + " (" + to_string(errno) + ")");
  }
  if ((res = ioctl(m_fd, I2C_SLAVE, MAG3110_I2C_ADDRESS)) < 0) {
    throw runtime_error("Failed to acquire bus access and/or talk to slave");
  }
	if ((rsp = readRegister(MAG3110_WHO_AM_I)) != MAG3110_WHO_AM_I_RSP) {
		throw runtime_error("Failed to find MAG3110 connected");
	}
  reset();
  if (m_debug) {
    cout << "Initialization successful" << endl;
  }
}

uint8_t MAG3110::readRegister(uint8_t const& t_addr) const
{
  uint8_t res;
  const int LEN = 1;
  if (write(m_fd, &t_addr, LEN) != LEN) {
    throw runtime_error("Failed to write to the i2c bus");
  }
  if (read(m_fd, &res, LEN) != LEN) {
    throw runtime_error("Failed to read from the i2c bus");
  }
  return res;
}

void MAG3110::writeRegister(uint8_t const& t_addr, uint8_t const& t_val) const
{
  const int LEN = 2;
  uint8_t data[LEN] = {0};
  data[0] = t_addr;
  data[1] = t_val;
  if (write(m_fd, data, LEN) != LEN) {
    throw runtime_error("Failed to write to the i2c bus");
  }
}

void MAG3110::enterStandby(void)
{
  m_activeMode = false;
  uint8_t reg = readRegister(MAG3110_CTRL_REG1);
  writeRegister(MAG3110_CTRL_REG1, (reg & ~(0x03)));
}

void MAG3110::exitStandby(void)
{
  m_activeMode = true;
  uint8_t reg = readRegister(MAG3110_CTRL_REG1);
  writeRegister(MAG3110_CTRL_REG1, (reg | MAG3110_ACTIVE_MODE));
}

void MAG3110::start(void)
{
  exitStandby();
}

int MAG3110::readAxis(uint8_t const& t_axis) const
{
  uint8_t msbAddr = t_axis + 0x08;
  uint8_t lsbAddr = msbAddr + 0x01;
  uint8_t msb = readRegister(msbAddr);
  uint8_t lsb = readRegister(lsbAddr);
  int res = static_cast<int16_t>(lsb | (msb << 8));

  return res;
}

void MAG3110::setOffset(uint8_t const& t_axis, int const& t_offset) const
{
  // msb bits [14:7], lsb bits [6:0]
  uint8_t msbAddr = t_axis + 0x08;
  uint8_t lsbAddr = msbAddr + 0x01;
  writeRegister(msbAddr, ((t_offset >> 7) & 0xFF));
  writeRegister(lsbAddr, ((t_offset << 1) & 0xFF));
}

int MAG3110::readOffset(uint8_t const& t_axis) const
{
  return (readAxis(t_axis + 0x08) >> 1);
}

void MAG3110::reset(void)
{
  enterStandby();
  writeRegister(MAG3110_CTRL_REG1, 0x00);
  writeRegister(MAG3110_CTRL_REG2, 0x80);
  m_calibrationMode = false;
  m_activeMode = false;
  m_rawMode = false;
  m_calibrated = false;
  setOffset(MAG3110_X_AXIS, 0);
  setOffset(MAG3110_Y_AXIS, 0);
  setOffset(MAG3110_Z_AXIS, 0);
}

void MAG3110::readMag(int* t_x, int* t_y, int* t_z) const
{
  const int LEN = 1;
  if (write(m_fd, &MAG3110_OUT_X_MSB, LEN) != LEN) {
    throw runtime_error("Failed to write to the i2c bus");
  }
  const int BYTES = 6;
  uint16_t val[BYTES] = {0};
	for (uint8_t i = 0; i < BYTES; ++i)
	{
    if (read(m_fd, &val[i], LEN) != LEN) {
      throw runtime_error("Failed to read from the i2c bus");
    }
  }
	*t_x = static_cast<int16_t>(((val[0] & 0xFF) << 8) | (val[1] & 0xFF));
	*t_y = static_cast<int16_t>(((val[2] & 0xFF) << 8) | (val[3] & 0xFF));
	*t_z = static_cast<int16_t>(((val[4] & 0xFF) << 8) | (val[5] & 0xFF));
}

void MAG3110::readMicroTesla(double* t_x, double* t_y, double* t_z) const
{
	int x, y, z;
	readMag(&x, &y, &z);
	*t_x = x * 0.1f;
	*t_y = y * 0.1f;
	*t_z = z * 0.1f;
}

double MAG3110::getMagnitude(double const& t_x, double const& t_y, 
    double const& t_z) const
{
  return sqrt(pow(t_x, 2.0) + pow(t_y, 2.0) + pow(t_z, 2.0));
}

bool MAG3110::dataReady(void) const
{
  return ((readRegister(MAG3110_DR_STATUS) & 0x08) >> 3);
}

double MAG3110::readHeading(void)
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
	return m_calibrated;
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
