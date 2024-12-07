#include "file.h"

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

void LoadDefaultConfig(const char *filename);

config_t *ReadConfigFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL || fgetc(file) == EOF) {
        fclose(file);
        LoadDefaultConfig(filename);
        file = fopen(filename, "r");
    } else
        rewind(file);

    config_t *config = malloc(sizeof(config_t) * 4);

    while (!feof(file)) {
        char arg[10];
        fscanf(file, "%s", arg);
        if (!strcmp(arg, "ARENA")) {
            int *v1 = malloc(sizeof(int)), *v2 = malloc(sizeof(int));
            strcpy(config[0].arg, arg);
            config[0].data = malloc(sizeof(int) * 2);
            fscanf(file, "%d %d", v1, v2);
            config[0].data[0] = v1;
            config[0].data[1] = v2;
        } else if (!strcmp(arg, "STATUS")) {
            char *v1 = malloc(sizeof(char *)), *v2 = malloc(sizeof(char *)), *v3 = malloc(sizeof(char *));
            strcpy(config[1].arg, arg);
            config[1].data = malloc(sizeof(char *) * 3);
            fscanf(file, "%s %s %s", v1, v2, v3);
            config[1].data[0] = v1;
            config[1].data[1] = v2;
            config[1].data[2] = v3;
        } else if (!strcmp(arg, "SEED")) {
            long *v1 = malloc(sizeof(long));
            strcpy(config[2].arg, arg);
            config[2].data = malloc(sizeof(long));
            fscanf(file, "%ld", v1);
            config[2].data[0] = v1;
        } else if (!strcmp(arg, "REC")) {
            int *v1 = malloc(sizeof(int));
            strcpy(config[3].arg, arg);
            config[3].data = malloc(sizeof(int));
            fscanf(file, "%d", v1);
            config[3].data[0] = v1;
        }
    }
    fclose(file);
    return config;
}

void LoadDefaultConfig(const char *filename) {
    FILE *file = fopen(filename, "w");
    fputs("ARENA 0 0\n", file);
    fputs("STATUS Name Surname 123456\n", file);
    fputs("SEED 1234567890\n", file);
    fputs("REC 0\n", file);
    fclose(file);
}

void SaveScore(const config_t *config, const long score) {
    FILE *file = fopen("scoreboard.txt", "a");
    fprintf(file, "%s - %02ld:%02ld.%02ld\n",
            (char *) config[1].data[0],
            score / 1000 / 60,
            (score / 1000) % 60,
            score % 1000);
    fclose(file);
}
