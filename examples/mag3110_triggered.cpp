#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_triggered.cpp

    Trigger measurements
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.reset();

  int bx, by, bz;
  while (true) {
    mag.triggerMeasurement();  
    mag.getMag(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
