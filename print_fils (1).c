#include "print_files.h"

void write_to_files(word* word_list, symbols_to_print_list* externs_to_print_head,
                    symbols_to_print_list* entries_to_print_head, char* file_name,
                    int ic, int dc, data* data_list) {
    char extern_file[strlen(file_name) + strlen(".ext") + 1];
    char entry_file[strlen(file_name) + strlen(".ent") + 1];
    char ob_file[strlen(file_name) + strlen(".ob") + 1];

    strcpy(extern_file, file_name);
    strcat(extern_file, ".ext");

    strcpy(entry_file, file_name);
    strcat(entry_file, ".ent");

    strcpy(ob_file, file_name);
    strcat(ob_file, ".ob");

    /* Write to extern file */
    exist_file(externs_to_print_head, extern_file, 4);

    /* Write to entry file */
    exist_file(entries_to_print_head, entry_file, 3);

    exist_ob_file(word_list, ob_file, ic, dc);
}

int exist_file(symbols_to_print_list* list, char* name, int num_digits) {
    if (list == NULL) {
        return 0;  // No need to create a file if list is empty
    }

    FILE *file = fopen(name, "w+");
    if (file == NULL) {
        fprintf(stderr, "Error opening %s file\n", name);
        return 1;
    }

    symbols_to_print_list* current = list;
    while (current) {
        fprintf(file, "%-4s %0*d\n", current->name, num_digits, current->line);
        current = current->next;
    }

    fclose(file);
    return 0;
}

int exist_ob_file(word* list, char* name, int ic_count, int dc_count, data* data_list) {
    if (list == NULL) {
        return 0;  // No need to create a file if list is empty
    }

    int IC = 100;
    FILE *file = fopen(name, "w+");
    if (file == NULL) {
        fprintf(stderr, "Error opening %s file\n", name);
        return 1;
    }
    fprintf(file, "   %d %d\n", ic_count, dc_count);
    word* current = list;
    while (current) {
        fprintf(file, "%04d %05d\n", IC,  current.info);
        current = current->next;
        IC++;
    }

    data* current_data = data_list;
    while(current_data) {
        fprintf(file, "%04d %05d\n", IC, current_data->info);
        current_data = current_data->next;
        IC++;
    }
    fclose(file);
    return 0;
}
