#include <sys/types.h>
#include <signal.h>
#include "Kill.h"

int kill_maison(pid_t pid, int sig){
    kill(pid, sig);
}