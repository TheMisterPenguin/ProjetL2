#include <affichage.h>
#include <listes.h>
#include <code_erreur.h>
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

list *listeDeTextures; 
list *buffer_affichage;

void * ajout_text_liste(void * t){return t;}

void detruire_texture(t_aff **texture){

    free((*texture)->aff_fenetre);
    if((*texture)->frame_anim != NULL)
        free((*texture)->frame_anim);

    SDL_DestroyTexture((*texture)->texture);

    *texture = NULL;
}

void detruire_liste_textures(t_l_aff **l_texture){
    int i;
    const unsigned int nb_val = (*l_texture)->nb_valeurs;

    /* Destruction des textures */
    for(i = 0; i < nb_val; i++){

        if ((*l_texture)->liste[i] != NULL)
            detruire_texture(&(*l_texture)->liste[i]);
    }

    /* Destruction de la liste */
    free((*l_texture)->liste);
    free((*l_texture));

    *l_texture = NULL;
}

bool rect_correct_texture(const SDL_Rect * const to_verify, const int width, const int height){
    
    if(to_verify->h > height)
        return faux;
    if(to_verify->w > width)
        return faux;
    if(to_verify->x > width)
        return faux;
    if(to_verify->y > height)
        return faux;
    
    return vrai;
}

err_t update_frame_texture(t_aff *texture, const int x, const int y){
    SDL_Rect temp = *(texture->frame_anim);

    temp.x = x;
    temp.y = y;

    if(rect_correct_texture(&temp, texture->width, texture->height)){
        *(texture->frame_anim) = temp;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

void next_frame_x(t_aff *texture){
    
    texture->frame_anim->x += (texture->frame_anim->w);

    if (!rect_correct_texture(texture->frame_anim, texture->width - 1, texture->height)) /* Si l'on dépasse la texture */
        texture->frame_anim->x = 0;
}   

void next_frame_y(t_aff *texture){
    texture->frame_anim->y += (texture->frame_anim->h);

    if (!rect_correct_texture(texture->frame_anim, texture->width, texture->height - 1)) /* Si l'on dépasse la texture */
        texture->frame_anim->y = 0; 
}

err_t next_frame_y_indice(t_aff *texture, const unsigned int indice)
{
    int temp = texture->frame_anim->y;
    texture->frame_anim->y = (texture->frame_anim->h) * indice; /* On met à jour */

    if (!rect_correct_texture(texture->frame_anim, texture->width, texture->height)){ /* Indice trop grand */
        texture->frame_anim->y = temp;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const float multpilicateur_taille){
    SDL_Surface * chargement = NULL;
    t_aff *texture = NULL;

    /* Chargement de la texture dans une surface */
    chargement = SDL_LoadBMP(nom_fichier);
    if(! chargement){
        fprintf(stderr,"Erreur lors du chargement de la texture : %s\n", SDL_GetError());
        return NULL;
    }

    texture = malloc(sizeof(t_aff));
 
    /* Copie de la ressource dans une structure SDL_Texture */
    texture->texture = SDL_CreateTextureFromSurface(rendu_principal, chargement);
    if(! texture->texture){
        fprintf(stderr,"Erreur lors de la convertion de la surface : %s\n", SDL_GetError());
        free(texture);
        return NULL;
    }

    SDL_FreeSurface(chargement); 

    SDL_QueryTexture(texture->texture, NULL, NULL, &texture->width, &texture->height);

    if(taille_t_x > -1 && taille_t_y > -1){
        texture->frame_anim = malloc(sizeof(SDL_Rect));

        /* Création de la vue d'animation */
        texture->frame_anim->w = taille_t_x;
        texture->frame_anim->h = taille_t_y;
        texture->frame_anim->x = 0;
        texture->frame_anim->y = 0;

        if (!rect_correct_texture(texture->frame_anim, texture->width, texture->height))
        {
            fprintf(stderr, "Erreur lors de la création de la texture : taille de la zone affichée supérieure à la texture !\n");
            free(texture->frame_anim);
            free(texture);
            return NULL;
        }
    }
    else
        texture->frame_anim = NULL;


    texture->aff_fenetre = malloc(sizeof(SDL_Rect));

    /* Création de la vue de la fenêtre */
    texture->aff_fenetre->x = x;
    texture->aff_fenetre->y = y;

    if (taille_t_x > -1 && taille_t_y > -1){
        texture->aff_fenetre->h = (int)taille_t_y * multpilicateur_taille;
        texture->aff_fenetre->w = (int)taille_t_x * multpilicateur_taille;
    }
    else {
        texture->aff_fenetre->h = (int)texture->height * multpilicateur_taille;
        texture->aff_fenetre->w = (int)texture->width * multpilicateur_taille;
    }
        ajout_droit(listeDeTextures, texture);

        return texture;
    }

err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu){
    if(texture->frame_anim != NULL)
        return SDL_RenderCopy(rendu,texture->texture, texture->frame_anim, texture->aff_fenetre);
    else
        return SDL_RenderCopy(rendu, texture->texture, NULL, texture->aff_fenetre);
}

err_t afficher_buffer(const list * const buffer, SDL_Renderer *rendu){

    if(liste_vide(buffer))
        return BUFFER_EMPTY;
    
    en_tete(buffer);

    while(!hors_liste(buffer)){

        if(afficher_texture(valeur_elt(buffer), rendu) < 0){ /* On affiche la texture actuelle à l'écran */
            fprintf(stderr,"Erreur lors de l'affichage de la texture : %s\n", SDL_GetError());
            return SDL_ERREUR;
        }

        suivant(buffer);
    }

    return AUCUNE_ERREUR;
}


