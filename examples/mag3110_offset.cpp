#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_offset.cpp

    This example shows how to set a custom magnetic field offset.
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;
  
  mag.initialize("/dev/i2c-1");
  mag.reset();

  int bx, by, bz;
  mag.getMag(&bx, &by, &bz);
  mag.displayMag(bx, by, bz);
  mag.setOffset(bx, by, bz);
  mag.triggerMeasurement();
  mag.getMag(&bx, &by, &bz);
  mag.displayMag(bx, by, bz);

  return 0;
}
