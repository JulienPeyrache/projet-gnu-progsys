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



int main(int a, char **commande1){
    char *commande = commande1[0];
    if((commande[0] == 'l') && (commande[1] =='s'))
    {
        char* subcom;

        memcpy(subcom, &commande[3], sizeof(commande)-3);
        ls(subcom);

    }

    else if((commande[0] == 'e') && (commande[1] == 'c') && (commande[2] == 'h') && (commande[3] == 'o'))
    {
        char* subcom;

        memcpy(subcom, &commande[5], sizeof(commande)-5);
        echo(subcom);
    }

    else if((commande[0] == 'r') && (commande[1] == 'm'))
    {
        char* subcom;

        memcpy(subcom, &commande[3], sizeof(commande)-3);
        rm(subcom);
    }

    else if((commande[0] == 't') && (commande[1] == 'e') && (commande[2] == 'e'))
    {
        char* subcom;

        memcpy(subcom, &commande[4], sizeof(commande)-4);
        tee(subcom);
    }
    return 0;
}
