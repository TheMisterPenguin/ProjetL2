#include <commun.h>
#include <stdio.h>

/** 
 * \file init.c
 * \brief Contient toutes les fonctions pour initialiser le programme
 * \author Ange Despert
 * \version 0.1
 * \date 10/01/22
 */

/**
 * \fn void fermer_SDL(void);
 * \brief Fonction qui détruit la fenêtre principale et ferme la SDL
 * \author Ange Despert
 */
static void fermer_SDL(void)
{

    SDL_DestroyWindow(fenetre_Principale);
    printf("Destruction de la fenêtre !\n");

    SDL_Quit();
    printf("Fermeture de la SDL\n");
}

static void detruire_renderer(void)
{

    SDL_DestroyRenderer(rendu_principal);
}

/**
 * \fn void init_SDL(void);
 * \brief Fonction qui démarre la SDL et créer la fenêtre principale
 * \author Ange Despert
 */
static void init_SDL(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){ 
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(SDL_ERREUR);
    }

    printf("SDL initialisée !\n");

    fenetre_Principale = SDL_CreateWindow("Bloody Sanada",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            FENETRE_LONGUEUR,
                                            FENETRE_LARGEUR,
                                            SDL_WINDOW_SHOWN);

    if(! fenetre_Principale){
        fprintf(stderr,"Erreur lors de la création de la fenêtre : (%s)\n", SDL_GetError());
        exit(SDL_ERREUR);
    }

    printf("Fenêtre crée !\n");
}

static void init_rc_commun(void){
    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (rendu_principal == NULL){
        fprintf(stderr, "Échec de l'initialisation du rendu (%s)\n", SDL_GetError());
        exit(SDL_ERREUR);
    }


}
/**
 * \brief Fonction ajoutée à la liste de atexit() afin de libérer toute la mémoire allouée
 */
void aff_cleanup(void)
{
    running = faux;
    detruire_liste_textures(&listeDeTextures);
    detruire_joueur(perso_principal);
}

void init_affichage(){
    listeDeTextures = malloc(sizeof(t_aff *)); 
    listeDeTextures->liste = malloc(sizeof(t_aff));
    listeDeTextures->nb_valeurs = 0;
}

/**
 * \fn void init();
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
void init(){
    init_SDL();
    atexit(fermer_SDL);
    //init_sGame();
    init_rc_commun();
    atexit(detruire_renderer);
    init_affichage();
    atexit(aff_cleanup);
}