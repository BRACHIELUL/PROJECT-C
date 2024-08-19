
#ifndef EXTERN_LIST_H
#define EXTERN_LIST_H

#define MAX_LINE_LENGTH 80

typedef struct externs{
	      
	char* info;
	struct externs * next;

} externs;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"


externs * create_extern(char *name);
void insert_to_extern_table(externs **head, char *info);
void print_extern_list(externs *head);
void free_extern_list(externs *head);

#endif




