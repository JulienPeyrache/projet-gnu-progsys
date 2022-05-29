#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Echo.h"
#include "Cat.h"
#include "Tee.h"
#include "Rm.h"
#include "Mkdir.h"
#include "Ls.h"
#include "Mv.h"
#include "Grep.h"
#include "Kill.h"



int main()
{
    printf("%s", "Vous pouvez démarrer une ligne de commande:");
    char *commande;
    scanf(commande);
    while(commande != "quit")
    {
    char verif;
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
        char subcom;

        memcpy(subcom, &commande[4], sizeof(commande)-4);
        cat(subcom);
    }

    else if(memcpy(verif, &commande[0], 5) == "kill ")
    {
        char subcom;
    }
    }
    return 0;
}

