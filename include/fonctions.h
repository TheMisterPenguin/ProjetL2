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

#ifndef __H_FONCTION__
#define __H_FONCTION__

/**
 * \fn void init(void);
 * \brief Fonction qui initialise le Programme
 * \author Ange Despert
 */
extern void init(void);

/**
 * \fn void terminate(void);
 * \brief Fonction qui appelle les fonctions pour terminer le programme
 * \author Ange Despert
 */
extern void terminate_init(void);



/**
 * \fn init_event(void)
 * \brief Fonction qui initialise les fonctions liées aux évenements
 * 
 */
void init_event(void);
#endif