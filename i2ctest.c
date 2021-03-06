#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <ioctl.h>  

#define I2C_SLAVE 0x0703
#define I2C_BUS 0x0720
#define I2C_READ 1
#define I2C_WRITE 0
#define I2C_BYTE 1
#define I2C_BYTE_DATA 2 

union i2c_data
{
  uint8_t  byte;
};

struct i2c_ioctl_args
{
  char read_write;
  uint8_t command;
  int size;
  union i2c_data *data;
};

int i2c_access (int fd, char rw, uint8_t command, int size, union i2c_data *data)
{
  struct i2c_ioctl_args args;

  args.read_write = rw;
  args.command    = command;
  args.size       = size;
  args.data       = data;
  return ioctl(fd, I2C_BUS, &args);
}

int write_i2c_register(int fd, int reg, int value)
{
  union i2c_data data ;

  data.byte = value ;
  return i2c_access(fd, I2C_WRITE, reg, I2C_BYTE_DATA, &data);
}

int read_i2c(int fd)
{
  union i2c_data data;

  if (i2c_access(fd, I2C_READ, 0, I2C_BYTE, &data))
    return -1 ;
  else
    return data.byte & 0xFF;
}

int setup_i2c(const char *device, int id)
{
  int fd = 0;

  if ((fd = open(device, O_RDWR)) < 0)
    return -1;

  if (ioctl(fd, I2C_SLAVE, id) < 0)
    return -1;

  return fd ;
}

int main(void) {
    
    int fd = setup_i2c("/dev/i2c-1", 0x52);
    if (fd < 0) {
        printf("Error setting up I2C: %d\n", errno);
        exit(0);
    }
    write_i2c_register(fd, 0x40, 0x00);
    usleep(500);

    int bytes[6];
    int i;
    while(1) {
    
        i2c_access(fd, I2C_WRITE, 0x00, I2C_BYTE, NULL) ;
        usleep(500);
    
        for (i=0; i<6; i++) {
            bytes[i] = read_i2c(fd);
        }

        int joyX = bytes[0];
        int joyY = bytes[1];

        printf("X: %4d\tjoyY = %4d\n", joyX, joyY);
    }
    return 0;
}
