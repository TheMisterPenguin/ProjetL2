#ifndef __MENUS_H__
#define __MENUS_H__

#include "definition_commun.h"

typedef enum{JEU,PAUSE,PRINCIPAL,INVENTAIRE}menus_t;

extern menus_t menus;

extern void afficher_menu(menus_t * menu);

#endif