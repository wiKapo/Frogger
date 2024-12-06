#include "file.h"

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

config_t* read_config_file(const char* filename){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
        endwin();
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    config_t *config = malloc(sizeof(config_t) * 4);

    char arg[10];
    while(!feof(file)){
         fscanf(file, "%s", arg);
         if (!strcmp(arg, "ARENA")){
             int *v1 = malloc(sizeof(int)), *v2 = malloc(sizeof(int));

             config[0].data = malloc(sizeof(int) * 2);
             fscanf(file, "%d %d", v1, v2);
             config[0].data[0] = v1;
             config[0].data[1] = v2;
         } else if (!strcmp(arg, "STATUS")){
             char *v1 = malloc(sizeof(char*)), *v2 = malloc(sizeof(char*)), *v3 = malloc(sizeof(char*));

             config[1].data = malloc(sizeof(char*) * 3);
             fscanf(file, "%s %s %s", v1, v2, v3);
             config[1].data[0] = v1;
             config[1].data[1] = v2;
             config[1].data[2] = v3;
         }
    }
    fclose(file);
    return config;
}

//
// Created by wikapo on 12/6/24.
//
