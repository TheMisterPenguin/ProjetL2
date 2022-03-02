#include <commun.h>
#include <string.h>

/**
 * \file monstre.c
 * \author Bruneau Antoine (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

void detruire_monstre(monstre_t** monstre){
    free((**monstre).texture);
    free(*monstre);
    *monstre = NULL;
}

void detuire_base_monstres(base_monstres_t** base_monstres){
    int i;
    for(i=0; i < (**base_monstres).nb_monstre; i++){
        detruire_monstre((**base_monstres).tab + i);
    }
    free((**base_monstres).tab);
    free(*base_monstres);
    *base_monstres = NULL;
}



base_monstres_t* charger_monstres(char* nom_fichier){
    FILE* fichier = fopen(nom_fichier, "r");
    char tampon[30];
    int i;
    int nb_monstre = 0;
    int pdv, attaque, gainXp;
    float vitesse;
    monstre_t* monstre;

    if(!fichier){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier : %s\n");
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

    //allocation de base_monstre avec le nombre de monstre nécéssaire
    base_monstres_t* base_monstres = malloc(sizeof(base_monstres_t));
    base_monstres->tab = malloc(sizeof(monstre_t*) * nb_monstre);
    base_monstres->nb_monstre = nb_monstre;
    
    fscanf(fichier, "%s", tampon);
    i = 0;
    //tant qu'on est pas arrivé à la fin du fichier
    while(strcmp(tampon,"END")){
        if(tampon[0] == '['){
            monstre = malloc(sizeof(monstre_t));
            //inserrer les caractèristiques dans monstre_t
            strcpy(monstre->nom_monstre,tampon);
            fscanf(fichier, "%d", &pdv);
            monstre->pdv = pdv;
            fscanf(fichier, "%d", &attaque);
            monstre->attaque = attaque;
            fscanf(fichier, "%f", &vitesse);
            monstre->vitesse = vitesse;
            fscanf(fichier, "%d", &gainXp);
            monstre->gainXp = gainXp;
            //inserrer monstre_t dans base_monstre_t
            base_monstres->tab[i++] = monstre;
        }
        fscanf(fichier, "%s", tampon);
    }
    return base_monstres;  
}