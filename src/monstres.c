#include <monstres.h>
#include <string.h>

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