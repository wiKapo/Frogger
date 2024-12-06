#include <stdio.h>

#ifndef FILE_H
#define FILE_H

typedef struct {
  char arg[10];
  void** data;
} config_t;

config_t* read_config_file(const char* filename);

#endif //FILE_H
