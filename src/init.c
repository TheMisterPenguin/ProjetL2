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
 * \fn void init_SDL(void);
 * \brief Fonction qui démarre la SDL et créer la fenêtre principale
 * \author Ange Despert
 */
void init_SDL(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 ){ 
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(SDL_ERREUR);
    }

    printf("SDL initialisée !\n");

    fenetre_Principale = SDL_CreateWindow("Bloody Sanada",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            FENETRE_LONGUER,
                                            FENETRE_LARGEUR,
                                            SDL_WINDOW_SHOWN);

    if(! fenetre_Principale){
        fprintf(stderr,"Erreur lors de la création de la fenêtre : (%s)\n", SDL_GetError());
        exit(SDL_ERREUR);
    }

    printf("Fenêtre crée !\n");
}

/**
 * \fn void init();
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
void init(){
    init_SDL();
}