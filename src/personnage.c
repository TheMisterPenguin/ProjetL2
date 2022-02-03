#include <stdlib.h>
#include "personnage.h"

/**
 * \file personnage.c
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant le personnage
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */



joueur_t * creer_personnage(char * nom){
	joueur_t * perso = malloc(sizeof(joueur_t));
	perso->nom_pers = malloc(sizeof(char) * strlen(nom));
}