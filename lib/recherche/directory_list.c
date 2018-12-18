#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>

// Structure qui stocke un élément de l'arborescence
struct dir_item{
    char name[90000]; // Nom de l'élément
    char path[90000]; // Chemin de l'élément
    struct dir_item * directory_content; // Contenu de l'élément si il s'agit d'un dossier
    struct dir_item * next; // Prochaine élément sur la liste
};

typedef struct dir_item * ptDir_item;


// Charge récursivement l'aborenscence de path dans la liste origin
void load_list(char *path, ptDir_item *origin){

	int firstItem = 1; // Définit si il s'agit du première item de la liste 
	DIR *directory; // Répertoire à charger
	struct dirent *curdir; // Element courant du répertoire chargé
	ptDir_item cur_pt = malloc(sizeof(struct dir_item)); // Element courant de la liste chainée
	ptDir_item next_pt = malloc(sizeof(struct dir_item));  // Prochain élément de la liste chainée 
	ptDir_item dir_content = malloc(sizeof(struct dir_item)); // Contenu du répertoire chargé si l'élément est un répertoire (voir plus bas)

	directory = opendir(path);
	if (directory==NULL){
		//printf("ERREUR LORS DE L'OUVERTURE DE %s (%s)\n", path, strerror(errno)); 
		return;
	}

	while((curdir = readdir(directory)) != NULL){

		if(strcmp(".", curdir->d_name) && strcmp("..", curdir->d_name)){

			if(firstItem == 1){
				strcpy((*origin)->name, curdir->d_name);
				sprintf((*origin)->path, "%s/%s", path, (*origin)->name);
				//printf("Save : %s\n", (*origin)->path);
				(*origin)->directory_content = NULL;
				(*origin)->next = NULL;
				cur_pt = *origin;
				firstItem = 0;
			}
			else{
				next_pt = malloc(sizeof(struct dir_item));
				strcpy(next_pt->name, curdir->d_name);
				sprintf(next_pt->path, "%s/%s", path, next_pt->name);
				//printf("Save : %s\n", next_pt->path);
				next_pt->next = NULL;
				next_pt->directory_content = NULL;
				cur_pt->next = next_pt;
				cur_pt = next_pt;
			}

			if(curdir->d_type & DT_DIR){
				dir_content = malloc(sizeof(struct dir_item));
				load_list(cur_pt->path, &dir_content);
				if(strcmp(dir_content->name, ""))
					cur_pt->directory_content = dir_content;
				
			}
			else{
				//printf("Not a directory (%s)\n", curdir->d_name);
			}
		}
	}
	closedir(directory);
}

// Affiche la liste list avec indentation en fonction des répertoires.
// indent correspond à l'indentation, l'appel initial se fait avec 0.
void print_list(ptDir_item list, int indent){

	ptDir_item pt_nav;
	pt_nav = list;
	int i = 0;

	while(pt_nav != NULL){

		 for (int i = 0; i < indent; ++i)
		 {
		 	printf("\t");
		 }
		printf("%s\n", pt_nav->name);
		if(pt_nav->directory_content != NULL){
			print_list(pt_nav->directory_content, indent + 1);
		}
		pt_nav = pt_nav->next;
	}
}

// Recherche le fichier du nom de target dans la liste list
void search_list(char *target, ptDir_item list){

	ptDir_item pt_nav;
	pt_nav = list;

	while(pt_nav != NULL){

		if(!strcmp(target, pt_nav->name)){
			printf("%s\n", pt_nav->path);
		}

		if(pt_nav->directory_content != NULL){
			search_list(target, pt_nav->directory_content);
		}
		pt_nav = pt_nav->next;
	}

}