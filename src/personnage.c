#include <stdlib.h>
#include <string.h>
#include <personnage.h>
#include <affichage.h>
#include <json-c/json.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <code_erreur.h>

#ifndef _WIN32
	#include <pwd.h>
	#include <unistd.h>
#endif

void copy(const byte * origin, byte *out, size_t size){
	for(unsigned int i = 0; i < size; i++)
		out[i] = origin[i];
}

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

char save_path[500];

void check_repertoire_jeux(){
	struct stat stats;

	struct passwd *pw = getpwuid(getuid());

	sprintf(save_path, "%s/%s", pw->pw_dir, SAVE_PATH); /* On récupère le répertoire home */

	stat(save_path, &stats);
	if (S_ISDIR(stats.st_mode)){ /* Si le repertoire existe */
		printf("Le répertoire de sauvegarde existe déja\n");
		return;
	}

	int err = mkdir(save_path, S_IRWXU); /* On créer le répertoire */

	printf("Création du répertoire de sauvegarde : %s\n", save_path);

	if (err == -1){ /* On regarde s'il y a une erreur */ 
		switch (errno)
		{
		case EACCES:
			printf("Le dossier parent n'autorise pas l'écriture\n");
			exit(EXIT_FAILURE);
		case ENOENT :
			printf("Le dossier spécifié est introuvable !\n");
			exit(EXIT_FAILURE);
		default:
			perror("mkdir");
			exit(EXIT_FAILURE);
		}
	}
}

joueur_t *perso_principal;

void creer_sauvegarde_json(joueur_t *j){
	/* Object JSON principal */
	json_object *sauvegarde = json_object_new_object();

	json_object *nom_joueur = json_object_new_string(j->nom_pers);
	json_object *niveau = json_object_new_int(j->niveau);
	json_object *xp = json_object_new_int(j->xp);
	json_object *maxPdv = json_object_new_int(j->maxPdv);
	json_object *pdv = json_object_new_int(j->pdv);
	json_object *attaque = json_object_new_int(j->attaque);
	json_object *defense = json_object_new_int(j->defense);
	json_object *orientation = json_object_new_int(j->statut->orientation);
	json_object *bouclier_equipe = json_object_new_boolean(j->statut->bouclier_equipe);
	json_object *x_map = json_object_new_int(j->statut->zone_colision.x);
	json_object *y_map = json_object_new_int(j->statut->zone_colision.y);

	/* Création des tableaux */
	json_object *statut = json_object_new_object();
	json_object *trigger = json_object_new_array_ext(TAILLE_TRIGGER);

	json_object *trigger_value;

	for(unsigned int i = 0; i < TAILLE_TRIGGER; i++){
		trigger_value = json_object_new_int( (int) j->trigger[i]);
		json_object_array_add(trigger, trigger_value);
	}

	json_object_object_add(statut, "Orientation", orientation);
	json_object_object_add(statut, "Bouclie equipee", bouclier_equipe);
	json_object_object_add(statut, "x map", x_map);
	json_object_object_add(statut, "y map", y_map);

	json_object_object_add(sauvegarde, "Nom Joueur", nom_joueur);
	json_object_object_add(sauvegarde, "Niveau", niveau);
	json_object_object_add(sauvegarde, "Points d'experience", xp);
	json_object_object_add(sauvegarde, "Pv", pdv);
	json_object_object_add(sauvegarde, "Points de vie Max", maxPdv);
	json_object_object_add(sauvegarde, "Attaque", attaque);
	json_object_object_add(sauvegarde, "Defense", defense);
	json_object_object_add(sauvegarde, "Statut", statut);
	json_object_object_add(sauvegarde, "Triggers", trigger);

	char *path = calloc(strlen(save_path) + 15, sizeof(char));

	sprintf(path,"%s/perso.sav", save_path);

	//json_object_to_file(path, sauvegarde);

	printf("%s\n", path);

	FILE * sauv = fopen(path, "w");

	if(!sauv){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur lors de la sauvegarde", "Imposible de créer le fichier de la sauvegarde \n", NULL);
		exit(ERREUR_FICHIER);
	}

	const char * json = json_object_to_json_string(sauvegarde);

	fwrite(json,sizeof(char),strlen(json), sauv);

	fclose(sauv);

	free(path);

}

bool sauv_existe(char *nom_sauv){
	if(fopen(nom_sauv,"r"))
		return vrai;

	return faux;
}

joueur_t *charger_sauvegarde_joueur(char *nom_sauv){

	/* On récupère la sauvegarde */
	json_object *sauvegarde = json_object_from_file(nom_sauv);

	if(!sauvegarde){
		fprintf(stderr,"Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	/* On récupère les valeurs dans la sauvegarde */
	json_object *nom_joueur = json_object_object_get(sauvegarde, "Nom Joueur");
	if (!nom_joueur){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *niveau = json_object_object_get(sauvegarde, "Niveau");
	if (!niveau){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *xp = json_object_object_get(sauvegarde, "Points d'experience");
	if (!xp)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *maxPdv = json_object_object_get(sauvegarde, "Points de vie Max");
	if (!maxPdv)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *attaque = json_object_object_get(sauvegarde, "Attaque");
	if (!attaque)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *defense = json_object_object_get(sauvegarde, "Defense");
	if (!defense)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *statut = json_object_object_get(sauvegarde, "Statut");
	if (!statut)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}


}

joueur_t *new_joueur(const char* nom){
	byte *trig = calloc(TAILLE_TRIGGER, sizeof(byte));

	joueur_t *j = creer_joueur(nom, 0, 0, 10, 10, 10, 10, 1, trig, NORD, faux);
	free(trig);

	return j;
}

joueur_t *creer_joueur(const char *nom, const int niveau, const int xp, const int maxPdv, const int pdv, const int attaque, const int defense, const int vitesse, const byte trig[TAILLE_TRIGGER], const t_direction orientation, const bool bouclier_equipe)
{

	joueur_t * perso = malloc(sizeof(joueur_t));
	perso->nom_pers = malloc(sizeof(char) * (strlen(nom) + 1));
	
	strcpy(perso->nom_pers, nom);
	perso->niveau = niveau;
	perso->xp = xp;
	perso->maxPdv = maxPdv;
	perso->pdv = pdv;
	perso->attaque = attaque;
	perso->defense = defense;
	perso->vitesse = vitesse;
	perso->trigger = calloc(TAILLE_TRIGGER, sizeof(byte));
	copy(trig, perso->trigger, TAILLE_TRIGGER);
	perso->statut = malloc(sizeof(statut_t));
	perso->statut->duree = 0;
	perso->statut->en_mouvement = faux;
	perso->statut->orientation = orientation;
	perso->statut->bouclier_equipe = bouclier_equipe;
	perso->statut->action = RIEN;

	perso->textures_joueur = init_textures_joueur(perso);

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