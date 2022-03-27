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

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;

SDL_Window *fenetre_sous_rendu = NULL;
SDL_Renderer *sous_rendu = NULL;
bool running = vrai;

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

    if (SDL_Init(SDL_INIT_EVERYTHING) ){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de l'initialisation de la SDL : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        exit(SDL_ERREUR);
    }

    printf("SDL initialisée !\n");

    SDL_DisplayMode m;

    // On récupère les informations de l'écran
    if (SDL_GetCurrentDisplayMode(0, &m)){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la récupération de la résolution de l'écran : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        exit(SDL_ERREUR);
    }

    FENETRE_LONGUEUR = m.w; // On récupère la largeur de l'écran
    FENETRE_LARGEUR = m.h; // On récupère la hauteur de l'écran

    // On crée la fenêtre principale
    fenetre_Principale = SDL_CreateWindow("Bloody Sanada",
                                          0,
                                          0,
                                          FENETRE_LONGUEUR,
                                          FENETRE_LARGEUR,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);

    if(! fenetre_Principale){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la création de la fenêtre : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        exit(SDL_ERREUR);
    }

    printf("Fenêtre crée !\n");
}

static void init_rc_commun(void){
    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (rendu_principal == NULL){
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de la création du rendu principal : %s\n Erreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        SDL_DestroyWindow(fenetre_Principale);
        exit(SDL_ERREUR);
    }

}
/**
 * \brief Fonction ajoutée à la liste de atexit() afin de libérer toute la mémoire allouée
 */
void aff_cleanup(void)
{
    running = faux;
    detruire_liste(&buffer_affichage);
    detruire_liste(&listeDeTextures);
}

void init_affichage(){

    listeDeTextures = init_liste(ajout_text_liste, (void (*)(void *)) detruire_texture, (void (*)(void *))info_texture);

    if(!listeDeTextures){
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de l'initialisation de la liste de textures : %s\n Erreur : 0x%X\n", SDL_GetError(), ERREUR_LISTE);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        exit(ERREUR_LISTE);
    }
    SDL_Rect t1 = {.h = FENETRE_LARGEUR, .w = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    SDL_Rect t2 = {.w = FENETRE_LONGUEUR, .h = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    ty = t2;
    tx = t1;

    multiplicateur_x = (float) FENETRE_LONGUEUR / 1920;
    multiplicateur_y = (float) FENETRE_LARGEUR / 1080;

    printf("multix : %f, multi_y %f\n", multiplicateur_x, multiplicateur_y);
    buffer_affichage = init_liste(NULL,NULL,NULL);
    atexit(aff_cleanup);
}

SDL_Texture* init_sousbuffer(t_map *map){

    if(SDL_CreateWindowAndRenderer(
    floor(map->text_map->width * map->text_map->multipli_taille),
    floor(map->text_map->height * map->text_map->multipli_taille), 
    SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL,
    fenetre_sous_rendu,
    sous_rendu))
    {
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de la création du sous rendu: %s\n Erreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        exit(SDL_ERREUR);
    }

    SDL_Texture *sous_buffer = SDL_CreateTexture(rendu_principal,
                                                 SDL_PIXELFORMAT_RGBA8888,
                                                 SDL_TEXTUREACCESS_TARGET,
                                                 floor(map->text_map->width * map->text_map->multipli_taille),
                                                 floor(map->text_map->height * map->text_map->multipli_taille));
    if(!sous_buffer){
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de la création du sous buffer : %s\n Erreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        exit(SDL_ERREUR);
    }
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