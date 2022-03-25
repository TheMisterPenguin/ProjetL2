#include <commun.h>
#include <stdio.h>
#include <listes.h>
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

    SDL_DisplayMode m;

    if (SDL_GetCurrentDisplayMode(0, &m))
    {
        fprintf(stderr, "Erreur : impossible de récupérer la taille de l'écran : %s\n", SDL_GetError());
        exit(SDL_ERREUR);
    }
    FENETRE_LONGUEUR = m.w;
    FENETRE_LARGEUR = m.h;

    fenetre_Principale = SDL_CreateWindow("Bloody Sanada",
                                          0,
                                          0,
                                          FENETRE_LONGUEUR,
                                          FENETRE_LARGEUR,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);

    if(! fenetre_Principale){
        fprintf(stderr,"Erreur lors de la création de la fenêtre : (%s)\n", SDL_GetError());
        exit(SDL_ERREUR);
    }

    printf("Fenêtre crée !\n");
}

static void init_rc_commun(void){
    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1,  SDL_RENDERER_ACCELERATED);
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
    vider_liste(buffer_affichage);
    vider_liste(listeDeTextures);
}

void init_affichage(){
    listeDeTextures = init_liste(ajout_text_liste, (void (*)(void *)) detruire_texture);
    SDL_Rect t1 = {.h = FENETRE_LARGEUR, .w = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    SDL_Rect t2 = {.w = FENETRE_LONGUEUR, .h = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    ty = t2;
    tx = t1;

    multiplicateur_x = (float) FENETRE_LONGUEUR / 1920;
    multiplicateur_y = (float) FENETRE_LARGEUR / 1080;

    printf("multix : %f, multi_y %f\n", multiplicateur_x, multiplicateur_y);
    buffer_affichage = init_liste(NULL,NULL);
    atexit(aff_cleanup);
}

/**
 * \fn void init();
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
void init(){
    init_SDL();
    atexit(fermer_SDL);
    init_rc_commun();
    atexit(detruire_renderer);
    SDL_ShowCursor(SDL_DISABLE);
    init_affichage();
}