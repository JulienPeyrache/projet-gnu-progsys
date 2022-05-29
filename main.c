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
    char *commande;
    scanf("%s", commande);
    while(commande != "quit")
    {
    char* verif;
    if(strcmp(&commande, "ls ", 3) == 0)
    {
        char* subcom;

        memcpy(subcom, &commande[3], strlen(commande)-3);
        ls(subcom);

    }


    else if(strcmp(&commande, "echo ", 5) == 0)
    {
        char* subcom;

        memcpy(subcom, &commande[5], strlen(commande)-5);
        echo(subcom);
    }

    else if(strcmp(&commande, "rm ", 3) == 0)
    {
        char* subcom;

        memcpy(subcom, &commande[3], strlen(commande)-3);
        rm(subcom);
    }

    else if(strcmp(&commande, "tee ", 4) == 0)
    {
        char* subcom;

        memcpy(subcom, &commande[4], strlen(commande)-4);
        tee(subcom);
    }

    else if(strcmp(&commande, "cat ", 4) == 0)
    {
        char* subcom;

        memcpy(subcom, &commande[4], strlen(commande)-4);
        cat(subcom);
    }

    else if(strcmp(&commande, "kill ", 5) == 0)
    {
        char* subcom;

        if (&commande[5] != "-")
            {
                memcpy(subcom, &commande[5], strlen(commande) - 5);
                kill(subcom, 15);
            }
    }

    else if(strcmp(&commande, "mv ", 3) == 0)
    {
        int espace;
        for (int i = 4; i < strlen(commande); i++)
        {
            if(strcmp(&commande[i], " ", 1) == 0)
            {
                espace = i
            }
        }


        char* subcom1;
        char* subcom2;

        memcpy(subcom1, &commande[3], espace - 3);
        memcpy(subcom2, &commande[espace + 1], strlen(commande) - espace - 1);
        mv(subcom1, subcom2);
    }
    }
    return 0;
}

