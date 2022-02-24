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

objet_t ** init_objet(){
    objet_t ** tabObj; //pointeur d'objets retourné
    FILE * obj; //fichier source contenant les objets


    t_item type;
    char nom[50];
    int i = 0, niveau, att, def, vit;
    char c;
    int nbObj = 0; //nombre d'objets dans le fichier source

    obj = fopen("../ressource/objet.txt", "r");

    if(obj == NULL){
        fprintf( stderr, "fichier source objet inaccessible\n") ;
        return((objet_t**)NULL);
    }
    //compte les objets (1 par ligne)
    while(fscanf(obj, "%c", &c) == 1){
        if(c == '\n') nbObj++;
    }

    fseek(obj,0,SEEK_SET); // le pointeur du fichier pointe à son début

    if( (tabObj = malloc(sizeof(objet_t*) * nbObj)) == NULL ){
        fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] obj1s\n",
      		   nbObj ) ;
      	  return((objet_t**)NULL);
    }

    while(fscanf(obj, "%d%50[^:]:%d%d%d%d", (int *)&type, nom, &niveau, &att, &def, &vit) == 6){
        tabObj[i] = creer_objet(type, nom, niveau, att, def, vit);
    }

    fclose(obj);

    return tabObj;
}

void afficher_objet(objet_t * obj){
    printf("type: %d\nnom: %s\nniveau: %d\nattaque: %d\ndefense: %d\nvitesse: %d\n",
    obj->type, obj->nom, obj->niveau, obj->attaque, obj->defense, obj->vitesse);
}

void detruire_objet(objet_t *obj){
    free(obj->nom);
    free(obj);
}