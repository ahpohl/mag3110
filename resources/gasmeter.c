#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <time.h>

void getMagneticField(int* file, int* xMag, int* yMag, int* zMag)
{
	char reg[1] = {0x01};
	write(*file, reg, 1);
	char data[1] = {0};
	if (read(*file, data, 1) != 1)
	{
		printf("Error : Input/Output error\n");
		exit(EXIT_FAILURE);
	}
	char data_0 = data[0];

	reg[0] = 0x02;
	write(*file, reg, 1);
	read(*file, data, 1);
	char data_1 = data[0];

	reg[0] = 0x03;
	write(*file, reg, 1);
	read(*file, data, 1);
	char data_2 = data[0];

	reg[0] = 0x04;
	write(*file, reg, 1);
	read(*file, data, 1);
	char data_3 = data[0];

	reg[0] = 0x05;
	write(*file, reg, 1);
	read(*file, data, 1);
	char data_4 = data[0];

	reg[0] = 0x06;
	write(*file, reg, 1);
	read(*file, data, 1);
	char data_5 = data[0];

	*xMag = (data_0 * 256 + data_1);
	if (*xMag > 32767) {
		*xMag -= 65536;
	}
	*yMag = (data_2 * 256 + data_3);
	if (*yMag > 32767) {
		*yMag -= 65536;
	}
	*zMag = (data_4 * 256 + data_5);
	if (*zMag > 32767) {
	  *zMag -= 65536;
	} 
} 

int main(int argc, char** argv) 
{
  int file;
	char* bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) {
		printf("Failed to open the bus.\n");
		exit(EXIT_FAILURE);
	}
	ioctl(file, I2C_SLAVE, 0x0E);

	char config[2] = {0};
	config[0] = 0x10;
	config[1] = 0x01;
	write(file, config, 2);
	sleep(1);

  
  FILE * fp;
  int xMag, yMag, zMag;
  double sMag;
  time_t timestamp;
  while (1) {
    getMagneticField(&file, &xMag, &yMag, &zMag);
    sMag = sqrt(xMag*xMag + yMag*yMag + zMag*zMag);  
    timestamp = time(NULL);
    fp = fopen("mag.txt", "a");
    fprintf(fp, "%ld,%d,%d,%d,%.2f\n", timestamp, xMag, yMag, zMag, sMag);
    fclose(fp);
    sleep(1);
  }
  return EXIT_SUCCESS;
}
