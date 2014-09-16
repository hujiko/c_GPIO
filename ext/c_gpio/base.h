#ifndef S_GPIO
#define S_GPIO

struct GPIO {
  int port;
  VALUE onLowCallback;
  VALUE onHighCallback;
  pthread_t watchThread;
  int threadRunning;
  void *ptr;
};

#endif

VALUE GPIO_BASE_init(VALUE self, VALUE port);
VALUE GPIO_BASE_get_value(VALUE self);
VALUE GPIO_BASE_set_value(VALUE self, VALUE value);
VALUE GPIO_BASE_get_direction(VALUE self);
VALUE GPIO_BASE_set_direction(VALUE self, VALUE direction);
