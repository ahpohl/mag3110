#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_calibrated.cpp

    Calibrate the magnetic field from the MAG3110 sensor by applying an
    offset to the raw sensor values

    Compile with
    g++ mag3110_calibrated.cpp -o calibrated -lmag3110 -L../ -I../include 
    -static 

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

  // Calibrate sensor
  mag.calibrate();

  // Put chip into active mode and start measurements
  mag.start();

  // Get offset
  int16_t bxoff, byoff, bzoff;
  mag.getOffset(&bxoff, &byoff, &bzoff);
  cout << "Offsets: " << bxoff << ", " << byoff << ", " << bzoff << endl;

  int bx, by, bz;
  double magnitude;
  while (true) {
    // Read magnetic field
    mag.getMag(&bx, &by, &bz);

    // Calulate magnitude of magnetic field
    magnitude = mag.getMagnitude(bx, by, bz); 

    // Output magnetic field and magnitude
    mag.displayMag(bx, by, bz, magnitude);

    // Delay
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
