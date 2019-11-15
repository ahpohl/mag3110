#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_poll.cpp

    Poll magnetic field from the MAG3110 sensor. Wait until new magnetic field
    data is available.

    Compile with
    g++ mag3110_poll.cpp -o poll -lmag3110 -L../ -I../include -static 

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
