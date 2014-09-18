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

  char mountedPinDirection[40];

  sprintf(mountedPinDirection, "/sys/class/gpio/gpio%d/direction", pinNumber);

  int i;
  for (i = 0; i < 10; i++) {
    if( access( mountedPinDirection, W_OK ) != -1 ) {
      // The pin is mounted, so we can return
      return;
    } else {
      // The pin seems to be not mounted yet.
      // so we wait 20ms and check again
      usleep(20 * 1000);
    }
  }

  // If we reach this part, mounting in time was not possible
  rb_raise(rb_eSystemCallError, "Was not able to mount GPIO pin");
}

void pi_io_unmountPin(int pinNumber) {
  pi_io_writeToMountFile((char*)"/sys/class/gpio/unexport", pinNumber);
}
