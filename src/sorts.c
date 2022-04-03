#include <sorts.h>
#include <monstres.h>
#include <personnage.h>
#include <affichage.h>
#include <listes.h>
#include <map.h>



/**
 * \file sorts.c
 * \author Antoine Bruneau (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les sorts
 * \version 0.1
 * \date 22/03/2022
 * \copyright Copyright (c) 2022
 */

base_sort_t liste_base_sort[3];


void init_liste_base_sort(){
    liste_base_sort[SP_WITCHER].type = SP_WITCHER;
    liste_base_sort[SP_WITCHER].collision.w = 18;
    liste_base_sort[SP_WITCHER].collision.h = 18;
}

void creer_sort_monstre(monstre_t * monstre, joueur_t * joueur){
    sort_t * sort = malloc(sizeof(sort_t));

    sort->cible.x = joueur->statut->vrai_zone_collision.x;
    sort->cible.y = joueur->statut->vrai_zone_collision.x;
    sort->statut = LANCER;
    sort->collision.x = monstre->collision.x;
    sort->collision.y = monstre->collision.y;
    switch(monstre->type){
        case WITCHER :
            sort->collision.h = liste_base_sort[SP_WITCHER].collision.h * (map->taille_case / TAILLE_CASE);
            sort->collision.w = liste_base_sort[SP_WITCHER].collision.w * (map->taille_case / TAILLE_CASE);
            sort->type = SP_WITCHER;
            sort->texture = creer_texture(PATH_SPELL_WITCHER, LARGEUR_ENTITE, LONGUEUR_ENTITE, monstre->collision.x, monstre->collision.y , map->taille_case / TAILLE_CASE);
            sort->texture->duree_frame_anim = NB_FPS;
            /* placer texture */
            
            orienter_sort_vers_joueur(monstre, sort, joueur);
        default : break;
    }
    ajout_droit(map->liste_sorts , sort);
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
        next_frame_x_indice(sort->texture, round((360-teta)/(double)45));
    else
        next_frame_x_indice(sort->texture, round(teta/(double)45));
}

void action_sort(sort_t * sort){
    int orientation = current_frame_x(sort->texture);

    sort->texture->aff_fenetre->x = sort->collision.x - floor(13 * sort->texture->multipli_taille);
    sort->texture->aff_fenetre->y = sort->collision.y - floor(13 * sort->texture->multipli_taille);
    
    switch(orientation){
        case 1:
            deplacement_y_entite(map, sort->texture, -2, &(sort->collision) );
        case 0:
            deplacement_x_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case 3:
            deplacement_y_entite(map, sort->texture, 2, &(sort->collision) );
        case 2:
            deplacement_x_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case 5:
            deplacement_x_entite(map, sort->texture, -2, &(sort->collision) );
        case 4:
            deplacement_y_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case 7:
            deplacement_y_entite(map, sort->texture, -2, &(sort->collision) );
        case 6:
            deplacement_x_entite(map, sort->texture, -2, &(sort->collision) ); break;
        default : break;
    }

}