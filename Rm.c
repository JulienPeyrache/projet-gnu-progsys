#include <unistd.h> 

int rm (const char *pathname){
    rmdir(pathname);
}