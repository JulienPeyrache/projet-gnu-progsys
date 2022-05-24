#include <stdio.h>
#include <stdlib.h>

int ls(char* path){
    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        printf("ls: cannot open %s\n", path);
        return 1;
    }
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fp) != -1){
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}