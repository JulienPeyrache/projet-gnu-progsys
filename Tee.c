#include <stdio.h>


int tee(char *file_title){
    
    FILE *fd = fopen(file_title, "w");
    fputs(stdout, fd);
    fclose(fd);
    return 0;
}