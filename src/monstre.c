/**
 * \file monstre.c
 * \author Descomps Max (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Fichier contenant toutes les fonctions concernant les monstres
 * \version 0.1
 * \date 01/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

/**
 * \struct struct monstre
 * \brief Structure monstre
 * 
 * \author Descomps Max
 */



typedef struct monstre_s
{
	char nom_monstre[20]; /**<Le nom du monstre*/
	short int niveau; /**<Le niveau du monstre*/
    int pdv;
    int attaque; /**<attaque du monstre*/
    int defense; /**<defense du monstre*/
    int vitesse; /**<vitesse de déplacement du monstre*/
} monstre_t;