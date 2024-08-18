
#ifndef SYMBOLS_TO_PRINT_LIST_H
#define SYMBOLS_TO_PRINT_LIST_H

#define MAX_LINE_LENGTH 80



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct symbols_to_print{      
	char* name;
	int line;
	struct symbols_to_print * next;
} symbols_to_print;

symbols_to_print * create_print_extern(char *name, int line);
void insert_to_externs_to_print(symbols_to_print **head, char *name, int line);
void free_data_list(symbols_to_print *head);

#endif

