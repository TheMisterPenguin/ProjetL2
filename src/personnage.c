#include <stdlib.h>
#include <commun.h>
#include <string.h>

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

joueur_t *perso_principal;

FILE * sauv_existe(char *nom_sauv){
	FILE * f = fopen(nom_sauv,"r+");
}

joueur_t *charger_sauvegarde_joueur(FILE *sauvegarde){
	
}

joueur_t *creer_joueur(const char *nom)
{

	joueur_t * perso = malloc(sizeof(joueur_t));
	perso->nom_pers = malloc(sizeof(char) * (strlen(nom) + 1));
	perso->trigger = malloc(sizeof(byte) * TAILLE_TRIGGER);
	strcpy(perso->nom_pers, nom);
	
	return perso;
}

void detruire_joueur(joueur_t *j){

	free(j->nom_pers);
	free(j->trigger);
	free(j);
}