#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include <fcntl.h>
#define BUFFER_SIZE 5

void pi_io_writeToMountFile(char *fileName, int content) {
  int fd;
  char buffer[BUFFER_SIZE];
  ssize_t bytes_written;

  fd = open(fileName, O_WRONLY);
  if (-1 == fd) {
    rb_raise(rb_eArgError, "Could not open GPIO connection - mounting GPIO pin not possible");
  }

  bytes_written = snprintf(buffer, BUFFER_SIZE, "%d", content);
  write(fd, buffer, bytes_written);

  close(fd);
}

void pi_io_mountPin(int pinNumber) {
  pi_io_writeToMountFile((char*)"/sys/class/gpio/export", pinNumber);
}

void pi_io_unmountPin(int pinNumber) {
  pi_io_writeToMountFile((char*)"/sys/class/gpio/unexport", pinNumber);
}
