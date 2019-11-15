#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @example mag3110_dros.cpp

    This example sets different data rates.

    Compile with
    g++ mag3110_dros.cpp -o dros -lmag3110 -L../ -I../include -static 

    */

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mag;
  uint8_t dros;
  cout << hex << setiosflags(ios::showbase);

  mag.initialize("/dev/i2c-1");
  mag.reset();
  mag.start();

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_80_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_40_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl; 

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_20_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_10_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_5_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_2_5_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_1_25_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  mag.setDR_OS(MAG3110::MAG3110_DR_OS_0_63_16);
  dros = mag.getDR_OS();
  cout << "Data rate: " << static_cast<int>(dros) << endl;

  return 0;
}
