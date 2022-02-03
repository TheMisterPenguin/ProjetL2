#include <commun.h>
#include <stdio.h>

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;
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