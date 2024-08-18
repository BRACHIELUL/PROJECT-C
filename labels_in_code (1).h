#ifndef LABELS_IN_CODE_H
#define LABELS_IN_CODE_H

#define MAX_LINE_LENGTH 80

typedef struct label_name{
	char  name[MAX_LINE_LENGTH];
	struct label * next;
} label_name;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general_funcs.h"



label_name * create_label_name(char *name);
void insert_to_labels_in_code(label_name **head, char *name);
void print_labels_in_code(label_name *head);
void free_labels_in_code(label_name *head);

#endif

