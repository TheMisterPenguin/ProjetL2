#include <stdlib.h>
#include <string.h>
#include <personnage.h>
#include <affichage.h>
#include <json-c/json.h>
#include <string.h>
#include <code_erreur.h>
#include <inventaire.h>
#include <monstres.h>
#include <sorts.h>
#include <listes.h>
#include <coffres.h>
#include <map.h>




/**
 * \file personnage.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant le personnage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

static void copy(const byte * origin, byte *out, size_t size){
	for(unsigned int i = 0; i < size; i++)
		out[i] = origin[i];
}


void creer_sauvegarde_json(joueur_t *j){

	log_info( "Création du fichier de sauvegarde...\n");

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
	json_object *orientation = json_object_new_int(j->statut->orient_dep);
	json_object *bouclier_equipe = json_object_new_boolean(j->statut->bouclier_equipe);
	json_object *x_map = json_object_new_int(j->statut->vrai_zone_collision.x);
	json_object *y_map = json_object_new_int(j->statut->vrai_zone_collision.y);
	json_object *id_map = json_object_new_int(map->id_map);

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
	json_object_object_add(statut, "id map", id_map);
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

	if(!path)
		erreur("Erreur d'allocation mémoire", OUT_OF_MEM);

	sprintf(path,"%s/perso.sav", save_path);

	FILE * sauv = fopen(path, "w");

	if(!sauv)
		erreur("Erreur lors de la sauvegarde : Impossible de créer le fichier de la sauvegarde !", ERREUR_FICHIER);

	const char * json = json_object_to_json_string(sauvegarde);

	fwrite(json,sizeof(char),strlen(json), sauv);

	fclose(sauv);

	free(path);

	log_info( "Fichier de sauvegarde créé !\n");
}

bool sauv_existe(char *nom_sauv){
	if(fopen(nom_sauv,"r"))
		return vrai;

	return faux;
}

joueur_t *charger_sauvegarde_joueur(char *nom_sauv, char * f_src_obj, joueur_t *joueurs[], unsigned short int nb_joueurs){

	log_info( "Chargement de la sauvegarde...\n");

	/* On récupère la sauvegarde */
	json_object *sauvegarde = json_object_from_file(nom_sauv);
	if(!sauvegarde)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	/* On récupère les valeurs dans la sauvegarde */
	json_object *nom_joueur = json_object_object_get(sauvegarde, "Nom Joueur");
	if (!nom_joueur)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *niveau = json_object_object_get(sauvegarde, "Niveau");
	if (!niveau)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *xp = json_object_object_get(sauvegarde, "Points d'experience");
	if (!xp)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *Pdv = json_object_object_get(sauvegarde, "Pv");
	if (!Pdv)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *maxPdv = json_object_object_get(sauvegarde, "Points de vie Max");
	if (!maxPdv)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *attaque = json_object_object_get(sauvegarde, "Attaque");
	if (!attaque)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *vitesse = json_object_object_get(sauvegarde, "Vitesse");
	if (!vitesse)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *defense = json_object_object_get(sauvegarde, "Defense");
	if (!defense)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *statut = json_object_object_get(sauvegarde, "Statut");
	if (!statut)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *trigger = json_object_object_get(sauvegarde, "Triggers");
	if (!trigger)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *orientation = json_object_object_get(statut, "Orientation");
	if (!orientation)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *bouclier_equipe = json_object_object_get(statut, "Bouclie equipe");
	if (!bouclier_equipe)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *x_map = json_object_object_get(statut, "x map");
	if (!x_map)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *y_map = json_object_object_get(statut, "y map");
	if (!y_map)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	json_object *id_map = json_object_object_get(statut, "id map");
	if(!id_map)
		erreur("Erreur lors de la lecture de la sauvegarde : %s\n", ERREUR_FICHIER, json_util_get_last_err());

	byte *trigger_tab = calloc(TAILLE_TRIGGER, sizeof(byte));

	if(!trigger_tab)
		erreur("Erreur lors de la lecture de la sauvegarde : Plus assez de mémoire !\n", OUT_OF_MEM);

	json_object *element_trig;

	for(unsigned int i = 0; i < TAILLE_TRIGGER; i++){
		element_trig = json_object_array_get_idx(trigger, i);
		trigger_tab[i] = (byte) json_object_get_int(element_trig);
	}

	char nom_fichier_map[50];

    SDL_SetRenderTarget(rendu_principal, NULL);
    SDL_SetTextureBlendMode(fenetre_finale->texture, SDL_BLENDMODE_BLEND);

    for(unsigned int i = 255; i > 0; i -= 5 ){ /* Fondu (disparition de la map) */
        if (SDL_SetTextureAlphaMod(fenetre_finale->texture, i) < 0)
            fprintf(stderr, "Erreur lors de la modification de l'alpha : %s\n", SDL_GetError());
        if(SDL_RenderClear(rendu_principal) < 0)
            fprintf(stderr, "Erreur : le buffer d'affichage n'a pas pu être vidé : %s\n", SDL_GetError());
        if (afficher_texture(fenetre_finale, rendu_principal) != 0)
            fprintf(stderr,"Erreur : la texture ne peut être affichée à l'écran : %s\n", SDL_GetError());
        SDL_RenderPresent(rendu_principal);
        SDL_Delay(10);
    }

    sprintf(nom_fichier_map, "map/%d.json", json_object_get_int(id_map));
    detruire_map(&map,  joueurs, nb_joueurs);
    detruire_texture(&fenetre_finale);
    map = charger_map(nom_fichier_map);

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
		json_object_get_boolean(bouclier_equipe),
        0,
        f_src_obj
	);
	free(trigger_tab);

    init_sousbuffer(map, j);

    /* Mise à jour des textures du joueur */
    for(unsigned short int i = 0; i < 1; i++){
        
        j->statut->zone_colision.h = (map)->taille_case;
        j->statut->zone_colision.w = (map)->taille_case;

        j->statut->vrai_zone_collision.h = (map)->taille_case;
        j->statut->vrai_zone_collision.w = (map)->taille_case;

        for(unsigned int y = 0; y < j->textures_joueur->nb_valeurs; y++){
            j->textures_joueur->liste[y]->multipli_taille = (map)->taille_case / TAILLE_CASE;
            def_texture_taille(j->textures_joueur->liste[i], LONGUEUR_ENTITE * (map)->taille_case / TAILLE_CASE, LARGEUR_ENTITE * (map)->taille_case / TAILLE_CASE);
        }
    }

    tp_joueurs(map, json_object_get_int(x_map), json_object_get_int(y_map), &j, 1);


	log_info( "Chargement de la sauvegarde réussi !");

	return j;
}

