
#ifndef LABEL_LIST_H
#define LABEL_LIST_H

#define MAX_LINE_LENGTH 80


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general_funcs.h"
#include "errors.h"


typedef struct label{
	char  name[MAX_LINE_LENGTH];
	char before[MAX_LINE_LENGTH];
	int position;
	struct label * next;
	

} label;


label * create_label(char *name, char* before,int position);
void insert_to_label_table(label **head, char *name, char* before,int position);
void print_label_list(label *head);
void free_label_list(label *head);

#endif


