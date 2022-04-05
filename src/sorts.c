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

base_sort_t liste_base_sort[3];


void init_liste_base_sort(liste_base_monstres_t * liste_base_monstres){
    liste_base_sort[SP_WITCHER].type = SP_WITCHER;
    liste_base_sort[SP_WITCHER].collision.w = 15;
    liste_base_sort[SP_WITCHER].collision.h = 15;
    liste_base_sort[SP_WITCHER].degat = liste_base_monstres->tab[WITCHER].attaque;
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
            sort->degat = liste_base_sort[SP_WITCHER].degat;
            sort->type = SP_WITCHER;
            sort->texture = creer_texture(PATH_SPELL_WITCHER, LARGEUR_ENTITE, LONGUEUR_ENTITE, monstre->collision.x, monstre->collision.y , map->taille_case / TAILLE_CASE);
            sort->texture->duree_frame_anim = NB_FPS;
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
        next_frame_x_indice(sort->texture, (int)round((360-teta)/(double)45) % 8);
    else
        next_frame_x_indice(sort->texture, (int)round(teta/(double)45) % 8);
}

void action_sort(sort_t * sort, joueur_t joueur[2]){
    int orientation = current_frame_x(sort->texture);
    bool deplacer_1 = vrai;
    bool deplacer_2 = vrai;

    place_rect_center_from_point(sort->texture->aff_fenetre, get_rect_center_coord(&sort->collision));
    printf("orientation = %d\n", orientation);
    switch(orientation){
        case 0:
            deplacer_1 = deplacement_y_entite(map, sort->texture, -2, &(sort->collision) ); 
            printf("deplacement_1 = %d\n", deplacer_1);break;
        case 1:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 1, &(sort->collision) );
            printf("deplacement_1 = %d\n", deplacer_1);
            deplacer_2 = deplacement_y_entite(map, sort->texture, -1, &(sort->collision) );
            printf("deplacement_2 = %d\n", deplacer_2);
            break;
        case 2:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case 3:
            deplacer_1 = deplacement_x_entite(map, sort->texture, 1, &(sort->collision) );
            deplacer_2 = deplacement_y_entite(map, sort->texture, 1, &(sort->collision) ); break;
        case 4:
            deplacer_1 = deplacement_y_entite(map, sort->texture, 2, &(sort->collision) ); break;
        case 5:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -1, &(sort->collision) );
            deplacer_2 = deplacement_y_entite(map, sort->texture, 1, &(sort->collision) ); break;
        case 6:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -2, &(sort->collision) ); break;
        case 7:
            deplacer_1 = deplacement_x_entite(map, sort->texture, -1, &(sort->collision) ); 
            deplacer_2 = deplacement_y_entite(map, sort->texture, -1, &(sort->collision) ); break;
        default : break;
    }

    /* detruit sort si rencontre un obstacle qui n'est pas un joueur*/
    if(deplacer_1 == faux || deplacer_2 == faux)
        if(valeur_elt(map->liste_collisions) != &(joueur[0].statut->vrai_zone_collision)){
            detruire_collision_dans_liste(map->liste_collisions, &(sort->collision));
		    oter_elt(map->liste_sorts);
            printf("c'est un mur\n");
        }

}