
#ifndef DATA_LIST_H
#define DATA_LIST_H

#define MAX_LINE_LENGTH 80

typedef struct data{
	      
	char* info;
	int DC;
	struct data * next;	

} data;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"



data * create_data(char *name,int DC);
void insert_to_data_table(data **head, char *info, int DC);
void print_data_list(data *head);
void free_data_list(data *head);

#endif




