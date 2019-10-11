#include <iostream>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <chrono>

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "mag3110.hpp"

using namespace std;

uint8_t const MAG3110::MAG3110_I2C_ADDRESS = 0x0E;
uint8_t const MAG3110::MAG3110_WHO_AM_I_RSP = 0xC4;
int const MAG3110::CALIBRATION_TIMEOUT = 100; // ms
double const MAG3110::DEG_PER_RAD = (180.0 / M_PI);
  
// register addresses
uint8_t const MAG3110::MAG3110_DR_STATUS = 0x00;
uint8_t const MAG3110::MAG3110_OUT_X_MSB = 0x01;
uint8_t const MAG3110::MAG3110_OUT_X_LSB = 0x02;
uint8_t const MAG3110::MAG3110_OUT_Y_MSB = 0x03;
uint8_t const MAG3110::MAG3110_OUT_Y_LSB = 0x04;
uint8_t const MAG3110::MAG3110_OUT_Z_MSB = 0x05;
uint8_t const MAG3110::MAG3110_OUT_Z_LSB = 0x06;
uint8_t const MAG3110::MAG3110_WHO_AM_I =	 0x07;
uint8_t const MAG3110::MAG3110_SYSMOD =		 0x08;
uint8_t const MAG3110::MAG3110_OFF_X_MSB = 0x09;
uint8_t const MAG3110::MAG3110_OFF_X_LSB = 0x0A;
uint8_t const MAG3110::MAG3110_OFF_Y_MSB = 0x0B;
uint8_t const MAG3110::MAG3110_OFF_Y_LSB = 0x0C;
uint8_t const MAG3110::MAG3110_OFF_Z_MSB = 0x0D;
uint8_t const MAG3110::MAG3110_OFF_Z_LSB = 0x0E;
uint8_t const MAG3110::MAG3110_DIE_TEMP =  0x0F;
uint8_t const MAG3110::MAG3110_CTRL_REG1 = 0x10;
uint8_t const MAG3110::MAG3110_CTRL_REG2 = 0x11;
  
// CTRL_REG1 Settings
// Output Data Rate/Oversample Settings
// DR_OS_80_16 -> Output Data Rate = 80Hz, 
// Oversampling Ratio = 16
uint8_t const MAG3110::MAG3110_DR_OS_80_16 =    0x00;
uint8_t const MAG3110::MAG3110_DR_OS_40_32 =		0x08;
uint8_t const MAG3110::MAG3110_DR_OS_20_64 =		0x10;
uint8_t const MAG3110::MAG3110_DR_OS_10_128 =	  0x18;
uint8_t const MAG3110::MAG3110_DR_OS_40_16 =		0x20;
uint8_t const MAG3110::MAG3110_DR_OS_20_32 =		0x28;
uint8_t const MAG3110::MAG3110_DR_OS_10_64 =		0x30;
uint8_t const MAG3110::MAG3110_DR_OS_5_128 =		0x38;
uint8_t const MAG3110::MAG3110_DR_OS_20_16 =		0x40;
uint8_t const MAG3110::MAG3110_DR_OS_10_32 =		0x48;
uint8_t const MAG3110::MAG3110_DR_OS_5_64 =		  0x50;
uint8_t const MAG3110::MAG3110_DR_OS_2_5_128 =	0x58;
uint8_t const MAG3110::MAG3110_DR_OS_10_16 =		0x60;
uint8_t const MAG3110::MAG3110_DR_OS_5_32 =		  0x68;
uint8_t const MAG3110::MAG3110_DR_OS_2_5_64 =   0x70;
uint8_t const MAG3110::MAG3110_DR_OS_1_25_128 = 0x78;
uint8_t const MAG3110::MAG3110_DR_OS_5_16 =     0x80;
uint8_t const MAG3110::MAG3110_DR_OS_2_5_32 =	  0x88;
uint8_t const MAG3110::MAG3110_DR_OS_1_25_64	= 0x90;
uint8_t const MAG3110::MAG3110_DR_OS_0_63_128 = 0x98;
uint8_t const MAG3110::MAG3110_DR_OS_2_5_16 =   0xA0;
uint8_t const MAG3110::MAG3110_DR_OS_1_25_32 =  0xA8;
uint8_t const MAG3110::MAG3110_DR_OS_0_63_64 =  0xB0;
uint8_t const MAG3110::MAG3110_DR_OS_0_31_128 = 0xB8;
uint8_t const MAG3110::MAG3110_DR_OS_1_25_16 =  0xC0;
uint8_t const MAG3110::MAG3110_DR_OS_0_63_32 =  0xC8;
uint8_t const MAG3110::MAG3110_DR_OS_0_31_64 =  0xD0;
uint8_t const MAG3110::MAG3110_DR_OS_0_16_128 = 0xD8;
uint8_t const MAG3110::MAG3110_DR_OS_0_63_16 =  0xE0;
uint8_t const MAG3110::MAG3110_DR_OS_0_31_32 =  0xE8;
uint8_t const MAG3110::MAG3110_DR_OS_0_16_64 =  0xF0;
uint8_t const MAG3110::MAG3110_DR_OS_0_08_128 = 0xF8;

