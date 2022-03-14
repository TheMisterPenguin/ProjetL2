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
	
	strcpy(perso->nom_pers, nom);
	perso->niveau = 0;
	perso->xp = 0;
	perso->maxPdv = 10;
	perso->pdv = 10;
	perso->attaque = 10;
	perso->defense = 10;
	perso->vitesse = 1;
	perso->trigger = malloc(sizeof(byte) * TAILLE_TRIGGER);
	perso->statut = malloc(sizeof(statut_t));
	perso->statut->duree = 0;
	perso->statut->en_mouvement = 0;
	perso->statut->orientation = SUD;
	perso->statut->bouclier_equipe = 0;
	perso->statut->action = RIEN;
	
	return perso;
}

void detruire_joueur(joueur_t *j){

	free(j->nom_pers);
	free(j->trigger);
	free(j->statut);
	free(j);
}

joueur_t *caracteristiques(joueur_t* perso){
	perso->attaque = 10+1*(perso->niveau);
	perso->defense = 10+1*(perso->niveau);
	perso->maxPdv = 10+5*(perso->niveau);
	perso->pdv = perso->maxPdv;
	return perso;
}

void afficher_statistiques(joueur_t* perso){
	if(perso != NULL){
		printf("Nom : %s\nNiveau : %d\nExpérience : %d\nPoints de vie max : %d\nPoints de vie actuels : %d\nAttaque : %d\nDéfense : %d\nVitesse : %d\n",
		perso->nom_pers,perso->niveau,perso->xp,perso->maxPdv,perso->pdv,perso->attaque,perso->defense,perso->vitesse);
	} else {
		printf("Pas de perso\n");
	}	
}

joueur_t *levelup(joueur_t* perso){
	perso->niveau += 1;
	caracteristiques(perso);
	return perso;
}

joueur_t *gain_xp(joueur_t* perso){
	while(perso->xp >= 150+100*perso->niveau){
		perso->xp = (perso->xp)-(150+100*(perso->niveau));
		levelup(perso);		
	}
	return perso;
}