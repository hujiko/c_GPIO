#include <ruby.h>

#include "mount.h"
#include "led.h"
#include "button.h"
#include "base.h"
#include "pwm.h"
#include "file_stuff.h"


void GPIO_deallocate(void *pi_io) {
  // We can not unmount it here, because maybe another object is looking for the same pin?
  //pi_io_unmountPin(ptr->port);

  free(pi_io);
}

VALUE GPIO_allocate(VALUE self) {
  struct GPIO *pi_io = malloc(sizeof(struct GPIO));

  return Data_Wrap_Struct(self, NULL, GPIO_deallocate, pi_io);
}


//Ruby-Einstiegsmethode. Sie muss immer mit Init_ beginnen und auf den Namen der Extension enden. 
void Init_gpio(void) {
  VALUE GPIO_MODULE, GPIO_PWM, GPIO_LED, GPIO_BASE, GPIO_BUTTON;

  GPIO_MODULE = rb_const_get(rb_cObject, rb_intern("GPIO"));

  GPIO_LED = rb_define_class_under(GPIO_MODULE, "Led", rb_cObject);
  rb_define_alloc_func(GPIO_LED, GPIO_allocate);
  rb_define_method(GPIO_LED, "initialize", GPIO_LED_init,     1);
  rb_define_method(GPIO_LED, "turn_on!",   GPIO_LED_turn_on,  0);
  rb_define_method(GPIO_LED, "turn_off!",  GPIO_LED_turn_off, 0);


  GPIO_BASE = rb_define_class_under(GPIO_MODULE, "Base", rb_cObject);
  rb_define_alloc_func(GPIO_BASE, GPIO_allocate);
  rb_define_method(GPIO_BASE, "initialize",    GPIO_BASE_init,          1);
  rb_define_method(GPIO_BASE, "value",         GPIO_BASE_get_value,     0);
  rb_define_method(GPIO_BASE, "value=",        GPIO_BASE_set_value,     1);
  rb_define_method(GPIO_BASE, "direction",     GPIO_BASE_get_direction, 0);
  rb_define_method(GPIO_BASE, "direction=",    GPIO_BASE_set_direction, 1);
  rb_define_method(GPIO_BASE, "wait_for_high", GPIO_BASE_wait_for_high, 1);
  rb_define_method(GPIO_BASE, "wait_for_low",  GPIO_BASE_wait_for_low,  1);


  GPIO_BUTTON = rb_define_class_under(GPIO_MODULE, "Button", rb_cObject);
  rb_define_alloc_func(GPIO_BUTTON, GPIO_allocate);
  rb_define_method(GPIO_BUTTON, "initialize",           GPIO_BUTTON_init,                  1);
  rb_define_method(GPIO_BUTTON, "pressed?",             GPIO_BUTTON_is_pressed,            0);
  // Yes e want to delegate to the GPIO_BASE here
  rb_define_method(GPIO_BUTTON, "wait_for_high",        GPIO_BASE_wait_for_high,           1);
  rb_define_method(GPIO_BUTTON, "wait_for_low",         GPIO_BASE_wait_for_low,            1);

  GPIO_PWM = rb_define_class_under(GPIO_MODULE, "Pwm", rb_cObject);
  rb_define_alloc_func(GPIO_PWM, GPIO_allocate);
  rb_define_method(GPIO_PWM, "initialize", GPIO_PWM_init,     1);
  rb_define_method(GPIO_PWM, "move_to",    GPIO_PWM_position, 1);
}
