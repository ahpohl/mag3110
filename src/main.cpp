#include <iostream>
#include <cmath>
#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;

  mySensor.initialize("/dev/i2c-1");
  double x, y, z;
  mySensor.readMicroTesla(&x, &y, &z);
  double mag = sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
  cout << "x: " << x 
    << ", y: " << y 
    << ", z: " << z 
    << ", <B>: " << mag 
    << " µT" << endl;

  return 0;
}
