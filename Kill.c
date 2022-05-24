#include <sys/types.h>
#include <signal.h>

int kill_maison(pid_t pid, int sig){
    kill(pid, sig);
}