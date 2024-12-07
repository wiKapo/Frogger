#include <stdio.h>

#ifndef FILE_H
#define FILE_H

typedef struct {
  char arg[10];
  void** data;
} config_t;

config_t* ReadConfigFile(const char* filename);
void SaveScore(const config_t *config, long score);

#endif //FILE_H