// Other CTRL_REG1 Settings
uint8_t const MAG3110::MAG3110_FAST_READ = 			     0x04;
uint8_t const MAG3110::MAG3110_TRIGGER_MEASUREMENT = 0x02;
uint8_t const MAG3110::MAG3110_ACTIVE_MODE =			   0x01;
uint8_t const MAG3110::MAG3110_STANDBY_MODE =		     0x00;

// CTRL_REG2 Settings
uint8_t const MAG3110::MAG3110_AUTO_MRST_EN = 0x80;
uint8_t const MAG3110::MAG3110_RAW_MODE = 	  0x20;
uint8_t const MAG3110::MAG3110_NORMAL_MODE =	0x00;
uint8_t const MAG3110::MAG3110_MAG_RST =		  0x10;

// SYSMOD Readings
uint8_t const MAG3110::MAG3110_SYSMOD_STANDBY =    0x00;
uint8_t const MAG3110::MAG3110_SYSMOD_ACTIVE_RAW = 0x01;
uint8_t const MAG3110::MAG3110_SYSMOD_ACTIVE	=	   0x02;
uint8_t const MAG3110::MAG3110_X_AXIS =            0x01;
uint8_t const MAG3110::MAG3110_Y_AXIS =            0x03;
uint8_t const MAG3110::MAG3110_Z_AXIS =            0x05;

