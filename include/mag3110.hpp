#ifndef MAG3110_HPP
#define MAG3110_HPP
#include <cstdint>

/** @brief A class to drive the mag3110 3-axis magnetometer

    This class is derived from the Sparkfun Arduino library and
    has been ported to plain C++.
 
    @author Alexander Pohl <webmaster@ahpohl.com>
    @date October 2019
    */

class MAG3110
{
public:
  /// I2C address of the chip
  static uint8_t const MAG3110_I2C_ADDRESS;
  /// Device identifier
  static uint8_t const MAG3110_WHO_AM_I_RSP;
  /// Calibration timeout constant [ms]
  static int const CALIBRATION_TIMEOUT;
  /// Temperature offset
  static int const MAG3110_DIE_TEMP_OFFSET;
 
  /** @defgroup REGISTERS 
      @name Register addresses
      
      These attributes describe the register addresses
      */
  ///@{

  /// Data ready status per axis
  static uint8_t const MAG3110_DR_STATUS;
  /// Bits [15:8] of X measurement
  static uint8_t const MAG3110_OUT_X_MSB;
  /// Bits [7:0] of X measurement
  static uint8_t const MAG3110_OUT_X_LSB;
  /// Bits [15:8] of Y measurement
  static uint8_t const MAG3110_OUT_Y_MSB;
  /// Bits [7:0] of Y measurement
  static uint8_t const MAG3110_OUT_Y_LSB;
  /// Bits [15:8] of Z measurement
  static uint8_t const MAG3110_OUT_Z_MSB;
  /// Bits [7:0] of Z measurement
  static uint8_t const MAG3110_OUT_Z_LSB;
  /// Device identification
  static uint8_t const MAG3110_WHO_AM_I;
  /// Current System Mode
  static uint8_t const MAG3110_SYSMOD;
  /// Bits [14:7] of user X offset
  static uint8_t const MAG3110_OFF_X_MSB;
  /// Bits [6:0] of user X offset
  static uint8_t const MAG3110_OFF_X_LSB;
  /// Bits [14:7] of user Y offset
  static uint8_t const MAG3110_OFF_Y_MSB;
  /// Bits [6:0] of user Y offset
  static uint8_t const MAG3110_OFF_Y_LSB;
  /// Bits [14:7] of user Z offset 
  static uint8_t const MAG3110_OFF_Z_MSB;
  /// Bits [6:0] of user Z offset
  static uint8_t const MAG3110_OFF_Z_LSB;
  /// Temperature, signed 8 bits in °C
  static uint8_t const MAG3110_DIE_TEMP;
  /// Operation modes
  static uint8_t const MAG3110_CTRL_REG1;
  /// Operation modes
  static uint8_t const MAG3110_CTRL_REG2;
  ///@}
  
