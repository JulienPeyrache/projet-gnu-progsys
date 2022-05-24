#include <stdio.h>
#include <stdlib.h>

int mv (char* source, char* destination){
    rename(source, destination);
}