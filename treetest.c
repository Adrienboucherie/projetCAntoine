#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "lib/recherche/recherche.h"

#define CONF_FILE "tree.conf"
#define L 60

int main(int nbarg, char *args[]){

	if(nbarg < 2){
		printf("Veuillez spécifier le nom d'un fichier à rechercher.\n");
		return 0;
	}

	FILE *conf; // Fichier de configuration
	char config_line[L]; // Ligne dans le fichier de configuration
	char rootdir[L]; // Répertoire racine spécificé dans le fichier de configuration
	char v1[L], v2[L]; // Nom de la variable et sa valeur dans le ficher de configuration
	ptDir_item liste = malloc(sizeof(struct dir_item)); // Adresse du début de la liste chainée

	// Traitement du tree.conf
	conf = fopen(CONF_FILE,"r") ;
	if (conf==NULL) { perror(CONF_FILE) ; return 1 ; }
	while(fgets(config_line,L-1,conf)!=NULL)
	{
		// Récupération des variables de la configuration
		config_parseLineNoWS(config_line, v1, v2);
		if(config_line[0] != '#'){
			//printf("%s : %s\n", v1, v2);
			if(strcmp(v1, rootdir))
				strcpy(rootdir, v2);
		}
	}

	printf("Racine de l'arboresence : %s\n", rootdir);
	printf("Fichier recherché : %s\n", args[1]);
	printf("Chargement de l'arboresence...\n");
	load_list(rootdir, &liste);
	//print_list(liste, 0);
	printf("Recherhce du fichier dans l'arboresence...\n");
	search_list(args[1], liste);
	
	return 0;

}