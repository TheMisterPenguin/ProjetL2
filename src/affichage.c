#include <affichage.h>
#include <listes.h>
#include <code_erreur.h>
#include <personnage.h>
#include <math.h>
#include <map.h>
#include <definition_commun.h>
#include <interface.h>

/**
 * \file affichage.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fonctions liées au module affichage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */


list *listeDeTextures; 
list *buffer_affichage;

t_aff * heal = NULL; //init_animations()
t_aff *fenetre_finale = NULL; /* La fenêtre de jeu finale sans l'interface */

long int compteur;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
SDL_Rect tx,ty;

float multiplicateur_x, multiplicateur_y; /* Multiplicateurs qui dépendent de la résolution */

void * ajout_text_liste(void * t){return t;}

void detruire_texture(t_aff **texture){
    if(texture == NULL)
        return;
    
    if((*texture)->aff_fenetre != NULL)
        free((*texture)->aff_fenetre);

    if((*texture)->frame_anim != NULL)
        free((*texture)->frame_anim);

    // ne pas faire SDL_DestroyTexture (deja dans f_close(SDL_DestroyRenderer))

    free(*texture);
    *texture = NULL;
}

void detruire_liste_textures(t_l_aff **l_texture){

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

void info_texture(t_aff * texture){
    printf("texture width: %d, height: %d\n", texture->width, texture->height);
}

t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const float multiplicateur_taille){
    SDL_Surface * chargement = NULL;
    t_aff *texture = NULL;

    texture = malloc(sizeof(t_aff));
    /* Chargement de la texture dans une surface */
    if(nom_fichier != NULL){
        chargement = SDL_LoadBMP(nom_fichier);
        if(! chargement){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la création de la texture : %s\nErreur : 0x%X\n", SDL_GetError(), ERREUR_FICHIER);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, msp);

            free(msp);
            return NULL;
        }
    
        /* Copie de la ressource dans une structure SDL_Texture */
        texture->texture = SDL_CreateTextureFromSurface(rendu_principal, chargement);
        SDL_FreeSurface(chargement); 
        if(! texture->texture){
            char *msp = malloc(sizeof(char) * (500));

            sprintf(msp, "Erreur lors de la convertion de la surface : %s\nErreur : 0x%X\n", SDL_GetError(), ERREUR_SDL_SURFACE);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la convertion de la surface : %s\nErreur : 0x%X\n", SDL_GetError(), ERREUR_SDL_SURFACE);

            free(msp);
            free(texture);
            return NULL;
        }

        SDL_QueryTexture(texture->texture, NULL, NULL, &texture->width, &texture->height);
    }


    if(taille_t_x > -1 && taille_t_y > -1){
        texture->frame_anim = malloc(sizeof(SDL_Rect));

        /* Création de la vue d'animation */
        texture->frame_anim->w = taille_t_x;
        texture->frame_anim->h = taille_t_y;
        texture->frame_anim->x = 0;
        texture->frame_anim->y = 0;
    }
    else
        texture->frame_anim = NULL;


    texture->aff_fenetre = malloc(sizeof(SDL_Rect));

    /* Création de la vue de la fenêtre */
    texture->aff_fenetre->x = x;
    texture->aff_fenetre->y = y;
    if(multiplicateur_taille != 0){
        if (taille_t_x > -1 && taille_t_y > -1){
            texture->aff_fenetre->h = (int)taille_t_y * multiplicateur_taille;
            texture->aff_fenetre->w = (int)taille_t_x * multiplicateur_taille;
        }
        else {
            texture->aff_fenetre->h = (int)texture->height * multiplicateur_taille;
            texture->aff_fenetre->w = (int)texture->width * multiplicateur_taille;
        }

        texture->multipli_taille = multiplicateur_taille;
    }
    else{
        texture->aff_fenetre->h = FENETRE_LARGEUR;
        texture->aff_fenetre->w = FENETRE_LONGUEUR;

        texture->multipli_taille = (float)FENETRE_LONGUEUR / texture->width;
    }

    texture->compteur_frame_anim = 0;
    ajout_droit(listeDeTextures, texture);

    return texture;
}

