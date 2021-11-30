#include <stdio.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>
#include "linux/gpio.h"
#include "sys/ioctl.h"
#include "Wii2c.h"
#include "WiiPIO.h"

//int init(int gpiovals[14]);

int main(int argc, char **argv) {

    int rv;
    int result;
    int bytes_read;
    int fd;
    fd = open("/dev/gpiochip0",O_RDWR);


    // First half of array is for X axis, second half is for Y axis
    int gpiovals[14] = {4, 17, 27, 22, 10, 9, 11, 14, 15, 18, 23, 24, 25, 8};
    struct gpiohandle_request * req = WiiPIOinit(gpiovals);
    

    rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &(req[0]));
    struct gpiohandle_data data;
    data.values[0]=1; // value to output (0 or 1)
    
    rv=ioctl(req[0].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    
    // Nunchuck returns 6 bytes
    unsigned char nc_data[6];
    
    int i;
    unsigned char joyX, joyY;
    unsigned char buffer = 0x00;
    // Initialize the Nunchuck's I2C settings
    fd = Wii2c_setup();
    
    while(1) {
        
        result = write(fd, buffer, 1);
        usleep(500);

        for (i = 0; i < 6; i++) {
            bytes_read = read(fd, nc_data[i], 1);
        }

        joyX = nc_data[0];
        joyY = nc_data[1];
        printf("X: %d\tY: %d\n", joyX, joyY);

	//Write out to LEDs

    }
    return 0;
}
