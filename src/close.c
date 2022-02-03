#include <commun.h>
#include <stdio.h>

/**
 * \file close.c
 * \brief Fichier contenant les fonctions pour terminer le programme
 * \author Ange Despert
 * \version 1
 * \date 20/01/02
 */

/**
 * \fn void fermer_SDL(void);
 * \brief Fonction qui détruit la fenêtre principale et ferme la SDL
 * \author Ange Despert
 */
static void fermer_SDL(void){

    SDL_DestroyWindow(fenetre_Principale);
    printf("Destruction de la fenêtre !\n");

    SDL_Quit();
    printf("Fermeture de la SDL\n");
}

/**
 * \fn void terminate(void);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
void terminate(void){
    fermer_SDL();

    exit(0);
}