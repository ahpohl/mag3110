#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_basic.cpp

    Basic example to read the magnetic field from the MAG3110 sensor

    Compile with
    g++ mag3110_basic.cpp -o basic -lmag3110 -L../ -I../include -static 

    */

using namespace std;

int main(int argc, char** argv)
{
  // Instantiate MAG3110 library
  MAG3110 mag;

  // Initialize I2C communication
  mag.initialize("/dev/i2c-1");

  // Reset chip registers to defaults
  mag.reset();

  // Put chip into active mode and start measurements
  mag.start();

  int bx, by, bz;
  while (true) {
    // Read magnetic field
    mag.getMag(&bx, &by, &bz);

    // Output magnetic field
    mag.displayMag(bx, by, bz);

    // Delay
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
