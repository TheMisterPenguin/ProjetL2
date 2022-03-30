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

    /* On initialise le programme */
    SDL_SetMainReady();
    init();

    /* On affiche l'introduction */
    afficher_intro();

    /* On charge la map */
    fichier_map = charger_f_map("map.json");
    map = charger_s_map(fichier_map);
    text = texture_map(map); 

    //TEMPORAIREMENT ICI -- test animation heal (équiper consommable puis touche e) -- TEMPORAIREMENT ICI
    heal = (creer_texture("ressources/sprite/heal.bmp", LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 0, 0, (FENETRE_LONGUEUR * 0.022f) / 16 * 3));

    /* On créer le joueur */
    joueurs[0] = new_joueur("joueur1");
    joueurs[1] = new_joueur("joueur2");
    joueur1 = joueurs[0];
    joueur2 = joueurs[1];
    joueur1->pdv = 5;

    next_texture_joueur1 = joueur1->textures_joueur->liste[TEXT_MARCHER];
    next_texture_joueur2 = joueur2->textures_joueur->liste[TEXT_MARCHER];

    objets = creer_liste_objet();
    creer_textures_objets(objets);
    tout_ramasser(objets, joueur1->inventaire);

    /*test de l'allocation des textures*/
    for (i = 0; i < joueur1->textures_joueur->nb_valeurs; i++)
        if (joueur1->textures_joueur->liste == NULL)
            fermer_programme(EXIT_FAILURE);

    for (i = 0; i < joueur2->textures_joueur->nb_valeurs; i++)
        if (joueur2->textures_joueur->liste == NULL)
            fermer_programme(EXIT_FAILURE);

    /* On verifie si le répertoire de sauvegarde existe */
    check_repertoire_jeux();

    rect_centre(&(joueur1->statut->zone_colision));

    init_sousbuffer(map, joueur1);

    SDL_RenderClear(rendu_principal);
    temp.x=0;
    temp.y=0;
    temp.w=floor(map->text_sol->width * map->text_sol->multipli_taille);
    temp.h=floor(map->text_sol->height * map->text_sol->multipli_taille);

    if(SDL_RenderCopy(rendu_principal, text->texture, NULL, &temp))
        fprintf(stderr, "Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());

    SDL_QueryTexture(map->text_map->texture, NULL, NULL, &(map->text_map->width), &(map->text_map->height));

    SDL_SetRenderTarget(rendu_principal, NULL);


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
                deplacement_y_pers(map, joueur1, -3);
                break;
            case SUD:
                deplacement_y_pers(map, joueur1, 3);
                break;
            case OUEST:
                deplacement_x_pers(map, joueur1, -3);
                break;
            case EST:
                deplacement_x_pers(map, joueur1, 3);
                break;
            }
        }

        if (joueur2->statut->en_mouvement){ /* Déplacement map */
            switch (joueur2->statut->orientation)
            {
            case NORD:
                deplacement_y_pers(map, joueur2, -3);
                break;
            case SUD:
                deplacement_y_pers(map, joueur2, 3);
                break;
            case OUEST:
                deplacement_x_pers(map, joueur2, -3);
                break;
            case EST:
                deplacement_x_pers(map, joueur2, 3);
                break;
            }
        }

        texture_temp1 = next_frame_joueur(joueur1);
        if (texture_temp1)
            next_texture_joueur1 = texture_temp1;
        
        texture_temp2 = next_frame_joueur(joueur2);
        if (texture_temp2)
            next_texture_joueur2 = texture_temp2;

        SDL_RenderClear(rendu_principal);
        /* On affiche la carte */
        afficher_texture(map->text_map, rendu_principal);

        #ifdef __DEBUG__
            SDL_RenderDrawRect(rendu_principal, &tx);
            SDL_RenderDrawRect(rendu_principal, &(joueur1->statut->zone_colision));
            SDL_RenderDrawRect(rendu_principal, &ty);
        #endif

        /* On affiche le joueur1 */
        afficher_texture(next_texture_joueur1, rendu_principal);

        /* On affiche le joueur2 */
        afficher_texture(next_texture_joueur2, rendu_principal);

        /* On affiche l'interface */
        RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)joueur1->pdv/joueur1->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));
        
        RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20 + FENETRE_LARGEUR/25 + 20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)joueur2->pdv/joueur2->maxPdv), color(0, 153, 51,0.9), color(125, 125, 125, 1));


        SDL_RenderPresent(rendu_principal);

        // vider_liste(buffer_affichage);
        fin = SDL_GetPerformanceCounter();

        temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((1000 / (float) NB_FPS) - temps_passe));
        if(compteur == NB_FPS)
            compteur = 0;
        compteur++;
    }

    return AUCUNE_ERREUR;
}