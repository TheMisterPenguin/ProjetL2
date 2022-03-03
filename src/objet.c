#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <objet.h>

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
    objet_t *obj = NULL;
    
    if((obj = malloc(sizeof(objet_t))) == NULL ){
      fprintf( stderr , "creer_objet: debordement memoire lors de la creation d'un objet de type objet_t\n");
      return((objet_t *)NULL);
    }
    
    if((obj->nom = malloc(sizeof(char) * strlen(nom) + 1)) == NULL )
    {
      fprintf( stderr , "creer_objet: debordement memoire lors de la creation du nom d'un objet_t") ;
      return((objet_t *)NULL);
    }

    strcpy(obj->nom, nom);
    obj->type = type;
    obj->niveau = niveau;
    obj->attaque = att;
    obj->defense = def;
    obj->vitesse = vit;

    return obj;
}

void afficher_objet(objet_t * obj){
    if(obj != NULL){
    printf("type: %d\nnom: %s\nniveau: %d\nattaque: %d\ndefense: %d\nvitesse: %d\n",
    obj->type, obj->nom, obj->niveau, obj->attaque, obj->defense, obj->vitesse);
    }
    else printf("afficher_objet: objet vide\n");
}

void detruire_objet(objet_t **obj){
    free((*obj)->nom);
    (*obj)->nom = NULL;

    free(*obj);
    *obj = NULL;
}