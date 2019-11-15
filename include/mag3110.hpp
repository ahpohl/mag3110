#ifndef MAG3110_HPP
#define MAG3110_HPP
#include <cstdint>

/** @brief A class to drive the MAG3110 3-axis magnetometer

    This class is derived from the <a href="https://github.com/sparkfun/SparkFun_MAG3110_Breakout_Board_Arduino_Library" target="_blank">Sparkfun Arduino library</a> and has been ported to plain C++.
 
    @author Alexander Pohl <alex@ahpohl.com>
    */

class MAG3110
{
public:
  /** @name General attributes */
  ///@{

  /// I2C address of the chip
  static uint8_t const MAG3110_I2C_ADDRESS;
  /// Device identifier
  static uint8_t const MAG3110_WHO_AM_I_RSP;
  /// Temperature offset
  static int const MAG3110_DIE_TEMP_OFFSET;
  ///@} 

  /** @name Register addresses */
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
  
  /** @name Control register 1: data rate and oversampling settings */
  ///@{

  /// Output rate = 80 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_80_16;
  /// Output rate = 40 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_40_32;
  /// Output rate = 20 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_20_64;
  /// Output rate = 10 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_10_128;
  /// Output rate = 40 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_40_16;
  /// Output rate = 20 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_20_32;
  /// Output rate = 10 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_10_64;
  /// Output rate = 5 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_5_128;
  /// Output rate = 20 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_20_16;
  /// Output rate = 10 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_10_32;
  /// Output rate = 5 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_5_64;
  /// Output rate = 2.5 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_2_5_128;
  /// Output rate = 10 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_10_16;
  /// Output rate = 5 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_5_32;
  /// Output rate = 2.5 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_2_5_64;
  /// Output rate = 1.25 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_1_25_128;
  /// Output rate = 5 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_5_16;
  /// Output rate = 2.5 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_2_5_32;
  /// Output rate = 1.25 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_1_25_64;
  /// Output rate = 0.63 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_0_63_128;
  /// Output rate = 2.5 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_2_5_16;
  /// Output rate = 1.25 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_1_25_32;
  /// Output rate = 0.63 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_0_63_64;
  /// Output rate = 0.31 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_0_31_128;
  /// Output rate = 1.25 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_1_25_16;
  /// Output rate = 0.63 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_0_63_32;
  /// Output rate = 0.31 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_0_31_64;
  /// Output rate = 0.16 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_0_16_128;
  /// Output rate = 0.63 Hz, oversampling ratio = 16
  static uint8_t const MAG3110_DR_OS_0_63_16;
  /// Output rate = 0.31 Hz, oversampling ratio = 32
  static uint8_t const MAG3110_DR_OS_0_31_32;
  /// Output rate = 0.16 Hz, oversampling ratio = 64
  static uint8_t const MAG3110_DR_OS_0_16_64;
  /// Output rate = 0.08 Hz, oversampling ratio = 128
  static uint8_t const MAG3110_DR_OS_0_08_128;
  ///@}

  /** @name Control register 1: other settings */
  ///@{

  /// Fast read mode
  static uint8_t const MAG3110_FAST_READ;
  /// Trigger immediate measurement
  static uint8_t const MAG3110_TRIGGER_MEASUREMENT;
  /// Operation mode
  static uint8_t const MAG3110_ACTIVE_MODE;
  ///@}

  /** @name Control register 2 settings */
  ///@{

  /// Automatic magnetic sensor reset
  static uint8_t const MAG3110_AUTO_MRST_EN;
  /// Data output correction
  static uint8_t const MAG3110_RAW_MODE;
  /// Magnetic sensor reset (one-shot).
  static uint8_t const MAG3110_MAG_RST;
  ///@}

  /** @name SYSMOD readings */
  ///@{

  /// Standby mode
  static uint8_t const MAG3110_SYSMOD_STANDBY;
  /// Active mode, raw data
  static uint8_t const MAG3110_SYSMOD_ACTIVE_RAW;
  /// Active mode, user corrected data
  static uint8_t const MAG3110_SYSMOD_ACTIVE;
  ///@}

