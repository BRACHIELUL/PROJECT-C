#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#define MAX_LINE_LENGTH 80


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "label_list.h"
#include "entry_list.h"
#include "extern_list.h"
#include "errors.h"
#include "symbols_to_print_list.h"
#include "labels_in_code.h"
#include "data_list.h"
#include "word_list.h"

int second_pass(label* symbol_table, label_name* labels_in_code, word* word_list,
                        externs* external_symbols, entry* entry_symbols, symbols_to_print ** externs_to_print_head,
                        symbols_to_print** entries_to_print_head);

int handle_entry_file(entry* entry_symbols, label* symbol_table, symbols_to_print* entries_to_print_head);

label* find_label_in_list(char* name, label* symbol_table);

#endif

