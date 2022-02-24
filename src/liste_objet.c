#include <liste_objet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//creer la structure contenant la liste des objets
lobjet_t * creer_liste_objet(){
    lobjet_t * liste_obj; //le pointeur sur structure contenant la liste d'objets que la fonction retourne
    FILE * obj; //fichier source contenant les objets


    t_item type;
    char nom[50];
    int i = 0;
    int niveau, att, def, vit;
    char c;
    int nb_obj = 0; //nombre d'objets dans le fichier source

    if(( liste_obj= malloc(sizeof(lobjet_t))) == NULL )
    {
      fprintf( stderr , "creer_liste_objet: debordement memoire lors de la creation d'une structure lobjet_t\n");
      return((lobjet_t *)NULL);
    }

    obj = fopen("../ressource/objet.txt", "r");

    if(obj == NULL){
        fprintf( stderr, "fichier source objet inaccessible\n") ;
        return((lobjet_t*)NULL);
    }

    liste_obj->nb = 0;
    liste_obj->liste = (objet_t **)NULL ;

    //compte les objets (1 par ligne)
    while(fscanf(obj, "%c", &c) == 1){
        if(c == '\n') nb_obj++;
    }

    fseek(obj,0,SEEK_SET); // le pointeur du fichier pointe à son début

    if( nb_obj > 0 ){
        if( (liste_obj->liste = malloc(sizeof(objet_t*) * nb_obj)) == NULL ){
            fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] obj1s\n",
                nb_obj ) ;
            return((lobjet_t*)NULL);
        }

        while(fscanf(obj, "%d%50[^:]:%d%d%d%d", (int *)&type, nom, &niveau, &att, &def, &vit) == 6){
            liste_obj->liste[i++] = creer_objet(type, nom, niveau, att, def, vit);
        }

        liste_obj->nb = i;
    }


    fclose(obj);

    return liste_obj;
}