err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu){
    if(texture->frame_anim != NULL)
        return SDL_RenderCopy(rendu,texture->texture, texture->frame_anim, texture->aff_fenetre);
    else
        return SDL_RenderCopy(rendu, texture->texture, NULL, texture->aff_fenetre);
}

t_l_aff* init_textures_joueur(joueur_t *j, int num_j){
    t_l_aff* textures_joueur = malloc(sizeof(t_l_aff));
    textures_joueur->nb_valeurs = NB_SPRITE_JOUEUR;
    textures_joueur->liste = malloc(sizeof(t_aff)*NB_SPRITE_JOUEUR);

/* Création d'une nouvelle liste de textures pour le joueur. */
    //textures joueur1
    if(num_j == 0){
      textures_joueur->liste[TEXT_MARCHER] = (creer_texture(N_T_MARCHER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE)));
      textures_joueur->liste[TEXT_ATTAQUE] = (creer_texture(N_T_ATTAQUE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE)));
      textures_joueur->liste[TEXT_ATTAQUE_CHARGEE] = creer_texture(N_T_ATTAQUE_CHARGEE, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));
      textures_joueur->liste[TEXT_CHARGER] = creer_texture(N_T_CHARGER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));
      textures_joueur->liste[TEXT_MARCHER_BOUCLIER] = creer_texture(N_T_MARCHER_BOUCLIER, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));
    }
    //textures joueur2
    else{
        textures_joueur->liste[TEXT_MARCHER] = (creer_texture(N_T_MARCHER2, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE)));
        textures_joueur->liste[TEXT_ATTAQUE] = (creer_texture(N_T_ATTAQUE2, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE)));
        textures_joueur->liste[TEXT_ATTAQUE_CHARGEE] = creer_texture(N_T_ATTAQUE_CHARGEE2, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));
        textures_joueur->liste[TEXT_CHARGER] = creer_texture(N_T_CHARGER2, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));
        textures_joueur->liste[TEXT_MARCHER_BOUCLIER] = creer_texture(N_T_MARCHER_BOUCLIER2, LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 150, 150, floor(map->taille_case / TAILLE_PERSONNAGE));    }

    textures_joueur->liste[TEXT_MARCHER]->duree_frame_anim = 5;
    textures_joueur->liste[TEXT_ATTAQUE]->duree_frame_anim = 4;
    textures_joueur->liste[TEXT_ATTAQUE_CHARGEE]->duree_frame_anim = 3;
    textures_joueur->liste[TEXT_CHARGER]->duree_frame_anim = 5;
    textures_joueur->liste[TEXT_MARCHER_BOUCLIER]->duree_frame_anim = 5;

    /* positionnement au dernier sprite*/
    next_frame_x_indice(textures_joueur->liste[TEXT_CHARGER], 2);

    /* On créer la zone de colision du personnage */
    j->statut->zone_colision.w = TAILLE_PERSONNAGE * textures_joueur->liste[TEXT_MARCHER]->multipli_taille;
    j->statut->zone_colision.h = TAILLE_PERSONNAGE * textures_joueur->liste[TEXT_MARCHER]->multipli_taille;

    if(num_j == 0)
        ajout_droit(map->liste_collisions, &j->statut->vrai_zone_collision);
    else
        ajout_droit(map->liste_collisions, &j->statut->zone_colision);

    return textures_joueur;
}

t_aff* init_texture_joueur(t_l_aff* textures_joueur, joueur_t * joueur){
    /* if sauvegarde existante -> return texture sauvegardée du joueur*/
    if(joueur->statut->bouclier_equipe)
        return textures_joueur->liste[TEXT_MARCHER_BOUCLIER];
    else
        return textures_joueur->liste[TEXT_MARCHER];
}

