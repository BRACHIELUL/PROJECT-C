
#ifndef ENTRY_LIST_H
#define ENTRY_LIST_H

#define MAX_LINE_LENGTH 80

typedef struct entry{
	      
	char* info;
	struct entry * next;
	
} entry;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"



entry * create_entry(char *name);
void insert_to_entry_table(entry **head, char *info);
void print_entry_list(entry *head);
void free_entry_list(entry *head);

#endif




