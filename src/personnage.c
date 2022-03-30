#include <stdlib.h>
#include <string.h>
#include <personnage.h>
#include <affichage.h>
#include <json-c/json.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <code_erreur.h>
#include <inventaire.h>
#include <monstres.h>
#include <sorts.h>
#include <listes.h>

#ifndef _WIN32
	#include <pwd.h>
	#include <unistd.h>
#else
	#include <direct.h>
	#include <windows.h>
#endif


/**
 * \file personnage.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant le personnage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

void copy(const byte * origin, byte *out, size_t size){
	for(unsigned int i = 0; i < size; i++)
		out[i] = origin[i];
}

char save_path[500];

void check_repertoire_jeux(){
	struct stat stats;

	#ifndef _WIN32
	struct passwd *pw = getpwuid(getuid());
	sprintf(save_path, "%s/%s", pw->pw_dir, SAVE_PATH); /* On récupère le répertoire home */
	#else
	char *home = getenv("HOMEPATH");
	sprintf(save_path, "%s\\AppData\\Local\\%s", home ,SAVE_PATH);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Répertoire de sauvegarde : %s", save_path);
	#endif

	stat(save_path, &stats);
	if (S_ISDIR(stats.st_mode)){ /* Si le repertoire existe */
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Le répertoire de sauvegarde existe déja !\n");
		return;
	}

	/* On créer le répertoire */

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Création du répertoire de sauvegarde...\n");
	#ifdef _WIN32
		int err = mkdir(save_path);
	#else
		int err = mkdir(save_path, S_IRWXU);
	#endif

	if (err != 0){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Impossible de créer le répertoire de sauvegarde : %s\n", strerror(errno));
		fermer_programme(ERR_CREATION_REPERTOIRE_SAUVEGARDE);
	}
	else
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Répertoire de sauvegarde créé !\n");
}

void creer_sauvegarde_json(joueur_t *j){

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Création du fichier de sauvegarde...\n");

	/* Object JSON principal */
	json_object *sauvegarde = json_object_new_object();

	json_object *nom_joueur = json_object_new_string(j->nom_pers);
	json_object *niveau = json_object_new_int(j->niveau);
	json_object *xp = json_object_new_int(j->xp);
	json_object *maxPdv = json_object_new_int(j->maxPdv);
	json_object *pdv = json_object_new_int(j->pdv);
	json_object *attaque = json_object_new_int(j->attaque);
	json_object *defense = json_object_new_int(j->defense);
	json_object *vitesse = json_object_new_int(j->vitesse);
	json_object *orientation = json_object_new_int(j->statut->orientation);
	json_object *bouclier_equipe = json_object_new_boolean(j->statut->bouclier_equipe);
	json_object *x_map = json_object_new_int(j->statut->zone_colision.x);
	json_object *y_map = json_object_new_int(j->statut->zone_colision.y);

	/* Création des tableaux */
	json_object *statut = json_object_new_object();
	json_object *trigger = json_object_new_array();

	json_object *trigger_value;
	for(unsigned int i = 0; i < TAILLE_TRIGGER; i++){
		trigger_value = json_object_new_int( (int) j->trigger[i]);
		json_object_array_add(trigger, trigger_value);
	}

	json_object_object_add(statut, "Orientation", orientation);
	json_object_object_add(statut, "Bouclie equipe", bouclier_equipe);
	json_object_object_add(statut, "x map", x_map);
	json_object_object_add(statut, "y map", y_map);

	json_object_object_add(sauvegarde, "Nom Joueur", nom_joueur);
	json_object_object_add(sauvegarde, "Niveau", niveau);
	json_object_object_add(sauvegarde, "Points d'experience", xp);
	json_object_object_add(sauvegarde, "Pv", pdv);
	json_object_object_add(sauvegarde, "Points de vie Max", maxPdv);
	json_object_object_add(sauvegarde, "Attaque", attaque);
	json_object_object_add(sauvegarde, "Defense", defense);
	json_object_object_add(sauvegarde, "Vitesse", vitesse);
	json_object_object_add(sauvegarde, "Statut", statut);
	json_object_object_add(sauvegarde, "Triggers", trigger);

	char *path = calloc(strlen(save_path) + 15, sizeof(char));

	sprintf(path,"%s/perso.sav", save_path);

	//json_object_to_file(path, sauvegarde);


	FILE * sauv = fopen(path, "w");

	if(!sauv){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur lors de la sauvegarde", "Imposible de créer le fichier de la sauvegarde \n", NULL);
		fermer_programme(ERREUR_FICHIER);
	}

	const char * json = json_object_to_json_string(sauvegarde);

	fwrite(json,sizeof(char),strlen(json), sauv);

	fclose(sauv);

	free(path);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fichier de sauvegarde créé !\n");
}

bool sauv_existe(char *nom_sauv){
	if(fopen(nom_sauv,"r"))
		return vrai;

	return faux;
}

