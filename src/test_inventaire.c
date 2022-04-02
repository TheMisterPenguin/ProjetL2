#include <commun.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

/**
 * \file test_inventaire.c
 * \author Max Descomps (Max.Descomps.Etu@univ-lemans.fr)
 * \brief Programme de test du module inventaire
 * \version 0.3
 * \date 02/04/2022
 * \copyright Copyright (c) 2022
 */

long int compteur;
t_map *test_map;
unsigned int FENETRE_LONGUEUR, FENETRE_LARGEUR;
joueur_t * perso_principal = NULL;
objet_t * objet_test = NULL;
lobjet_t * sac = NULL;
lobjet_t * equipe = NULL;

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

void generation_inventaire(void) {
    //création inventaire
    inventaire_t * inventaire = creer_inventaire();
    
    CU_ASSERT_NOT_EQUAL(inventaire, NULL);
    CU_ASSERT_NOT_EQUAL(inventaire->sac, NULL);
    CU_ASSERT_NOT_EQUAL(inventaire->equipe, NULL);
    CU_ASSERT_NOT_EQUAL(inventaire->sac->liste, NULL);
    CU_ASSERT_NOT_EQUAL(inventaire->equipe->liste, NULL);
    CU_ASSERT_EQUAL(inventaire->sac->nb, 0);
    CU_ASSERT_EQUAL(inventaire->equipe->nb, 0);
    CU_ASSERT_EQUAL(inventaire->sac->liste[0], NULL);
    CU_ASSERT_EQUAL(inventaire->equipe->liste[0], NULL);

    //destruction inventaire
    detruire_inventaire(&inventaire);
    CU_ASSERT_EQUAL(inventaire, NULL);
}

void modification_inventaire(void) {
    int type;

    //création objets
    CU_ASSERT_NOT_EQUAL(objets = creer_liste_objet("../ressource/objet.txt"), NULL);
    CU_ASSERT_NOT_EQUAL(objet_test = creer_objet("ressources/objet/old_sword.bmp", arme, "sabre du purificateur", 0, 5, 2, 2), NULL);

    //modification inventaire (sac)
    ramasser_objet(objet_test, perso_principal->inventaire);
    CU_ASSERT_NOT_EQUAL(sac->liste[(sac->nb)-1], NULL);
    CU_ASSERT_NOT_EQUAL(sac->nb, 0);
    CU_ASSERT_EQUAL(equipe->liste[0], NULL);
    CU_ASSERT_EQUAL(equipe->nb, 0);

    //statistiques inchangées
    CU_ASSERT_EQUAL(perso_principal->niveau, 0);
    CU_ASSERT_EQUAL(perso_principal->xp, 0);
    CU_ASSERT_EQUAL(perso_principal->maxPdv, 10);
    CU_ASSERT_EQUAL(perso_principal->pdv, 10);
    CU_ASSERT_EQUAL(perso_principal->attaque, 10);
    CU_ASSERT_EQUAL(perso_principal->defense, 10);
    CU_ASSERT_EQUAL(perso_principal->vitesse, 1);
    CU_ASSERT_EQUAL(perso_principal->attaque_actif, 10);
    CU_ASSERT_EQUAL(perso_principal->defense_actif, 10);
    CU_ASSERT_EQUAL(perso_principal->vitesse_actif, 1);

    //modification des objets équipés
    equiper_objet(perso_principal, &(sac->liste[(sac->nb)-1]));

    //vérifiaction des valeurs du tableau d'objets équipés
    for(type=0; type<NB_TYPE_OBJ; type++){
        if(type != arme)
            CU_ASSERT_EQUAL(equipe->liste[type], NULL);
    }
    CU_ASSERT_NOT_EQUAL(equipe->liste[arme], NULL);

    //test modification statistiques
    CU_ASSERT_EQUAL(perso_principal->vitesse_actif, perso_principal->vitesse + objet_test->vitesse);
    CU_ASSERT_EQUAL(perso_principal->attaque_actif, perso_principal->attaque + objet_test->attaque);
    CU_ASSERT_EQUAL(perso_principal->defense_actif, perso_principal->defense + objet_test->defense);

    //test avec valeurs extremes (négatives, 0, grand)
    //test d'appels multiples
}


int main(){
    init();

    map = charger_s_map(charger_f_map("map.json"));
    perso_principal = new_joueur("test", 0);

    sac = perso_principal->inventaire->sac;
    equipe = perso_principal->inventaire->equipe;
    
    CU_pSuite pSuite = NULL;
    
    if ( CUE_SUCCESS != CU_initialize_registry() )
        return CU_get_error();

    pSuite = CU_add_suite( "personnage_test_suite", init_suite, clean_suite );
    if ( NULL == pSuite ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    

    if ( (NULL == CU_add_test(pSuite, "generation_inventaire", generation_inventaire)) ||
        (NULL == CU_add_test(pSuite, "modification_inventaire", modification_inventaire))
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