void appliquer_coord_rect(const SDL_Rect * const a_copier, t_l_aff *textures){

    for(unsigned int i = 0; i < textures->nb_valeurs; i++){
        textures->liste[i]->aff_fenetre->x = a_copier->x - (16 * textures->liste[i]->multipli_taille);
        textures->liste[i]->aff_fenetre->y = a_copier->y - (16 * textures->liste[i]->multipli_taille);
    }
}

t_aff *next_frame_joueur(joueur_t *j)
{
    t_l_aff *textures_joueur = j->textures_joueur;
    statut_t *statut = j->statut;
    t_aff **textures = textures_joueur->liste;
    int pause = 0;

    appliquer_coord_rect(&(j->statut->zone_colision), textures_joueur);

    if (statut->duree > 0 && (compteur % 2) == 0)
        (statut->duree)--;

    if (statut->action == ATTAQUE_OU_CHARGER && statut->duree == 0)
        statut->action = CHARGER;
    if ((statut->action == RIEN || statut->action == ATTAQUE_OU_CHARGER) && statut->en_mouvement)
    {
        if ((compteur % 5) == 0) /*compteur%5 pour la vitesse d'affichage*/
            if (statut->bouclier_equipe)
            {
                next_frame_y_indice(textures[TEXT_MARCHER_BOUCLIER], statut->orientation);
                next_frame_x(textures[TEXT_MARCHER_BOUCLIER]);
                return textures[TEXT_MARCHER_BOUCLIER];
            }
            else
            {
                next_frame_y_indice(textures[TEXT_MARCHER], statut->orientation);
                next_frame_x(textures[TEXT_MARCHER]);
                return textures[TEXT_MARCHER];
            }
        else
            pause = 1;
    }
    else
    {
        if (statut->action == BLOQUER)
        {
            // bloquer les coups
        }
        else if (statut->action == CHARGER)
        {
            if ((compteur % 5) == 0)
            { /*compteur%5 pour la vitesse d'affichage*/
                next_frame_x(textures[TEXT_CHARGER]);
                if (statut->en_mouvement)
                    next_frame_y_indice(textures[TEXT_CHARGER], 2 * (statut->orientation) + (textures[TEXT_CHARGER]->frame_anim->x) / (int)LONGUEUR_PERSONNAGE);
                else
                    next_frame_y_indice(textures[TEXT_CHARGER], 2 * (statut->orientation));
                return textures[TEXT_CHARGER];
            }
            else
                pause = 1;
        }
        else if (statut->action == ATTAQUE)
        {
            if ((compteur % 4) == 0)
            { /*compteur%4 pour la vitesse d'affichage*/
                next_frame_x(textures[TEXT_ATTAQUE]);
                next_frame_y_indice(textures[TEXT_ATTAQUE], statut->orientation);
                /*si il a fait le tour du fichier sprite attaque, l'action est terminée*/
                if ((textures[TEXT_ATTAQUE]->frame_anim->x) == (LONGUEUR_PERSONNAGE * 2))
                    statut->action = RIEN;
                return textures[TEXT_ATTAQUE];
            }
            else
                pause = 1;
        }
        else if (statut->action == ATTAQUE_CHARGEE)
        {
            if ((compteur % 3) == 0)
            { /*compteur%3 pour la vitesse d'affichage*/
                // lorseque l'on rentre pour la première fois dans cette phase d'attaque chargée
                if (statut->duree == (DUREE_ATTAQUE_CHARGEE - 1))
                    next_frame_x_indice(textures[TEXT_ATTAQUE_CHARGEE], (statut->orientation) * 2 - 1);
                next_frame_x(textures[TEXT_ATTAQUE_CHARGEE]);
                /*si il a fait le tour du fichier sprite attaque, l'action est terminée*/
                if (((textures[TEXT_ATTAQUE_CHARGEE]->frame_anim->x) == (statut->orientation) * 2 * LONGUEUR_PERSONNAGE) && (statut->duree != (DUREE_ATTAQUE_CHARGEE - 1)))
                    statut->action = RIEN;
                return textures[TEXT_ATTAQUE_CHARGEE];
            }
            else
                pause = 1;
        }
    }
    /*si aucune des conditions*/
    if (pause)
        return NULL;
    else if (statut->bouclier_equipe)
        return textures[TEXT_MARCHER_BOUCLIER];
    else
        return textures[TEXT_MARCHER];
}

