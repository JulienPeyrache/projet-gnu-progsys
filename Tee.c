#include <stdio.h>


int tee(char *file_title){
    //Lire ce qu'il y a dans stdin, le réécrire dans stdout et l'écrire dans le fichier.
    
    FILE *fd = fopen(file_title, "w");
    fputs(stdout, fd);
    fclose(fd);
    return 0;
}