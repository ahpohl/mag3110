#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;
  mySensor.setDebug();
  mySensor.initialize("/dev/i2c-1");
  mySensor.reset();
  mySensor.start();
  //mySensor.calibrate();
  
  int xoff, yoff, zoff;
  mySensor.getOffset(&xoff, &yoff, &zoff);
  cout << "Offset: " << xoff << ", " << yoff << ", " << zoff << endl;
  double heading = mySensor.getHeading();
  cout << "Heading: " << heading << " deg" << endl;

  ofstream file;
  file.open("mag.txt", ios::app);
  time_t timestamp;

  while (true) {
    int x, y, z;
    mySensor.readMag2(&x, &y, &z);
    double mag = mySensor.getMagnitude(x, y, z);
    cout << "x: " << setw(6) << x 
      << ", y: " << setw(6) << y 
      << ", z: " << setw(6) << z 
      << ", <B>: " << setw(6) << fixed << setprecision(0) << mag 
      << endl;
    timestamp = time(nullptr);
    file << timestamp << "," << x << "," << y << "," << z 
      << "," << mag << endl;
    sleep(1);
  }

  file.close();

  return 0;
}
