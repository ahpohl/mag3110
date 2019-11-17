#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_raw.cpp

    Basic example to read the magnetic field from the MAG3110 sensor
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.setRawMode(true);
  cout << (mag.isRaw() ? "Mode: raw" : "Mode: not raw") << endl;
  mag.setRawMode(false);
  cout << (mag.isRaw() ? "Mode: raw" : "Mode: not raw") << endl;
  mag.setRawMode(true);
  cout << (mag.isRaw() ? "Mode: raw" : "Mode: not raw") << endl;
  mag.setRawMode(false);
  cout << (mag.isRaw() ? "Mode: raw" : "Mode: not raw") << endl;

  return 0;
}