  /** @defgroup CTRL_REG1_DROS
      @name Control register 1: data rate and oversampling settings
            
      These attributes select the data rate and oversampling ratio.
      For example: DR_OS_80_16 -> Output Data Rate = 80 Hz, 
      oversampling ratio = 16.
      */
  ///@{
  static uint8_t const MAG3110_DR_OS_80_16;
  static uint8_t const MAG3110_DR_OS_40_32;
  static uint8_t const MAG3110_DR_OS_20_64;
  static uint8_t const MAG3110_DR_OS_10_128;
  static uint8_t const MAG3110_DR_OS_40_16;
  static uint8_t const MAG3110_DR_OS_20_32;
  static uint8_t const MAG3110_DR_OS_10_64;
  static uint8_t const MAG3110_DR_OS_5_128;
  static uint8_t const MAG3110_DR_OS_20_16;
  static uint8_t const MAG3110_DR_OS_10_32;
  static uint8_t const MAG3110_DR_OS_5_64;
  static uint8_t const MAG3110_DR_OS_2_5_128;
  static uint8_t const MAG3110_DR_OS_10_16;
  static uint8_t const MAG3110_DR_OS_5_32;
  static uint8_t const MAG3110_DR_OS_2_5_64;
  static uint8_t const MAG3110_DR_OS_1_25_128;
  static uint8_t const MAG3110_DR_OS_5_16;
  static uint8_t const MAG3110_DR_OS_2_5_32;
  static uint8_t const MAG3110_DR_OS_1_25_64;
  static uint8_t const MAG3110_DR_OS_0_63_128;
  static uint8_t const MAG3110_DR_OS_2_5_16;
  static uint8_t const MAG3110_DR_OS_1_25_32;
  static uint8_t const MAG3110_DR_OS_0_63_64;
  static uint8_t const MAG3110_DR_OS_0_31_128;
  static uint8_t const MAG3110_DR_OS_1_25_16;
  static uint8_t const MAG3110_DR_OS_0_63_32;
  static uint8_t const MAG3110_DR_OS_0_31_64;
  static uint8_t const MAG3110_DR_OS_0_16_128;
  static uint8_t const MAG3110_DR_OS_0_63_16;
  static uint8_t const MAG3110_DR_OS_0_31_32;
  static uint8_t const MAG3110_DR_OS_0_16_64;
  static uint8_t const MAG3110_DR_OS_0_08_128;
  ///@}

  /** @defgroup CTRL_REG1_OTHER
      @name Control register 1: other settings
      
      These attributes select a fast read mode, trigger a measurement and
      put the chip into active mode
      */
  ///@{
  static uint8_t const MAG3110_FAST_READ;
  static uint8_t const MAG3110_TRIGGER_MEASUREMENT;
  static uint8_t const MAG3110_ACTIVE_MODE;
  ///@}

  /** @defgroup CTRL_REG2
      @name Control register 2 settings
      
      These attributes enable an auto magnetic reset, put the chip into 
      raw mode ignoring the offset correction, and perform a magnetic reset
      */
  ///@{
  static uint8_t const MAG3110_AUTO_MRST_EN;
  static uint8_t const MAG3110_RAW_MODE;
  static uint8_t const MAG3110_MAG_RST;
  ///@}

  /** @defgroup SYSMOD
      @name SYSMOD readings
      
      These attributes indicate the current device operation mode,
      standby, active or active raw mode
      */
  ///@{
  static uint8_t const MAG3110_SYSMOD_STANDBY;
  static uint8_t const MAG3110_SYSMOD_ACTIVE_RAW;
  static uint8_t const MAG3110_SYSMOD_ACTIVE;
  ///@}

  /** @defgroup DR_STATUS
      @name DR_STATUS readings

      These attributes provide the aquisition status information of the OUT_X, 
      OUT_Y, and OUT_Z registers
      */
  ///@{
  static uint8_t const MAG3110_DR_STATUS_XDR;
  static uint8_t const MAG3110_DR_STATUS_YDR;
  static uint8_t const MAG3110_DR_STATUS_ZDR;
  static uint8_t const MAG3110_DR_STATUS_XYZDR;
  static uint8_t const MAG3110_DR_STATUS_XOW;
  static uint8_t const MAG3110_DR_STATUS_YOW;
  static uint8_t const MAG3110_DR_STATUS_ZOW;
  static uint8_t const MAG3110_DR_STATUS_XYZOW;
  ///@}

  /** @defgroup AXES
      @name Magnetomoeter axes

      These attributes describe the base address of the magnetometer axes
      */
  ///@{
  static uint8_t const MAG3110_X_AXIS;
  static uint8_t const MAG3110_Y_AXIS;
  static uint8_t const MAG3110_Z_AXIS;
  ///@}

