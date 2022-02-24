#include <stdlib.h>
#include <commun.h>
#include <string.h>
#include <stdio.h>

/**
 * \file objet.c
 * \author Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les objets
 * \version 0.2
 * \date 24/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

objet_t *creer_objet(const t_item type, const char * nom, const short int niveau, const int att, const int def, const int vit)
{
    objet_t *obj = malloc(sizeof(objet_t));
    obj->nom = malloc(sizeof(char) * strlen(nom) + 1);
    
    obj->type = type;
    strcpy(obj->nom, nom);
    obj->niveau = niveau;
    obj->attaque = att;
    obj->defense = def;
    obj->vitesse = vit;

    return obj;
}

// void init_objet(){
//     FILE * obj;
//     t_item type;
//     char nom[50];
//     int niveau;
//     int att;
//     int def;
//     int vit;

//     obj = fopen("ressource/objet.txt", "r");

//     if(obj == NULL){
//         printf("erreur, fichier objet inaccessible\n");
//         return;
//     }
    
//     while(fscanf(obj, "%i%50[^:]:%i%i%i%i", (int *)&type, nom, &niveau, &att, &def, &vit) == 6){
//         printf("%i %s %i %i %i %i\n", type, nom, niveau, att, def, vit);
//     }

//     fclose(obj);
// }

void detruire_objet(objet_t *obj){
    free(obj->nom);
    free(obj);
}