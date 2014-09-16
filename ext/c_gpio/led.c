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

  if (0 >= gpio_port)
    rb_raise(rb_eArgError, "GPIO Port can not be 0");

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  GPIO_INTERNAL_set_direction(ptr->port, (char *) "out");

  return self;
}

VALUE GPIO_LED_turn_on(VALUE self) {
  struct GPIO *ptr;
  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_value(ptr->port, (char *) "0");

  return self;
}

VALUE GPIO_LED_turn_off(VALUE self) {
  struct GPIO *ptr;
  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_value(ptr->port, (char *) "1");

  return self;
}
