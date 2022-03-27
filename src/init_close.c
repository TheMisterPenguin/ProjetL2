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


list *f_close = NULL; /**< Liste des fonctions à appeler lors de la fermeture du programme*/

void fermer_programme(int code_erreur){
    en_queue(f_close);

    while(!hors_liste(f_close)){
        void (*fonction)(void) =  valeur_elt(f_close);
        fonction();
        precedent(f_close);
    }

    detruire_liste(&f_close);

    exit(code_erreur);
}

/**
 * \fn void fermer_SDL(void);
 * \brief Fonction qui détruit la fenêtre principale et ferme la SDL
 * \author Ange Despert
 */
static void fermer_SDL(void)
{

    SDL_DestroyWindow(fenetre_Principale);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fenêtre principale détruite");

    SDL_Quit();
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL Arrêtée");
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

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Démarrage de la SDL");

    if (SDL_Init(SDL_INIT_EVERYTHING) ){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de l'initialisation de la SDL : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        fermer_programme(SDL_ERREUR);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL initialisée !");

    SDL_DisplayMode m;

    // On récupère les informations de l'écran
    if (SDL_GetCurrentDisplayMode(0, &m)){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la récupération de la résolution de l'écran : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        fermer_programme(SDL_ERREUR);
    }

    FENETRE_LONGUEUR = m.w; // On récupère la largeur de l'écran
    FENETRE_LARGEUR = m.h; // On récupère la hauteur de l'écran

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Résolution de l'écran : %dx%d", FENETRE_LONGUEUR, FENETRE_LARGEUR);

    // On crée la fenêtre principale
    fenetre_Principale = SDL_CreateWindow("Bloody Sanada",
                                          0,
                                          0,
                                          FENETRE_LONGUEUR,
                                          FENETRE_LARGEUR,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(! fenetre_Principale){
        char *msp = malloc(sizeof(char) * (500));

        sprintf(msp, "Erreur lors de la création de la fenêtre : %s\nErreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);

        free(msp);
        fermer_programme(SDL_ERREUR);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fenêtre principale créée");
}

static void init_rc_commun(void){

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Création du rendu principal");

    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (rendu_principal == NULL){
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de la création du rendu principal : %s\n Erreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        SDL_DestroyWindow(fenetre_Principale);
        fermer_programme(SDL_ERREUR);
    }

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Rendu principal créé");
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
        fermer_programme(ERREUR_LISTE);
    }
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Liste de textures initialisée");

    SDL_Rect t1 = {.h = FENETRE_LARGEUR, .w = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    SDL_Rect t2 = {.w = FENETRE_LONGUEUR, .h = 16 * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3)};
    ty = t2;
    tx = t1;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Rectangle de texture initialisé");

    multiplicateur_x = (float) FENETRE_LONGUEUR / 1920;
    multiplicateur_y = (float) FENETRE_LARGEUR / 1080;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Multiplicateur initialisés : %f, %f", multiplicateur_x, multiplicateur_y);

    buffer_affichage = init_liste(NULL,NULL,NULL);
}

SDL_Texture* init_sousbuffer(t_map *map){

    if(SDL_CreateWindowAndRenderer(
    floor(map->text_map->width * map->text_map->multipli_taille),
    floor(map->text_map->height * map->text_map->multipli_taille), 
    SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL,
    &fenetre_sous_rendu,
    &sous_rendu))
    {
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de la création du sous rendu: %s\n Erreur : 0x%X\n", SDL_GetError(), SDL_ERREUR);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        fermer_programme(SDL_ERREUR);
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
        fermer_programme(SDL_ERREUR);
    }
    return sous_buffer;
}

/**
 * \fn void init();
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
void init(){

    f_close = init_liste(NULL, NULL, NULL); 

    if(!f_close){
        char *msp = malloc(sizeof(char) * (500));
        sprintf(msp, "Erreur lors de l'initialisation de la liste de fermeture : %s\n Erreur : 0x%X\n", SDL_GetError(), ERREUR_LISTE);
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", msp, NULL);
        free(msp);
        exit(ERREUR_LISTE);
    }

    init_SDL();

    ajout_droit(f_close, fermer_SDL); 

    init_rc_commun();

    ajout_droit(f_close, detruire_renderer); //Ajout de la fonction de destruction du rendu principal

    SDL_ShowCursor(SDL_DISABLE); // On cache le curseur

    init_affichage();

    ajout_droit(f_close, aff_cleanup); //Ajout de la fonction de destruction de l'affichage
}