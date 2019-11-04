#include <iostream>
#include <chrono>
#include <thread>
#include "mag3110.hpp"

/** @brief Basic

    Poll magnetic field from the MAG3110 sensor. Wait until new magnetic field
    data is available.

    Compile with
    g++ mag3110_poll.cpp -o poll -lmag3110 -L../ -I../include -static 

    */

using namespace std;

int main(int argc, char** argv)
{
  // Instantiate MAG3110 library
  MAG3110 mag;

  // Initialize I2C communication
  mag.initialize("/dev/i2c-1");

  // Reset chip registers to defaults
  mag.reset();

  // Select moderate data rate
  mag.setDR_OS(MAG3110::MAG3110_DR_OS_0_63_128);

  // Get delay
  int delay = mag.getDelay();
  cout << "Delay: " << delay << " ms" << endl;

  // Enable debug output
  mag.setDebug(true);

  int bx, by, bz;
  mag.getMag(&bx, &by, &bz);

  // Test if data is already ready
  if (mag.isDataReady()) {
    cout << "Data is already available, but it shouldn't" << endl;
  }

  while (true) {
    // Poll magnetic field data
    mag.getMagPoll(&bx, &by, &bz);

    // Output magnetic field
    mag.displayMag(bx, by, bz);
  }

  return 0;
}
