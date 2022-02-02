/**
 * \file fonctions.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier qui contient les définitions de toutes les fonctions
 * \version 0.1
 * \date 02/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef H_FONCTION
#define H_FONCTION
extern void init(void);
/**
 * \fn void init(void);
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */

/**
 * \fn void terminate(void);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
extern void terminate(void);

/**
 * \fn void jeu_event(void)
 * \brief Fonction qui gère les événements
 * \author Despert Ange
 * 
 */
extern void jeu_event(void);
#endif