#include <commun.h>
#include <fonctions.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;
t_game game;



int main(int argc, char** argv)
{
    game.init = init;
    /* Initialisation simple */
    
    game.init();

    while(SDL_TRUE){
        jeu_event();
    }

}