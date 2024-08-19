/*#ifndef PRINT_FILES_H
#define PRINT_FILES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols_to_print_list.h"
#include "word_list.h"

typedef struct symbols_to_print_list {
    char* name;
    int line;
    struct symbols_to_print_list* next;
} symbols_to_print_list;

typedef struct word {
    int info;
    struct word* next;
} word;

typedef struct data {
    int info;
    struct data* next;
} data;




void write_to_files(word* word_list, symbols_to_print_list* externs_to_print_head,
                    symbols_to_print_list* entries_to_print_head, char* file_name,
                    int ic, int dc, data* data_list);
int exist_file(symbols_to_print_list* list, char* name, int num_digits);
int exist_ob_file(word* list, char* name, int ic_count, int dc_count, data* data_list);


/*void write_to_files(word* word_list, symbols_to_print* symbols_to_print_head, symbols_to_print_list* entries_to_print_head, char* file_name, int ic, int dc, data* data_list);

int exist_file(symbols_to_print_list* list, char* name, int num_digits);

int exist_ob_file(word* list, char* name, int ic, int dc, data* data_list);*/




/*#endif*/ 



#ifndef PRINT_FILES_H
#define PRINT_FILES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbols_to_print_list.h"
#include "word_list.h"
#include "data_list.h"

void write_to_files(word* word_list, symbols_to_print* symbols_to_print_head, symbols_to_print* entries_to_print_head, char* file_name, int ic, int dc, data* data_list);

int exist_file(symbols_to_print* list, char* name, int num_digits);

int exist_ob_file(word* list, char* name, int ic, int dc, data* data_list);

#endif

