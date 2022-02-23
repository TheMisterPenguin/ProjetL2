#include <stdlib.h>
#include <commun.h>
#include <string.h>

/**
 * \file objet.c
 * \author Descomps Max
 * \brief Fichier contenant toutes les fonctions concernant les objets
 * \version 0.1
 * \date 23/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

objet_t *creer_objet(const char * nom, const short int niveau, const int att, const int def, const int vit)
{
    objet_t *obj = malloc(sizeof(objet_t));
    obj->nom = malloc(sizeof(char) * strlen(nom) + 1);
    
    strcpy(obj->nom, nom);
    obj->niveau = niveau;
    obj->attaque = att;
    obj->defense = def;
    obj->vitesse = vit;
}

void detruire_objet(objet_t *obj){
    free(obj->nom);
    free(obj);
}