joueur_t *charger_sauvegarde_joueur(char *nom_sauv){

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Chargement de la sauvegarde...\n");

	/* On récupère la sauvegarde */
	json_object *sauvegarde = json_object_from_file(nom_sauv);

	if(!sauvegarde){
		fprintf(stderr,"Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	/* On récupère les valeurs dans la sauvegarde */
	json_object *nom_joueur = json_object_object_get(sauvegarde, "Nom Joueur");
	if (!nom_joueur){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *niveau = json_object_object_get(sauvegarde, "Niveau");
	if (!niveau){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *xp = json_object_object_get(sauvegarde, "Points d'experience");
	if (!xp)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *Pdv = json_object_object_get(sauvegarde, "Pv");
	if (!Pdv){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *maxPdv = json_object_object_get(sauvegarde, "Points de vie Max");
	if (!maxPdv)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *attaque = json_object_object_get(sauvegarde, "Attaque");
	if (!attaque)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *vitesse = json_object_object_get(sauvegarde, "Vitesse");
	if (!vitesse){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *defense = json_object_object_get(sauvegarde, "Defense");
	if (!defense)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *statut = json_object_object_get(sauvegarde, "Statut");
	if (!statut)
	{
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *trigger = json_object_object_get(sauvegarde, "Triggers");
	if (!trigger){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *orientation = json_object_object_get(statut, "Orientation");
	if (!orientation){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *bouclier_equipe = json_object_object_get(statut, "Bouclie equipe");
	if (!bouclier_equipe){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *x_map = json_object_object_get(statut, "x map");
	if (!x_map){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	json_object *y_map = json_object_object_get(statut, "y map");
	if (!y_map){
		fprintf(stderr, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());

		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur lors de la lecture de la sauvegarde : %s\n", json_util_get_last_err());
		return NULL;
	}

	byte *trigger_tab = calloc(TAILLE_TRIGGER, sizeof(byte));

	if(!trigger_tab){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur lors du chargement de la sauvegarde", "Plus assez de mémoire !\n", NULL);
		fermer_programme(OUT_OF_MEM);
	}

	json_object *element_trig;

	for(unsigned int i = 0; i < TAILLE_TRIGGER; i++){
		element_trig = json_object_array_get_idx(trigger, i);
		trigger_tab[i] = (byte) json_object_get_int(element_trig);
	}

	joueur_t * j = creer_joueur(
		json_object_get_string(nom_joueur),
		json_object_get_int(niveau),
		json_object_get_int(xp),
		json_object_get_int(maxPdv),
		json_object_get_int(Pdv),
		json_object_get_int(attaque),
		json_object_get_int(defense),
		json_object_get_int(vitesse),
		trigger_tab,
		json_object_get_int(orientation),
		json_object_get_boolean(bouclier_equipe)
	);
	free(trigger_tab);

	j->statut->zone_colision.x = json_object_get_int(x_map);
	j->statut->zone_colision.y = json_object_get_int(y_map);

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Chargement de la sauvegarde réussi !");

	return j;
}

joueur_t *new_joueur(const char* nom){
	byte *trig = calloc(TAILLE_TRIGGER, sizeof(byte));

	joueur_t *j = creer_joueur(nom, 0, 0, 10, 10, 10, 10, 1, trig, NORD, faux);
	free(trig);

	j->statut->zone_colision.x = 0;
	j->statut->zone_colision.y = 0;

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
    perso->attaque_actif = attaque;
	perso->defense_actif = defense;
	perso->vitesse_actif = vitesse;
	perso->trigger = calloc(TAILLE_TRIGGER, sizeof(byte));
	copy(trig, perso->trigger, TAILLE_TRIGGER);
	perso->statut = malloc(sizeof(statut_t));
	perso->statut->duree = 0;
	perso->statut->en_mouvement = faux;
	perso->statut->orientation = orientation;
	perso->statut->bouclier_equipe = bouclier_equipe;
	perso->statut->action = RIEN;

	perso->textures_joueur = init_textures_joueur(perso);

    perso->inventaire = creer_inventaire();

	return perso;
}

void detruire_joueur(joueur_t *j){

	free(j->nom_pers);
	free(j->trigger);
	free(j->statut);
	detruire_liste_textures(&(j->textures_joueur));
	free(j);
    detruire_inventaire(&(j->inventaire));
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
		perso->nom_pers,perso->niveau,perso->xp,perso->maxPdv,perso->pdv,perso->attaque_actif,perso->defense_actif,perso->vitesse_actif);
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


void environnement_joueur(list * liste_monstre, list * liste_sort, joueur_t * joueur){
	monstre_t * monstre;
	sort_t * sort;
	t_direction orientation;

	en_tete(liste_monstre);
	en_tete(liste_sort);

	while(!hors_liste(liste_monstre)){
		monstre = valeur_elt(liste_monstre);
		//entite_en_collision renvoi un booleen ainsi qu'une orientation en paramètre
		if(entite_en_collision(monstre->collision, joueur->statut->zone_colision, &orientation)){
			/* si le coup est bloqué */
			if(joueur->statut->action == BLOQUER){
				monstre->orientation = joueur->statut->orientation;
				monstre->action = MONSTRE_BLESSE;
				monstre->duree = DUREE_MONSTRE_BLESSE;
			}
			else{
				(joueur->pdv) -= monstre->attaque;
				if(joueur->pdv <= 0)
					game_over = TRUE;
				else{
					joueur->statut->orientation = orientation;
					joueur->statut->action = J_BLESSE;
					joueur->statut->duree = DUREE_JOUEUR_BLESSE;
				}
			}
		}
		/* si un monstre est touché */
		if(joueur->statut->action == ATTAQUE){
			if(entite_subit_attaque(monstre->texture, joueur->statut)){
				(monstre->pdv) -= joueur->attaque_actif;
				if(monstre->pdv <= 0)
					oter_elt(liste_monstre);
				else{
					monstre->orientation = joueur->statut->orientation;
					monstre->action = MONSTRE_BLESSE;
				}
			}
		}
		if(joueur->statut->action == ATTAQUE_CHARGEE){
			//modif l'orientation du personnage pendant qu'il tourne
			if(entite_subit_attaque_zone(monstre->texture, joueur->statut)){
				
			}
		}
		suivant(liste_monstre);
	}


	while(!hors_liste(liste_sort)){

	}


}