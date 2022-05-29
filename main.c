#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/stat.h>
#include <signal.h>

int cat(char *file_title){
    FILE *fd = fopen(file_title, "r");
    char c;
    while((c = fgetc(fd)) != EOF){
        putchar(c);
    }
    fclose(fd);
    return 0;
}


int echo(char* blabla){
    printf("%s", blabla);
}

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

int kill_maison(pid_t pid, int sig){
    kill(pid, sig);
}

int ls(char* path){
    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        printf("ls: cannot open %s\n", path);
        return 1;
    }
    char* line = NULL;
    size_t len = 0;
    while(getline(&line, &len, fp) != -1){
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}

int mkdir_maison(const char *pathname, mode_t mode){
    mkdir(pathname, mode);
}

int mv (char* source, char* destination){
    rename(source, destination);
}

int rm (const char *pathname){
    rmdir(pathname);
}

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

int main()
{
    printf("%s", "Vous pouvez démarrer une ligne de commande:");
    char *commande = "begin";
    
    while(commande != "quit")
    {
    scanf("%s", commande);
    char* verif;
    if(memcpy(verif, &commande[0], 3) == "ls ")
    {
        char* subcom;

        memcpy(subcom, &commande[3], sizeof(commande)-3);
        ls(subcom);

    }


    else if(memcpy(verif, &commande[0], 5) == "echo ")
    {
        char* subcom;

        memcpy(subcom, &commande[5], sizeof(commande)-5);
        echo(subcom);
    }

    else if(memcpy(verif, &commande[0], 3) == "rm ")
    {
        char* subcom;

        memcpy(subcom, &commande[3], sizeof(commande)-3);
        rm(subcom);
    }

    else if(memcpy(verif, &commande[0], 4) == "tee ")
    {
        char* subcom;

        memcpy(subcom, &commande[4], sizeof(commande)-4);
        tee(subcom);
    }

    else if(memcpy(verif, &commande[0], 4) == "cat ")
    {
        char* subcom;

        memcpy(subcom, &commande[4], sizeof(commande)-4);
        cat(subcom);
    }

    else if(memcpy(verif, &commande[0], 5) == "kill ")
    {
        char* subcom;
    }
    }
    return 0;
}

