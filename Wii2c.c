#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include <wiringPi.h>
//#include <wiringPiI2C.h>
#include <errno.h>

int Wii2c_setup(void) 
{
    int NUNCHUCK_DEVICE = 0x52;
    int fd, result;
    unsigned char buffer[100] = {0};
    
    // Open i2c bus
    fd = open("/dev/i2c-1", O_RDWR) 
    if (fd < 0) {
        printf("Error setting up I2C: %d\n", errno);
        exit(-1);
    }
    
    // Set device address
    result = ioctl(fd, I2C_SLAVE, 0x70);
    
    //buffer[0x40] = 0x00;
    result = write(fd, buffer, 100);    
    if (result == 0) {
        printf("Error writing to device: %d\n", errno);
        exit(-2);
    }

    usleep(500);

    return fd;
    }
}
