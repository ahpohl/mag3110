#include <iostream>
#include <iomanip>
#include <cstring>
#include <chrono>
#include <thread>
#include <errno.h>
#include <wiringPi.h>
#include "mag3110.hpp"

/** @example mag3110_interrupt.cpp

    This example uses the interrupt output pin of the MAG3110 sensor and waits
    until new data is available before reading the magnetic field. It uses
    the wiringPi library to setup a gpio pin as an interrupt on a rising edge.
    */

using namespace std;

int const MAG3110_PIN = 7;
static volatile bool isEvent = false;

void magISR(void)
{
  isEvent = true;
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
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;

  uint8_t dros = mag.getDR_OS();
  cout << "DR_OS: " << static_cast<unsigned int>(dros) << endl;

  mag.reset();
  dros = mag.getDR_OS();
  cout << "DR_OS: " << static_cast<unsigned int>(dros) << endl;

  mag.start();
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_10_16);
  dros = mag.getDR_OS();
  cout << "DR_OS: " << static_cast<unsigned int>(dros) << endl;

  int bx, by, bz;
  chrono::high_resolution_clock::time_point start_isr, end_isr;
  
  while (true) {
    start_isr = chrono::system_clock::now();
    while (!isEvent) {
      this_thread::sleep_for(chrono::milliseconds(1));
    }
    mag.getMag(&bx, &by, &bz);
    mag.displayMag(bx, by, bz);
    isEvent = false;
    end_isr = chrono::system_clock::now();
    cout << "Duration: " << chrono::duration_cast<chrono::milliseconds>(
      end_isr - start_isr).count() << " ms" << endl;
  }

  return 0;
}
