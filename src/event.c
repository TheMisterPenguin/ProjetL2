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
#include <event.h>

static void keyIn(SDL_KeyboardEvent * ev){

    switch(ev->keysym.sym){
        case TOUCHE_BAS : printf("On se déplace vers le bas\n");break;
        case TOUCHE_HAUT : printf("On se déplace vers le haut\n");break;
        case TOUCHE_DROITE : printf("On se déplace vers la droite\n");break;
        case TOUCHE_GAUCHE : printf("On se déplace vers la gauche\n");break;
        default : printf("Touche enclenchée !\n");
    }
    
}

void jeu_event(void){
    SDL_Event lastEvent;

    while(SDL_PollEvent(&lastEvent)){
        switch(lastEvent.type){
            case SDL_QUIT : printf("Détection de la fermeture de la fenêtre\n");exit(EXIT_SUCCESS);
            case SDL_KEYDOWN : game.getKeyboardInput((SDL_KeyboardEvent*)&lastEvent);

        }
    }
}

void init_event(void){

    game.getKeyboardInput = keyIn;
}