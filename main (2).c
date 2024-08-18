
#include "first_pass.h"
#include "open_macro.h"
#include "general_funcs.h"
#include "second_pass.h"
#include "entry_list.h"
#include "labels_in_code.h"
#include "extern_list.h"
#include "symbols_to_print_list.h"
#include "label_list.h"
#include "data_list.h"
#include "word_list.h"
#include "print_files.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char* argv[]) {
    FILE* file;
    FILE* file_macro;
    int IC;
    int DC;
    char* dot_pos;
    char name[strlen(argv[1])];
    if(argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
   
    strcpy(name,argv[1]);
    dot_pos=strchr(name,'.');
    if(dot_pos!=NULL)
    {
    	*dot_pos='\0';
    }
    file_macro = fopen("open_macros_file.am", "w");
    if(file_macro == NULL) {
        printf("Error opening file_macro\n");
	fclose(file);
        return 1;
    }

    open_macro(file,file_macro);
    fclose(file_macro);
    fclose(file);

    label *head = NULL;
    externs *extern_head = NULL;
    data *data_head = NULL;
    entry *entry_head = NULL;
    word *word_head = NULL;
    label* symbol_table=NULL;
    label_name* labels_in_code =NULL;
    symbols_to_print_list* externs_to_print_head=NULL;
    symbols_to_print_list* entries_to_print_head=NULL;
   
    first_pass(file_macro,&head,&extern_head,&data_head,&entry_head,&word_head,&IC, &DC);
   
    if(!second_pass(&symbol_table,&labels_in_code,&word_head,
                        extern_head,&entry_head,&externs_to_print_head,
                        &entries_to_print_head))
    {
	write_to_files(word_head,externs_to_print_head,entries_to_print_head,name,IC,DC,data_head);
    }
   /* free_lists(........);*/
    return 0;
}


