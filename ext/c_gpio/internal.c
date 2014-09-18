#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "file_stuff.h"
#define FILE_NAME_BUFFER_SIZE 50

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
