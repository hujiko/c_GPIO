#ifndef S_GPIO
#define S_GPIO

struct GPIO {
  int port;
  void *ptr;
};

extern const char *GPIO_IN;
extern const char *GPIO_OUT;
extern const char *GPIO_HIGH;
extern const char *GPIO_LOW;

#endif

VALUE GPIO_BASE_init(VALUE self, VALUE port);
VALUE GPIO_BASE_get_value(VALUE self);
VALUE GPIO_BASE_set_value(VALUE self, VALUE value);
VALUE GPIO_BASE_get_direction(VALUE self);
VALUE GPIO_BASE_set_direction(VALUE self, VALUE direction);
VALUE GPIO_BASE_wait_for_high(VALUE self, VALUE block);
VALUE GPIO_BASE_wait_for_low(VALUE self, VALUE block);
