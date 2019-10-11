#ifndef MAG3110_HPP
#define MAG3110_HPP
#include <cstdint>


class MAG3110
{
public:
  static uint8_t const MAG3110_I2C_ADDRESS = 0x0E;
  static uint8_t const MAG3110_WHO_AM_I_RSP = 0xC4;
  static int const CALIBRATION_TIMEOUT = 10000; // ms
  static double const DEG_PER_RAD = (180.0/3.14159265358979);
  
  // register addresses
  static uint8_t const MAG3110_DR_STATUS = 0x00;
  static uint8_t const MAG3110_OUT_X_MSB = 0x01;
  static uint8_t const MAG3110_OUT_X_LSB = 0x02;
  static uint8_t const MAG3110_OUT_Y_MSB = 0x03;
  static uint8_t const MAG3110_OUT_Y_LSB = 0x04;
  static uint8_t const MAG3110_OUT_Z_MSB = 0x05;
  static uint8_t const MAG3110_OUT_Z_LSB = 0x06;
  static uint8_t const MAG3110_WHO_AM_I =	 0x07;
  static uint8_t const MAG3110_SYSMOD =		 0x08;
  static uint8_t const MAG3110_OFF_X_MSB = 0x09;
  static uint8_t const MAG3110_OFF_X_LSB = 0x0A;
  static uint8_t const MAG3110_OFF_Y_MSB = 0x0B;
  static uint8_t const MAG3110_OFF_Y_LSB = 0x0C;
  static uint8_t const MAG3110_OFF_Z_MSB = 0x0D;
  static uint8_t const MAG3110_OFF_Z_LSB = 0x0E;
  static uint8_t const MAG3110_DIE_TEMP =  0x0F;
  static uint8_t const MAG3110_CTRL_REG1 = 0x10;
  static uint8_t const MAG3110_CTRL_REG2 = 0x11;
  
  // CTRL_REG1 Settings
  // Output Data Rate/Oversample Settings
  // DR_OS_80_16 -> Output Data Rate = 80Hz, 
  // Oversampling Ratio = 16
  static uint8_t const MAG3110_DR_OS_80_16 =    0x00;
  static uint8_t const MAG3110_DR_OS_40_32 =		0x08;
  static uint8_t const MAG3110_DR_OS_20_64 =		0x10;
  static uint8_t const MAG3110_DR_OS_10_128 =	  0x18;
  static uint8_t const MAG3110_DR_OS_40_16 =		0x20;
  static uint8_t const MAG3110_DR_OS_20_32 =		0x28;
  static uint8_t const MAG3110_DR_OS_10_64 =		0x30;
  static uint8_t const MAG3110_DR_OS_5_128 =		0x38;
  static uint8_t const MAG3110_DR_OS_20_16 =		0x40;
  static uint8_t const MAG3110_DR_OS_10_32 =		0x48;
  static uint8_t const MAG3110_DR_OS_5_64 =		  0x50;
  static uint8_t const MAG3110_DR_OS_2_5_128 =	0x58;
  static uint8_t const MAG3110_DR_OS_10_16 =		0x60;
  static uint8_t const MAG3110_DR_OS_5_32 =		  0x68;
  static uint8_t const MAG3110_DR_OS_2_5_64 =   0x70;
  static uint8_t const MAG3110_DR_OS_1_25_128 = 0x78;
  static uint8_t const MAG3110_DR_OS_5_16 =     0x80;
  static uint8_t const MAG3110_DR_OS_2_5_32 =	  0x88;
  static uint8_t const MAG3110_DR_OS_1_25_64	= 0x90;
  static uint8_t const MAG3110_DR_OS_0_63_128 = 0x98;
  static uint8_t const MAG3110_DR_OS_2_5_16 =   0xA0;
  static uint8_t const MAG3110_DR_OS_1_25_32 =  0xA8;
  static uint8_t const MAG3110_DR_OS_0_63_64 =  0xB0;
  static uint8_t const MAG3110_DR_OS_0_31_128 = 0xB8;
  static uint8_t const MAG3110_DR_OS_1_25_16 =  0xC0;
  static uint8_t const MAG3110_DR_OS_0_63_32 =  0xC8;
  static uint8_t const MAG3110_DR_OS_0_31_64 =  0xD0;
  static uint8_t const MAG3110_DR_OS_0_16_128 = 0xD8;
  static uint8_t const MAG3110_DR_OS_0_63_16 =  0xE0;
  static uint8_t const MAG3110_DR_OS_0_31_32 =  0xE8;
  static uint8_t const MAG3110_DR_OS_0_16_64 =  0xF0;
  static uint8_t const MAG3110_DR_OS_0_08_128 = 0xF8;

  // Other CTRL_REG1 Settings
  static uint8_t const MAG3110_FAST_READ = 			     0x04;
  static uint8_t const MAG3110_TRIGGER_MEASUREMENT = 0x02;
  static uint8_t const MAG3110_ACTIVE_MODE =			   0x01;
  static uint8_t const MAG3110_STANDBY_MODE =		     0x00;

  // CTRL_REG2 Settings
  static uint8_t const MAG3110_AUTO_MRST_EN = 0x80;
  static uint8_t const MAG3110_RAW_MODE = 	  0x20;
  static uint8_t const MAG3110_NORMAL_MODE =	0x00;
  static uint8_t const MAG3110_MAG_RST =		  0x10;

  // SYSMOD Readings
  static uint8_t const MAG3110_SYSMOD_STANDBY =    0x00;
  static uint8_t const MAG3110_SYSMOD_ACTIVE_RAW = 0x01;
  static uint8_t const	MAG3110_SYSMOD_ACTIVE	=	   0x02;
  static uint8_t const MAG3110_X_AXIS =            0x01;
  static uint8_t const MAG3110_Y_AXIS =            0x03;
  static uint8_t const MAG3110_Z_AXIS =            0x05;

  // methods
  MAG3110(void);
  ~MAG3110(void);
  void setDebug(void);
  void initialize(const char* t_bus);
  void start(void);
  void reset(void);
  void enterStandby(void);
  void exitStandby(void);
  void setRawMode(bool const t_raw);
  void triggerMeasurement(void);
  void setDR_OS(uint8_t const t_DROS);
  void enterCalMode(void);
  void calibrate(void);
  void exitCalMode(void);
  void writeRegister(uint8_t const& t_addr, uint8_t const& t_val) const;
  void setOffset(int const& t_xoff, int const& t_yoff, 
    int const& t_zoff) const;
  void writeOffset(uint8_t const& t_axis, int const& t_offset) const;
  void getOffset(int* t_xoff, int* t_yoff, int* t_zoff) const; 
  void readMag(int* t_x, int* t_y, int* t_z) const; 
  void readMicroTesla(double* t_x, double* t_y, double* t_z) const;
  bool isActive(void);
  bool isRaw(void);
  bool isCalibrated(void);
  bool dataReady(void) const;  
  uint8_t getSysMode(void);
  uint8_t readRegister(uint8_t const& t_addr) const;
  int readAxis(uint8_t const& t_axis) const;
  int readOffset(uint8_t const& t_axis) const;
  double getMagnitude(double const& t_x, double const& t_y, 
    double const& t_z) const;
  double readHeading(void);

private:
  bool m_debug;
  bool m_activeMode;
  bool m_rawMode;
  bool m_calibrated;
  bool m_error;
  int m_fd;
  int m_xmin;
  int m_xmax;
  int m_ymin;
  int m_ymax;
  int m_timeLastChange;
  double m_xscale;
  double m_yscale;
};

#endif // MAG3110_HPP
