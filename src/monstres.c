#include <monstres.h>
#include <string.h>
#include <personnage.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/**
 * \file monstre.c
 * \author Bruneau Antoine (Antoine.Bruneau.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 03/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

srand(time(NULL)); //initialisation des nombres aléatoires

void detruire_monstre(monstre_t** monstre){
    free((**monstre).texture);
    free(*monstre);
    *monstre = NULL;
}

void detruire_liste_base_monstres(liste_base_monstres_t** liste_base_monstres){

    int i;
    for(i=0; i < (**liste_base_monstres).nb_monstre; i++){
        free((**liste_base_monstres).tab[i]);
    }
    free((**liste_base_monstres).tab);
    free(*liste_base_monstres);
    *liste_base_monstres = NULL;
}

monstre_t* creer_monstre(liste_base_monstres_t* liste_base_monstre, char* nom_monstre, position_t position){
    int i;
    base_monstre_t* base_monstre;
    /* allocation monstre_t*/
    monstre_t* monstre = malloc(sizeof(monstre_t));
    
    for(i=0; i<liste_base_monstre->nb_monstre; i++){
        if(strcmp(liste_base_monstre->tab[i]->nom_monstre,nom_monstre) == 0){
            strcpy(monstre->nom_monstre,nom_monstre);
            monstre->position = position;
            monstre->texture = //cree_texture
            /*copie les informations de base_monstre dans monstre*/
            base_monstre = liste_base_monstre->tab[i];
            monstre->pdv = base_monstre->pdv;
            monstre->attaque = base_monstre->attaque;
            monstre->vitesse = base_monstre->vitesse;
            monstre->gainXp = base_monstre->gainXp;

            return monstre;
        }
    }
    return NULL;
}

liste_base_monstres_t* charger_monstres(char* nom_fichier){
    FILE* fichier = fopen(nom_fichier, "r");
    char tampon[30];
    int i;
    int nb_monstre = 0;
    base_monstre_t* base_monstre;
    liste_base_monstres_t* liste_base_monstres = NULL;

    if(!fichier){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier\n");
        return NULL;
    }

    fscanf(fichier, "%s", tampon);
    //tant qu'on est pas arrivé à la fin du fichier
    while(strcmp(tampon,"END")){
        //compte le nombre de monstre
        if(tampon[0] == '[')
            nb_monstre++;
        fscanf(fichier, "%s", tampon);
    }
    //revient au début du fichier
    fseek(fichier,0,SEEK_SET);

    //allocation de liste_base_monstre avec le nombre de monstre nécéssaire
    liste_base_monstres = malloc(sizeof(liste_base_monstres_t));
    liste_base_monstres->tab = malloc(sizeof(monstre_t*) * nb_monstre);
    liste_base_monstres->nb_monstre = nb_monstre;
    
    fscanf(fichier, "%s", tampon);
    i = 0;
    //tant qu'on est pas arrivé à la fin du fichier
    while(strcmp(tampon,"END")){
        if(tampon[0] == '['){
            base_monstre = malloc(sizeof(base_monstre_t));
            //inserrer les caractèristiques dans base_monstre_t
            strcpy(base_monstre->fichier_image,tampon);
            fscanf(fichier, "%s", base_monstre->nom_monstre);
            fscanf(fichier, "%d", &(base_monstre->pdv));
            fscanf(fichier, "%d", &(base_monstre->attaque));
            fscanf(fichier, "%f", &(base_monstre->vitesse));
            fscanf(fichier, "%d", &(base_monstre->gainXp));
            //inserrer monstre_t dans liste_base_monstre_t
            liste_base_monstres->tab[i++] = base_monstre;
        }
        fscanf(fichier, "%s", tampon);
    }
    fclose(fichier);
    return liste_base_monstres;  
}












int distance_joueur(monstre_t * monstre){
    int x = distance_x_joueur(monstre);
    int y = distance_y_joueur(monstre);

    return sqrt(x*x + y*y);
}

int distance_x_joeur(monstre_t * monstre){
    return monstre->collision.x - perso_principal->zone_collision.x;
}

int distance_y_joeur(monstre_t * monstre){
    return monstre->collision.y - perso_principal->zone_collision.y;
}


void marcher_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, (current_frame_x(monstre->texture)+1) % 2);
        default : break; 
    }
}

