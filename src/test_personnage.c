#include <commun.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * \file test_personnage.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module personnage
 * \version 0.2
 * \date 28/03/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
joueur_t * perso_principal = NULL;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void personnage_test_1(void) {
    CU_ASSERT_NOT_EQUAL(perso_principal = new_joueur("test", 0), NULL);
    //autres tests similaires
}

void personnage_test_2(void) {
    CU_ASSERT_NOT_EQUAL(objets = creer_liste_objet(), NULL);
    creer_textures_objets(objets);
    tout_ramasser(objets, perso_principal->inventaire);
}


int main(){
    init();

    map = charger_s_map(charger_f_map("map.json"));
    
    CU_pSuite pSuite = NULL;
    
    if ( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

    pSuite = CU_add_suite( "personnage_test_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    if ( (NULL == CU_add_test(pSuite, "personnage_test_1", personnage_test_1)) ||
        (NULL == CU_add_test(pSuite, "personnage_test_2", personnage_test_2))
        )
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