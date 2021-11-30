#ifndef __WII2C_H_
#define __WII2C_H_

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

int i2c_access (int, char, uint8_t, int, union i2c_data *);
int write_i2c_register(int, int, int);
int read_i2c(int);
int setup_i2c(const char *, int);

#endif

