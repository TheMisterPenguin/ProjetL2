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
#include <personnage.h>

/**
 * \fn void keyDown(SDL_KeyboardEvent * ev)
 * \brief Fonction qui gère les événements quand une touche du clavier est pressée
 * \author Antoine Bruneau
 * \param SDL_KeyboardEvent* une structure contenant l'évênement
 */
static void keyDown(SDL_KeyboardEvent * ev){
    statut_t* statut = perso_principal->statut;

    if (ev->keysym.sym == SDLK_ESCAPE)
        exit(EXIT_SUCCESS);
    if(statut->action == RIEN || statut->action == CHARGER)
        switch(ev->keysym.sym){
            case TOUCHE_BAS : statut->orientation = SUD;  statut->en_mouvement = vrai; break;
            case TOUCHE_HAUT : statut->orientation = NORD;  statut->en_mouvement = vrai; break;
            case TOUCHE_DROITE : statut->orientation = EST;  statut->en_mouvement = vrai; break;
            case TOUCHE_GAUCHE : statut->orientation = OUEST;  statut->en_mouvement = vrai; break;
            case TOUCHE_TAB :
                SDL_ShowCursor(SDL_ENABLE);
                afficher_menu_pause();
                break;
            /*case TOUCHE_RETOUR : 
            if(menus == PAUSE){
                menus = JEU;
            } else {
                menus = PAUSE;
            }; break; A décommenter quand la texture menu pause sera faite*/
        }
}

/**
 * \fn void keyUp(SDL_KeyboardEvent * ev)
 * \brief Fonction qui gère les événements quand une touche du clavier est relachée
 * \author Antoine Bruneau
 * \param SDL_KeyboardEvent* une structure contenant l'évênement
 */
static void keyUp(SDL_KeyboardEvent * ev){
    t_direction orientation = perso_principal->statut->orientation;

    if( (ev->keysym.sym == TOUCHE_BAS && orientation == SUD) || (ev->keysym.sym == TOUCHE_DROITE && orientation == EST) || (ev->keysym.sym == TOUCHE_GAUCHE && orientation == OUEST) || (ev->keysym.sym == TOUCHE_HAUT && orientation == NORD) )
        perso_principal->statut->en_mouvement = faux;
}

/**
 * \fn void mouseButtonDown(SDL_MouseButtonEvent * ev)
 * \brief Fonction qui gère les événements quand un bouton de la souris est pressée
 * \author Antoine Bruneau
 * \param SDL_KeyboardEvent* une structure contenant l'évênement
 */
static void mouseButtonDown(SDL_MouseButtonEvent * ev){
    statut_t* statut = perso_principal->statut;

    if(statut->action == RIEN && statut->duree == 0){
        if(ev->button == SDL_BUTTON_LEFT){
            statut->action = ATTAQUE_OU_CHARGER;
            statut->duree = DUREE_ATTAQUE_OU_CHARGEE;
        }
        else if(ev->button == SDL_BUTTON_RIGHT && statut->bouclier_equipe){
            statut->action = BLOQUER;
            statut->duree = DUREE_BLOQUER;
        }
    }
}

/**
 * \fn void mouseButtonUp(SDL_MouseButtonEvent * ev)
 * \brief Fonction qui gère les événements quand un bouton de la souris est relachée
 * \author Antoine Bruneau
 * \param SDL_KeyboardEvent* une structure contenant l'évênement
 */
static void mouseButtonUp(SDL_MouseButtonEvent * ev){
    statut_t* statut = perso_principal->statut;

    if(ev->button == SDL_BUTTON_LEFT){
        if(statut->action == CHARGER){
            statut->action = ATTAQUE_CHARGEE;
            statut->en_mouvement = faux;
            statut->duree = DUREE_ATTAQUE_CHARGEE;
        }
        else if(statut->action == ATTAQUE_OU_CHARGER){
            statut->action = ATTAQUE;
            statut->duree = DUREE_ATTAQUE;
        }
    }
    else if( ev->button == SDL_BUTTON_RIGHT && (statut->action == BLOQUER || statut->action == CHARGER) )
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