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
#include "map.h"
#include "personnage.h"

typedef enum {TEXT_MARCHER, TEXT_ATTAQUE, TEXT_ATTAQUE_CHARGEE, TEXT_CHARGER, TEXT_MARCHER_BOUCLIER}t_texture_perso;

#define NB_FPS 60 /**< Le nombre maximum de FPS */
#define NB_SPRITE_JOUEUR 5 /**< Le nombre de sprites différents du joueur */

/* On définit l'emplacement des textures du joueur */
#define N_T_MARCHER "ressources/sprite/marcher.bmp"
#define N_T_ATTAQUE "ressources/sprite/attaque.bmp"
#define N_T_ATTAQUE_CHARGEE "ressources/sprite/attaque_chargee.bmp"
#define N_T_CHARGER "ressources/sprite/charger.bmp"
#define N_T_MARCHER_BOUCLIER "ressources/sprite/marcher_bouclier.bmp"

/* On définit la taille d'une frame de sprite */
#define LONGUEUR_PERSONNAGE 48
#define LARGEUR_PERSONNAGE 48

/**
 * \struct s_aff
 * \brief Structure qui permet l'affichage d'une texture à l'écran de manière précise
 *
 * # Le but de la structure
 * Cette structure à pour but de permettre l'affichage d'une texture à l'écran de manière précise.
 * Ainsi, on peut facilement placer une texture où l'on veut sans 
 */
