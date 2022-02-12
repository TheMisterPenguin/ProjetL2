#include <affichage.h>
/**
 * \file affichage.c
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions relatives à l'affichage
 * \version 0.1
 * \date 12/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

/**
 * \fn t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const int multpilicateur_taille)
 * \brief Fonction qui renvoie charge une texture et la prépare à ce faire afficher
 *
 * \param nom_fichier Le nom du fichier contenant la texture
 * \param taille_t_x La longueur de la texture à montrer
 * \param taille_t_y La largeur de la texture à montrer
 * \param x La coordonnée x où afficher la texture à l'écran
 * \param y La coordonnée y où afficher la texture à l'écran
 * \param multpilicateur_taille Une valeur par laquelle multiplier la taille de la texture
 * \return t_aff* Une structure qui permet l'affichage de la texture à l'écran
 */
t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const int multpilicateur_taille){
    SDL_Surface * chargement;
    t_aff *texture = NULL;

    /* Chargement de la texture dans une surface */
    chargement = SDL_LoadBMP(nom_fichier);
    if(! chargement){
        fprintf(stderr,"Erreur lors du chargement de la texture : %s\n", SDL_GetError());
        exit(ERREUR_TEXTURE);
    }

    texture = malloc(sizeof(t_aff));

    /* Copie de la ressource dans une structure SDL_Texture */
    texture->texture = SDL_CreateTextureFromSurface(rendu_principal, chargement);
    if(! texture->texture){
        fprintf(stderr,"Erreur lors de la convertion de la surface : %s\n", SDL_GetError());
        free(texture);
        exit(ERREUR_TEXTURE);
    }

    SDL_FreeSurface(chargement); 

    texture->frame_anim = malloc(sizeof(SDL_Rect));

    /* Création de la vue d'animation */
    texture->frame_anim->w = taille_t_x;
    texture->frame_anim->h = taille_t_y;
    texture->frame_anim->x = 0;
    texture->frame_anim->y = 0;

    /* Création de la vue de la fenêtre */
    texture->aff_fenetre->x = x;
    texture->aff_fenetre->y = y;
    texture->aff_fenetre->h = (int) taille_t_y * multpilicateur_taille;
    texture->aff_fenetre->w = (int) taille_t_x * multpilicateur_taille;

    return texture;
}