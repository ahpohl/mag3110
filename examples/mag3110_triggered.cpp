#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_triggered.cpp

    This example actively triggers measurements of the magnetic field. After
    each sensor read, the chip goes automatically back into standby mode.
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  mag.reset();

  int bx, by, bz;
  while (true) {
    cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
    mag.triggerMeasurement();
    mag.getMag(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
    this_thread::sleep_for(chrono::seconds(1));
  }

  return 0;
}