err_t afficher_buffer(list *buffer, SDL_Renderer *rendu){

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

void rect_centre_x(SDL_Rect *rectangle){
    unsigned int centre_x = get_screen_center().x;

    rectangle->x = centre_x;

    if (rectangle->w % 2)
    {
        rectangle->x -= rectangle->w / 2 + 1;
    }
    else
    {
        rectangle->x -= rectangle->w / 2;
    }
}

void rect_centre_y(SDL_Rect *rectangle){
    unsigned int centre_y = get_screen_center().y;

    rectangle->y = centre_y;

    if (rectangle->h % 2)
    {
        rectangle->y -= rectangle->h / 2 + 1;
    }
    else
    {
        rectangle->y -= rectangle->h / 2;
    }
}

void rect_centre(SDL_Rect *rectangle){
    
    rect_centre_x(rectangle);
    rect_centre_y(rectangle);

}

void rect_centre_rect_x(SDL_Rect *rectangle, SDL_Rect *rectangle_centre){
    unsigned int centre_x = rectangle_centre->w / 2;

    rectangle->x = centre_x;

    if (rectangle->w % 2)
    {
        rectangle->x -= rectangle->w / 2 + 1;
    }
    else
    {
        rectangle->x -= rectangle->w / 2;
    }
}

void rect_centre_rect_y(SDL_Rect *rectangle, SDL_Rect *rectangle_centre){
    unsigned int centre_y = rectangle_centre->h / 2;

    rectangle->y = centre_y;

    if (rectangle->h % 2)
    {
        rectangle->y -= rectangle->h / 2 + 1;
    }
    else
    {
        rectangle->y -= rectangle->h / 2;
    }
}

void rect_centre_rect(SDL_Rect *rectangle, SDL_Rect *rectangle_centre){
    
    rect_centre_rect_x(rectangle, rectangle_centre);
    rect_centre_rect_y(rectangle, rectangle_centre);

}

void deplacer_texture_centre(t_aff *texture, int x, int y){
    
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);
     
    rect_centre(texture->aff_fenetre);

    texture->aff_fenetre->x += x;
    texture->aff_fenetre->y += y; 
}

void deplacer_rect_origine(SDL_Rect *r, int x, int y){

    r->x = x;
    r->y = y;
}

void deplacer_texture_origine(t_aff *texture, int x, int y){
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);



    deplacer_rect_origine(texture->aff_fenetre, x, y);
}

