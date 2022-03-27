/**
 * \file code_erreur.h
 * \author Despert Ange (Ange.Despert.Etu@univ-lemans.fr)
 * \brief Fichier contenant les codes d'erreur du programme
 * \version 0.1
 * \date 02/02/2022
 * 
 * \copyright Copyright (c) 2022
 * 
 */

#ifndef __H_CODE_ERREUR__
#define __H_CODE_ERREUR__

enum
{
    AUCUNE_ERREUR,
    SDL_ERREUR,
    ERREUR_TEXTURE,
    OUT_OF_MEM,
    BUFFER_EMPTY,
    ERREUR_FICHIER,
    ERREUR_FONCTION,
    ERREUR_MAP,
    ERREUR_INIT,
    ERREUR_SDL_IMG,
    ERREUR_SDL_TTF,
    ERREUR_SDL_MIX,
    ERREUR_SDL_AUDIO,
    ERREUR_SDL_TIMER,
    ERREUR_SDL_MOUSE,
    ERREUR_SDL_JOYSTICK,
    ERREUR_SDL_RENDER,
    ERREUR_SDL_WINDOW,
    ERREUR_SDL_MUSIC,
    ERREUR_SDL_SURFACE,
    ERREUR_SDL_PIXEL,
    ERREUR_SDL_MOUSEMOTION,
    ERREUR_SDL_MOUSEBUTTON,
    ERREUR_SDL_KEYBOARD,
    ERREUR_SDL_SCANCODE,
    ERREUR_SDL_QUIT,
    ERREUR_SDL_EVENT,
    ERREUR_SDL_TIMER_START,
    ERREUR_SDL_TIMER_STOP,
    ERREUR_LISTE,
    ERR_CREATION_REPERTOIRE_SAUVEGARDE
};

#endif