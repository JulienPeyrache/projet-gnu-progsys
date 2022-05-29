#include <stdio.h>
#include <stdlib.h>
#include "Cat.h"

int cat(char *file_title){
    FILE *fd = fopen(file_title, "r");
    char c;
    while((c = fgetc(fd)) != EOF){
        putchar(c);
    }
    fclose(fd);
    return 0;
}