joueur_t *new_joueur(const char* nom, int num_j, char * f_src_obj){
	
	log_info("Création du joueur %d...", num_j + 1);

	byte *trig = calloc(TAILLE_TRIGGER, sizeof(byte));
  
	joueur_t *j = creer_joueur(nom, 0, 0, 100, 50, 10, 10, 1, trig, NORD_1, faux, num_j, f_src_obj);
	free(trig); //pour l'instant non_utilisé (refait dans creer_joueur)

	j->statut->zone_colision.x = 0;
	j->statut->zone_colision.y = 0;

	return j;
}

joueur_t *creer_joueur(const char *nom, const int niveau, const int xp, const int maxPdv, const int pdv, const int attaque, const int defense, const int vitesse, const byte trig[TAILLE_TRIGGER], const t_direction_1 orient, const bool bouclier_equipe, const int num_j, char * f_src_obj)
{
	joueur_t * perso = malloc(sizeof(joueur_t));

	if(!perso)
		erreur("Erreur lors de la création du joueur : Plus assez de mémoire !\n", OUT_OF_MEM);

	perso->nom_pers = malloc(sizeof(char) * (strlen(nom) + 1));
	
	if(!perso->nom_pers)
		erreur("Erreur lors de la création du joueur : Plus assez de mémoire !\n", OUT_OF_MEM);
	
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

	if(!perso->trigger)
		erreur("Erreur lors de la création du joueur : Plus assez de mémoire !\n", OUT_OF_MEM);

	copy(trig, perso->trigger, TAILLE_TRIGGER);

	perso->statut = malloc(sizeof(statut_t));

	if(!perso->statut)
		erreur("Erreur lors de la création du joueur : Plus assez de mémoire !\n", OUT_OF_MEM);

	perso->statut->duree = 0;
    perso->statut->duree_anim = 0;
	perso->statut->en_mouvement = faux;
	perso->statut->orient_dep = NORD_1;
	perso->statut->bouclier_equipe = bouclier_equipe;
	perso->statut->action = RIEN;
	perso->statut->animation = RIEN;

	perso->statut->vrai_zone_collision.x = 0;
	perso->statut->vrai_zone_collision.y = 0;
	perso->statut->vrai_zone_collision.w = map->taille_case;
	perso->statut->vrai_zone_collision.h = map->taille_case;

	perso->statut->zone_colision.x = 0;
	perso->statut->zone_colision.y = 0;
	perso->textures_joueur = init_textures_joueur(perso, num_j);
	perso->inventaire = creer_inventaire(f_src_obj);
	perso->statut->texture_prec = perso->textures_joueur->liste[TEXT_MARCHER];

	return perso;
}

