#include <stdio.h>

// Pour une ligne donnée, affecte à v1 et v2 les valeurs d'un string sous
// la forme v1 = v2
int config_parseLine(const char *src, char *v1, char *v2){

	if(sscanf(src, "%s = %s", v1, v2) == 2)
		return 0;
	else
		return 1;

}

// La même chose qu'au dessus, mais en prenant en compte les commentaires et les espaces
// encadrant le égal
int config_parseLineNoWS(const char *src, char *v1, char *v2){

	if(sscanf(src, "%[A-z/:.\\]=%[A-z/:.\\]", v1, v2) == 2)
		return 0;
	else
		return 1;

}