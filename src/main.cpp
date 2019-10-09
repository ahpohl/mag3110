#include <iostream>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;
  mySensor.initialize("/dev/i2c-1");
  mySensor.start();
  
  int x, y, z;
  mySensor.readMag(&x, &y, &z);
  double mag = mySensor.getMagnitude(x, y, z);
  cout << "x: " << x 
    << ", y: " << y 
    << ", z: " << z 
    << ", <B>: " << mag 
    << endl;

  return 0;
}
