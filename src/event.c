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
        case TOUCHE_BAS : perso_principal->orientation = SUD;break;
        case TOUCHE_HAUT : perso_principal->orientation = NORD;break;
        case TOUCHE_DROITE : perso_principal->orientation = EST;break;
        case TOUCHE_GAUCHE : perso_principal->orientation = OUEST;break;
    }
}

void jeu_event(void){
    SDL_Event lastEvent;

    while(SDL_PollEvent(&lastEvent)){
        switch(lastEvent.type){
            case SDL_QUIT : printf("Détection de la fermeture de la fenêtre\n");exit(EXIT_SUCCESS);
            case SDL_KEYDOWN : keyIn((SDL_KeyboardEvent*)&lastEvent);

        } 
    }
}

void init_event(void){

    game.getKeyboardInput = keyIn;
}