void detruire_joueur(joueur_t *j){

	free(j->nom_pers);
	free(j->trigger);
	free(j->statut);
	// detruire_liste_textures(&(j->textures_joueur));
	detruire_inventaire(&(j->inventaire));

	free(j);
}

void maj_statistiques(joueur_t* perso){
	perso->attaque = 10+1*(perso->niveau);
	perso->defense = 10+1*(perso->niveau);
	perso->maxPdv = 10+5*(perso->niveau);
	perso->pdv = perso->maxPdv;
}

void afficher_statistiques(joueur_t* perso){
	if(perso != NULL){
		printf("Nom : %s\nNiveau : %d\nExpérience : %d\nPoints de vie max : %d\nPoints de vie actuels : %d\nAttaque : %d\nDéfense : %d\nVitesse : %d\n",
		perso->nom_pers,perso->niveau,perso->xp,perso->maxPdv,perso->pdv,perso->attaque_actif,perso->defense_actif,perso->vitesse_actif);
	} else {
		printf("Pas de perso\n");
	}	
}

void levelup(joueur_t* perso){
	perso->niveau += 1;
	maj_statistiques(perso);
}

void gain_xp(joueur_t* perso){
	while(perso->xp >= 150+100*perso->niveau){
		perso->xp = (perso->xp)-(150+100*(perso->niveau));
		levelup(perso);		
	}
}

SDL_Rect * zone_en_dehors_hitbox(SDL_Rect * hitbox,SDL_Rect * sprite, t_direction_2 orient){
	SDL_Rect * result = malloc(sizeof(SDL_Rect));

	result->w =  hitbox->w;
	result->h =  hitbox->h;
	/* chaque orientation corespond à une zone d'attaque spécifique par rapport au joueur */
	switch(orient){
		case NORD_2:
			result->x = hitbox->x;
			result->y = hitbox->y - hitbox->h ;
			break;
		case NORD_EST_2:
			result->x = hitbox->x + hitbox->w;
			result->y = hitbox->y - hitbox->h ;
			break;
		case EST_2: 
			result->x = hitbox->x + hitbox->w;
			result->y = hitbox->y;
			break;
		case SUD_EST_2:
			result->x = hitbox->x + hitbox->w;
			result->y = hitbox->y + hitbox->h;
			break;
		case SUD_2:
			result->x = hitbox->x;
			result->y = hitbox->y + hitbox->h;
			break;
		case SUD_OUEST_2:
			result->x = hitbox->x - hitbox->w;
			result->y = hitbox->y + hitbox->h;
			break;
		case OUEST_2:
			result->x = hitbox->x - hitbox->w;
			result->y = hitbox->y;
			break;
		case NORD_OUEST_2:
			result->x = hitbox->x - hitbox->w;
			result->y = hitbox->y - hitbox->h;
			break;
		default: break;
	}
	return result;
}

