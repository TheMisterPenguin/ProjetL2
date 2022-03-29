#include <commun.h>
#include <event.h>
#include <personnage.h>
#include <affichage.h>

/**
 * \file event.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fonctions de gestion des événements du jeu
 * \version 0.1
 * \date 02/02/2022
 * \copyright Copyright (c) 2022
 */

/**
 * \fn void keyDown(SDL_KeyboardEvent * ev, joueur_t ** joueurs)
 * \brief Fonction qui gère les événements quand une touche du clavier est pressée par un joueur
 * \author Antoine Bruneau
 * \param ev Structure contenant l'événement
 * \param joueurs Joueurs pouvant provoquer l'événement
 */
static void keyDown(SDL_KeyboardEvent * ev, joueur_t ** joueurs){
    joueur_t * joueur = joueurs[0];
    statut_t* statut = joueur->statut;

    if (ev->keysym.sym == SDLK_ESCAPE){ /* On affiche le menu de pause si on appuye sur echap */
        SDL_ShowCursor(SDL_ENABLE);
        afficher_menu_pause(joueur);
        SDL_ShowCursor(SDL_DISABLE);
    }

    int flags;

    if(statut->action == RIEN || statut->action == CHARGER)
        switch(ev->keysym.sym){
            case SDLK_DOWN :
            case TOUCHE_BAS : statut->orientation = SUD;  statut->en_mouvement = vrai; break;
            case SDLK_UP :
            case TOUCHE_HAUT : statut->orientation = NORD;  statut->en_mouvement = vrai; break;
            case SDLK_RIGHT :
            case TOUCHE_DROITE : statut->orientation = EST;  statut->en_mouvement = vrai; break;
            case SDLK_LEFT :
            case TOUCHE_GAUCHE : statut->orientation = OUEST;  statut->en_mouvement = vrai; break;
            case TOUCHE_TAB :
                joueur->statut->en_mouvement = faux;
                SDL_ShowCursor(SDL_ENABLE);
                afficher_inventaire(joueur);
                SDL_ShowCursor(SDL_DISABLE);
                break;
            case SDLK_F11 :
                joueur->statut->en_mouvement = faux;
                flags = SDL_GetWindowFlags(fenetre_Principale);

                if(flags & SDL_WINDOW_FULLSCREEN_DESKTOP){
                    if(SDL_SetWindowFullscreen(fenetre_Principale, 0)){
                        char *msp = malloc(sizeof(char) * (500));

                        sprintf(msp, "Erreur lors du changement d'état de la fenêtre : %s\nErreur : 0x%X\n", SDL_GetError(), ERREUR_SDL_WINDOW);
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

                        free(msp);
                        fermer_programme(ERREUR_SDL_WINDOW);
                    }

                }
                else{
                    if(SDL_SetWindowFullscreen(fenetre_Principale, SDL_WINDOW_FULLSCREEN)){
                        char *msp = malloc(sizeof(char) * (500));

                        sprintf(msp, "Erreur lors du changement d'état de la fenêtre : %s\nErreur : 0x%X\n", SDL_GetError(), ERREUR_SDL_WINDOW);
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

                        free(msp);
                        fermer_programme(ERREUR_SDL_WINDOW);
                    }
                }
                break;
            /*case TOUCHE_RETOUR : 
            if(menus == PAUSE){
                menus = JEU;
            } else {
                menus = PAUSE;
            }; break; A décommenter quand la texture menu pause sera faite*/
            case TOUCHE_CONSOMMABLE :
                if(joueur->inventaire->equipe->liste[consommable] != NULL){
                    consommer_objet(joueur);
                    anim_effet_joueur(heal, joueur);
                }
                break;
        }
}

/**
 * \fn void keyUp(SDL_KeyboardEvent * ev, joueur_t ** joueurs)
 * \brief Fonction qui gère les événements quand une touche du clavier est relachée par un joueur
 * \author Antoine Bruneau
 * \param ev Structure contenant l'événement
 * \param joueurs Joueurs pouvant provoquer l'événement
 */
static void keyUp(SDL_KeyboardEvent * ev, joueur_t ** joueurs){
    joueur_t * joueur = joueurs[0];
    t_direction orientation = joueur->statut->orientation;

    switch(ev->keysym.sym){
        case TOUCHE_BAS :
        case SDLK_DOWN : 
            if(orientation == SUD)
                joueur->statut->en_mouvement = faux;
            break;
        case TOUCHE_HAUT :
        case SDLK_UP :
            if (orientation == NORD)
                joueur->statut->en_mouvement = faux;
            break;
        case TOUCHE_DROITE :
        case SDLK_RIGHT :
            if (orientation == EST)
                joueur->statut->en_mouvement = faux;
            break;
        case TOUCHE_GAUCHE :
        case SDLK_LEFT :
            if (orientation == OUEST)
                joueur->statut->en_mouvement = faux;
            break;
    }
}

/**
 * \fn void mouseButtonDown(SDL_MouseButtonEvent * ev, joueur_t ** joueurs)
 * \brief Fonction qui gère les événements quand un bouton de la souris est pressée par un joueur
 * \author Antoine Bruneau
 * \param ev Structure contenant l'événement
 * \param joueurs Joueurs pouvant provoquer l'événement
 */
static void mouseButtonDown(SDL_MouseButtonEvent * ev, joueur_t ** joueurs){
    joueur_t * joueur = joueurs[0];
    statut_t* statut = joueur->statut;

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
 * \fn void mouseButtonUp(SDL_MouseButtonEvent * ev, joueur_t ** joueurs)
 * \brief Fonction qui gère les événements quand un bouton de la souris est relachée par un joueur
 * \author Antoine Bruneau
 * \param ev Structure contenant l'évênement
 * \param joueurs Joueurs pouvant provoquer l'événement
 */
static void mouseButtonUp(SDL_MouseButtonEvent * ev, joueur_t ** joueurs){
    joueur_t * joueur = joueurs[0];
    statut_t* statut = joueur->statut;

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
        joueur->statut->action = RIEN;    
}


void jeu_event(joueur_t ** joueurs){
    SDL_Event lastEvent;

    while(SDL_PollEvent(&lastEvent)){
        switch(lastEvent.type){
            case SDL_QUIT : printf("Détection de la fermeture de la fenêtre\n");fermer_programme(EXIT_SUCCESS);
            case SDL_KEYDOWN : keyDown((SDL_KeyboardEvent*)&lastEvent.key, joueurs); break;
            case SDL_KEYUP : keyUp((SDL_KeyboardEvent*)&lastEvent.key, joueurs); break;
            case SDL_MOUSEBUTTONDOWN : mouseButtonDown((SDL_MouseButtonEvent*)&lastEvent.button, joueurs); break;
            case SDL_MOUSEBUTTONUP : mouseButtonUp((SDL_MouseButtonEvent*)&lastEvent.button, joueurs); break;
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
            fermer_programme(EXIT_SUCCESS);
        case SDL_KEYDOWN:
            return vrai;
        }
    }

    return faux;
}