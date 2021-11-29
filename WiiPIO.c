#include <stdio.h>

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>

#include "linux/gpio.h"
#include "sys/ioctl.h"
#include "WiiPIOinit.h"
struct gpiohandle_data WiiPIOinit(int GPIO){
	int fd, rv;
        /* Open the gpio device */
        fd = open("/dev/gpiochip0", O_RDWR);
        if (fd < 0){
                printf("%s\n", strerror(errno));
                exit(1);
        }

	//Struct and setup to define GPIO18 as output for LED blinking
        struct gpiohandle_request req;
        memset(&req, 0, sizeof(struct gpiohandle_request));
        req.flags = GPIOHANDLE_REQUEST_OUTPUT;
        req.lines = 1;
        req.lineoffsets[0] = GPIO;
        req.default_values[0] = 0;
        strcpy(req.consumer_label, "Wii");
        rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
	
	struct gpiohandle_data data;
	return data;
}
