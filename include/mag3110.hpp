#ifndef MAG3110_HPP
#define MAG3110_HPP
#include <cstdint>

/////////////////////////////////////////
// MAG3110 I2C Address    			       //
/////////////////////////////////////////
const int MAG3110_I2C_ADDRESS = 0x0E;

/////////////////////////////////////////
// MAG3110 Magnetometer Registers      //
/////////////////////////////////////////
const int MAG3110_DR_STATUS	=   0x00;
const int MAG3110_OUT_X_MSB =		0x01;
const int MAG3110_OUT_X_LSB	=		0x02;
const int MAG3110_OUT_Y_MSB	=		0x03;
const int MAG3110_OUT_Y_LSB	=		0x04;
const int MAG3110_OUT_Z_MSB	=		0x05;
const int MAG3110_OUT_Z_LSB	=		0x06;
const int MAG3110_WHO_AM_I =		0x07;
const int MAG3110_SYSMOD =			0x08;
const int MAG3110_OFF_X_MSB =		0x09;
const int MAG3110_OFF_X_LSB	=		0x0A;
const int MAG3110_OFF_Y_MSB	=		0x0B;
const int MAG3110_OFF_Y_LSB	=		0x0C;
const int MAG3110_OFF_Z_MSB	=		0x0D;
const int MAG3110_OFF_Z_LSB	=		0x0E;
const int MAG3110_DIE_TEMP =		0x0F;
const int MAG3110_CTRL_REG1	=		0x10;
const int MAG3110_CTRL_REG2	=		0x11;

////////////////////////////////
// MAG3110 WHO_AM_I Response  //
////////////////////////////////
const int MAG3110_WHO_AM_I_RSP = 0xC4;

/////////////////////////////////////////
// MAG3110 Commands and Settings       //
/////////////////////////////////////////

// CTRL_REG1 Settings
// Output Data Rate/Oversample Settings
// DR_OS_80_16 -> Output Data Rate = 80Hz, Oversampling Ratio = 16

const int MAG3110_DR_OS_80_16 =		 0x00;
const int MAG3110_DR_OS_40_32 =		 0x08;
const int MAG3110_DR_OS_20_64 =		 0x10;
const int MAG3110_DR_OS_10_128 =	 0x18;
const int MAG3110_DR_OS_40_16	=		 0x20;
const int MAG3110_DR_OS_20_32	=		 0x28;
const int MAG3110_DR_OS_10_64	=		 0x30;
const int MAG3110_DR_OS_5_128	=		 0x38;
const int MAG3110_DR_OS_20_16	=		 0x40;
const int MAG3110_DR_OS_10_32	=		 0x48;
const int MAG3110_DR_OS_5_64 =		 0x50;
const int MAG3110_DR_OS_2_5_128 =	 0x58;
const int MAG3110_DR_OS_10_16	=		 0x60;
const int MAG3110_DR_OS_5_32 =		 0x68;
const int MAG3110_DR_OS_2_5_64 =   0x70;
const int MAG3110_DR_OS_1_25_128 = 0x78;
const int MAG3110_DR_OS_5_16 =     0x80;
const int MAG3110_DR_OS_2_5_32 =	 0x88;
const int	MAG3110_DR_OS_1_25_64	=  0x90;
const int MAG3110_DR_OS_0_63_128 = 0x98;
const int MAG3110_DR_OS_2_5_16 =   0xA0;
const int MAG3110_DR_OS_1_25_32	=  0xA8;
const int MAG3110_DR_OS_0_63_64	=  0xB0;
const int MAG3110_DR_OS_0_31_128 = 0xB8;
const int MAG3110_DR_OS_1_25_16	=  0xC0;
const int MAG3110_DR_OS_0_63_32	=  0xC8;
const int MAG3110_DR_OS_0_31_64 =  0xD0;
const int MAG3110_DR_OS_0_16_128 = 0xD8;
const int MAG3110_DR_OS_0_63_16	=  0xE0;
const int MAG3110_DR_OS_0_31_32	=  0xE8;
const int MAG3110_DR_OS_0_16_64	=  0xF0;
const int MAG3110_DR_OS_0_08_128 = 0xF8;

// Other CTRL_REG1 Settings
const int MAG3110_FAST_READ = 			    0x04;
const int MAG3110_TRIGGER_MEASUREMENT	= 0x02;
const int MAG3110_ACTIVE_MODE =			    0x01;
const int MAG3110_STANDBY_MODE =		    0x00;

// CTRL_REG2 Settings
const int MAG3110_AUTO_MRST_EN = 0x80;
const int MAG3110_RAW_MODE = 	   0x20;
const int MAG3110_NORMAL_MODE	=	 0x00;
const int MAG3110_MAG_RST =		   0x10;

// SYSMOD Readings
const int MAG3110_SYSMOD_STANDBY =    0x00;
const int MAG3110_SYSMOD_ACTIVE_RAW =	0x01;
const int	MAG3110_SYSMOD_ACTIVE	=	    0x02;
const int MAG3110_X_AXIS =            0x01;
const int MAG3110_Y_AXIS =            0x03;
const int MAG3110_Z_AXIS =            0x05;

const int CALIBRATION_TIMEOUT = 5000; // ms
const double DEG_PER_RAD = (180.0 / 3.14159265358979);

class MAG3110
{
public:
  MAG3110(void);
  ~MAG3110(void);
  void setDebug(void);
  void initialize(const char* t_bus);
  uint8_t readRegister(uint8_t const& t_addr) const;
  void writeRegister(uint8_t const& t_addr, uint8_t const& t_val) const;
  void enterStandby(void);
  void exitStandby(void);
  void setOffset(uint8_t const& t_axis, int const& t_offset) const;
  int readOffset(uint8_t const& t_axis) const; 
  void reset(void);
  void readMag(int* t_x, int* t_y, int* t_z) const; 
  void readMicroTesla(double* t_x, double* t_y, double* t_z) const;
  double getMagnitude(double const& t_x, double const& t_y, 
    double const& t_z) const;

  bool dataReady(void) const;
  double readHeading(void);
  void setDR_OS(uint8_t t_DROS);
  void triggerMeasurement(void);
  void rawData(bool t_raw);
  void start(void);
  bool isActive(void);
  bool isRaw(void);
  bool isCalibrated(void);
  bool isCalibrating(void);
  uint8_t getSysMode(void);
  void enterCalMode(void);
  void calibrate(void);
  void exitCalMode(void);
  bool error;
  float x_scale;
  float y_scale;

protected:
  int readAxis(uint8_t const& t_axis) const;

private:
  bool m_debug;
  int m_fd;
  int m_xoffset;
  int m_yoffset;
  int m_xmin;
  int m_xmax;
  int m_ymin;
  int m_ymax;
  int m_timeLastChange;
  bool m_calibrationMode;
  bool m_activeMode;
  bool m_rawMode;
  bool m_calibrated;
};

#endif // MAG3110_HPP
