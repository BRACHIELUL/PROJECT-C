
#ifndef OPEN_MACRO_H
#define OPEN_MACRO_H

#define MAX_LINE_LENGTH 80
#define LENGTH_MAC 5
#define MAX_INSTRUCTION_LENGTH 5
#define NUM_OF_OPCODES 17

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_list.h"
#include "general_funcs.h"
#include "errors.h"


void open_macro(FILE *file,FILE *mac_file);
int is_macro(FILE* file,char* line, macro_node **head, char *sub_line,int line_count);
void appendLine(char **info, char *line);
int check_if_macro(char* sub_line);
char* copy_info_to_temp(char* line);

#endif