MAG3110::MAG3110(void)
{
  m_debug = false;
	m_xscale = 0.0f;
	m_yscale = 0.0f;
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

void MAG3110::standby(void)
{
  m_activeMode = false;
  uint8_t reg = readRegister(MAG3110_CTRL_REG1);
  writeRegister(MAG3110_CTRL_REG1, (reg & ~(0x03)));
}

void MAG3110::start(void)
{
  m_activeMode = true;
  uint8_t reg = readRegister(MAG3110_CTRL_REG1);
  writeRegister(MAG3110_CTRL_REG1, (reg | MAG3110_ACTIVE_MODE));
}

int MAG3110::readAxis(uint8_t const& t_axis) const
{
  uint8_t msbAddr = t_axis;
  uint8_t lsbAddr = t_axis + 0x01;
  uint8_t msb = readRegister(msbAddr);
  uint8_t lsb = readRegister(lsbAddr);
  return static_cast<int16_t>((lsb & 0xFF) | ((msb & 0xFF) << 8));
}

void MAG3110::writeOffset(uint8_t const& t_axis, int const& t_offset) const
{
  // msb bits [14:7], lsb bits [6:0]
  uint8_t msbAddr = t_axis + 0x08;
  uint8_t lsbAddr = msbAddr + 0x01;
  writeRegister(msbAddr, static_cast<uint8_t>((t_offset >> 7) & 0xFF));
  writeRegister(lsbAddr, static_cast<uint8_t>((t_offset << 1) & 0xFF));
}

int MAG3110::readOffset(uint8_t const& t_axis) const
{
  return (readAxis(t_axis + 0x08) >> 1);
}

void MAG3110::setOffset(int const& t_xoff, int const&  t_yoff, 
  int const& t_zoff) const
{
  writeOffset(MAG3110_X_AXIS, t_xoff);
  writeOffset(MAG3110_Y_AXIS, t_yoff);
  writeOffset(MAG3110_Z_AXIS, t_zoff);
}

void MAG3110::getOffset(int* t_xoff, int* t_yoff, int* t_zoff) const
{
  *t_xoff = readOffset(MAG3110_X_AXIS);
  *t_yoff = readOffset(MAG3110_Y_AXIS);
  *t_zoff = readOffset(MAG3110_Z_AXIS);
}

void MAG3110::reset(void)
{
  standby();
  writeRegister(MAG3110_CTRL_REG1, 0x00);
  writeRegister(MAG3110_CTRL_REG2, 0x80);
  writeOffset(MAG3110_X_AXIS, 0);
  writeOffset(MAG3110_Y_AXIS, 0);
  writeOffset(MAG3110_Z_AXIS, 0);
  m_activeMode = false;
  m_rawMode = false;
  m_calibrated = false;
}

void MAG3110::readMag(int* t_x, int* t_y, int* t_z) const
{
  *t_x = readAxis(MAG3110_X_AXIS);
  *t_y = readAxis(MAG3110_Y_AXIS);
  *t_z = readAxis(MAG3110_Z_AXIS);
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

void MAG3110::setDR_OS(uint8_t const t_DROS)
{
  bool wasActive = m_activeMode;
  if (m_activeMode) {
    standby();
  }
  uint8_t reg = readRegister(MAG3110_CTRL_REG1) & 0x07;
  writeRegister(MAG3110_CTRL_REG1, (reg | t_DROS));
  if (wasActive) {
    start();
  }
}

void MAG3110::setRawMode(bool const t_raw)
{
  if (t_raw) {
    m_rawMode = true;
    writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN | (0x01 << 5));
  } else {
    m_rawMode = false;
    writeRegister(MAG3110_CTRL_REG2, MAG3110_AUTO_MRST_EN & ~(0x01 << 5));
  }
}

void MAG3110::calibrate(void)
{
  int xmin = 0x7FFF, xmax = -0x8000;
  int ymin = 0x7FFF, ymax = -0x8000;
  int zmin = 0x7FFF, zmax = -0x8000;
  setRawMode(true);  
  setDR_OS(MAG3110_DR_OS_80_16);
  if (!m_activeMode) { start(); }
	int x, y, z;
  auto start = chrono::system_clock::now();
  chrono::high_resolution_clock::time_point end;
  do {
    readMag(&x, &y, &z);
	  if (x < xmin) { xmin = x; }
    if (x > xmax) { xmax = x; }
    if (y < ymin) { ymin = y; }
    if (y > ymax) { ymax = y; }
    if (z < zmin) { zmin = z; }
    if (z > zmax) { zmax = z; }
    if (m_debug) {
      cout << "x: " << xmin << " < " << x << " < " << xmax 
        << ", y: " << ymin << " < " << y << " < " << ymax
        << ", z: " << zmin << " < " << z << " < " << zmax << endl;
    }
    end = chrono::system_clock::now();
  } while ((chrono::duration_cast<chrono::milliseconds>
    (end - start).count() < CALIBRATION_TIMEOUT));

  writeOffset(MAG3110_X_AXIS, (xmin + xmax) / 2);
	writeOffset(MAG3110_Y_AXIS, (ymin + ymax) / 2);
  writeOffset(MAG3110_Z_AXIS, (zmin + zmax) / 2);
	m_xscale = 1.0 / (xmax - xmin);
	m_yscale = 1.0 / (ymax - ymin);
	setRawMode(false);
  m_calibrated = true;
}

double MAG3110::getHeading(void)
{
	int x, y, z;
	readMag(&x, &y, &z);
	return (atan2(y*m_yscale, x*m_xscale) * DEG_PER_RAD);
}

void MAG3110::triggerMeasurement(void)
{	
	uint8_t reg = readRegister(MAG3110_CTRL_REG1);
	writeRegister(MAG3110_CTRL_REG1, (reg |  0x02));
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

uint8_t MAG3110::getSysMode(void)
{
	return readRegister(MAG3110_SYSMOD);
}

