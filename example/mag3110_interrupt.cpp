#include <iostream>
#include <chrono>
#include <thread>
#include <wiringPi.h>
#include "mag3110.hpp"

/** @brief Basic

    Example to use interrupt output pin of MAG3110 sensor.

    Compile with
    g++ mag3110_interrupt.cpp -o interrupt -Wl,-Bstatic -lmag3110 -Wl,-Bdynamic -lwiringPi -L../ -I../include
    */

using namespace std;

int const INT_PIN = 7;

void myInterrupt (void)
{
  ++globalCounter ;
}


int main(int argc, char** argv)
{
  wiringPiSetup();  
  pinMode(INT_PIN, INPUT);
  pullUpDnControl (INT_PIN, PUD_DOWN);
  MAG3110 mag;
  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_0_63_128);
  mag.start();

  int bx, by, bz;
  int state;

  while (true) {
    mag.getMag(&bx, &by, &bz);
    //mag.displayMag(bx, by, bz);
    this_thread::sleep_for(chrono::milliseconds(100));
    state = digitalRead(INT_PIN);
    cout << "Pin state: " << state << endl;
  }

  return 0;
}
