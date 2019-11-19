#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_poll.cpp

    This example polls the chip and waits until new data is available before
    reading the magnetic field.
    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;
  
  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_0_63_128);

  int delay = mag.getDelay();
  cout << "Delay: " << delay << " ms" << endl;
  mag.setDebug(true);

  int bx, by, bz;
  mag.getMag(&bx, &by, &bz);

  if (mag.isDataReady()) {
    cout << "Data is already available, but it shouldn't" << endl;
  }

  while (true) {
    mag.getMagPoll(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
  }

  return 0;
}
