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

SDL_GameController * manette;

/**
 * \fn void keyDown(SDL_KeyboardEvent * ev, joueur_t ** joueurs)
 * \brief Fonction qui gère les événements quand une touche du clavier est pressée par un joueur
 * \author Antoine Bruneau
 * \param ev Structure contenant l'événement
 * \param joueurs Joueurs pouvant provoquer l'événement
 */
static void keyDown(SDL_KeyboardEvent * ev, joueur_t ** joueurs){
    joueur_t * joueur1 = joueurs[0];
    joueur_t * joueur2 = joueurs[1];

    int flags;

    //tous les joueurs ____________________________________________________________________

    if (ev->keysym.sym == SDLK_ESCAPE){ /* On affiche le menu de pause si on appuye sur echap */
        //empêche un joueur de marcher à l'infini lors du maintien d'une touche directionnel en ouvrant un menu et du relachement de la touche dans le menu
        stoper_mouvement_joueurs(joueurs);

        SDL_ShowCursor(SDL_ENABLE);
        afficher_menu_pause(joueur1);
        SDL_ShowCursor(SDL_DISABLE);
    }
    if((joueur1->statut->action == RIEN || joueur1->statut->action == CHARGER) && (joueur2 == NULL || (joueur2->statut->action == RIEN || joueur2->statut->action == CHARGER)))
        switch(ev->keysym.sym){
            case SDLK_F11 :
                joueur1->statut->en_mouvement = faux;

                if(joueur2 != NULL)
                    joueur2->statut->en_mouvement = faux;

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
        }

    //joueur1 _____________________________________________________________
    if(joueur1->statut->action == RIEN || joueur1->statut->action == CHARGER){
        switch(ev->keysym.sym){
            case TOUCHE_BAS : joueur1->statut->orientation = SUD;  joueur1->statut->en_mouvement = vrai; break;
            case TOUCHE_HAUT : joueur1->statut->orientation = NORD;  joueur1->statut->en_mouvement = vrai; break;
            case TOUCHE_DROITE : joueur1->statut->orientation = EST;  joueur1->statut->en_mouvement = vrai; break;
            case TOUCHE_GAUCHE : joueur1->statut->orientation = OUEST;  joueur1->statut->en_mouvement = vrai; break;
            case TOUCHE_TAB :
                //empêche un joueur de marcher à l'infini lors du maintien d'une touche directionnel en ouvrant un menu et du relachement de la touche dans le menu
                stoper_mouvement_joueurs(joueurs);

                SDL_ShowCursor(SDL_ENABLE);
                afficher_inventaire(joueur1, TOUCHE_TAB);
                SDL_ShowCursor(SDL_DISABLE);
                break;
            case TOUCHE_CONSOMMABLE :
                if(joueur1->inventaire->equipe->liste[consommable] != NULL){
                    joueur1->statut->en_mouvement = faux;
                    consommer_objet(joueur1);
                    text_copier_position(heal, joueur1->textures_joueur->liste[0]); // amélioration: centrer pour toutes les tailles
                    joueur1->statut->duree_anim = DUREE_SOIN;
                    joueur1->statut->animation = SOIN;
                }
                break;
        }
        if(joueur2 == NULL){//mode solo
            switch(ev->keysym.sym){
                case SDLK_DOWN : joueur1->statut->orientation = SUD;  joueur1->statut->en_mouvement = vrai; break;
                case SDLK_UP : joueur1->statut->orientation = NORD;  joueur1->statut->en_mouvement = vrai; break;
                case SDLK_RIGHT : joueur1->statut->orientation = EST;  joueur1->statut->en_mouvement = vrai; break;
                case SDLK_LEFT : joueur1->statut->orientation = OUEST;  joueur1->statut->en_mouvement = vrai; break;
            }
        }
    }
            
    //joueur2 _____________________________________________________________

    if(joueur2 != NULL){ //mode coopération
        if(joueur2->statut->action == RIEN || joueur2->statut->action == CHARGER)
        switch(ev->keysym.sym){
            case SDLK_DOWN : joueur2->statut->orientation = SUD;  joueur2->statut->en_mouvement = vrai; break;
            case SDLK_UP : joueur2->statut->orientation = NORD;  joueur2->statut->en_mouvement = vrai; break;
            case SDLK_RIGHT : joueur2->statut->orientation = EST;  joueur2->statut->en_mouvement = vrai; break;
            case SDLK_LEFT : joueur2->statut->orientation = OUEST;  joueur2->statut->en_mouvement = vrai; break;
            case SDLK_p :
                //empêche un joueur de marcher à l'infini lors du maintien d'une touche directionnel en ouvrant un menu et du relachement de la touche dans le menu
                stoper_mouvement_joueurs(joueurs);

                SDL_ShowCursor(SDL_ENABLE);
                afficher_inventaire(joueur2, SDLK_p);
                SDL_ShowCursor(SDL_DISABLE);
                break;
            case SDLK_RETURN :
                if(joueur2->inventaire->equipe->liste[consommable] != NULL){
                    joueur2->statut->en_mouvement = faux;
                    consommer_objet(joueur2);
                    text_copier_position(heal, joueur2->textures_joueur->liste[0]); // amélioration: centrer pour toutes les tailles
                    joueur2->statut->duree_anim = DUREE_SOIN;
                    joueur2->statut->animation = SOIN;
                }
                break;
        }
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
    joueur_t * joueur1 = joueurs[0];
    joueur_t * joueur2 = joueurs[1];
    t_direction orientation1 = joueur1->statut->orientation;
    t_direction orientation2;

    //joueur1 _____________________________________________________________

    switch(ev->keysym.sym){
        case TOUCHE_BAS :
            if(orientation1 == SUD)
                joueur1->statut->en_mouvement = faux;
            break;
        case TOUCHE_HAUT :
            if (orientation1 == NORD)
                joueur1->statut->en_mouvement = faux;
            break;
        case TOUCHE_DROITE :
            if (orientation1 == EST)
                joueur1->statut->en_mouvement = faux;
            break;
        case TOUCHE_GAUCHE :
            if (orientation1 == OUEST)
                joueur1->statut->en_mouvement = faux;
            break;
    }
    if(joueur2 == NULL){//mode solo
            switch(ev->keysym.sym){
                case SDLK_DOWN : 
                    if(orientation1 == SUD)
                        joueur1->statut->en_mouvement = faux;
                    break;
                case SDLK_UP : 
                    if(orientation1 == NORD)
                        joueur1->statut->en_mouvement = faux;
                    break;
                case SDLK_RIGHT : 
                    if(orientation1 == EST)
                        joueur1->statut->en_mouvement = faux;
                    break;
                case SDLK_LEFT : 
                    if(orientation1 == OUEST)
                        joueur1->statut->en_mouvement = faux;
                    break;
            }
        }

    //joueur2 _____________________________________________________________

    if(joueur2 != NULL){ //mode coopération
        orientation2 = joueur2->statut->orientation;
        
        switch(ev->keysym.sym){
            case SDLK_DOWN : 
                if(orientation2 == SUD)
                    joueur2->statut->en_mouvement = faux;
                break;
            case SDLK_UP :
                if (orientation2 == NORD)
                    joueur2->statut->en_mouvement = faux;
                break;
            case SDLK_RIGHT :
                if (orientation2 == EST)
                    joueur2->statut->en_mouvement = faux;
                break;
            case SDLK_LEFT :
                if (orientation2 == OUEST)
                    joueur2->statut->en_mouvement = faux;
                break;
        }
    }
}

void joystick_button_down(SDL_JoyButtonEvent *ev, joueur_t **j){
    joueur_t *joueur = j[0];
    statut_t *statut = joueur->statut;

    switch(ev->button){
        case SDL_CONTROLLER_BUTTON_START : 
            afficher_menu_pause_manette(joueur);
            //empêche un joueur de marcher à l'infini lors du maintien d'une touche directionnel en ouvrant un menu et du relachement de la touche dans le menu
            stoper_mouvement_joueurs(j);
            break;
        case SDL_CONTROLLER_BUTTON_X :
            statut->action = ATTAQUE_OU_CHARGER;
            statut->duree = DUREE_ATTAQUE_OU_CHARGEE;
            break;
        case SDL_CONTROLLER_BUTTON_GUIDE :
            afficher_inventaire_manette(joueur);

            break;
    }
}

void joystick_button_up(SDL_JoyButtonEvent *ev, joueur_t **j)
{
    joueur_t *joueur = j[0];
    statut_t *statut = joueur->statut;

    switch (ev->button)
    {
    case SDL_CONTROLLER_BUTTON_X:
        if (statut->action == CHARGER)
        {
            statut->action = ATTAQUE_CHARGEE;
            statut->en_mouvement = faux;
            statut->duree = DUREE_ATTAQUE_CHARGEE;
        }
        else if (statut->action == ATTAQUE_OU_CHARGER)
        {
            statut->action = ATTAQUE;
            statut->duree = DUREE_ATTAQUE;
        }
        break;
    }
}


void joystick_stick(joueur_t **j){
    joueur_t *joueur = j[0];
    statut_t *statut = joueur->statut;
    Sint16 axe_x = SDL_GameControllerGetAxis(manette, 0); /* On récupère la valeur du stick  */
    Sint16 axe_y = SDL_GameControllerGetAxis(manette, 1); /* On récupère la valeur du stick  */

    if((axe_y > -25735 && axe_y < 25735)){ /* Possible mouvement de l'axe x */
        if (axe_x > 10000){
            statut->orientation = EST;
            statut->en_mouvement = vrai;
        }
        else{ 
            if (axe_x < -10000){
                statut->orientation = OUEST;
                statut->en_mouvement = vrai;
            }
            else
                statut->en_mouvement = faux;
        }
    }

    if ((axe_x > -25735 && axe_x < 25735)){
        if (axe_y > 10000){
            statut->orientation = SUD;
            statut->en_mouvement = vrai;
        }
        else {
            if (axe_y < -10000){
                statut->orientation = NORD;
                statut->en_mouvement = vrai;
            }
            else
                statut->en_mouvement = faux;
        }
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

void jeu_event_manette(joueur_t **joueurs){
    SDL_Event lastEvent;

    joystick_stick(joueurs);

    while (SDL_PollEvent(&lastEvent))
    {
        switch (lastEvent.type)
        {
        case SDL_QUIT:
            printf("Détection de la fermeture de la fenêtre\n");
            fermer_programme(EXIT_SUCCESS);
        case SDL_JOYBUTTONDOWN:
            joystick_button_down((SDL_JoyButtonEvent *)&lastEvent, joueurs);
            break;
        case SDL_JOYBUTTONUP:
            joystick_button_up((SDL_JoyButtonEvent *)&lastEvent, joueurs);
            break;
        }
    }
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