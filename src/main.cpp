#include <iostream>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;

  mySensor.initialize("/dev/i2c-1");
  double x, y, z;
  mySensor.readMicroTesla(&x, &y, &z);
  double mag = mySensor.getMagnitude(x, y, z);
  cout << "x: " << x 
    << ", y: " << y 
    << ", z: " << z 
    << ", <B>: " << mag 
    << " µT" << endl;
  mySensor.setOffset(MAG3110_X_AXIS, 5000);
  mySensor.setOffset(MAG3110_Y_AXIS, -5000);
  mySensor.setOffset(MAG3110_Z_AXIS, 5000);
  int x_off, y_off, z_off;
  x_off = mySensor.readOffset(MAG3110_X_AXIS);
  y_off = mySensor.readOffset(MAG3110_Y_AXIS);
  z_off = mySensor.readOffset(MAG3110_Z_AXIS);
  cout << "Offsets: " << x_off << ", " << y_off << ", " << z_off << endl;
  
  mySensor.readMicroTesla(&x, &y, &z);
  mag = mySensor.getMagnitude(x, y, z);
  cout << "x: " << x
    << ", y: " << y
    << ", z: " << z
    << ", <B>: " << mag
    << " µT" << endl;

  return 0;
}
