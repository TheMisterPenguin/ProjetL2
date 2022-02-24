#include <objet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//initialise la liste des objets
objet_t ** init_objet(){
    objet_t ** tabObj; //le pointeur d'objets retourné
    FILE * obj; //fichier source contenant les objets


    t_item type;
    char nom[50];
    int i = 0, niveau, att, def, vit;
    char c;
    int nbObj = 0; //nombre d'objets dans le fichier source

    obj = fopen("../ressource/objet.txt", "r");

    if(obj == NULL){
        fprintf( stderr, "fichier source objet inaccessible\n") ;
        return((objet_t**)NULL);
    }
    //compte les objets (1 par ligne)
    while(fscanf(obj, "%c", &c) == 1){
        if(c == '\n') nbObj++;
    }

    fseek(obj,0,SEEK_SET); // le pointeur du fichier pointe à son début

    if( (tabObj = malloc(sizeof(objet_t*) * nbObj)) == NULL ){
        fprintf( stderr , "init_objet: debordement memoire lors de la creation d'une liste de [%d] obj1s\n",
      		   nbObj ) ;
      	  return((objet_t**)NULL);
    }

    while(fscanf(obj, "%d%50[^:]:%d%d%d%d", (int *)&type, nom, &niveau, &att, &def, &vit) == 6){
        tabObj[i++] = creer_objet(type, nom, niveau, att, def, vit);
    }

    fclose(obj);

    return tabObj;
}