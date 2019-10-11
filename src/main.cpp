#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;
  mySensor.setDebug();
  mySensor.initialize("/dev/i2c-1");
  mySensor.calibrate();
  if (mySensor.isCalibrated()) {
    cout << "Calibration successful" << endl;
  }
  int xoff, yoff, zoff;
  mySensor.getOffset(&xoff, &yoff, &zoff);
  cout << "Offset: " << xoff << ", " << yoff << ", " << zoff << endl;
  double heading = mySensor.getHeading();
  cout << "Heading: " << heading << " deg" << endl;
  

  while (true) {
    int x, y, z;
    mySensor.readMag(&x, &y, &z);
    double mag = mySensor.getMagnitude(x, y, z);
    cout << "x: " << setw(6) << x 
      << ", y: " << setw(6) << y 
      << ", z: " << setw(6) << z 
      << ", <B>: " << fixed << setprecision(0) << mag 
      << endl;
    sleep(1);
  }

  return 0;
}