  /** @name DR_STATUS readings */
  ///@{

  /// X-axis new data available
  static uint8_t const MAG3110_DR_STATUS_XDR;
  /// Y-axis new data available
  static uint8_t const MAG3110_DR_STATUS_YDR;
  /// Z-axis new data available
  static uint8_t const MAG3110_DR_STATUS_ZDR;
  /// X-,Y- or Z-axis new data available
  static uint8_t const MAG3110_DR_STATUS_XYZDR;
  /// X-axis data overwrite
  static uint8_t const MAG3110_DR_STATUS_XOW;
  /// Y-axis data overwrite
  static uint8_t const MAG3110_DR_STATUS_YOW;
  /// Z-axis data overwrite
  static uint8_t const MAG3110_DR_STATUS_ZOW;
  /// X-, Y- or Z-axis data overwrite
  static uint8_t const MAG3110_DR_STATUS_XYZOW;
  ///@}

  /** @name Magnetometer base address */
  ///@{

  /// X-axis base address
  static uint8_t const MAG3110_X_AXIS;
  /// Y-axis base address
  static uint8_t const MAG3110_Y_AXIS;
  /// Z-axis base address
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
  /** brief Get library version
      
      This function outputs the library version and build date
      */
  void getVersion(void) const;
  /** @brief Control debug output
      
      This function enables or disables debug output of the member functions.  
      
      @param t_debug True: debug output enabled, false: debug output disabled
      */
  void setDebug(bool t_debug);
  /** @brief Initialize I2C communication
      
      This funtion initializes the I2C communication with the chip
      and identifies the chip as a MAG3110.
      
      @param t_bus The I2C bus device
      */
  void initialize(const char* t_bus);
  /** @brief Read a register

      This function reads a register at the given address
    
      @param t_addr Address of the register
      */
  uint8_t readRegister(uint8_t const& t_addr) const;
  /** @brief Write a register

      This function writes a value to the register at the given address.
      
      @param t_addr Address of the register
      @param t_val Value to write
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
  
      @returns True: chip is active, false: chip is in standby
      */ 
  bool isActive(void) const;
  /** @brief Test if raw mode

      This function tests whether the chip is in active raw mode.
  
      @returns True: chip is in active raw mode, false: chip is not in active
               raw mode
      */
  bool isRaw(void) const;
  /** @brief Set raw mode

      This function puts the chip into active raw mode. In raw active mode,
      the chip does not automatically apply the user offset correction and 
      outputs the raw magnetometer reading. Useful for calibration.
  
      @param t_raw True: enable active raw mode, false: disable active raw mode
      */
  void setRawMode(bool const t_raw) const;
  /** @brief Set fast read

      This function selects a fast read mode. In normal read mode, the full
      16-bit values are read. With fast read enabled, 8-bit values are read
      from the MSB registers (auto-increment skips over the LSB register
      in burst-read mode).

      @param t_fast True: enable fast read, false: disable fast read
      */
  void setFastRead(bool const t_fast) const;
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

