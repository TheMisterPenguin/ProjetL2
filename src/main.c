#include <commun.h>
#include <fonctions.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;

int main(int argc, char** argv)
{
    /* Initialisation simple */
    init();

    while(SDL_TRUE){
        jeu_event();
    }

    terminate();

    return 0;
}