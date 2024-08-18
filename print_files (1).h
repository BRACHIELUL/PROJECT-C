#ifndef PRINT_FILES_H
#define PRINT_FILES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols_to_print_list.h"
#include "word_list.h"

void write_to_files(word* word_list, symbols_to_print_list* symbols_to_print_head, symbols_to_print_list* entries_to_print_head, char* file_name, int ic, int dc, data* data_list);

int exist_file(symbols_to_print_list* list, char* name, int num_digits);

int exist_ob_file(word* list, char* name, int ic, int dc, data* data_list);

#endif

