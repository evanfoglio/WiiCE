#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "linux/gpio.h"
#include "sys/ioctl.h"
#include "Wii2c.h"
#include "WiiPIO.h"

//int init(int gpiovals[14]);
void lightUpAll(struct gpiohandle_request * req, int * gpios);
void ledCtrlX(int value, struct gpiohandle_request * req);
void ledCtrlY(int value, struct gpiohandle_request * req);

int main(int argc, char **argv) {

    int nc_bytes[6];
    int i;

    // First half of array is for X axis, second half is for Y axis
    int gpiovals[14] = {17, 27, 22, 10, 9, 5, 6, 14, 15, 18, 23, 24, 25, 8};
    
    struct gpiohandle_request req[14];

    // Open Wii-Nunchuck at i2c address 0x52
    int fd = setup_i2c("/dev/i2c-1", 0x52);
    if (fd < 0) {
        printf("Error setting up I2C: %d\n", errno);
        exit(0);
    }
    
    // Initialize the GPIOs
    WiiPIOinit(gpiovals, req);

    // Nunchuck is initialized by writing 0x00 to address 0x40    
    write_i2c_register(fd, 0x40, 0x00);
    usleep(500);

    while(1) {
    
        // Invoke a response by writing 0 to address 0
        i2c_access(fd, I2C_WRITE, 0x00, I2C_BYTE, NULL) ;
        usleep(500);
    
        // Read all 6 bytes from the Nunchuck
        for (i = 0; i < 6; i++) {
            nc_bytes[i] = read_i2c(fd);
        }

        int joyX = nc_bytes[0];
        int joyY = nc_bytes[1];

        printf("X: %4d\tjoyY = %4d\n", joyX, joyY);
    }
    return 0;
}

/*
 * This function takes in the array of GPIOs and 
 * assuming they have all been initialized,
 * turns all of the GPIOs on
 */
void lightUpAll(struct gpiohandle_request * req, int * gpios) {

    int rv;
    struct gpiohandle_data data;
    memset(&data,0,sizeof(struct gpiohandle_data));
    data.values[0]=1; // value to output (0 or 1)

    for(int i = 0; i < 14; i++) {

	rv = ioctl(req[i].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data); 

    }

}


void ledCtrlX(int value, struct gpiohandle_request * req) {
    int rv;
    struct gpiohandle_data data[7];
    for(int i = 0; i < 7; i++) 
        memset(&data[i],0,sizeof(struct gpiohandle_data));

    if(value < 40){
	    data[3].values[0]=1;
	    data[2].values[0]=1;
	    data[1].values[0]=1;
	    data[0].values[0]=1;
    }
    else if(value < 60){
	    data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
    }
    else if(value < 90){
	    data[3].values[0]=1;
            data[2].values[0]=1;
    }
    else if(value > 190){
	    data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
            data[6].values[0]=1;
    }
    else if(value > 150){
	    data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
    }
    else if(value > 120){
	    data[3].values[0]=1;
            data[4].values[0]=1;
    }
    else{
	    data[3].values[0]=1;	
    }
    for(int i = 0; i < 7; i++) {
	rv = ioctl(req[i].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data[i]);
    }	

}

void ledCtrlY(int value, struct gpiohandle_request * req) {

    int rv;
    struct gpiohandle_data data[7];
    for(int i = 0; i < 7; i++) 
        memset(&data[i],0,sizeof(struct gpiohandle_data));
    if(value < 45){
            data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
            data[0].values[0]=1;
    }
    else if(value < 60){
            data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
    }
    else if(value < 90){
            data[3].values[0]=1;
            data[2].values[0]=1;
    }
    else if(value > 190){
            data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
            data[6].values[0]=1;
    }
    else if(value > 165){
            data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
    }
    else if(value > 140){
            data[3].values[0]=1;
            data[4].values[0]=1;
    }
    else{
            data[3].values[0]=1;
    }
   
    for(int i = 0; i < 7; i++) {
        rv = ioctl(req[i+7].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data[i]);
    }

}


















