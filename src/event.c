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

    if (ev->keysym.sym == SDLK_ESCAPE){ /* On affiche le menu de pause si on appuye sur echap */
        SDL_ShowCursor(SDL_ENABLE);
        afficher_menu_pause();
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
                afficher_inventaire();
                break;
            case SDLK_F11 :
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

    switch(ev->keysym.sym){
        case TOUCHE_BAS :
        case SDLK_DOWN : 
            if(orientation == SUD)
                perso_principal->statut->en_mouvement = faux;
            break;
        case TOUCHE_HAUT :
        case SDLK_UP :
            if (orientation == NORD)
                perso_principal->statut->en_mouvement = faux;
            break;
        case TOUCHE_DROITE :
        case SDLK_RIGHT :
            if (orientation == EST)
                perso_principal->statut->en_mouvement = faux;
            break;
        case TOUCHE_GAUCHE :
        case SDLK_LEFT :
            if (orientation == OUEST)
                perso_principal->statut->en_mouvement = faux;
            break;
    }
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
            fermer_programme(EXIT_SUCCESS);
        case SDL_KEYDOWN:
            return vrai;
        }
    }

    return faux;
}