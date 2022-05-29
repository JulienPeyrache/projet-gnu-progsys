#include <unistd.h> 
#include "Rm.h"
int rm (const char *pathname){
    rmdir(pathname);
}