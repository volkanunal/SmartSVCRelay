#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define baudrate 9600

#include "RGKR.h"


int open_serial_port(const char * device, uint32_t baud_rate)
{
  int fd = open(device, O_RDWR | O_NOCTTY);
  if (fd == -1)
  {
      fprintf(stderr,"failed to open com port \n");
    perror(device);
    return -1;
  }
 
  
  int result = tcflush(fd, TCIOFLUSH);

  if (result)
  {
    perror("tcflush failed");  
  }
 
  struct termios options;
  result = tcgetattr(fd, &options);
  if (result)
  {
    perror("tcgetattr failed");
    close(fd);
    return -1;
  }
 
  options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
  options.c_oflag &= ~(ONLCR | OCRNL);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
 
  options.c_cc[VTIME] = 1;
  options.c_cc[VMIN] = 0;
 
  switch (baud_rate)
  {
  case 4800:   cfsetospeed(&options, B4800);   break;
  case 9600:   cfsetospeed(&options, B9600);   break;
  case 19200:  cfsetospeed(&options, B19200);  break;
  case 38400:  cfsetospeed(&options, B38400);  break;
  case 115200: cfsetospeed(&options, B115200); break;
  default:
    fprintf(stderr, "warning: baud rate %u is not supported, using 9600.\n",
      baud_rate);
    cfsetospeed(&options, B9600);
    break;
  }

  cfsetispeed(&options, cfgetospeed(&options));
 
  result = tcsetattr(fd, TCSANOW, &options);
  if (result)
  {
    perror("tcsetattr failed");
    close(fd);
    return -1;
  }
 
  return fd;
}
 
int write_port(int fd, uint8_t * buffer, size_t size)
{
  ssize_t result = write(fd, buffer, size);
  if (result != (ssize_t)size)
  {
    perror("failed to write to port");
    return -1;
  }
  return 0;
}
 

ssize_t read_port(int fd, uint8_t * buffer, size_t size)
{
  RGKR_Uart_Params.idx = 0;

  while (RGKR_Uart_Params.idx < size)
  {
    ssize_t r = read(fd, buffer + RGKR_Uart_Params.idx, size - RGKR_Uart_Params.idx);
    
   // printf("Coming Data = %02x \r\n", buffer[RGKR_Uart_Params.idx]);

    if(buffer[RGKR_Uart_Params.idx] == 0x42) break;

    if (r < 0)
    {
      perror("failed to read from port");
      return -1;
    }

    RGKR_Uart_Params.idx++;
  }

  return RGKR_Uart_Params.idx;
}