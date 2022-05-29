#include <stdio.h>
#include <stdlib.h>
#include "Grep.h"

int grep (char *filtre){
    //Lire ce qu'il y a dans stdin, filtrer les champs qui nous concernent avec le filtre et les réécrire dans stdout.
    char chaine[100];
    
    while (fgets(chaine, 100, stdin) != NULL){
        if (strstr(chaine, filtre) != NULL){
            printf("%s", chaine);
        }
    }
    return 0;
}