      @returns True: new set of data ready, false: no new data ready
      */
  bool isDataReady(void) const;
  /** @brief Set data rate and oversampling ratio

      This function sets the data rate (DR) and the oversampling ratio (OS) of 
      the chip. The combination of the two settings determines the ADC data rate 
      (80-1280 Hz), the typical current (8.6-900.0 µA) and the average noise level
      (0.25-0.40 µT rms). For details see the
      <a href="MAG3110_reference.pdf" target="_blank">technical reference</a> on page 20.

      @param t_DROS data rate and oversampling ratio setting
      @see getDR_OS()
      */
  void setDR_OS(uint8_t const t_DROS);
  /** @brief Get data rate and oversampling ratio

      This function gets the date rate (DR) and oversampling ratio (OS) 
      setting.

      @returns MAG3110_DR_OS_* constant
      @see setDR_OS()
      */
  uint8_t getDR_OS(void) const;
  /** @brief Set delay

      This function sets a delay between measurements. The length of the 
      delay is pre-determined by the current data rate and oversampling setting
      and ranges from 13 ms (80 Hz) to 12.8 s (0.08 Hz).
      
      @param t_DROS Data rate and oversampling ratio setting
      @see setDelay(int)
      @see getDelay()
      */
  void setDelay(uint8_t t_DROS);
  /** @brief Set delay

      This function sets a delay between measurements in milli seconds. 
      
      @param t_delay Delay in [ms]
      @see setDelay(uint8_t)
      @see getDelay()
      */
  void setDelay(int t_delay);
  /** @brief Get delay

      This function gets the delay between measurements. 
      
      @returns Delay in [ms]
      @see setDelay(uint8_t)
      @see setDelay(int)
      */
  int getDelay(void) const;
  /** @brief Set magnetic offset
      
      This function sets a user magnetic offset. The user offsets have a 
      maximum range -10.000 to +10.000 bit counts per x, y, z-axis and are 
      automatically substracted from the magnetic field readings before they
      are written to the output registers. The user offsets are not substracted
      when the chip is in raw active mode.
      
      @param t_bxoff X-axis magnetic offset
      @param t_byoff Y-axis magnetic offset
      @param t_bzoff Z-axis magnetic offset
      @see getOffset()
      @see calibrate()     
      */
  void setOffset(int16_t const& t_bxoff, int16_t const& t_byoff, 
    int16_t const& t_bzoff) const;
  /** @brief Get magnetic offset
      
      This function gets the user magnetic offsets.

      @param t_bxoff X-axis magnetic offset
      @param t_byoff Y-axis magnetic offset
      @param t_bzoff Z-axis magnetic offset
      @see setOffset()
      @see calibrate()
      */
  void getOffset(int16_t* t_bxoff, int16_t* t_byoff, int16_t* t_bzoff) const;
  /** @brief Calibrate magnetic reading
    
      This function calibrates the magnetic readings of the chip. The initial
      magnetic induction is set to approximately zero along each axis by 
      applying a user magnetic offset.

      @see setOffset()
      @see getOffset()
      */
  void calibrate(void);
  /** @brief Get magnetic field strength
      
      This function gets the magnetic field strength along each axis.

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @see getMagDelayed()
      @see getMagPoll()
      */
  void getMag(int* t_bx, int* t_by, int* t_bz) const;
  /** @brief Get magnetic field strength (delayed)
      
      This function gets the magnetic field strength along each axis. The 
      output is delayed.

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @see getMag()
      @see getMagPoll()
      @see setDelay(int)
      */
  void getMagDelayed(int* t_bx, int* t_by, int* t_bz) const;
  /** @brief Poll magnetic field strength
      
      This function polls the magnetic field strength along each axis. It
      waits until new data is ready before a new read request is made. 

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @see getMag()
      @see getMagDelayed()
      */
  void getMagPoll(int* t_bx, int* t_by, int* t_bz) const;
  /** @brief Calculate magnetic field strength
      
      This function calculates the magnitude of the magnetic field.

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @returns Magnitude of the magnetic field
      @see getMag()
      @see getMagDelayed()
      @see getMagPoll()
      */
  double getMagnitude(int const& t_bx, int const& t_by, 
    int const& t_bz) const;
  /** @brief Display magnetic field strength

      This function displays the magnetic field strength along each
      axis.

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @see getMag()
      */
  void displayMag(int const& t_bx, int const& t_by, int const& t_bz) const;
  /** @brief Display magnetic field strength

      This function displays the magnetic field strength along each
      axis and the magnitude of the magnetic field.

      @param t_bx X-axis component
      @param t_by Y-axis component
      @param t_bz Z-axis component
      @param t_mag Magnitute of magnetic field
      @see getMag()
      */
  void displayMag(int const& t_bx, int const& t_by, int const& t_bz, 
    double const& t_mag) const;
  /** @brief Get temperature
    
      This function reads the die temperature inside the chip. The output
      range is limited from -40°C to 125°C

      @returns Temperature in °C  
      */
  int getTemperature(void) const;
  
private:
  /// Debug flag
  bool m_debug;
  /// I2C bus file descriptor
  int m_fd;
  /// Delay in milli seconds
  int m_delay;
};

#endif // MAG3110_HPP
