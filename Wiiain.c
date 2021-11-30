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
void lightUpAll(struct gpiohandle_request * req, int * gpios);
void ledCtrlX(int value, struct gpiohandle_request * req);
void ledCtrlY(int value, struct gpiohandle_request * req);



int main(int argc, char **argv) {

    int rv;
    int result;
    int bytes_read;
    //int fd;
    //fd = open("/dev/gpiochip0",O_RDWR);


    // First half of array is for X axis, second half is for Y axis
    int gpiovals[14] = {17, 27, 22, 10, 9, 5, 6, 14, 15, 18, 23, 24, 25, 8};
    
    struct gpiohandle_request req[14];
    WiiPIOinit(gpiovals, req);

    //struct gpiohandle_data data;
    //memset(&data,0,sizeof(struct gpiohandle_data)); 
    //data.values[0]=1; // value to output (0 or 1)
    //wirtes first gpio in array high, 4 doesnt work?
    //rv=ioctl( req[0].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    

    // Nunchuck returns 6 bytes
    int nc_data[6];
    int i;
    unsigned char buffer = 0x00;
    // Initialize the Nunchuck's I2C settings
    int fd = Wii2c_setup();
    while(1) {
        
        result = write(fd, buffer, 1);
        usleep(500);

        for (i = 0; i < 6; i++) {
            bytes_read = read(fd, nc_data[i], 1);
        }

        int joyX = nc_data[0];
        int joyY = nc_data[1];

	//Write out to LEDs
	ledCtrlX(200, &req);
	ledCtrly(200, &req);
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

    switch(value){
        case(value < 40):
	    data[3].values[0]=1;
	    data[2].values[0]=1;
	    data[1].values[0]=1;
	    data[0].values[0]=1;
	    break;
	case(value < 60):
	    data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
	    break;
	case(value < 90):
	    data[3].values[0]=1;
            data[2].values[0]=1;
	    break;
	case(value > 190):
	    data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
            data[6].values[0]=1;
            break;
	case(value > 150):
	    data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
	    break;
	case(value > 120):
	    data[3].values[0]=1;
            data[4].values[0]=1;
	    break;
	default :
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

    switch(value){
        case(value < 40):
            data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
            data[0].values[0]=1;
            break;
        case(value < 60):
            data[3].values[0]=1;
            data[2].values[0]=1;
            data[1].values[0]=1;
            break;
        case(value < 90):
            data[3].values[0]=1;
            data[2].values[0]=1;
            break;
        case(value > 190):
            data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
            data[6].values[0]=1;
            break;
        case(value > 150):
            data[3].values[0]=1;
            data[4].values[0]=1;
            data[5].values[0]=1;
            break;
        case(value > 120):
            data[3].values[0]=1;
            data[4].values[0]=1;
            break;
        default :
            data[3].values[0]=1;
    }
    for(int i = 0; i < 7; i++) {
        rv = ioctl(req[i+7].fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data[i]);
    }

}


















