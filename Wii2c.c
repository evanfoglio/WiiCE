#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> 
#include "Wii2c.h"

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
