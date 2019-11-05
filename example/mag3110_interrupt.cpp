#include <iostream>
#include <cstring>
#include <chrono>
#include <thread>
#include <errno.h>
#include <wiringPi.h>
#include "mag3110.hpp"

/** @brief Basic

    Example to use interrupt output pin of MAG3110 sensor.

    Compile with
    g++ mag3110_interrupt.cpp -o interrupt -Wl,-Bstatic -lmag3110 -Wl,-Bdynamic -lwiringPi -L../ -I../include
    */

using namespace std;

int const MAG3110_PIN = 7;
static volatile int globalCounter = 0;

void magISR(void)
{
  ++globalCounter;
}


int main(int argc, char** argv)
{
  if (wiringPiSetup() < 0)
  {
    throw runtime_error(string("Unable to setup wiringPi: ") + 
      + strerror(errno) + " (" + to_string(errno) + ")");
  }
  if (wiringPiISR(MAG3110_PIN, INT_EDGE_RISING, &magISR) < 0)
  {
    throw runtime_error(string("Unable to setup ISR: ") + 
      + strerror(errno) + " (" + to_string(errno) + ")");
  }
  MAG3110 mag;
  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_10_128);
  mag.start();
  
  int myCounter = 0;
  int bx, by, bz;
  
  while (true) {
    while (myCounter == globalCounter) {
      this_thread::sleep_for(chrono::milliseconds(1));
    }
    mag.getMag(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
    myCounter = globalCounter;
  }

  return 0;
}
