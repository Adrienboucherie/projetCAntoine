#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>		
#include <dirent.h>


// config.c
int config_parseLine(const char *, char *, char *);
int config_parseLineNoWS(const char *, char *, char *);

// directory_list.c
struct dir_item{
    char name[90000];
    char path[90000];
    struct dir_item * directory_content;
    struct dir_item * next;
};

typedef struct dir_item * ptDir_item;

void load_list(char *, ptDir_item *);
void print_list(ptDir_item list, int);
void search_list(char *, ptDir_item);
