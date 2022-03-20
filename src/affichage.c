#include <affichage.h>
#include <listes.h>
#include <code_erreur.h>
#include <personnage.h>
#include <math.h>
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

    free(*texture);
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

err_t next_frame_x_indice(t_aff *texture, const unsigned int indice)
{
    int temp = texture->frame_anim->x;
    texture->frame_anim->x = (texture->frame_anim->w) * indice; /* On met à jour */

    if (!rect_correct_texture(texture->frame_anim, texture->width, texture->height)){ /* Indice trop grand */
        texture->frame_anim->x = temp;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
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

void def_texture_taille(t_aff * a_modifier, const int longueur, const int largeur){
    a_modifier->aff_fenetre->w = longueur;
    a_modifier->aff_fenetre->h = largeur;
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
    if(multpilicateur_taille != 0){
        if (taille_t_x > -1 && taille_t_y > -1){
            texture->aff_fenetre->h = (int)taille_t_y * multpilicateur_taille;
            texture->aff_fenetre->w = (int)taille_t_x * multpilicateur_taille;
        }
        else {
            texture->aff_fenetre->h = (int)texture->height * multpilicateur_taille;
            texture->aff_fenetre->w = (int)texture->width * multpilicateur_taille;
        }

        texture->multipli_taille = multpilicateur_taille;
    }
    else{
        texture->aff_fenetre->h = FENETRE_LARGEUR;
        texture->aff_fenetre->w = FENETRE_LONGUEUR;

        texture->multipli_taille = (float)FENETRE_LONGUEUR / texture->width;
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

 t_l_aff* init_textures_joueur(){
    t_l_aff* textures_joueur = malloc(sizeof(t_l_aff));
    textures_joueur->nb_valeurs = NB_SPRITE_JOUEUR;
    textures_joueur->liste = malloc(sizeof(t_aff)*NB_SPRITE_JOUEUR);
/* Création d'une nouvelle liste de textures pour le joueur. */
    textures_joueur->liste[TEXT_MARCHER] = creer_texture(N_T_MARCHER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    textures_joueur->liste[TEXT_ATTAQUE] = creer_texture(N_T_ATTAQUE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    textures_joueur->liste[TEXT_ATTAQUE_CHARGEE] = creer_texture(N_T_ATTAQUE_CHARGEE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    textures_joueur->liste[TEXT_CHARGER] = creer_texture(N_T_CHARGER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    textures_joueur->liste[TEXT_MARCHER_BOUCLIER] = creer_texture(N_T_MARCHER_BOUCLIER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, (FENETRE_LONGUEUR * 0.022f) / 16 * 3);
    
/* Déplacement des textures au centre de l'écran. */
    deplacer_texture_centre(textures_joueur->liste[TEXT_MARCHER], 0, 0);
    deplacer_texture_centre(textures_joueur->liste[TEXT_ATTAQUE], 0, 0);
    deplacer_texture_centre(textures_joueur->liste[TEXT_ATTAQUE_CHARGEE], 0, 0);
    deplacer_texture_centre(textures_joueur->liste[TEXT_CHARGER], 0, 0);
    deplacer_texture_centre(textures_joueur->liste[TEXT_MARCHER_BOUCLIER], 0, 0);
    /* positionnement au dernier sprite*/
    next_frame_x_indice(textures_joueur->liste[TEXT_CHARGER], 2);
    return textures_joueur;
}

t_aff* init_texture_joueur(t_l_aff* textures_joueur){
    /* if sauvegarde existante -> return texture sauvegardée du joueur*/
    if(perso_principal->statut->bouclier_equipe)
        return textures_joueur->liste[TEXT_MARCHER_BOUCLIER];
    else
        return textures_joueur->liste[TEXT_MARCHER];
}

t_aff* next_frame_joueur(t_l_aff* textures_joueur){
    statut_t* statut = perso_principal->statut;
    t_aff** textures = textures_joueur->liste;
    int pause = 0;

    if(statut->duree>0 && (compteur%5) == 0)
        (statut->duree)--;

    for(unsigned i = TEXT_MARCHER; i < NB_SPRITE_JOUEUR; i++)
        text_copier_position(textures_joueur->liste[i], textures_joueur->liste[TEXT_MARCHER]);

    if(statut->action == ATTAQUE_OU_CHARGER && statut->duree == 0)
                statut->action = CHARGER;
    if( (statut->action == RIEN  || statut->action == ATTAQUE_OU_CHARGER) && statut->en_mouvement){
        if( (compteur%5) == 0) /*compteur%5 pour la vitesse d'affichage*/
            if(statut->bouclier_equipe){
                next_frame_y_indice(textures[TEXT_MARCHER_BOUCLIER], statut->orientation);
                next_frame_x(textures[TEXT_MARCHER_BOUCLIER]);
                return textures[TEXT_MARCHER_BOUCLIER];
            }
            else{
                next_frame_y_indice(textures[TEXT_MARCHER], statut->orientation);
                next_frame_x(textures[TEXT_MARCHER]);
                return textures[TEXT_MARCHER];
            }
        else
            pause = 1;
    }
    else{
        if(statut->action == BLOQUER){
            //bloquer les coups
        }
        else if(statut->action == CHARGER){ 
            if((compteur%5) == 0){ /*compteur%5 pour la vitesse d'affichage*/
                next_frame_x(textures[TEXT_CHARGER]);
                if(statut->en_mouvement)
                    next_frame_y_indice(textures[TEXT_CHARGER], 2 * (statut->orientation) + (textures[TEXT_CHARGER]->frame_anim->x) / (int) LONGUEUR_PERSONNAGE );
                else
                    next_frame_y_indice(textures[TEXT_CHARGER], 2 * (statut->orientation) );
                return textures[TEXT_CHARGER];
            }
            else
                pause = 1;
        }
        else if(statut->action == ATTAQUE){
            if( (compteur%4) == 0){ /*compteur%4 pour la vitesse d'affichage*/
                next_frame_x(textures[TEXT_ATTAQUE]);
                next_frame_y_indice(textures[TEXT_ATTAQUE], statut->orientation);
                /*si il a fait le tour du fichier sprite attaque, l'action est terminée*/
                if( (textures[TEXT_ATTAQUE]->frame_anim->x) == (LONGUEUR_PERSONNAGE*2) )
                    statut->action = RIEN;
                return textures[TEXT_ATTAQUE];
            }
            else
                pause = 1;
        }
        else if(statut->action == ATTAQUE_CHARGEE){
            if( (compteur%3) == 0){ /*compteur%3 pour la vitesse d'affichage*/
                //lorseque l'on rentre pour la première fois dans cette phase d'attaque chargée
                if(statut->duree == (DUREE_ATTAQUE_CHARGEE-1))
                    next_frame_x_indice(textures[TEXT_ATTAQUE_CHARGEE], (statut->orientation)*2 - 1 );
                next_frame_x(textures[TEXT_ATTAQUE_CHARGEE]);
                /*si il a fait le tour du fichier sprite attaque, l'action est terminée*/
                if( ( (textures[TEXT_ATTAQUE_CHARGEE]->frame_anim->x) == (statut->orientation)*2*LONGUEUR_PERSONNAGE) && (statut->duree != (DUREE_ATTAQUE_CHARGEE-1) ) )
                    statut->action = RIEN;
                return textures[TEXT_ATTAQUE_CHARGEE];
            }
            else
                pause = 1;
        }
    }
    /*si aucune des conditions*/
    if(pause)
        return NULL;
    else if(statut->bouclier_equipe)
        return textures[TEXT_MARCHER_BOUCLIER];
    else
        return textures[TEXT_MARCHER];
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

point get_screen_center(){
    point p;

    p.x = FENETRE_LONGUEUR / 2;
    p.y = FENETRE_LARGEUR / 2;

    return p;
}

bool point_in_rect(SDL_Rect r, point p){
    SDL_Rect p2r = {.x = p.x, .y = p.y, .w = 1, .h = 1};

    return SDL_IntersectRect(&r, &p2r, NULL);

}

void deplacer_texture_centre(t_aff *texture, int x, int y){
    point centre = get_screen_center();
    
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);
     
    texture->aff_fenetre->x = centre.x;

    if(texture->aff_fenetre->w % 2){
        texture->aff_fenetre->x -= texture->aff_fenetre->w / 2 + 1;
    }
    else{
        texture->aff_fenetre->x -= texture->aff_fenetre->w / 2;
    }

    texture->aff_fenetre->y = centre.y;

    if (texture->aff_fenetre->h % 2)
    {
        texture->aff_fenetre->y -= texture->aff_fenetre->h / 2 + 1;
    }
    else
    {
        texture->aff_fenetre->y -= texture->aff_fenetre->h / 2;
    }

    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y; 
}

void deplacer_texture_origine(t_aff *texture, int x, int y)
{
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);



    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y;
}


void deplacer_texture_haut_droit(t_aff *texture, int x, int y)
{
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);

    texture->aff_fenetre->x = FENETRE_LONGUEUR;

    texture->aff_fenetre->x -= texture->aff_fenetre->w;

    texture->aff_fenetre->y = 0;

    texture->aff_fenetre->y -= texture->aff_fenetre->h;


    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y;
}

void deplacer_texture_bas_gauche(t_aff *texture, int x, int y)
{
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);

    texture->aff_fenetre->x = 0;

    texture->aff_fenetre->x -= texture->aff_fenetre->w;

    texture->aff_fenetre->y = FENETRE_LARGEUR;

    texture->aff_fenetre->y -= texture->aff_fenetre->h;

    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y;
}

void deplacer_texture_bas_droit(t_aff *texture, int x, int y)
{
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);

    texture->aff_fenetre->x = FENETRE_LONGUEUR;

    texture->aff_fenetre->x -= texture->aff_fenetre->w;

    texture->aff_fenetre->y = FENETRE_LARGEUR;

    texture->aff_fenetre->y -= texture->aff_fenetre->h;

    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y;
}

void modif_affichage_rect(t_aff *texture, SDL_Rect r){
    texture->frame_anim->h = r.h;
    texture->frame_anim->w = r.w;
}

void deplacement_x_pers(t_aff *map, t_aff *pers, int x){

    int *x_map = &(map->frame_anim->x); /* La coordonnée x actuelle de la map */
    int *x_pers = &(pers->aff_fenetre->x); /* La coordonnée x actuelle du joueur */
    const long int taille_unite = floor(FENETRE_LONGUEUR / (float)map->width); /* Calcul en nombre de pixels d'une unité de déplacement */
    const int pers_x_milieu = floor(get_screen_center().x - 8 * pers->multipli_taille);
    const int map_milieu = floor(get_screen_center().x / map->multipli_taille);

    if (*x_map + x < 0) { /* La map ne peut pas plus aller à gauche */
            // printf("La map ne peut plus aller à gauche, déplacement du personnage\n");
            *x_pers += x * taille_unite; /* On déplace le personnage de x unités */
            return;
        }
    if (*x_map + x > (map->width - map_milieu)){ /* L'écran est en bordure de map droite */
        *x_pers += x * taille_unite;
        return;
    }
    if(*x_pers == pers_x_milieu ) /* On se trouve dans l'intervalle normal */
        *x_map += x; /* On déplace la map en fond */
    else
        *x_pers += x * taille_unite;

}

void deplacement_y_pers(t_aff *map, t_aff *pers, int y){

    int *y_map = &(map->frame_anim->y);                                        /* La coordonnée x actuelle de la map */
    int *y_pers = &(pers->aff_fenetre->y);                                     /* La coordonnée x actuelle du joueur */
    const long int taille_unite = floor(FENETRE_LONGUEUR / (float)map->width); /* Calcul en nombre de pixels d'une unité de déplacement */
    const int pers_y_milieu = floor(get_screen_center().y - 8 * pers->multipli_taille);
    const int map_milieu = floor(get_screen_center().y / map->multipli_taille);

    if (*y_map + y < 0) { /* La map ne peut pas plus aller à haut */
        *y_pers += y * taille_unite; /* On déplace le personnage de x unités */
        return;
    }
    if (*y_map + y > (map->height - map_milieu)) { /* L'écran est en bordure de map bas */
        *y_pers += y * taille_unite;
        return;
    }
    if (*y_pers == pers_y_milieu) /* On se trouve dans l'intervalle normal */
        *y_map += y;              /* On déplace la map en fond */
    else
        *y_pers += y * taille_unite;
}

void text_copier_position(t_aff * a_modifier, const t_aff * const original){
    a_modifier->aff_fenetre->x = original->aff_fenetre->x;
    a_modifier->aff_fenetre->y = original->aff_fenetre->y;
}