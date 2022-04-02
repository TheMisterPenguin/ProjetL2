#include <commun.h>
#include <stdio.h>
#include <listes.h>
#include <time.h>

/** 
 * \file init_close.c
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Contient toutes les fonctions pour initialiser le programme
 * \version 0.2
 * \date 27/03/22
 * \copyright Copyright (c) 2022
 */

typedef struct t_map t_map;

SDL_Window *fenetre_Principale = NULL;
SDL_Renderer *rendu_principal = NULL;

SDL_Window *fenetre_sous_rendu = NULL;
SDL_Renderer *sous_rendu = NULL;
bool running = vrai;
SDL_Rect * hors_hitbox = NULL;


list *f_close = NULL; /**< Liste des fonctions à appeler lors de la fermeture du programme*/

void fermer_programme(int code_erreur){
    #ifdef _DEBUG_COLLISION /* Affichage des collisions */

        if(hors_hitbox)
            free(hors_hitbox);
    #endif
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

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER))
        erreur("Erreur lors de l'initialisation de la SDL : %s", SDL_ERREUR, SDL_GetError());

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL initialisée !");

    SDL_DisplayMode m;

    // On récupère les informations de l'écran
    if (SDL_GetCurrentDisplayMode(0, &m))
        erreur("Erreur lors de la récupération de la résolution de l'écran : %s", SDL_ERREUR, SDL_GetError());

    FENETRE_LONGUEUR = m.w; // On récupère la largeur de l'écran
    FENETRE_LARGEUR = m.h; // On récupère la hauteur de l'écran

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Résolution de l'écran : %dx%d", FENETRE_LONGUEUR, FENETRE_LARGEUR);

    // On crée la fenêtre principale
    fenetre_Principale = SDL_CreateWindow("Bloody Sanada", 0, 0, FENETRE_LONGUEUR, FENETRE_LARGEUR, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(! fenetre_Principale)
        erreur("Erreur lors de la création de la fenêtre principale : %s", SDL_ERREUR, SDL_GetError());

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Fenêtre principale créée");

    manette = SDL_GameControllerOpen(0);

    if(manette != NULL)
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Manette détectée");
    else
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Aucune manette détectée");

}

static void init_rc_commun(void){

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Création du rendu principal");

    rendu_principal =    SDL_CreateRenderer(fenetre_Principale,
                                            -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (rendu_principal == NULL)
        erreur("Erreur lors de la création du rendu principal : %s", SDL_ERREUR, SDL_GetError());

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

    if(!listeDeTextures)
        erreur("Erreur lors de l'initialisation de la liste de textures", ERREUR_LISTE);

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

void init_sousbuffer(t_map *map, joueur_t * joueur){

    SDL_Texture *sous_buffer = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));
    if(!sous_buffer)
        erreur("Erreur lors de la création de la texture de sous-buffer : %s", SDL_ERREUR, SDL_GetError());
    /* On alloue le second  buffer */
    map->text_map = malloc(sizeof(t_aff));

    if(!map->text_map)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->aff_fenetre = malloc(sizeof(SDL_Rect));

    if (!map->text_map->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    map->text_map->frame_anim = malloc(sizeof(SDL_Rect));

    if (!map->text_map->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    /* On alloue le troisième  buffer */
    fenetre_finale = malloc(sizeof(t_aff));

    if (!fenetre_finale)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->texture = SDL_CreateTexture(rendu_principal, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, floor(map->text_sol->width * map->text_sol->multipli_taille), floor(map->text_sol->height * map->text_sol->multipli_taille));
    
    if (!fenetre_finale->texture)
        erreur("Erreur lors de la créations des buffers : %s", SDL_ERREUR , SDL_GetError());

    fenetre_finale->aff_fenetre = malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->aff_fenetre)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim = malloc(sizeof(SDL_Rect));

    if (!fenetre_finale->frame_anim)
        erreur("Erreur : Plus de mémoire", OUT_OF_MEM);

    fenetre_finale->frame_anim->x = 0;
    fenetre_finale->frame_anim->y = 0;
    fenetre_finale->frame_anim->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    fenetre_finale->frame_anim->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    fenetre_finale->aff_fenetre->x = 0;
    fenetre_finale->aff_fenetre->y = 0;
    fenetre_finale->aff_fenetre->w = FENETRE_LONGUEUR;
    fenetre_finale->aff_fenetre->h = FENETRE_LARGEUR;

    map->text_map->texture = sous_buffer;

    /* On définit la partie de la map que l'on voie à l'écran */
    map->text_map->aff_fenetre->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->aff_fenetre->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    map->text_map->aff_fenetre->x = 0;
    map->text_map->aff_fenetre->y = 0;

    /* On place la partie de la map que l'on voit */
    map->text_map->frame_anim->w = floor(FENETRE_LONGUEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;
    map->text_map->frame_anim->h = floor(FENETRE_LARGEUR / (float)floor(TAILLE_PERSONNAGE * ((FENETRE_LONGUEUR * 0.022f) / 16 * 3))) * map->taille_case;

    map->text_map->frame_anim->x = 0;
    map->text_map->frame_anim->y = 0;

    ty.w = fenetre_finale->frame_anim->w;
    ty.h = joueur->statut->zone_colision.h;

    tx.h = fenetre_finale->frame_anim->h;
    tx.w = joueur->statut->zone_colision.w;

    rect_centre_rect_y(&ty, fenetre_finale->frame_anim);
    rect_centre_rect_x(&tx, fenetre_finale->frame_anim);

    if (SDL_SetRenderTarget(rendu_principal, map->text_map->texture))
        erreur("Erreur lors de la création du sous buffer : %s\n", SDL_ERREUR, SDL_GetError());
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

    init_SDL();

    ajout_droit(f_close, fermer_SDL); 

    init_rc_commun();

    ajout_droit(f_close, detruire_renderer); //Ajout de la fonction de destruction du rendu principal

    SDL_ShowCursor(SDL_DISABLE); // On cache le curseur

    init_affichage();

    ajout_droit(f_close, aff_cleanup); //Ajout de la fonction de destruction de l'affichage
}