#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>
#include <unistd.h>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;
  mySensor.setDebug();
  mySensor.initialize("/dev/i2c-1");
  mySensor.calibrate();
  
  cout << "Raw mode" << endl;
  mySensor.setRawMode(true);
  
  int x, y, z;
  mySensor.readMag(&x, &y, &z);
  mySensor.displayMag(x, y, z); 
  
  int xoff, yoff, zoff;
  mySensor.getOffset(&xoff, &yoff, &zoff);
  cout << "Get offset: " << xoff << ", " << yoff << ", " << zoff << endl;
  mySensor.setRawMode(false);
  mySensor.readMag(&x, &y, &z);
  mySensor.displayMag(x, y, z);
  

  if (mySensor.isCalibrated()) {
    double heading = mySensor.getHeading();
    cout << "Heading: " << heading << " deg" << endl;
  }
  
  int temp = mySensor.getTemperature();
  cout << "Temperature: " << temp << "°C" << endl;
  
  /*
  ofstream file;
  file.open("mag.txt", ios::app);
  time_t timestamp;

  while (true) {
    int x, y, z;
    mySensor.readMag(&x, &y, &z);
    double mag = mySensor.getMagnitude(x, y, z);
    mySensor.displayMag(x, y, z, mag);
    timestamp = time(nullptr);
    file << timestamp << "," << x << "," << y << "," << z 
      << "," << mag << endl;
    sleep(1);
  }

  file.close();
  */

  return 0;
}