SDL_bool entite_subit_attaque(SDL_Rect * monstre_hitbox, joueur_t * joueur){
	/* stocke la zone d'attaque actuelle du joueur */
	SDL_Rect * zone_attaque = zone_en_dehors_hitbox(&(joueur->statut->vrai_zone_collision), joueur->textures_joueur->liste[0]->aff_fenetre, joueur->statut->orient_att);
	SDL_Rect * hitbox = malloc(sizeof(SDL_Rect));
	hitbox->w = monstre_hitbox->w;
	hitbox->h = monstre_hitbox->h;
	hitbox->x = monstre_hitbox->x;
	hitbox->y = monstre_hitbox->y;
	
	/* regarde si la zone d'attaque du joueur est en contact avec la hitbox du monstre */
	SDL_bool statut = SDL_HasIntersection(zone_attaque, hitbox);
	free(zone_attaque);
	free(hitbox);
	return statut;
}

SDL_bool entite_en_collision(SDL_Rect * entite_1, SDL_Rect * entite_2, t_direction_1 * cote_entite_1, t_direction_1 * cote_entite_2){
	SDL_Rect temp;
	temp.w = entite_1->w;
	temp.h = entite_1->h;
	temp.y = entite_1->y;

	/* test collision cote OUEST de l'entite_1 */
	temp.x = entite_1->x - 1;
	if(SDL_HasIntersection(&temp,  entite_2)){
		/* cotés en collision */
		*cote_entite_1 = OUEST_1;
		*cote_entite_2 = EST_1;
		return vrai;
	}
	/* test collision cote EST de l'entite_1 */
	temp.x = entite_1->x + 1;
	if(SDL_HasIntersection(&temp,  entite_2)){
		/* cotés en collision */
		*cote_entite_1 = EST_1;
		*cote_entite_2 = OUEST_1;
		return vrai;
	}
	/* remise à l'origine */
	temp.x = entite_1->x;

	/* test collision cote NORD de l'entite_1 */
	temp.y = entite_1->y - 1;
	if(SDL_HasIntersection(&temp,  entite_2)){
		/* cotés en collision */
		*cote_entite_1 = NORD_1;
		*cote_entite_2 = SUD_1;
		return vrai;
	}
	/* test collision cote SUD de l'entite_1 */
	temp.y = entite_1->y + 1;
	if(SDL_HasIntersection(&temp,  entite_2)){
		/* cotés en collision */
		*cote_entite_1 = SUD_1;
		*cote_entite_2 = NORD_1;
		return vrai;
	}
	return faux;
}

