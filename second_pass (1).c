#include "second_pass.h"


int second_pass(label* symbol_table, label_name* labels_in_code, word* word_list,
                        externs* external_symbols, entry* entry_symbols, symbols_to_print_list** externs_to_print_head,
                        symbols_to_print_list** entries_to_print_head) {
    int error_found = 0;
    int IC = 0; 
    int find = 0;  
    int find_extern = 0; 
    externs* current_extern = external_symbols;
    label* current = symbol_table;

    *externs_to_print_head = NULL;
    *entries_to_print_head = NULL;

    while (word_list) {
        if (word_list.info.simple_info == LBL) { /* if there is a label */
            find = 0;
            find_extern = 0;  // Reset before checking externals
            current = symbol_table;

            while (current && find == 0) {
                if (strcmp(current->name, labels_in_code->label_name) == 0) {
                    find = 1; 
                    word_list.info.simple_info->data = current->position;
                     word_list.info.simple_info->are = 2;  
                } else {
                    current = current->next;
                }
            }

            if (find == 0) {  // If the label is not in the symbol table
                current_extern = external_symbols;  // Reset to the start of the externals list

                while (current_extern && find_extern == 0) {
                    if (strcmp(current_extern->info, labels_in_code->label_name) == 0) {
                        find_extern = 1; 
                        insert_to_symbols_to_print_table(externs_to_print_head, current_extern->info, IC);
                        word_list.info.simple_info->data = 0;
                        word_list.info.simple_info->are = 1;
                    } else {
                        current_extern = current_extern->next;
                    }
                }
            }

            if (find == 0 && find_extern == 0) {
                fprintf(stderr, "Error: label in line %d was not found\n", word_list->line);
                error_found = 1;  // Mark an error found
            }

            word_list = word_list->next;   
            labels_in_code = labels_in_code->next;
        }
        IC++;
    }

    error_found = handle_entry_file(entry_symbols, symbol_table, *entries_to_print_head) || error_found;
    return error_found;
}

int handle_entry_file(entry* entry_symbols, label* symbol_table, symbols_to_print_list* entries_to_print_head) {
    entry* current = entry_symbols;
    label* lbl;  
    char* name;

    if (!current) {
        return 0;
    }

    while (current) {
        name = current->info;
        lbl = find_label_in_list(name, symbol_table);
        if (lbl == NULL) {
            fprintf(stderr, "error: label %s was not existed\n", name);  
            return 1;  // Label not found, exit with error
        }
        insert_to_symbols_to_print_table(&entries_to_print_head, lbl->name, lbl->position);
        current = current->next;
    }

    return 0;
}

label* find_label_in_list(char* name, label* symbol_table) {
    label* current = symbol_table;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Return NULL if the label was not found
}
