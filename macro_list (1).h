
#ifndef MACRO_LIST_H
#define MACRO_LIST_H

#define MAX_LINE_LENGTH 80
#define LENGTH_MAC 5



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

typedef struct macro_node{

	char  name[MAX_LINE_LENGTH];
	char* info;
	struct macro_node * next;
} macro_node;


macro_node * create_macro(char *name, char* info);
void add_macro(macro_node **head, char *name_from_line, char* info);
void print_macro_list(macro_node *head);
void free_macro_list(macro_node *head);

#endif


