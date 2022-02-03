/**
 * \file event.c
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier qui appelle différentes fonctions en fonction du déclenchement d'évenements
 * \version 0.1
 * \date 02/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */
#include <commun.h>

static void keyIn(SDL_KeyboardEvent * ev){
    printf("Touche enclenchée !\n");
}

void jeu_event(void){
    SDL_Event lastEvent;

    while(SDL_PollEvent(&lastEvent)){
        switch(lastEvent.type){
            case SDL_QUIT : game.stop();
            case SDL_KEYDOWN : game.getKeyboardInput((SDL_KeyboardEvent*)&lastEvent);

        }
    }
}

void init_event(void){

    game.getKeyboardInput = keyIn;
}