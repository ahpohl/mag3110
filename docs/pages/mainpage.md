@mainpage Documentation

## Hardware

Freescale’s MAG3110 is a small, low-power, digital 3-axis magnetometer. The device can be used in conjunction with a 3-axis accelerometer to realize an orientation independent electronic compass that can provide accurate heading information. It features a standard I<SUP>2</SUP>C serial interface output and is capable of measuring magnetic fields with an output data rate (ODR) up to 80 Hz; these output data rates correspond to sample intervals from 12.5 ms to several seconds. For details see the <a href="../pdf/MAG3110_reference.pdf" target="_blank">technical reference documentation</a>.

## Software

The MAG3110 library has been derived from the <a href="https://github.com/sparkfun/SparkFun_MAG3110_Breakout_Board_Arduino_Library" target="_blank">Sparkfun Arduino library</a> to C++ to allow embedded devices such as the Raspberry Pi with an I<SUP>2</SUP>C bus to use the breakout board directly. It uses much of the same API as the original library. However, a couple of methods have been renamed, added or removed. The source code can be downloaded from the MAG3110 <a href="https://github.com/ahpohl/mag3110" target="_blank">GitHub repository</a>.

## Links

* <a href="https://github.com/ahpohl/mag3110" target="_blank">Source Code GitHub repository</a>
* <a href="../pdf/MAG3110_reference.pdf" target="_blank">MAG3110 Technical Reference Documentation</a>.
* <a href="https://github.com/sparkfun/SparkFun_MAG3110_Breakout_Board_Arduino_Library" target="_blank">MAG3110 Sparkfun Arduino Library</a> 

## License

The library is licensed under the GNU Public License - see the LICENSE file for details. The library is provided as-is without any warranty given.
