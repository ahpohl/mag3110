#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_calibrated.cpp

    Calibrate the magnetic field from the MAG3110 sensor by applying an
    offset to the raw sensor values
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.calibrate();
  mag.start();

  int16_t bxoff, byoff, bzoff;
  mag.getOffset(&bxoff, &byoff, &bzoff);
  cout << "Offsets: " << bxoff << ", " << byoff << ", " << bzoff << endl;

  int bx, by, bz;
  double magnitude;
  while (true) {
    mag.getMag(&bx, &by, &bz);
    magnitude = mag.getMagnitude(bx, by, bz); 
    mag.displayMag(bx, by, bz, magnitude);
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
