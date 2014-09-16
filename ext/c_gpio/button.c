#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "mount.h"
#include "base.h"
#include "internal.h"
#include "file_stuff.h"

#include <pthread.h>


VALUE GPIO_BUTTON_init(VALUE self, VALUE port) {
  struct GPIO *ptr;
  int gpio_port = NUM2INT(port);

  if (0 >= gpio_port)
    rb_raise(rb_eArgError, "GPIO Port can not be 0");

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  GPIO_INTERNAL_set_direction(ptr->port, (char *) "in");

  return self;
}

VALUE GPIO_BUTTON_is_pressed(VALUE self) {
  struct GPIO *ptr;
  char content[20];

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_get_value(ptr->port, (char *) &content);

  if( strcmp((char *) "0", content) ) {
    return Qtrue;
  } else {
    return Qfalse;
  }
}
