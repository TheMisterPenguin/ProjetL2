#define SDL_MAIN_HANDLED

#include <commun.h>
#include <stdio.h>
#include <math.h>
#include <map.h>

/**
 * \file main.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme principal du jeu
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

void afficher_intro(void){
    int i;
    
    t_aff * text = creer_texture("ressources/background/logo.bmp", -1, -1, 0, 0, 0);

    /*if(! text){
        fprintf(stderr, "Erreur lors du chargement du menu ! \n");
    }*/

    def_texture_taille(text, FENETRE_LONGUEUR, FENETRE_LARGEUR);

    for(i = 0; i < 256; i += 5 ){ /* Fondu (apparition du logo) */
        if (logo_passer())
            return;
        SDL_SetTextureBlendMode(text->texture, SDL_BLENDMODE_BLEND);
        if (SDL_SetTextureAlphaMod(text->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(25);
    }

    SDL_Delay(1500); /* Temps pendant lequel le logo rest à l'écran */

    for (i = 255; i > 0; i -= 5) /* Fondu (disparition du logo) */
    {
        if (logo_passer())
            return;
        SDL_SetTextureBlendMode(text->texture, SDL_BLENDMODE_BLEND);
        if (SDL_SetTextureAlphaMod(text->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if (SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(text, rendu_principal) != 0)
            fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(25);
    }

    SDL_Delay(150);
}

int main(int argc, char** argv)
{
    int nb_joueurs;
    int debut, fin; /* le temps pour calculer les performances */
    int i;
    char *fichier_map = NULL;
    t_aff *text = NULL;
    t_aff *next_texture_joueur1 = NULL;
    t_aff *next_texture_joueur2 = NULL;
    t_aff *texture_temp1 = NULL;
    t_aff *texture_temp2 = NULL;
    SDL_Rect temp = {0};
    float temps_passe;
    joueur_t * joueurs[2] = {NULL}; //liste des joueurs pour amélioration: mode 2 joueurs
    joueur_t * joueur1 = NULL;
    joueur_t * joueur2 = NULL;
    list * animations = init_liste(NULL, NULL, (void (*)(void *))info_texture);

    /* On initialise le programme */
    SDL_SetMainReady();
    init();

    /* On créer les textures des menus */
    init_text_menus();

    /* On affiche l'introduction */
    afficher_intro();

    /* On affiche l'accueil du jeu */
    SDL_ShowCursor(SDL_ENABLE);
    afficher_menu_accueil(&nb_joueurs);
    SDL_ShowCursor(SDL_DISABLE);

    if(nb_joueurs == 2)
        creer_inventaire_j2();

    /* On charge la map */
    fichier_map = charger_f_map("map.json");
    map = charger_s_map(fichier_map);
    text = texture_map(map); 

    /* On créer le joueur */
    joueurs[0] = new_joueur("joueur1", 0);
    joueur1 = joueurs[0];
    joueur1->pdv = 5;

    /* On créer les animations */
    init_animations();

    next_texture_joueur1 = joueur1->textures_joueur->liste[TEXT_MARCHER];

    objets = creer_liste_objet();
    creer_textures_objets(objets);
    tout_ramasser(objets, joueur1->inventaire);

    /*test de l'allocation des textures*/
    for (i = 0; i < joueur1->textures_joueur->nb_valeurs; i++)
        if (joueur1->textures_joueur->liste == NULL)
            fermer_programme(EXIT_FAILURE);

    //même création pour le joueur2 si le mode coop est sélectionné
    if(nb_joueurs == 2){
        joueurs[1] = new_joueur("joueur2", 1);
        joueur2 = joueurs[1];
        joueur2->pdv = 7;
        next_texture_joueur2 = joueur2->textures_joueur->liste[TEXT_MARCHER];
        tout_ramasser(objets, joueur2->inventaire);

        for (i = 0; i < joueur2->textures_joueur->nb_valeurs; i++)
            if (joueur2->textures_joueur->liste == NULL)
                fermer_programme(EXIT_FAILURE);
    }

    /* On verifie si le répertoire de sauvegarde existe */
    check_repertoire_jeux();

    init_sousbuffer(map, joueur1);

    SDL_RenderClear(rendu_principal);

    if(SDL_RenderCopy(rendu_principal, text->texture, NULL, NULL))
        fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());

    SDL_QueryTexture(map->text_map->texture, NULL, NULL, &(map->text_map->width), &(map->text_map->height));

    /* On place le J1 au centre de l'écran */

    rect_centre_rect(&joueur1->statut->zone_colision, fenetre_finale->frame_anim);
    rect_centre_rect(&joueur1->statut->vrai_zone_collision, fenetre_finale->frame_anim);

    compteur = 0;
    while (running)
    {
        debut = SDL_GetPerformanceCounter();
        jeu_event(joueurs);

        // en_tete(buffer_affichage);
        if (joueur1->statut->en_mouvement){ /* Déplacement map */
            switch (joueur1->statut->orientation)
            {
            case NORD:
                deplacement_y_pers(map, joueur1, -1);
                break;
            case SUD:
                deplacement_y_pers(map, joueur1, 1);
                break;
            case OUEST:
                deplacement_x_pers(map, joueur1, -1);
                break;
            case EST:
                deplacement_x_pers(map, joueur1, 1);
                break;
            }
        }

        texture_temp1 = next_frame_joueur(joueur1);
        if (texture_temp1)
            next_texture_joueur1 = texture_temp1;

        if(nb_joueurs == 2){
            if (joueur2->statut->en_mouvement){
                switch (joueur2->statut->orientation)
                {
                case NORD:
                    deplacement_y_entite(map, joueur2->textures_joueur->liste[0], -1, &joueur2->statut->zone_colision);
                    break;
                case SUD:
                    deplacement_y_entite(map, joueur2->textures_joueur->liste[0], 1, &joueur2->statut->zone_colision);
                    break;
                case OUEST:
                    deplacement_x_entite(map, joueur2->textures_joueur->liste[0], -1, &joueur2->statut->zone_colision);
                    break;
                case EST:
                    deplacement_x_entite(map, joueur2->textures_joueur->liste[0], 1, &joueur2->statut->zone_colision);
                    break;
                }
            }
            texture_temp2 = next_frame_joueur(joueur2);
            if (texture_temp2)
                next_texture_joueur2 = texture_temp2;
        }       

        /* On affiche toutes les entitées sur la map */
        SDL_SetRenderTarget(rendu_principal, map->text_map->texture);
        SDL_RenderClear(rendu_principal);
        
        /* On cous les objets à la map */

        if (SDL_RenderCopy(rendu_principal, map->text_sol->texture, NULL, NULL))
            fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());

        #ifdef _DEBUG_COLLISION /* On affiche les collisions */
                SDL_SetRenderDrawColor(rendu_principal, 0, 255, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(rendu_principal, &joueur1->statut->vrai_zone_collision);
                SDL_RenderDrawRect(rendu_principal, &joueur2->statut->zone_colision);
                en_tete(map->liste_collisions);

                while(!hors_liste(map->liste_collisions)){
                    SDL_Rect *e = valeur_elt(map->liste_collisions);
                    SDL_RenderDrawRect(rendu_principal, e);
                    suivant(map->liste_collisions);
                }
                SDL_SetRenderDrawColor(rendu_principal, 0, 0, 0, SDL_ALPHA_OPAQUE);
        #endif

        
        /* On cous le joueur2 s'il existe*/
        if(nb_joueurs == 2)
            afficher_texture(next_texture_joueur2, rendu_principal);

        /* On affiche le 1er plan (joueur) */
        SDL_SetRenderTarget(rendu_principal, fenetre_finale->texture);
        SDL_RenderClear(rendu_principal);

        /* On cous la map */
        afficher_texture(map->text_map, rendu_principal);
                
        #ifdef _DEBUG_MOUVEMENT /* On affiche les informations liées au mouvement du personnage */
                SDL_SetRenderDrawColor(rendu_principal, 255, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(rendu_principal, &tx);
                SDL_RenderDrawRect(rendu_principal, &(joueur1->statut->zone_colision));
                SDL_RenderDrawRect(rendu_principal, &ty);
                SDL_SetRenderDrawColor(rendu_principal, 0, 0, 0, SDL_ALPHA_OPAQUE);

        #endif

        /* On cous le joueur1 */
        afficher_texture(next_texture_joueur1, rendu_principal);

        // Afficher les animations eventuelles
        lister_animations(joueurs, animations);
        afficher_animations(animations);
        vider_liste(animations);

        /* On passe à l'affichage du renderer sur la fenêtre */
        SDL_SetRenderTarget(rendu_principal, NULL);
        SDL_RenderClear(rendu_principal);

        /* On affiche le rendu principal final */
        afficher_texture(fenetre_finale, rendu_principal);

        /* On affiche l'interface */
        //barre de vie joueur1
        RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
        ((float)joueur1->pdv/joueur1->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));
        
        //barre de vie joueur2
        if(nb_joueurs == 2)
            RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20 + FENETRE_LARGEUR/25 + 20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)joueur2->pdv/joueur2->maxPdv), color(0, 153, 51,0.9), color(125, 125, 125, 1));

        SDL_RenderPresent(rendu_principal);

        fin = SDL_GetPerformanceCounter();

        temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float)NB_FPS) - temps_passe));

        if (compteur == NB_FPS)
            compteur = 0;
        compteur++;
    }

    return AUCUNE_ERREUR;
}