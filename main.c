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

int grep (char *filtre, char option){
    //Lire ce qu'il y a dans stdin, filtrer les champs qui nous concernent avec le filtre et les réécrire dans stdout.
    char chaine[100];
    FILE* stdin_custom = fopen("/dev/stdin", "r");
    FILE* stdout_custom = fopen("/dev/stdout", "w");
    while(fgets(chaine, 100, stdin_custom) != NULL){
        if ((option=='v')&&(strstr(chaine, filtre) == NULL)){
            fprintf(stdout_custom, "%s", chaine);
            }
        else if ((option =='a')&&(strstr(chaine, filtre) != NULL)){
            fprintf(stdout_custom, "%s", chaine);
        }
        else if (option =='i'){
            void parcours(int i, char* chainecar){
                if (i<strlen(chainecar)){
                    char* chainecar_bis = chainecar;
                    if ((chainecar[i]<90)&&(chainecar[i]>64)){
                        chainecar_bis[i] = chainecar_bis[i]+32;
                    }
                    else if ((chainecar[i]<122)&&(chainecar[i]>96)){
                        chainecar_bis[i] = chainecar_bis[i]-32;
                    }
                    if (strstr(chainecar_bis, filtre) != NULL){
                        fprintf(stdout_custom, "%s", chainecar_bis);
                    }
                    parcours(i+1, chainecar_bis);
                    parcours(i+1, chainecar);
                }
            }
            if (strstr(chaine, filtre) != NULL){
                fprintf(stdout_custom, "%s", chaine);
            }
            parcours(0, chaine);
            }
        }
    fclose(stdin_custom);
    stdout = stdin_custom;
    fclose(stdout_custom);
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

int tee(char* filename){
    FILE *fp = fopen(filename, "w");
    FILE *stdout_bis = fopen("/dev/stdout", "w");
    char *line = malloc(sizeof(char) * 100);
    size_t len = 100;
    while(getline(&line, &len, stdin) != -1){
        fwrite(line, 1, 100, fp);
        fprintf(stdout_bis, "%s", line);
    }
    stdout = stdout_bis;
    fclose(fp);
    return 0;
}

int main()
{
    printf("%s", "Vous pouvez démarrer une ligne de commande. Tapez quit pour arrêter.");
    char* commande = "begin";
    while(strcmp(commande,"quit")!=0){
        printf("%s", "\n >");
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
            if (args.nbarg == 2)
            {
                grep(args.arg[1], 'a');
            }
            else if (args.nbarg == 3)
            {
                if (strcmp(args.arg[1], "-i")==0){
                    grep(args.arg[2],'i');}
                else if (strcmp(args.arg[1], "-v")==0){
                    grep(args.arg[2],'v');
                }
                else{
                    printf("%s", "Erreur: arguments incorrects");
                }
            }
            else {
                printf("%s", "Erreur: nombre d'arguments incorrect");
            }
        } else if(strcmp(args.arg[0], "kill") == 0){  

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

