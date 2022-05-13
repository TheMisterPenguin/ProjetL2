/**
 * \file code_erreur.h
 * \author Ange Despert (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant les codes d'erreur du programme
 *
 * Ce fichier contient une enumeration des codes d'erreur du programme, permettant ainsi une modification simple et une gestion plus facile des erreurs.
 * \version 1.0
 * \date 05/04/22
 * \copyright Copyright (c) 2022
 */

#ifndef __H_CODE_ERREUR__
#define __H_CODE_ERREUR__
#include "log.h"

typedef int err_t;

/**
 * \brief L'énumération des codes d'erreur du programme
 * 
 * 
 * Cela permet une gestion plus simple des erreurs.
 * L'utilisateur peut donc connaitre aisaiment le code d'erreur et le message correspondant.
 * Permettant au developpeur de répondre à l'erreur en question.
 */
enum types_erreur 
{
    AUCUNE_ERREUR, /**< Aucune erreur */
    SDL_ERREUR, /**< Une erreur liée à la SDL */
    ERREUR_TEXTURE, /**< Une erreur liée à une texture */
    OUT_OF_MEM, /**< Une erreur liée à l'allocation mémoire */
    BUFFER_EMPTY, /**< Le buffer est vide */
    ERREUR_FICHIER, /**< Une erreur liée au fichier (introuvable ou écriture ou lecture impossible) */
    ERREUR_FONCTION, /**< Valeur renvoyée par une fonction qui échoue */
    ERREUR_MAP, /**< Une erreur liée à la map */
    ERREUR_INIT, /**< Une erreur liée à l'initialisation du programme*/
    ERREUR_SDL_IMG, /**< Une erreur liée à l'initialisation de SDL_image */
    ERREUR_SDL_TTF, /**< Une erreur liée à l'initialisation de SDL_ttf */
    ERREUR_SDL_MIX, /**< Une erreur liée à l'initialisation de SDL_mixer */
    ERREUR_SDL_AUDIO, /**< Une erreur liée à l'initialisation de SDL_audio */
    ERREUR_SDL_TIMER, /**< Une erreur liée à l'initialisation de SDL_timer */
    ERREUR_SDL_MOUSE, /**< Une erreur liée à l'initialisation de SDL_mouse */
    ERREUR_SDL_JOYSTICK, /**< Une erreur liée à l'initialisation de SDL_joystick */
    ERREUR_SDL_RENDER, /**< Une erreur liée à l'initialisation du rendu */
    ERREUR_SDL_WINDOW, /**< Une erreur liée à l'initialisation de la fenêtre */
    ERREUR_SDL_MUSIC, /**< Une erreur liée à l'initialisation de la musique */
    ERREUR_SDL_SURFACE, /**< Une erreur liée à l'initialisation de la surface */
    ERREUR_SDL_PIXEL, /**< Une erreur liée à l'initialisation du pixel */
    ERREUR_SDL_MOUSEMOTION, /**< Une erreur liée aux mouvements de la souris */
    ERREUR_SDL_MOUSEBUTTON, /**< Une erreur liée aux boutons de la souris */
    ERREUR_SDL_KEYBOARD, /**< Une erreur liée aux touches du clavier */
    ERREUR_SDL_SCANCODE, /**< Une erreur liée aux scancodes du clavier */
    ERREUR_SDL_QUIT, /**< Une erreur liée au clic sur la croix */
    ERREUR_SDL_EVENT, /**< Une erreur liée aux événements */
    ERREUR_SDL_TIMER_START, /**< Une erreur liée au démarrage du timer */
    ERREUR_SDL_TIMER_STOP, /**< Une erreur liée à l'arrêt du timer */
    ERREUR_LISTE, /**< Une erreur liée à une liste */
    ERR_CREATION_REPERTOIRE_SAUVEGARDE, /**< Une erreur liée à la création du répertoire de sauvegarde */
    ERR_RECTANGLE_TOO_BIG, /**< Une erreur liée au rectangle trop grand */
    ERREUR_JSON_CLE_NON_TROUVEE /**Une Erreur liée à l'impossibilité de trouver une clé dans un fichier JSON */
};

/**
 * \brief Macro qui permet de facilement afficher une erreur
 * \author Ange Despert
 * 
 * Attention, cette macro quitte le programme.
 * 
 */
#define erreur(msg, code_erreur, ...)                                                         \
    {                                                                                         \
        char *msp = malloc(sizeof(char) * (500));                                             \
        char *mspbis = malloc(sizeof(char) * (500));                                          \
        sprintf(msp, msg, ##__VA_ARGS__);                                                     \
        log_error("%s", msp);                                                                 \
        sprintf(mspbis, "%s\nErreur : 0x%X\n", msp, code_erreur);                             \
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Erreur", mspbis, NULL);               \
        free(msp);                                                                            \
        free(mspbis);                                                                         \
        fermer_programme(code_erreur);                                                        \
    }

/**
 * \brief Macro qui permet de facilement afficher un Warning
 * \author Ange Despert
 */
#define warning(msg, code_erreur, ...)                                                       \
    {                                                                                        \
        char *msp = malloc(sizeof(char) * (500));                                            \
        char *mspbis = malloc(sizeof(char) * (500));                                         \
        sprintf(msp, msg, ##__VA_ARGS__);                                                    \
        log_warn("%s", msp);                                                                 \
        sprintf(mspbis, "%s\nErreur : 0x%X\n", msp, code_erreur);                            \
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Attention", mspbis, NULL);         \
        free(msp);                                                                           \
        free(mspbis);                                                                        \
    }

#endif