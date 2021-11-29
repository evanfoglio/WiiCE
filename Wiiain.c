#include <stdio.h>

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>

#include "linux/gpio.h"
#include "sys/ioctl.h"

int init(int gpiovals[14]);

int main(int argc, char **argv) {

	int gpiovals[14] = {7, 17, 27, 22, 10, 9, 11, // X-axis Values
			   14, 15, 18, 23, 24, 25, 8};// Y-axis Values
	//initWiiPIO(int gpiovals[14]){

	//Assuming everything is set up below here,


	while(true) {

		//Read in I2C values


		//Write out to LEDs

	}





}



