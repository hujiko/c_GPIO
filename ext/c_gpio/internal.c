#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "file_stuff.h"
#define FILE_NAME_BUFFER_SIZE 50

void GPIO_INTERNAL_validate_pin(int pinNumber) {
  // Currently the rPI does only have GPIO Pins  from 2 to 27
  if(pinNumber < 2 || pinNumber > 27) {
    rb_raise(rb_eArgError, "The GPIO Port has to be between 2 and 27");
  }
}

void GPIO_INTERNAL_get_value(int pinNumber, char *dst) {
  char filename[FILE_NAME_BUFFER_SIZE];

  sprintf(filename, "/sys/class/gpio/gpio%d/value", pinNumber);

  GPIO_INTERNAL_getFileContent(filename, dst);
}

void GPIO_INTERNAL_set_value(int pinNumber, char* content) {
  char filename[FILE_NAME_BUFFER_SIZE];

  sprintf(filename, "/sys/class/gpio/gpio%d/value", pinNumber);

  GPIO_INTERNAL_writeFileContent(filename, content, strlen(content));
}

void GPIO_INTERNAL_get_direction(int pinNumber, char *dst) {
  char filename[FILE_NAME_BUFFER_SIZE];

  sprintf(filename, "/sys/class/gpio/gpio%d/direction", pinNumber);

  GPIO_INTERNAL_getFileContent(filename, dst);
}

void GPIO_INTERNAL_set_direction(int pinNumber, char *content) {
  char filename[FILE_NAME_BUFFER_SIZE];

  sprintf(filename, "/sys/class/gpio/gpio%d/direction", pinNumber);

  GPIO_INTERNAL_writeFileContent(filename, content, strlen(content));
}
