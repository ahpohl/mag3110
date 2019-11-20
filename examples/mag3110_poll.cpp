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
  mag.setDebug(true);  

  mag.initialize("/dev/i2c-1");
  mag.reset();
  
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_1_25_16);
  uint8_t dros = mag.getDR_OS();
  cout << "DR_OS: " << static_cast<int>(dros) << endl;
  int delay = mag.getDelay();
  cout << "Delay: " << delay << " ms" << endl;

  int bx, by, bz;
  while (true) {
    mag.getMagPoll(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
  }

  return 0;
}
