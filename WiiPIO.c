#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>

#include "linux/gpio.h"
#include "sys/ioctl.h"
#include "WiiPIO.h"
int WiiPIOinit(int * GPIOs, struct gpiohandle_request * req){

	int fd, rv, i;
        /* Open the gpio device */
        fd = open("/dev/gpiochip0", O_RDWR);
        if (fd < 0){
                printf("%s\n", strerror(errno));
                exit(1);
        }
	//struct gpiohandle_request req[14];
	//struct gpiohandle_data data[14];
	for(i=0; i<14; i++){
		//Struct and setup to define GPIO18 as output for LED blinking
	        memset(&req[i], 0, sizeof(struct gpiohandle_request));
	        req[i].flags = GPIOHANDLE_REQUEST_OUTPUT;
	        req[i].lines = 1;
	        req[i].lineoffsets[0] = GPIOs[i];
	        req[i].default_values[0] = 0;
	        strcpy(req[i].consumer_label, "Wii");

	        rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req[i]); 
	}
	return req;
}

