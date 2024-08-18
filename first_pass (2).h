#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#define MAX_LINE_LENGTH 80

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label_list.h"
#include "data_list.h"
#include "general_funcs.h"
#include "instruction_code.h"
#include "entry_list.h"
#include "extern_list.h"
#include "errors.h"

void first_pass(FILE *file, label** head, externs **extern_head ,data **data_head, entry **entry_head, word **word_head, int* IC,int* DC)void first_pass(FILE *file);
int is_label(char* line);
char* get_word(char* line);
char* get_label_name(char* line);
int is_word_a_label(label* head, char* word);
int check_data_types(data** head,char *sub_line, int flag, int DC, char* word, int line_count);
void update_label_table(label *head,int IC);
char* my_strdup(char* s);


#endif




