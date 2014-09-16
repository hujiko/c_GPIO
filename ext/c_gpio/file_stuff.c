#ifndef __RUBY_H
  #define __RUBY_H
  #include <ruby.h>
#endif

#include <fcntl.h>

void GPIO_INTERNAL_getFileContent(char *filePath, char *dst) {
  FILE *file = fopen(filePath,"r");
  if(file == NULL) {
    rb_raise(rb_eArgError, "Could not open GPIO connection");
  }

  fscanf(file, "%s", dst);

  fclose(file);
}

void GPIO_INTERNAL_writeFileContent(char *filePath, char* content, size_t size) {
  int fd;

  fd = open(filePath, O_WRONLY);
  if (-1 == fd) {
    rb_raise(rb_eArgError, "Could not open File for writing");
  }

  write(fd, content, size);

  close(fd);
}