void environnement_joueurs(list * liste_monstres, list * liste_sorts, list * liste_coffres, joueur_t ** joueurs, int nb_joueur){
	monstre_t * monstre;
	sort_t * sort;
	statut_t * statut;
	t_direction_1 cote_joueur;
	t_direction_1 cote_monstre;
	t_direction_1 cote_sort;
	int i;

	for(i=0; i < nb_joueur; i++){
		statut = joueurs[i]->statut;

		en_tete(liste_monstres);
		while(!hors_liste(liste_monstres)){
			monstre = valeur_elt(liste_monstres);
			
			/* si le monstre touche un joueur */
			if(entite_en_collision(&(monstre->collision), &(statut->vrai_zone_collision), &cote_monstre, &cote_joueur)){
				/* le coup est bloqué */
				if(statut->animation == BLOQUER){
					monstre->orientation = cote_joueur;
					monstre->action = MONSTRE_BLESSE;
					monstre->duree = DUREE_MONSTRE_BLESSE;
				}
				/* coup non bloqué */
				else if(statut->action != J_BLESSE){
					(joueurs[i]->pdv) -= (monstre->attaque);
					if(joueurs[i]->pdv <= 0)
						/* pour l'instant on ferme le programme quand le joueur à perdu */
						running = faux;
					else{
						/* changement d'orientation pour que le joueur soit poussé en arrière */
						statut->orient_dep = cote_monstre;
						statut->en_mouvement = vrai;
						statut->action = J_BLESSE;
						statut->duree = DUREE_JOUEUR_BLESSE;
						/* laisser au joueur le temps de se replier */
						monstre->action = MONSTRE_PAUSE;
						monstre->duree = DUREE_MONSTRE_PAUSE;
					}
				}
			}
			/* si un monstre est touché */
			if(statut->action == ATTAQUE || statut->action == ATTAQUE_CHARGEE){
				if(entite_subit_attaque(&(monstre->collision), joueurs[i]) && monstre->action != MONSTRE_BLESSE){
					(monstre->pdv) -= joueurs[i]->attaque_actif;
					if(monstre->pdv <= 0){
						/* detruire la collision du monstre */
						detruire_collision_dans_liste(map->liste_collisions, &(monstre->collision));
						/* detruire le monstre */
						oter_elt(liste_monstres);
						/* actualiser l'xp du joueur */
						(joueurs[i]->xp)+= monstre->gainXp;
						gain_xp(joueurs[i]);
					}
					else{
						/* changement d'orientation pour que le monstre soit poussé en arrière */
						monstre->orientation = statut->orient_dep;
						monstre->action = MONSTRE_BLESSE;
						monstre->duree = DUREE_MONSTRE_BLESSE;
					}
				}
			}
			suivant(liste_monstres);
		}

		en_tete(liste_sorts);
		while(!hors_liste(liste_sorts)){
			sort = valeur_elt(liste_sorts);
			
			/* si le sort touche un joueur */
			if(entite_en_collision(&(sort->collision), &(statut->vrai_zone_collision), &cote_sort, &cote_joueur)){
				/* le sort n'est pas bloqué */
				if(statut->animation != BLOQUER && statut->action != J_BLESSE){
					(joueurs[i]->pdv) -= (sort->degat);
					if(joueurs[i]->pdv <= 0)
						/* pour l'instant on ferme le programme quand le joueur à perdu */
						running = faux;
					else{
						/* changement d'orientation pour que le joueur soit poussé en arrière */
						statut->orient_dep = cote_sort;
						statut->en_mouvement = vrai;
						statut->action = J_BLESSE;
						statut->duree = DUREE_JOUEUR_BLESSE;
					}
				}
				detruire_collision_dans_liste(map->liste_collisions, &(sort->collision));
				oter_elt(liste_sorts);
			}

			/* si un sort est attaqué */
			else if(statut->action == ATTAQUE || statut->action == ATTAQUE_CHARGEE){
				if(entite_subit_attaque(&(sort->collision), joueurs[i])){
					/* detruire la collision du sort */
					detruire_collision_dans_liste(map->liste_collisions, &(sort->collision));
					/* detruire le sort */
					oter_elt(liste_sorts);
				}
			}
			suivant(liste_sorts);
		}
	}
}

void stoper_mouvement_joueurs(joueur_t ** joueurs){
    joueurs[0]->statut->en_mouvement = faux;
    //si mode coopératif
    if(joueurs[1])
        joueurs[1]->statut->en_mouvement = faux;
}

int distance_x_joueur(SDL_Rect collision, joueur_t * joueur){
    return joueur->statut->vrai_zone_collision.x - collision.x;
}

int distance_y_joueur(SDL_Rect collision, joueur_t * joueur){
    return joueur->statut->vrai_zone_collision.y - collision.y;
}

int distance_joueur(SDL_Rect collision, joueur_t * joueur){
    int x = distance_x_joueur(collision, joueur);
    int y = distance_y_joueur(collision, joueur);

    return sqrt(x*x + y*y);
}