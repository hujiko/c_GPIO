#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "mount.h"
#include "base.h"
#include "led.h"
#include "internal.h"
#include "file_stuff.h"


VALUE GPIO_LED_init(VALUE self, VALUE port) {
  struct GPIO *ptr;
  int gpio_port = NUM2INT(port);

  GPIO_INTERNAL_validate_pin(gpio_port);

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  GPIO_INTERNAL_set_direction(ptr->port, (char *) GPIO_OUT);

  return self;
}

VALUE GPIO_LED_turn_on(VALUE self) {
  struct GPIO *ptr;
  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_value(ptr->port, (char *) GPIO_LOW);

  return self;
}

VALUE GPIO_LED_turn_off(VALUE self) {
  struct GPIO *ptr;
  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_value(ptr->port, (char *) GPIO_HIGH);

  return self;
}
