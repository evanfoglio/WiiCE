#include <stdio.h>

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>

#include "linux/gpio.h"
#include "sys/ioctl.h"
#include "Wii2c.h"
#include "WiiPIO.h"

int init(int gpiovals[14]);

int main(int argc, char **argv) {

    int gpiovals[14] = {7, 17, 27, 22, 10, 9, 11, // X-axis Values			   
                        14, 15, 18, 23, 24, 25, 8};// Y-axis Values

    int bytes[6];
    int i;

    // Initialize the Nunchuck's I2C settings
    Wii2c_setup();

    while(1) {
        
        wiringPiI2CWrite(fd, 0x00);
        delayMicroseconds(500);
        for (i=0; i<6; i++) {
            bytes[i] = wiringPiI2CRead(fd);
        }

        int joyX = bytes[0];
        int joyY = bytes[1];

		//Write out to LEDs

	}





}



