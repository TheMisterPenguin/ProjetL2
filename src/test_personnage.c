#include <commun.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * \file test_personnage.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module personnage
 * \version 0.2
 * \date 05/04/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
joueur_t * perso_principal = NULL;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void creation_personnage(void) {
    CU_ASSERT_NOT_EQUAL(perso_principal = new_joueur("test", 0, "ressources/objet/objet.txt"), NULL);
    CU_ASSERT_STRING_EQUAL(perso_principal->nom_pers, "test");

    //statistiques
    CU_ASSERT_EQUAL(perso_principal->niveau, 0);
    CU_ASSERT_EQUAL(perso_principal->xp, 0);
    CU_ASSERT_EQUAL(perso_principal->maxPdv, 100);
    CU_ASSERT_EQUAL(perso_principal->pdv, 50);
    CU_ASSERT_EQUAL(perso_principal->attaque, 10);
    CU_ASSERT_EQUAL(perso_principal->defense, 10);
    CU_ASSERT_EQUAL(perso_principal->vitesse, 1);
    CU_ASSERT_EQUAL(perso_principal->attaque_actif, 10);
    CU_ASSERT_EQUAL(perso_principal->defense_actif, 10);
    CU_ASSERT_EQUAL(perso_principal->vitesse_actif, 1);

    //inventaire
    CU_ASSERT_NOT_EQUAL(perso_principal->inventaire, NULL);

    //statut
    CU_ASSERT_NOT_EQUAL(perso_principal->statut, NULL);
    CU_ASSERT_EQUAL(perso_principal->statut->orient_dep, NORD_1);
    CU_ASSERT_EQUAL(perso_principal->statut->bouclier_equipe, faux);
    CU_ASSERT_EQUAL(perso_principal->statut->duree, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->duree_anim, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->en_mouvement, faux);
    CU_ASSERT_EQUAL(perso_principal->statut->action, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->animation, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->zone_colision.x, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->zone_colision.y, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->vrai_zone_collision.x, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->vrai_zone_collision.y, 0);
    CU_ASSERT_EQUAL(perso_principal->statut->vrai_zone_collision.w, map->taille_case);
    CU_ASSERT_EQUAL(perso_principal->statut->vrai_zone_collision.h, map->taille_case);

    //textures
    CU_ASSERT_NOT_EQUAL(perso_principal->textures_joueur, NULL);
}

int main(){
    init();

    charger_base_coffre("coffres.json", &liste_base_coffres);
    charger_base_monstre("monstres.json", &liste_base_monstres);

    map = charger_map("../bin/map/1.json");
    init_animations();
    
    CU_pSuite pSuite = NULL;
    
    if ( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

    pSuite = CU_add_suite( "personnage_test_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    if (NULL == CU_add_test(pSuite, "creation_personnage", creation_personnage))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    afficher_statistiques(perso_principal);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");

    // detruire_joueur(perso_principal);

    fermer_programme(EXIT_SUCCESS);

    CU_cleanup_registry();
    return CU_get_error();
}