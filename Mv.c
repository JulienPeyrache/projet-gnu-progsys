#include <stdio.h>
#include <stdlib.h>
#include "Mv.h"
int mv (char* source, char* destination){
    rename(source, destination);
}