#include <stdio.h>
#include <time.h>
#include <listes.hpp>
#include <map.hpp>
#include <event.hpp>
#include <log.hpp>
#include <utils.hpp>

/** 
 * \file init_close.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Contient toutes les fonctions pour initialiser le programme
 * \version 0.2
 * \date 27/03/22
 * \copyright Copyright (c) 2022
 */

typedef struct s_aff t_aff;


SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;

SDL_Window *fenetre_sous_rendu = NULL;
SDL_Renderer *sous_rendu = NULL;
bool running = vrai;
SDL_Rect * hors_hitbox = NULL;


list *f_close = NULL; /**< Liste des fonctions à appeler lors de la fermeture du programme*/

void fermer_programme(int code_erreur){
    log_info("Fermeture du programme ...");
    //éviter erreurs SDL_DestroyRenderer sur les SDL_Rect provoquées par text_copier_position() 
    if(liste_animations){
        t_aff * text_anim = NULL;
        en_tete(liste_animations);
        while(!hors_liste(liste_animations)){
            text_anim = (t_aff *) valeur_elt(liste_animations);
            if(text_anim->aff_fenetre)
                text_anim->aff_fenetre = NULL;
            suivant(liste_animations);
        }
    }

    en_queue(f_close);

    while(!hors_liste(f_close)){
        void (*fonction)(void) = (void (*)(void)) valeur_elt(f_close);
        fonction();
        precedent(f_close);
    }

    detruire_liste(&f_close);

    free(execDir);

    exit(code_erreur);
}

/**
 * \fn void fermer_SDL(void);
 * \brief Fonction qui détruit la fenêtre principale et ferme la SDL
 * \author Ange Despert
 */
static void fermer_SDL(void)
{
    log_debug("Destruction de la fenêtre");
    SDL_DestroyWindow(fenetre_Principale);
    log_debug("Fenêtre détruite");

    SDL_Quit();
    log_debug( "SDL Arrêtée");
}

static void detruire_renderer(void)
{
    log_debug("Destruction du rendu");
    SDL_DestroyRenderer(rendu_principal);
    log_debug("Rendu et textures détruites");
}

/**
 * \fn void init_SDL(void);
 * \brief Fonction qui démarre la SDL et créer la fenêtre principale
 * \author Ange Despert
 */
static void init_SDL(){

    log_debug("Démarrage de la SDL");

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
        erreur("Erreur lors de l'initialisation de la SDL : %s", SDL_ERREUR, SDL_GetError());

    log_debug( "SDL initialisée !");

    SDL_DisplayMode m;

    // On récupère les informations de l'écran
    if (SDL_GetCurrentDisplayMode(0, &m))
        erreur("Erreur lors de la récupération de la résolution de l'écran : %s", SDL_ERREUR, SDL_GetError());

    FENETRE_LONGUEUR = m.w; // On récupère la largeur de l'écran
    FENETRE_LARGEUR = m.h; // On récupère la hauteur de l'écran

    log_info( "Résolution de l'écran : %dx%d", FENETRE_LONGUEUR, FENETRE_LARGEUR);

    // On crée la fenêtre principale
    fenetre_Principale = SDL_CreateWindow("Bloody Sanada", 0, 0, FENETRE_LONGUEUR, FENETRE_LARGEUR, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(! fenetre_Principale)
        erreur("Erreur lors de la création de la fenêtre principale : %s", SDL_ERREUR, SDL_GetError());

    log_debug( "Fenêtre principale créée");   

    manette = SDL_GameControllerOpen(0);

    if(manette != NULL)
        log_info( "Manette détectée")
    else
        log_warn("Aucune manette détectée");
}

static void init_rc_commun(void){

    log_debug( "Création du rendu principal");

    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (rendu_principal == NULL)
        erreur("Erreur lors de la création du rendu principal : %s", SDL_ERREUR, SDL_GetError());

    log_debug( "Rendu principal créé");
}
/**
 * \brief Fonction ajoutée à la liste de atexit() afin de libérer toute la mémoire allouée
 */
void aff_cleanup(void)
{
    running = faux;
    detruire_liste(&listeDeTextures);
}

void init_affichage(){

    listeDeTextures = init_liste(ajout_text_liste, (void (*)(void *)) detruire_texture, (void (*)(void *))info_texture);

    if(!listeDeTextures)
        erreur("Erreur lors de l'initialisation de la liste de textures", ERREUR_LISTE);

    log_debug( "Liste de textures initialisée");

    SDL_Rect t1 = {.w = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3), .h = FENETRE_LARGEUR, };
    SDL_Rect t2 = {.w = FENETRE_LONGUEUR, .h = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    ty = t2;
    tx = t1;

    log_debug( "Rectangle de texture initialisé");

    multiplicateur_x = (float) FENETRE_LONGUEUR / 1920;
    multiplicateur_y = (float) FENETRE_LARGEUR / 1080;

    log_debug( "Multiplicateur initialisés : %f, %f", multiplicateur_x, multiplicateur_y);
}

/**
 * \fn void init();
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
void init(){
    srand(time(NULL)); //initialisation des nombres aléatoires
    f_close = init_liste(NULL, NULL, NULL);

    if(!f_close)
        erreur("Erreur lors de l'initialisation de la liste de fermeture", ERREUR_LISTE);

    _init_log();

    log_info("Démmarage du programme");

    init_SDL();

    ajout_droit(f_close, (void *)fermer_SDL); 

    init_rc_commun();

    ajout_droit(f_close, (void*) detruire_renderer); //Ajout de la fonction de destruction du rendu principal

    SDL_ShowCursor(SDL_DISABLE); // On cache le curseur

    init_affichage();

    ajout_droit(f_close, (void*) aff_cleanup); //Ajout de la fonction de destruction de l'affichage
}