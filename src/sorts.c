#include <sorts.h>
#include <monstres.h>
#include <personnage.h>
#include <listes.h>

/**
 * \file sorts.c
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les sorts
 * \version 0.1
 * \date 22/03/2022
 * \copyright Copyright (c) 2022
 */

void detruire_sort(sort_t ** sort){
    free((*sort)->texture);
    free(*sort);
    *sort = NULL;
}

void detruire_sort_cb(void * sort){
    detruire_sort(sort);
}

sort_t * ajouter_sort(sort_t* sort){
    return sort;
}

void * ajouter_sort_cb(void * sort){
    return ajouter_sort(sort);
}

base_sort_t liste_base_sort[3]; /* le tableau des différents sorts (modèles de sort) */

void init_liste_base_sort(liste_base_monstres_t * liste_base_monstres){
    liste_base_sort[SP_WITCHER].type = SP_WITCHER;
    liste_base_sort[SP_WITCHER].collision.w = TAILLE_CASE;
    liste_base_sort[SP_WITCHER].collision.h = TAILLE_CASE;
    liste_base_sort[SP_WITCHER].degat = liste_base_monstres->tab[WITCHER].attaque;
}

void creer_sort_monstre(monstre_t * monstre, joueur_t * joueur){
    sort_t * sort = malloc(sizeof(sort_t));

    /* positionner le sort sur la map à la même position que le monstre qui l'a créé */
    sort->collision.x = monstre->collision.x;
    sort->collision.y = monstre->collision.y;

    /* copier les propriétées du modèle de sort correspondant dans le sort créé */
    switch(monstre->type){
        case WITCHER :
            sort->collision.h = liste_base_sort[SP_WITCHER].collision.h * (map->taille_case / TAILLE_CASE);
            sort->collision.w = liste_base_sort[SP_WITCHER].collision.w * (map->taille_case / TAILLE_CASE);
            sort->degat = liste_base_sort[SP_WITCHER].degat;
            sort->type = SP_WITCHER;
            /* création de la texture du sort */
            sort->texture = creer_texture(PATH_SPELL_WITCHER, LARGEUR_ENTITE, LONGUEUR_ENTITE, monstre->collision.x, monstre->collision.y , map->taille_case / TAILLE_CASE);
            sort->texture->duree_frame_anim = NB_FPS;
        default : break;
    }
    orienter_sort_vers_joueur(monstre, sort, joueur);
    /* ajout du sort à la liste des sorts en jeu */
    ajout_droit(map->liste_sorts , sort);
    /* ajout du sort à la liste des collisons en jeu*/
    ajout_droit(map->liste_collisions, &(sort->collision));

}

void orienter_sort_vers_joueur(monstre_t * monstre, sort_t * sort, joueur_t * joueur){
    int x_joueur = distance_x_joueur(monstre->collision, joueur);
    int y_joueur = distance_y_joueur(monstre->collision, joueur);
    int x_ref = 0;
    int y_ref = -1;
    double cos0;
    double teta;
    /*calcul de l'angle entre les 2 vecteurs*/
    cos0 =  (x_joueur * x_ref + y_joueur * y_ref) / (sqrt((double)x_joueur * x_joueur + y_joueur * y_joueur) * sqrt((double) x_ref * x_ref + y_ref * y_ref));
    teta = acos(cos0) * CONVERTIR_RADIANT_DEGREE;
    //change d'orientation
    if(x_joueur < 0)
        next_frame_x_indice(sort->texture, (int)round((360-teta)/(double)45) % 8); /* %8 correspond au nombre nb d'orrientation du sprite du sort */
    else
        next_frame_x_indice(sort->texture, (int)round(teta/(double)45) % 8);
}

void action_sort(sort_t * sort, joueur_t joueur[2]){
    int orientation = current_frame_x(sort->texture);
    bool deplacer_1 = vrai;
    bool deplacer_2 = vrai;

    /* centre la texture du sort sur la zone de collision (hitbox) de celui-ci */
    place_rect_center_from_point(sort->texture->aff_fenetre, get_rect_center_coord(&sort->collision));
    switch(orientation){
        case NORD_2:
            deplacer_1 = deplacement_y_entite(map, sort->texture, -2, &(sort->collision) ); break; 
        case NORD_EST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 1, &(sort->collision) );
            deplacer_2 = deplacement_y_entite(map, sort->texture, -1, &(sort->collision) ); break;
        case EST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case SUD_EST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 1, &(sort->collision) );
            deplacer_2 = deplacement_y_entite(map, sort->texture, 1, &(sort->collision) ); break;
        case SUD_2:
            deplacer_1 = deplacement_y_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case SUD_OUEST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -1, &(sort->collision) );
            deplacer_2 = deplacement_y_entite(map, sort->texture, 1, &(sort->collision) ); break;
        case OUEST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -2, &(sort->collision) ); break;
        case NORD_OUEST_2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -1, &(sort->collision) ); 
            deplacer_2 = deplacement_y_entite(map, sort->texture, -1, &(sort->collision) ); break;
        default : break;
    }

    /* rencontre un obstacle */
    if(deplacer_1 == faux || deplacer_2 == faux)
        /*detruit sort si l'obstacle n'est pas un joueur*/
        if(valeur_elt(map->liste_collisions) != &(joueur[0].statut->vrai_zone_collision)){
            detruire_collision_dans_liste(map->liste_collisions, &(sort->collision));
		    oter_elt(map->liste_sorts);
        }

}