void deplacer_rect_haut_droit(SDL_Rect *r, int x, int y)
{
    r->x = FENETRE_LONGUEUR;

    r->x -= r->w;

    r->y = 0;

    r->x += x;
    r->y += y;
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

    deplacer_rect_haut_droit(texture->aff_fenetre, x, y);
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

void deplacement_x_pers(t_map *m, joueur_t * j, int x){

    int *x_map = &(fenetre_finale->frame_anim->x); /* La coordonnée x actuelle de la map */
    int *x_pers = &(j->statut->zone_colision.x); /* La coordonnée x actuelle du joueur */
    const long int taille_unite = floor(j->textures_joueur->liste[0]->multipli_taille); /* Calcul en nombre de pixels d'une unité de déplacement */
    SDL_Rect temp = {.x = j->statut->vrai_zone_collision.x + x * taille_unite, .y = j->statut->vrai_zone_collision.y, .w = j->statut->vrai_zone_collision.w, .h = j->statut->vrai_zone_collision.h};

    en_tete(m->liste_collisions);

    while(!hors_liste(m->liste_collisions)){
        SDL_Rect *element = valeur_elt(m->liste_collisions);

        if (element == &j->statut->vrai_zone_collision){ /* Si la collision nou concerne */
            suivant(m->liste_collisions);
            continue;
        }

        if(SDL_HasIntersection(&temp, element))
            return;
        suivant(m->liste_collisions);
    }

    if(*x_pers  + x * taille_unite < 0)
        return;
    if(*x_pers + j->statut->zone_colision.w + x * taille_unite > fenetre_finale->frame_anim->w)
        return;
    j->statut->vrai_zone_collision.x += x * taille_unite;
    if (*x_map + x * taille_unite < 0) { /* La map ne peut pas plus aller à gauche */
            *x_pers += x * taille_unite; /* On déplace le personnage de x unités */
            return;
        }
        if (*x_map + x * taille_unite > (m->text_map->width - fenetre_finale->frame_anim->w))
            { /* L'écran est en bordure de map droite */
                *x_pers += x * taille_unite;
                return;
            }
    if(rects_egal_x(&(j->statut->zone_colision), &tx))  /*On se trouve dans l'intervalle normal */
        *x_map += x * taille_unite; /* On déplace la map en fond */
    else
        *x_pers += x * taille_unite;
    
}

void deplacement_y_pers(t_map *m, joueur_t *j, int y){

    int *y_map = &(map->text_map->frame_anim->y);                                        /* La coordonnée y actuelle de la map */
    int *y_pers = &(j->statut->zone_colision.y);                                       /* La coordonnée y actuelle du joueur */
    const long int taille_unite = floor(j->textures_joueur->liste[0]->multipli_taille); /* Calcul en nombre de pixels d'une unité de déplacement */
    SDL_Rect temp = {.x = j->statut->vrai_zone_collision.x, .y = j->statut->vrai_zone_collision.y + y * taille_unite, .w = j->statut->vrai_zone_collision.w, .h = j->statut->vrai_zone_collision.h};

    en_tete(m->liste_collisions);

    while (!hors_liste(m->liste_collisions))
    {
        SDL_Rect *element = valeur_elt(m->liste_collisions);

        if (element == &j->statut->vrai_zone_collision){ /* Si la collision nou concerne */
            suivant(m->liste_collisions);
            continue;
        }

        if (SDL_HasIntersection(&temp, element))
            return;
        suivant(m->liste_collisions);
    }

    if (*y_pers + y * taille_unite < 0) /* Le personnage ne peut pas aller en haut */
        return;
    if (*y_pers + j->statut->zone_colision.h + y * taille_unite > fenetre_finale->frame_anim->h) /* Le personnage ne peut pas aller en bas */
        return;
    j->statut->vrai_zone_collision.y += y * taille_unite;
    if (*y_map + y * taille_unite < 0){ /* La map ne peut pas plus aller en haut */
        *y_pers += y * taille_unite; /* On déplace le personnage de x unités */
        return;
    }
    if (*y_map + y * taille_unite > (m->text_map->height - fenetre_finale->frame_anim->h)){ /* L'écran est en bordure de map bas*/
        *y_pers += y * taille_unite;
        return;
    }
    if (rects_egal_y(&(j->statut->zone_colision), &ty)) /*On se trouve dans l'intervalle normal */
        *y_map += y * taille_unite;                                    /* On déplace la map en fond */
    else
        *y_pers += y * taille_unite;
}

void text_copier_position(t_aff * a_modifier, const t_aff * const original){
    a_modifier->aff_fenetre->x = original->aff_fenetre->x;
    a_modifier->aff_fenetre->y = original->aff_fenetre->y;
}

bool rects_egal_x(const SDL_Rect * const r1, SDL_Rect const * const r2){

    if(r1->w != r2->w)
        return faux;

    if(r1->x == r2->x)
        return vrai;

    return faux;
}

bool rects_egal_y(const SDL_Rect *const r1, SDL_Rect const *const r2){

    if (r1->h != r2->h)
        return faux;

    if (r1->y == r2->y)
        return vrai;

    return faux;
}

SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
   SDL_Color col = {r,g,b,a};
   return col;
}

