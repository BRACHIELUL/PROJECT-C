#include "symbols_to_print_list.h"

symbols_to_print * create_symbols_to_print(char* name, int line)
{
		symbols_to_print *new_symbols_to_print = (symbols_to_print *)malloc(sizeof(symbols_to_print));
		if(new_symbols_to_print==NULL)
		{
			perror("error alocating memory for symbols_to_print");/*not sure how to do this error messege*/
			exit(1);
		}
		
		new_symbols_to_print->name = name;	
        new_symbols_to_print->line = line;
        new_symbols_to_print->next = NULL;/* Set the next pointer to NULL*/
	   	return new_symbols_to_print;
}


void insert_to_symbols_to_print_table(symbols_to_print **head, char* name, int line) 
{
    symbols_to_print *new_symbols_to_print = create_symbols_to_print(name, line);

    if (new_symbols_to_print == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_symbols_to_print;
    } else {
        symbols_to_print *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_symbols_to_print;
    }
}

void free_symbols_to_print_list(symbols_to_print *head) {
    symbols_to_print *current = head;
    while (current != NULL) {
        symbols_to_print *temp = current;
        current = current->next;
        free(temp->name);
	    free(temp);
    }
}



