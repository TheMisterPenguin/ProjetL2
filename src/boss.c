#include <boss.h>
#include <affichage.h>
#include <sorts.h>

void affichage_chargement_attaque_boss(t_aff * boule_1, t_aff * boule_2, int phase){
    switch(phase){

        case 1: 
        case 3: next_frame_indice(boule_1, 0, 0); next_frame_indice(boule_2, 0, 0); break;
        case 2: 
        case 4: next_frame_indice(boule_1, 0, 1); next_frame_indice(boule_2, 0, 1); break;
        case 5: 
        case 7: next_frame_indice(boule_1, 1, 0); next_frame_indice(boule_2, 1, 0); break;
        case 6: 
        case 8: next_frame_indice(boule_1, 1, 1); next_frame_indice(boule_2, 1, 1); break;
        case 9: 
        case 11: next_frame_indice(boule_1, 2, 0); next_frame_indice(boule_2, 2, 0); break;
        case 10: 
        case 12: next_frame_indice(boule_1, 2, 1); next_frame_indice(boule_2, 2, 1); break;

        // deplacement boule + scintillement
    }
}

void afficher_boss(boss_t boss){

}

void afficher_bosses(boss_t boss[3]){

    if(boss[0].action == ATTAQUE){
        t_aff * boule_1 = creer_texture(PATH_SPELL_BOSS,);
        t_aff * boule_2 = creer_texture(PATH_SPELL_BOSS,);
        affichage_chargement_attaque_boss(boule_1, boule_2, &(boss[0].duree));
    }
}