void orienter_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(WITCHER): next_frame_x_indice(monstre->texture, monstre->orientation); break;
        case(KNIGHT): next_frame_y_indice(monstre->texture, monstre->orientation); break;
        case(BOSS): /**/ break;
        default : break; 
    }
}

void monstre_en_garde(monstre_t * monstre){
    switch(monstre->type){
        case(KNIGHT): next_frame_x_indice(monstre->texture, 2); break;
        default : break; 
    }
}

void monstre_attaque(monstre_t * monstre /*liste texture sort*/){
    switch(monstre->type){
        case(WITCHER): next_frame_y_indice(monstre->texture, 1); break ;
        default: break;
    //creation texture sort + insertion dans liste sorts
    }
}

void fuir_joueur(monstre_t *monstre){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre);
    y_diff = distance_y_joeur(monstre);

    if( x_diff > y_diff ){
        if(y_diff < 0)
            monstre->orientation = SUD;
        else
            monstre->orientation = NORD;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = OUEST;
        else
            monstre->orientation = EST;
    }
    orienter_monstre(monstre);
    marcher_monstre(monstre);
}

void rush_joeur(monstre_t * monstre){
    int y_diff, x_diff;
    x_diff = distance_x_joueur(monstre);
    y_diff = distance_y_joeur(monstre);

    if( x_diff > y_diff ){
        if(y_diff < 0)
            monstre->orientation = NORD;
        else
            monstre->orientation = SUD;
    }
    else{
        if(x_diff < 0)
            monstre->orientation = EST;
        else
            monstre->orientation = OUEST;
    }
    orienter_monstre(monstre);
    marcher_monstre(monstre);
}

void agro_witcher(monstre_t * monstre){
    if(monstre->action == RUSH_OU_FUITE)
        if(monstre->duree > 0)
            if(compteur%5 == 0)
                fuir_joueur(monstre);
        else{
            monstre->action = MONSTRE_ATTAQUE;
            monstre->duree = DUREE_MONSTRE_ATTAQUE;
        }
    else
        if(monstre->duree > 0)
            if(compteur%5 == 0)
                monstre_attaque(monstre);
        else{
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
        }  
}

void agro_knight(monstre_t * monstre){
    if(monstre->action == RUSH_OU_FUITE){
        if(monstre->duree > 0)
            if(compteur%5 == 0)
                rush_joueur(monstre);
        else
            monstre->duree = DUREE_RUSH_OU_FUITE;
    }
}

void agro_monstre(monstre_t * monstre){
    switch(monstre->type){
        case(WITCHER): agro_witcher(monstre); break;
        case(KNIGHT): agro_knight(monstre); break;
        default : break; 
    }
}

void ronde_monstre(monstre_t * monstre){
    if(monstre->duree == 0){
        if(rand()%10){
            monstre->action = MONSTRE_MARCHER;
            monstre->duree = DUREE_MONSTRE_MARCHER;
            monstre->orientation = rand()%4;
            orienter_monstre(monstre);
        }else{
            monstre->action = MONSTRE_EN_GARDE;
            monstre->duree = DUREE_MONSTRE_EN_GARDE;
        }
    }
    if(monstre->action == MONSTRE_MARCHER){
        if(compteur%5 == 0)
            marcher_monstre(monstre);
        /*x et y*/
    }
    else
        monstre_en_garde(monstre);
}

void action_monstre(monstre_t * monstre){
    int choix;

    (monstre->duree)--;

    if(monstre->action == MONSTRE_MARCHER || monstre->action == MONSTRE_EN_GARDE){
        //si le monstre détecte le joueur
        if(distance_joueur(monstre) < DISTANCE_AGRO){
            monstre->action = RUSH_OU_FUITE;
            monstre->duree = DUREE_RUSH_OU_FUITE;
        }
        else
            ronde_monstre(monstre);
    }
    else
        agro_monstre(monstre);
    
    if(monstre->action == MONSTRE_MARCHER || monstre->action == RUSH_OU_FUITE)
        switch(monstre->orientation){
            case(NORD): (monstre->collision.y) += 3*(map->unite_dep_y); break;
            case(EST): (monstre->collision.x) += 3*(map->unite_dep_x); break;
            case(SUD): (monstre->collision.y) += 3*(map->unite_dep_y); break;
            case(OUEST): (monstre->collision.x) += 3*(map->unite_dep_x); break;
            default: break;
        }
}