void placer_texture(t_aff *texture, int x, int y){
    x = floor(x * texture->multipli_taille);
    y = floor(y * texture->multipli_taille);

    texture->aff_fenetre->x = x;
    texture->aff_fenetre->y = y;
}

void boucle_sprite(t_aff * texture, joueur_t ** joueurs){
    int debut, fin;
    float temps_passe;
    int fini = 0;

    while(!fini){
        debut = SDL_GetPerformanceCounter();

        if ((compteur % 5) == 0){ /*compteur%5 pour la vitesse d'affichage*/
            //affichage du rendu
            SDL_RenderClear(rendu_principal);

            /* On affiche la carte */
            afficher_texture(map->text_map, rendu_principal);

            /* On affiche les joueur */
            afficher_texture(joueurs[0]->textures_joueur->liste[TEXT_MARCHER], rendu_principal);
            afficher_texture(joueurs[1]->textures_joueur->liste[TEXT_MARCHER], rendu_principal);

            /* On affiche l'interface */
            RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)joueurs[0]->pdv/joueurs[0]->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));

            RenderHPBar(FENETRE_LONGUEUR/20, FENETRE_LARGEUR/20, FENETRE_LONGUEUR/4, FENETRE_LARGEUR/25,
            ((float)joueurs[1]->pdv/joueurs[1]->maxPdv), color(195,0,0,0.9), color(125, 125, 125, 1));

            /* On affiche l'animation */
            afficher_texture(texture, rendu_principal);
            SDL_RenderPresent(rendu_principal);

            //calcul de la suite de l'animation
            next_frame_x(texture);

            if(texture->frame_anim->x == 0){ //passage à la ligne suivante
                next_frame_y(texture);
                if(texture->frame_anim->y == 0)
                    fini = 1;
            }
        }

        fin = SDL_GetPerformanceCounter();

        //calcul du temps d'affichage
        temps_passe = (debut - fin) / (float)SDL_GetPerformanceFrequency();
        SDL_Delay(floor((200 / (float) NB_FPS) - temps_passe));
        if(compteur == NB_FPS)
            compteur = 0;
        compteur++;
    }
}

void anim_effet_joueur(t_aff * effet, int num_joueur, joueur_t ** joueurs){
    text_copier_position(effet, *(joueurs[num_joueur]->textures_joueur->liste)); //amélioration: centrer pour toutes les tailles

    boucle_sprite(effet, joueurs);
}

void rect_ecran_to_rect_map(SDL_Rect *ecran, SDL_Rect *r_map, int x, int y){
    const double multipli_x = (double) map->text_map->frame_anim->w / FENETRE_LONGUEUR;
    const double multipli_y = (double)map->text_map->frame_anim->h / FENETRE_LARGEUR;

    r_map->h = floor(ecran->h * multipli_y);
    r_map->w = floor(ecran->w * multipli_x);

    r_map->x = floor((ecran->x + x) * multipli_x);
    r_map->y = floor((ecran->y + y) * multipli_y);
}

void deplacement_x_entite(t_map *m, t_aff *texture, int x, SDL_Rect *r)
{
    const int taille_unite = floor(map->taille_case / TAILLE_PERSONNAGE);
    SDL_Rect temp = {.x = r->x + x * taille_unite, .y = r->y, .w = r->w, .h = r->h};

    en_tete(m->liste_collisions);

    while (!hors_liste(m->liste_collisions))
    {
        SDL_Rect *element = valeur_elt(m->liste_collisions);

        if (element == r){ /* Si la collision nouss concerne */
            suivant(m->liste_collisions);
            continue;
        }

        if (SDL_HasIntersection(&temp, element))
            return;
        suivant(m->liste_collisions);
    }

    if (r)
    {
        if (r->x + x * taille_unite < 0) /* Le personnage ne peut pas aller en haut */
            return;
        if (r->x + r->w + x * taille_unite > m->text_map->width) /* Le personnage ne peut pas aller en bas */
            return;
        if (texture->compteur_frame_anim % texture->duree_frame_anim)
            r->x += x * taille_unite;
    }
    else
    {
        if (texture->aff_fenetre->x + x * taille_unite < 0) /* Le personnage ne peut pas aller en haut */
            return;
        if (texture->aff_fenetre->x + texture->aff_fenetre->w + x * taille_unite > m->text_map->width) /* Le personnage ne peut pas aller en bas */
            return;
        if (texture->compteur_frame_anim % texture->duree_frame_anim)
            r->x += x * taille_unite;
    }

    if (texture->compteur_frame_anim == NB_FPS)
        (texture->compteur_frame_anim) = 0;
    else
        (texture->compteur_frame_anim)++;
}

