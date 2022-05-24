#include <stdio.h>
#include <stdlib.h>

int tee(char *filename){
    //read stdin, put it in a file and in stdout
    FILE *fp = fopen(filename, "w");
    FILE *stdin_bis = fopen("/dev/stdin", "r");
    FILE *stdout_bis = fopen("/dev/stdout", "w");
    char *line = NULL;
    size_t len = 0;
    while(getline(&line, &len, stdin) != -1){
        fprintf(fp, "%s", line);
        fprintf(stdout_bis, "%s", line);
    }
    return 0;
}