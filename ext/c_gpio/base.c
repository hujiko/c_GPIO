#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "base.h"
#include "internal.h"
#include "mount.h"
#include "file_stuff.h"

VALUE GPIO_BASE_init(VALUE self, VALUE port) {
  struct GPIO *ptr;
  int gpio_port = NUM2INT(port);

  if (0 >= gpio_port)
    rb_raise(rb_eArgError, "GPIO Port can not be 0");

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  return self;
}

VALUE GPIO_BASE_get_value(VALUE self) {
  struct GPIO *ptr;
  // We have assign a default value here, because if the file is empty,
  // It will NOT get overwritten, and you will see a memdump
  char content[255] = "";

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_get_value(ptr->port, (char *) &content);

  return rb_str_new2(content);
}

VALUE GPIO_BASE_set_value(VALUE self, VALUE value) {
  struct GPIO *ptr;

  char *content = StringValueCStr(value);

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_value(ptr->port, content);

  return self;
}

VALUE GPIO_BASE_get_direction(VALUE self) {
  struct GPIO *ptr;
  // We have assign a default value here, because if the file is empty,
  // It will NOT get overwritten, and you will see a memdump
  char content[255] = "";

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_get_direction(ptr->port, (char *) &content);

  return rb_str_new2(content);
}

VALUE GPIO_BASE_set_direction(VALUE self, VALUE direction) {
  struct GPIO *ptr;
  char *content = StringValueCStr(direction);

  Data_Get_Struct(self, struct GPIO, ptr);

  GPIO_INTERNAL_set_direction(ptr->port, content);

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

    if (strcmp(oldVal, newVal) != 0 && strcmp(newVal, "0") == 0) {
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

    if (strcmp(oldVal, newVal) != 0 && strcmp(newVal, "1") == 0) {
      rb_funcall(block, rb_intern("call"), 0);
    }

    strcpy(oldVal, newVal);

    usleep(10 * 1000);
  }

  return self;
}