  /** @brief Default constructor
      
      The default constructor initializes the private member variables.
      */
  MAG3110(void);
  /** @brief Default destcructor
      
      The default destructor removes the I<sup>2</sup>C bus handle
      */
  ~MAG3110(void);
  /** @brief Control debug output
      
      This function enables or disables debug output of the member functions.  
      
      @param t_debug true: debug output enabled, false: debug output disabled
      */
  void setDebug(bool t_debug);
  /** @brief Initialize I<sup>2</sup>C communication
      
      This funtion initializes the I<sup>2</sup>C communication with the chip
      and identifies the chip as a MAG3110.
      
      @param t_bus The I<sup>2</sup>C bus device, i.e.\ /dev/i2c-1
      */
  void initialize(const char* t_bus);
  /** @brief Read a register

      This function reads a register at the given address
    
      @param t_addr address of the register
      */
  uint8_t readRegister(uint8_t const& t_addr) const;
  /** @brief Write a register

      This function writes a value to the register at the given address.
      
      @param t_addr address of the register
      @param t_val value to write
      */
  void writeRegister(uint8_t const& t_addr, uint8_t const& t_val) const;
  /** @brief Standby

      This function puts the chip into standby mode.
      */
  void standby(void) const;
  /** @brief Start

      This function puts the chip into operation mode.
      */
  void start(void) const;
  /** @brief Reset

      This function resets the control registers, selects the default
      data rate and oversampling setting and resets the user provided
      axes offsets.
      */
  void reset(void);
  /** @brief Test if active

      This function tests whether the chip is in operation mode or in standby
      mode.
  
      @returns true: chip is active, false: chip is in standby
      */ 
  bool isActive(void) const;
  /** @brief Test if raw mode

      This function tests whether the chip is in active raw mode.
  
      @returns true: chip is in active raw mode, false: chip is not in active
               raw mode
      */
  bool isRaw(void) const;
    /** @brief Set raw mode

      This function puts the chip into active raw mode. In raw active mode,
      the chip does not automatically apply the user offset correction and 
      outputs the raw magnetometer reading. Useful for calibration.
  
      @param t_raw true: enable active raw mode, false: disable active raw mode
      */
  void setRawMode(bool const t_raw) const;
    /** @brief Trigger measurement
      
      This function triggers a measurement. In standby mode, the measurement will
      occur immediately and the chip returns to standby. In active mode, any
      measurement in progress will continue with the highest possible data rate
      for the currently selected oversampling rate.
      */
  void triggerMeasurement(void) const;
    /** @brief Test if new data are ready

      This function reads the ZYXDR bit of the DR_STATUS register and reports if
      new magnetic data are available.

      @returns true: new set of data ready, false: no new data ready
      */
  bool dataReady(void) const;
    /** @brief Set data rate and oversampling ratio

      This function sets the data rate (DR) and the oversampling ratio (OS) of 
      the chip. The combination of the two settings determines the ADC data rate 
      (80-1280 Hz), the typical current (8.6-900.0 µA) and the average noise level
      (0.25-0.40 µT rms). For details see the technical reference data sheet.

      @param t_DROS data rate and oversampling ratio setting
      @see @ref CTRL_REG1_DROS
      */
  void setDR_OS(uint8_t const t_DROS);
  uint8_t getDR_OS(void) const;
  void setDelay(uint8_t t_DROS);
  void setDelay(int t_delay);
  int getDelay(void) const;
  void setOffset(int16_t const& t_bxoff, int16_t const& t_byoff, 
    int16_t const& t_bzoff) const;
  void getOffset(int16_t* t_bxoff, int16_t* t_byoff, int16_t* t_bzoff) const;
  void calibrate(void); 
  void readMag(int* t_bx, int* t_by, int* t_bz) const;
  void getMag(int* t_bx, int* t_by, int* t_bz) const;
  int getMagPoll(int* t_bx, int* t_by, int* t_bz) const;
  double getMagnitude(int const& t_bx, int const& t_by, 
    int const& t_bz) const;
  void displayMag(int const& t_bx, int const& t_by, int const& t_bz) const;
  void displayMag(int const& t_bx, int const& t_by, int const& t_bz, 
    double const& t_mag) const;
  int getTemperature(void) const;
  
private:
  bool m_debug;
  int m_fd;
  int m_delay;
};

#endif // MAG3110_HPP
