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


static void keyDown(SDL_KeyboardEvent * ev){
    perso_principal->statut->en_mouvement = vrai;
    switch(ev->keysym.sym){
        case TOUCHE_BAS : perso_principal->statut->orientation = SUD;break;
        case TOUCHE_HAUT : perso_principal->statut->orientation = NORD;break;
        case TOUCHE_DROITE : perso_principal->statut->orientation = EST;break;
        case TOUCHE_GAUCHE : perso_principal->statut->orientation = OUEST;break;
        case SDLK_ESCAPE : exit(EXIT_SUCCESS);
    }
}

static void keyUp(SDL_KeyboardEvent * ev){
    if(ev->keysym.sym == TOUCHE_BAS || ev->keysym.sym == TOUCHE_DROITE || ev->keysym.sym == TOUCHE_GAUCHE || ev->keysym.sym == TOUCHE_HAUT)
        perso_principal->statut->en_mouvement = faux;
}

static void mouseButtonDown(SDL_MouseButtonEvent * ev){
    if(ev->button == SDL_BUTTON_LEFT && perso_principal->statut->action == RIEN){
        perso_principal->statut->action = ATTAQUE_OU_CHARGER;
        perso_principal->statut->duree = 30;
    }
    if(ev->button == SDL_BUTTON_RIGHT && perso_principal->statut->bouclier_equipe && perso_principal->statut->action == RIEN){
        perso_principal->statut->action = BLOQUER;
        perso_principal->statut->duree = 50;
    }
        
}

static void mouseButtonUp(SDL_MouseButtonEvent * ev){
    if(ev->button == SDL_BUTTON_LEFT)
        if(perso_principal->statut->action == CHARGER){
            perso_principal->statut->action = ATTAQUE_CHARGER;
            perso_principal->statut->duree = 150;
        }
        else if(perso_principal->statut->action == ATTAQUE)
            perso_principal->statut->action = RIEN;

    if(ev->button == SDL_BUTTON_RIGHT && perso_principal->statut->action == BLOQUER)
        perso_principal->statut->action = RIEN;    
}

void jeu_event(void){
    SDL_Event lastEvent;

    while(SDL_PollEvent(&lastEvent)){
        switch(lastEvent.type){
            case SDL_QUIT : printf("Détection de la fermeture de la fenêtre\n");exit(EXIT_SUCCESS);
            case SDL_KEYDOWN : keyDown((SDL_KeyboardEvent*)&lastEvent.key); break;
            case SDL_KEYUP : keyUp((SDL_KeyboardEvent*)&lastEvent.key); break;
            case SDL_MOUSEBUTTONDOWN : mouseButtonDown((SDL_MouseButtonEvent*)&lastEvent.button); break;
            case SDL_MOUSEBUTTONUP : mouseButtonUp((SDL_MouseButtonEvent*)&lastEvent.button); break;
        } 
    }
}

bool logo_passer(void){
    SDL_Event lastEvent;

    while (SDL_PollEvent(&lastEvent))
    {
        switch (lastEvent.type){
        case SDL_QUIT:
            printf("Détection de la fermeture de la fenêtre\n");
            exit(EXIT_SUCCESS);
        case SDL_KEYDOWN:
            return vrai;
        }
    }

    return faux;
}