#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include "mount.h"
#include "base.h"
#include "internal.h"
#include "file_stuff.h"
#include "pwm.h"

#include <pthread.h>

VALUE GPIO_PWM_init(VALUE self, VALUE port) {
  struct GPIO *ptr;
  int gpio_port = NUM2INT(port);

  GPIO_INTERNAL_validate_pin(gpio_port);

  pi_io_mountPin(gpio_port);

  Data_Get_Struct(self, struct GPIO, ptr);

  ptr->port = gpio_port;

  GPIO_INTERNAL_set_direction(ptr->port, (char *) GPIO_OUT);

  return self;
}

VALUE GPIO_PWM_position(VALUE self, VALUE vPosition) {
  struct GPIO *ptr;
  Data_Get_Struct(self, struct GPIO, ptr);

  int position = NUM2INT(vPosition);

  if(position < 0 || position > 200) {
    rb_raise(rb_eArgError, "Argument must be between 0 and 200");
  }

  // Position 0 is not 0 but 30, and max is not 200 but 230
  // Just for interface reasons, we accept values from 0 to 200
  // But internally we have to add 30
  ptr->pwmPosition = position + 30;

  pthread_t myThread;

  pthread_create(&myThread, NULL, &positioner, ptr);

  return self;
}


void *positioner(void *ptr) {

  struct GPIO *gpio = (struct GPIO *) ptr;

  float duration = 40.0;
  float uptime = gpio->pwmPosition / 100.0;

  // We can not use while(1) atm, because this whole thing is that unprecise, that the stepper engine will start jittering
  // while(1) {
  //   GPIO_INTERNAL_set_value(gpio->port, (char *) GPIO_HIGH);
  //   usleep(uptime * 1000);
  //   GPIO_INTERNAL_set_value(gpio->port, (char *) GPIO_LOW);
  //   usleep((duration - uptime) * 1000);
  // }

  int i;
  for (i = 0; i < 35; i++) {
    GPIO_INTERNAL_set_value(gpio->port, (char *) GPIO_HIGH);

    usleep(uptime * 1000);

    GPIO_INTERNAL_set_value(gpio->port, (char *) GPIO_LOW);
    usleep((duration - uptime) * 1000);
  }

  return NULL;
}
