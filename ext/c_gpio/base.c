#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "base.h"
#include "internal.h"
#include "mount.h"
#include "file_stuff.h"

const char *GPIO_IN   = "in";
const char *GPIO_OUT  = "out";
const char *GPIO_HIGH = "1";
const char *GPIO_LOW  = "0";

VALUE GPIO_BASE_init(VALUE self, VALUE port) {
  struct GPIO *ptr;
  int gpio_port = NUM2INT(port);

  GPIO_INTERNAL_validate_pin(gpio_port);

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  return self;
}

VALUE GPIO_BASE_get_value(VALUE self) {
  struct GPIO *ptr;
  // We have assign a default value here, because if the file is empty,
  // It will NOT get overwritten, and you will see a memdump
  char content[2] = "";

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_get_value(ptr->port, (char *) &content);

  if(strcmp(GPIO_HIGH, content) == 0) {
    return ID2SYM(rb_intern("high"));
  } else if(strcmp(GPIO_LOW, content) == 0) {
    return ID2SYM(rb_intern("low"));
  }

  rb_raise(rb_eRuntimeError, "Value was neither HIGH nor LOW");
}

VALUE GPIO_BASE_set_value(VALUE self, VALUE value) {
  struct GPIO *ptr;

  Data_Get_Struct(self, struct GPIO, ptr);

  if(SYM2ID(value) == rb_intern("low")) {
    GPIO_INTERNAL_set_value(ptr->port, (char *) GPIO_LOW);
  } else if(SYM2ID(value) == rb_intern("high")) {
    GPIO_INTERNAL_set_value(ptr->port, (char *) GPIO_HIGH);
  } else {
    rb_raise(rb_eArgError, "Only :low and :high are valid input");
  }

  return self;
}

VALUE GPIO_BASE_get_direction(VALUE self) {
  struct GPIO *ptr;
  // We have assign a default value here, because if the file is empty,
  // It will NOT get overwritten, and you will see a memdump
  char content[4] = "";

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_get_direction(ptr->port, (char *) &content);

  if(strcmp(GPIO_IN, content) == 0) {
    return ID2SYM(rb_intern("in"));
  } else if(strcmp(GPIO_OUT, content) == 0) {
    return ID2SYM(rb_intern("out"));
  }

  rb_raise(rb_eRuntimeError, "Direction was neither IN nor OUT");
}

VALUE GPIO_BASE_set_direction(VALUE self, VALUE direction) {
  struct GPIO *ptr;

  Data_Get_Struct(self, struct GPIO, ptr);

  if(SYM2ID(direction) == rb_intern("in")) {
    GPIO_INTERNAL_set_direction(ptr->port, (char *) GPIO_IN);
  } else if(SYM2ID(direction) == rb_intern("out")) {
    GPIO_INTERNAL_set_direction(ptr->port, (char *) GPIO_OUT);
  } else {
    rb_raise(rb_eArgError, "Only :in and :out are valid input");
  }

  return self;
}

VALUE GPIO_BASE_wait_for_low(VALUE self, VALUE block) {
  struct GPIO *gpio;
  char oldVal[20] = "1";
  char newVal[20] = "1";

  Data_Get_Struct(self, struct GPIO, gpio);

  while(1) {
    rb_thread_schedule();

    GPIO_INTERNAL_get_value(gpio->port, (char *) &newVal);

    if (strcmp(oldVal, newVal) != 0 && strcmp(newVal, (char *) GPIO_LOW) == 0) {
      rb_funcall(block, rb_intern("call"), 0);
    }

    strcpy(oldVal, newVal);

    usleep(10 * 1000);
  }

  return self;
}

VALUE GPIO_BASE_wait_for_high(VALUE self, VALUE block) {
  struct GPIO *gpio;
  char oldVal[20] = "1";
  char newVal[20] = "1";

  Data_Get_Struct(self, struct GPIO, gpio);

  while(1) {
    rb_thread_schedule();

    GPIO_INTERNAL_get_value(gpio->port, (char *) &newVal);

    if (strcmp(oldVal, newVal) != 0 && strcmp(newVal, (char *) GPIO_HIGH) == 0) {
      rb_funcall(block, rb_intern("call"), 0);
    }

    strcpy(oldVal, newVal);

    usleep(10 * 1000);
  }

  return self;
}
