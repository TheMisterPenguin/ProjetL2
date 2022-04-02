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
    liste_base_sort[SP_WITCHER].collision.w = TAILLE_CASE;
    liste_base_sort[SP_WITCHER].collision.h = TAILLE_CASE;

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
            sort->collision.h = liste_base_sort[SP_WITCHER].collision.h;
            sort->collision.w = liste_base_sort[SP_WITCHER].collision.w;
            sort->type = SP_WITCHER;
            sort->texture = creer_texture(PATH_SPELL_WITCHER, LARGEUR_ENTITE, LONGUEUR_ENTITE, monstre->collision.x, monstre->collision.y , 1);
            orienter_sort_vers_joueur(monstre, sort, joueur);
        default : break;
    }
    ajout_droit(map->liste_sorts , sort);
    ajout_droit(map->liste_collisions, &(sort->collision));

}

void orienter_sort_vers_joueur(monstre_t * monstre, sort_t * sort, joueur_t * joueur){
    double x_joueur = distance_x_joueur(monstre->collision, joueur);
    double y_joueur = distance_y_joueur(monstre->collision, joueur);
    double x_ref = 0;
    double y_ref = 1;
    double cos0;
    double teta;
    /*calcul de l'angle entre les 2 vecteurs*/
    cos0 = (x_joueur * x_ref + y_joueur * y_ref) / (sqrt(x_joueur * x_joueur + y_joueur * y_joueur) * sqrt(x_ref * x_ref + y_ref * y_ref));
    teta = acos(cos0);
    next_frame_x_indice(sort->texture, round(teta/45));
}

void action_sort(sort_t * sort){

}