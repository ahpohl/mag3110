#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_active.cpp

    This example puts the chip in active and standby mode.
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