typedef struct s_aff
{
    SDL_Texture *texture;  /**<Texture utilisée*/
    SDL_Rect *frame_anim;  /**<Désigne la zone de la texture à afficher*/
    SDL_Rect *aff_fenetre; /**<Désigne l'emplacement et la taille de l'objet à l'écran */
    int width;
    int height;
    float multipli_taille; /**<Sauvegarde du multiplicateur de taille de la texture*/
    unsigned int duree_frame_anim;
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
extern long int compteur;      /*compteur utilisé pour gérer la vitesse d'affichage (fps)*/
extern SDL_Rect tx, ty;
extern float multiplicateur_x, multiplicateur_y; /* Multiplicateurs qui dépendent de la résolution */

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
 * \fn t_aff * creer_texture(const char* nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const int multiplicateur_taille)
 * \brief Fonction qui renvoie, charge une texture et la prépare à se faire afficher
 *
 * \param nom_fichier Le nom du fichier contenant la texture
 * \param taille_t_x La longueur de la texture à montrer
 * \param taille_t_y La largeur de la texture à montrer
 * \param x La coordonnée x où afficher la texture à l'écran
 * \param y La coordonnée y où afficher la texture à l'écran
 * \param multiplicateur_taille Une valeur par laquelle multiplier la taille de la texture
 * \return t_aff* Une structure qui permet l'affichage de la texture à l'écran ou NULL s'il y a eu une érreur
 */
extern t_aff *creer_texture(const char *nom_fichier, const int taille_t_x, const int taille_t_y, const int x, const int y, const float multiplicateur_taille);

/**
 * \brief Affiche la texture donnée en paramètre à l'écran
 *
 * \param texture La texture à afficher
 * \param rendu Le rendu sur lequel afficher la texture à l'écran
 * \return 0 s'il n'y a pas eu d'erreur
 */
extern err_t afficher_texture(t_aff *texture, SDL_Renderer *rendu);

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
extern err_t afficher_buffer(list *buffer, SDL_Renderer *rendu);

/**
 * Déplacez la texture pour que son centre soit au centre de l'écran
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du centre de la texture.
 * @param y La coordonnée y du centre de la texture.
 */
void deplacer_texture_centre(t_aff *texture, int x, int y);

extern void deplacer_rect_origine(SDL_Rect *r, int x, int y);

/**
 * Déplacez l'origine de la texture aux coordonnées données.
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x de l'origine de la texture.
 * @param y La coordonnée y de l'origine de la texture.
 */
void deplacer_texture_origine(t_aff *texture, int x, int y);

void deplacer_rect_haut_droit(SDL_Rect *r, int x, int y);

/**
 * La texture est déplacée vers la droite et vers le haut
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche du rectangle.
 */
void deplacer_texture_haut_droit(t_aff *texture, int x, int y);

/**
 * La texture est déplacée vers le coin inférieur gauche de l'écran
 *
 * @param texture la texture à déplacer
 * @param x La coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
void deplacer_texture_bas_gauche(t_aff *texture, int x, int y);

/**
 * La texture est déplacée vers le coin inférieur droit de la fenêtre
 *
 * @param texture la texture à déplacer
 * @param x Coordonnée x du coin supérieur gauche de la texture.
 * @param y Coordonnée y du coin supérieur gauche de la texture.
 */
void deplacer_texture_bas_droit(t_aff *texture, int x, int y);

/**
 * Modifie le rectangle qui définit la zone de l'écran qui sera utilisée pour le rendu de la texture
 *
 * @param texture La texture à modifier.
 * @param r Le rectangle à appliquer.
 */
void modif_affichage_rect(t_aff *texture, SDL_Rect r);

/**
 * Permet de déplacer le personnage de x unités sur la map
 * 
 * \param map La map sur laquelle le personnage ce déplace
 * \param pers La texture du personnage elle même
 * \param x Le nombre d'unités de déplacements
 */
void deplacement_x_pers(t_map *m, joueur_t *j, int x);

/**
 * \fn t_l_aff* init_textures_joueur()
 * \brief Fonction qui creer et renvoie une liste de textures pour le personnage (joueur)
 * \author Antoine Bruneau
 * \return t_l_aff* Une liste de textures
 */
extern t_l_aff *init_textures_joueur(joueur_t *j);

/**
 * \fn t_aff* init_texture_joueur(t_l_aff* textures_joueur)
 * \brief Fonction qui renvoie la texture de départ du personnage (joueur)
 * \author Antoine Bruneau
 * \param t_l_aff* la liste de textures personnage
 * \return t_aff* Une textures personnage
 */
extern t_aff *init_texture_joueur(t_l_aff *textures_joueur);

/**
 * \fn t_aff * next_frame_joueur(t_l_aff* textures_joueur);
 * \brief Fonction qui modifie et renvoie une textures en fonction des évênements (clics, touches claviers). Cette texture renvoyée sera par la suite affichée.
 * \author Antoine Bruneau
 * \param t_l_aff* un structure contenant un tableau de textures joueur
 * \return t_aff* Une texture joueur
 */
extern t_aff *next_frame_joueur(joueur_t *j);

/**
 * Permet de déplacer le personnage de y unités sur la map
 *
 * \param map La map sur laquelle le personnage ce déplace
 * \param pers La texture du personnage elle même
 * \param y Le nombre d'unités de déplacements
 */
void deplacement_y_pers(t_map *m, joueur_t *j, int y);

/**
 * Fonction qui permet de définir exactement la taille de la texture à affichar sur l'écran
 * 
 * \param a_modifier La texture à modifier
 * \param longueur La nouvelle longueure en pixel à appliquer
 * \param largeur La nouvelle largeur en pixel à appliquer
 */
void def_texture_taille(t_aff *a_modifier, const int longueur, const int largeur);

/**
 * Fonction qui permet de placer 2 textures aux mêmes endroit à l'écran
 * 
 * \param a_modifier La texture dont on veut modifier la position
 * \param original La texture dont on veut copier la position
 */
void text_copier_position(t_aff *a_modifier, const t_aff *const original);

void rect_centre_x(SDL_Rect *rectangle);

void rect_centre_y(SDL_Rect *rectangle);

void rect_centre(SDL_Rect *rectangle);

bool rects_egal_x(const SDL_Rect *const r1, SDL_Rect const *const r2);

bool rects_egal_y(const SDL_Rect *const r1, SDL_Rect const *const r2);

/**
 * \fn SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
 * \brief Fonction qui permet de choisir une couleur SDL
 * \param r niveau de rouge
 * \param g niveau de vert
 * \param b niveau de bleu
 * \param a niveau d'opacité
 * \return SDL_Color une couleur SDL
 */
SDL_Color color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

/**
 * \fn void info_texture(t_aff * texture)
 * \brief Affiche des informations sur une texture
 * \param texture la texture sur laquelle on se renseigne
 */
void info_texture(t_aff * texture);

/**
 * \fn void placer_texture(t_aff *texture, int x, int y)
 * \brief Place une texture sur l'écran
 * \param texture Texture à placer
 * \param x Position horizontale
 * \param y Position verticale
 */
void placer_texture(t_aff *texture, int x, int y);
#endif