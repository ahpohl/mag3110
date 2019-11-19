#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_fast.cpp

    This example reads the magnetic field as fast as possible (80 Hz).
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.start();

  int bx, by, bz;
  while (true) {
    mag.getMagDelayed(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
  }

  return 0;
}
