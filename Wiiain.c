#include <stdio.h>

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>

#include "linux/gpio.h"
#include "sys/ioctl.h"

int init(int gpiovals[14]);

int main(int argc, char **argv) {

	int gpiovals[14] = {}


	init(int gpiovals[14]){
		int i;
		struct gpiohandle_data WiiPIOs[14];
		for(i=0; i<14; i++){
			WiiPIOs[i] = WiiPIOinit(gpioval[i]);
	}

}



