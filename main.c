#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

int cat(char* file_title){
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
    return 0;
}

int grep (char *filtre){
    //Lire ce qu'il y a dans stdin, filtrer les champs qui nous concernent avec le filtre et les réécrire dans stdout.
    char chaine[100];
    FILE* stdin_custom = fopen("/dev/stdin", "r");
    FILE* stdout_custom = fopen("/dev/stdout", "w");


    while (fgets(chaine, 100, stdin_custom) != NULL){
        if (strstr(chaine, filtre) != NULL){
            printf("%s", chaine);
        }
    }
    return 0;
}

int kill_maison(pid_t pid, int sig){
    kill(pid, sig);
    return 0;
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
    return 0;
}

int mv (char* source, char* destination){
    rename(source, destination);
    return 0;
}

struct arguments{
    char** arg;
    int nbarg;
};
typedef struct arguments arguments;

char* slice(char* chaine, int longueur){
    char* chaine_finale = malloc(longueur);
    strncpy(chaine_finale, chaine, longueur);
    return chaine_finale;
}

arguments decomp (char* commande){
    arguments args;
    args.nbarg = 0;
    args.arg = malloc(sizeof(char*));
    char* tmp = malloc(sizeof(char*));
    strcpy(tmp, commande);
    char* token = strtok(tmp, " ");
    while(token != NULL){
        args.nbarg++;
        args.arg = realloc(args.arg, args.nbarg * sizeof(char*));
        args.arg[args.nbarg - 1] = malloc(sizeof(char) * strlen(token));
        strcpy(args.arg[args.nbarg - 1], token);
        token = strtok(NULL, " ");
    }
    return args;
}

int rm (const char *pathname){
    rmdir(pathname);
    return 0;
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
    char* commande = "begin";
    while(strcmp(commande,"quit")!=0){
        printf("%s", ">");
        scanf("%s", commande);
        arguments args = decomp(commande);
        if(strcmp(args.arg[0], "ls") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                ls(args.arg[1]);
            }
        }
        else if(strcmp(args.arg[0], "mkdir") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                mkdir_maison(args.arg[1], 0777);
            }
        }
        else if(strcmp(args.arg[0], "mv") == 0){
            if (args.nbarg != 3)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                mv(args.arg[1], args.arg[2]);
            }
        }
        else if(strcmp(args.arg[0], "rm") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                rm(args.arg[1]);
            }
        }
        else if(strcmp(args.arg[0], "tee") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                tee(args.arg[1]);
            }
        }
        else if(strcmp(args.arg[0], "cat") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                cat(args.arg[1]);
            }
        } else if(strcmp(args.arg[0], "echo") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                echo(args.arg[1]);
            }
        } else if(strcmp(args.arg[0], "grep") == 0){
            if (args.nbarg != 2)
            {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
            else
            {
                grep(args.arg[1]);
            }
        } else if(strcmp(args.arg[0], "kill") == 0){    //kill(pid, sig)
            if ((args.nbarg == 4)&&(strcmp(args.arg[1], "-s") == 0)){
                kill_maison(atoi(args.arg[3]), atoi(args.arg[2]));
            } else if (args.nbarg == 3) {
                kill_maison(atoi(args.arg[2]), 15);
            } else {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
        }
        else{
            printf("%s", "Erreur: commande inconnue");
        }
    }
    return 0;
}

