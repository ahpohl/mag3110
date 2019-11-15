#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_active.cpp

    Basic example to read the magnetic field from the MAG3110 sensor

    Compile with
    g++ mag3110_active.cpp -o active -lmag3110 -L../ -I../include -static 

    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;

  mag.initialize("/dev/i2c-1");
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.standby();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.start();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.standby();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.start();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.standby();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;
  mag.start();
  cout << (mag.isActive() ? "Mode: active" : "Mode: standby") << endl;

  return 0;
}
