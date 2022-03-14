/**
 * \file affichage.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief 
 * \version 0.1
 * \date 12/03/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __AFFICHAGE_H__
#define __AFFICHAGE_H__
#include "SDL2/SDL.h"
#include "definition_commun.h"
#include "listes.h"

typedef enum {TEXT_MARCHER, TEXT_ATTAQUE, TEXT_ATTAQUE_CHARGEE, TEXT_CHARGER, TEXT_MARCHER_BOUCLIER}t_texture_perso;

#define NB_SPRITE_JOUEUR 5
//fichiers images personnage
#define N_T_MARCHER "ressources/sprite/marcher.bmp"
#define N_T_ATTAQUE "ressources/sprite/attaque.bmp"
#define N_T_ATTAQUE_CHARGEE "ressources/sprite/attaque_chargee.bmp"
#define N_T_CHARGER "ressources/sprite/charger.bmp"
#define N_T_MARCHER_BOUCLIER "ressources/sprite/marcher_bouclier.bmp"

#define LONGUEUR_PERSONNAGE 48
#define LARGEUR_PERSONNAGE 48

/**
 * \struct s_aff
 * \brief Structure qui permet l'affichage d'une texture à l'écran de manière précise
 *
 */
typedef struct s_aff
{
    SDL_Texture *texture;  /**<Texture utilisée*/
    SDL_Rect *frame_anim;  /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *aff_fenetre; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
    int width;
    int height;
} t_aff;
/**
 * \brief Structure contenant la liste des textures créées par le programme
 * 
 */
typedef struct s_l_aff{
    t_aff **liste;
    unsigned int nb_valeurs;
}t_l_aff;

/* Variables globales */
extern list *listeDeTextures;
extern list *buffer_affichage; /*<Buffer contenant toutes les textures à afficher */

/* Définition des fonctions */

/**
 * \fn void detruire_texture(t_aff **texture)
 * \brief Fonction qui détruit une structure d'affichage de texture passée en paramètre
 * \author Despert Ange
 * \param texture L'adresse du pointeur sur la structure à détruire
 */
extern void detruire_texture(t_aff **texture); /**<La liste des textures créées */
/**
 * \brief Fonction qui détruit une liste de textures
 *
 * \param l_texture L'adresse de la liste de texture à détruire
 */
extern void detruire_liste_textures(t_l_aff **l_texture);
/**
 * \brief Fonction qui détermine si la structure SDL_Rect ne dépasse pas la taille de la texture.
 *
 * \param to_verify La structure SDL_Rect à vérifier
 * \param width La longueur de la texture
 * \param height La largeur de la texture
 * \return vrai Si tout est OK, faux sinon.
 */
extern _Bool rect_correct_texture(const SDL_Rect *const to_verify, const int width, const int height);
/**
 * \fn t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const int multpilicateur_taille)
 * \brief Fonction qui renvoie, charge une texture et la prépare à se faire afficher
 *
 * \param nom_fichier Le nom du fichier contenant la texture
 * \param taille_t_x La longueur de la texture à montrer
 * \param taille_t_y La largeur de la texture à montrer
 * \param x La coordonnée x où afficher la texture à l'écran
 * \param y La coordonnée y où afficher la texture à l'écran
 * \param multpilicateur_taille Une valeur par laquelle multiplier la taille de la texture
 * \return t_aff* Une structure qui permet l'affichage de la texture à l'écran ou NULL s'il y a eu une érreur
 */
extern t_aff *creer_texture(const char *nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const float multpilicateur_taille);
/**
 * \brief Affiche la texture donnée en paramètre aux coordonnées donneés
 *
 * \param texture La texture à afficher
 * \param rendu Le rendu sur lequel afficher la texture
 * \param x La coordonnée x ou afficher la texture à l'écran
 * \param y La coordonnée y ou afficher la texture à l'écran
 * \return 0 s'il n'y a pas eu d'erreur
 */
extern err_t afficher_texture_emp(t_aff *texture, SDL_Renderer *rendu, const int x, const int y);
/**
 * \brief Affiche la texture donnée en paramètre à l'écran
 *
 * \param texture La texture à afficher
 * \param rendu Le rendu sur lequel afficher la texture à l'écran
 * \return 0 s'il n'y a pas eu d'erreur
 */
extern err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu);

/**
 * \fn t_l_aff* init_textures_joueur()
 * \brief Fonction qui creer et renvoie une liste de textures pour le personnage (joueur)
 * \author Antoine Bruneau
 * \return t_l_aff* Une liste de textures
 */
extern t_l_aff* init_textures_joueur();

/**
 * \fn t_aff* init_texture_joueur(t_l_aff* textures_joueur)
 * \brief Fonction qui renvoie la texture de départ du personnage (joueur)
 * \author Antoine Bruneau
 * \param t_l_aff* la liste de textures personnage
 * \return t_aff* Une textures personnage
 */
extern t_aff* init_texture_joueur(t_l_aff* textures_joueur);

/**
 * \fn t_aff * next_frame_joueur(t_l_aff* textures_joueur);
 * \brief Fonction qui modifie et renvoie une textures en fonction des évênements (clics, touches claviers). Cette texture renvoyée sera par la suite affichée.
 * \author Antoine Bruneau
 * \param t_l_aff* un structure contenant un tableau de textures joueur
 * \return t_aff* Une texture joueur
 */
extern t_aff * next_frame_joueur(t_l_aff* textures_joueur);

/**
 * \fn void next_frame_y(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des y
 *
 * \param t_aff* une texture joueur
 */
extern void next_frame_y(t_aff* texture);

/**
 * \fn void next_frame_x(t_aff *texture);
 * \brief Fonction qui positionne la texture au sprite d'après sur l'axe des x
 *
 * \param t_aff* une texture joueur
 */
extern void next_frame_x(t_aff *texture);

/**
 * \fn void next_frame_x_indice(t_aff *texture, const unsigned int indice);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des x
 *
 * \param t_aff* une texture joueur
 * \param const unsigned int qui correspond au n-ème sprite sur l'axe des x ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_x_indice(t_aff *texture, const unsigned int indice);

/**
 * \fn void next_frame_y_indice(t_aff *texture, const unsigned int indice);
 * \brief Fonction qui positionne la texture au n-ème sprite sur l'axe des y
 *
 * \param t_aff* une texture joueur
 * \param const unsigned int qui correspond au n-ème sprite sur l'axe des y ou l'on souhaite positionner la texture
 * \return err_t un entier pour savoir si il y a eu une erreur
 */
extern err_t next_frame_y_indice(t_aff *texture, const unsigned int indice); 

void *ajout_text_liste(void *t);

/**
 * Fonction qui affiche les textures contenues dans la liste en paramètre. 
 * 
 * Les premiers éléments seront en arrière plan et les derniers seront en 1er plan.
 * 
 * \param buffer La liste de textures que l'on veut afficher
 * \param rendu Le rendu sur lequel on veut afficher ces textures
 * \return Une valeur différente à 0 lors d'une erreur
 */
err_t afficher_buffer(const list *const buffer, SDL_Renderer *rendu);

#endif