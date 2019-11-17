#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_slow.cpp

    Basic example to read the magnetic field from the MAG3110 sensor as
    slow as possible
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_0_08_128);
  mag.start();

  int bx, by, bz;
  while (true) {
    mag.getMagDelayed(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
  }

  return 0;
}
