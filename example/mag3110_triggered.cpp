#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @brief Triggered

    Trigger measurements

    Compile with
    g++ mag3110_triggered.cpp -o triggered -lmag3110 -L../ -I../include -static 

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

  // Chip is in standby
  int bx, by, bz;
  while (true) {
    // Trigger one measurement
    mag.triggerMeasurement();  
  
    // Read magnetic field
    mag.getMag(&bx, &by, &bz);

    // Output magnetic field
    mag.displayMag(bx, by, bz);

    // Delay
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
