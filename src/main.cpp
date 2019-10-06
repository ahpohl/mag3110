#include "mag3110.hpp"

using namespace std;

int main(int argc, char** argv)
{
  MAG3110 mySensor;

  mySensor.initialize();

  return 0;
}