void deplacement_y_entite(t_map *m, t_aff *texture, int y, SDL_Rect *r)
{
    const int taille_unite = floor(map->taille_case / TAILLE_PERSONNAGE);
    SDL_Rect temp = {.x = r->x, .y = r->y + y * taille_unite, .w = r->w, .h = r->h};

    en_tete(m->liste_collisions);

    while (!hors_liste(m->liste_collisions)){
        SDL_Rect *element = valeur_elt(m->liste_collisions);

        if (element == r){ /* Si la collision nou concerne */
            suivant(m->liste_collisions);
            continue;
        }

        if (SDL_HasIntersection(&temp, element))
            return;
        suivant(m->liste_collisions);
    }

    if(r)
    {
        if(r->y + y * taille_unite  < 0) /* Le personnage ne peut pas aller en haut */
            return;
        if (r->y + r->h + y * taille_unite > m->text_map->height) /* Le personnage ne peut pas aller en bas */
            return;
        if(texture->compteur_frame_anim % texture->duree_frame_anim)
            r->y += y * taille_unite;
    }
    else
    {
        if (texture->aff_fenetre->y + y * taille_unite< 0) /* Le personnage ne peut pas aller en haut */
            return;
        if (texture->aff_fenetre->y + texture->aff_fenetre->h + y * taille_unite> m->text_map->height) /* Le personnage ne peut pas aller en bas */
            return;
        if (texture->compteur_frame_anim % texture->duree_frame_anim)
            r->y += y * taille_unite;
    }


    if(texture->compteur_frame_anim == NB_FPS)
        (texture->compteur_frame_anim) = 0;
    else
        (texture->compteur_frame_anim)++;
}

void init_animations(){
    heal = (creer_texture("ressources/sprite/heal.bmp", LARGEUR_PERSONNAGE, LONGUEUR_PERSONNAGE, 0, 0, (FENETRE_LONGUEUR * 0.022f) / 16 * 3));
}

t_aff * next_frame_animation(joueur_t * joueur){
    statut_t * statut = joueur->statut;

    if (statut->animation == SOIN)
    {
        if ((compteur % 2) == 0)
        {
            /*si on a fait le tour du spritesheet soin, l'animation est terminée*/
            if (statut->duree_anim == 0)
                statut->action = RIEN;
            printf("duree_anim: %d\n", statut->duree_anim);
            next_frame_x_indice(heal, (DUREE_SOIN - statut->duree_anim)%5);
            next_frame_y_indice(heal, (DUREE_SOIN - statut->duree_anim)/5);

            statut->duree_anim--;
        }
            return heal;
    }
    else{
        return NULL;
    }
}

void lister_animations(joueur_t ** joueurs, list * animations){

    if(joueurs[0]->statut->duree_anim != 0)
        ajout_droit(animations, next_frame_animation(joueurs[0]));
    
    if(joueurs[1] != NULL){
        if(joueurs[1]->statut->duree_anim != 0)
            ajout_droit(animations, next_frame_animation(joueurs[1]));
    }
}

void afficher_animations(list * animations){
    en_tete(animations);

    while(!hors_liste(animations)){
        afficher_texture(animations->ec->valeur, rendu_principal);

        suivant(animations);
    }
}