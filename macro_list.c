#include "macro_list.h"

macro_node * create_macro(char *name, char* info)
{
	
		macro_node *new_macro = (macro_node *)malloc(sizeof(macro_node));
		if(new_macro==NULL)
		{
			perror("error alocating memory for macro");/*not sure how to do this error messege*/
			exit(1);
		}
		strncpy(new_macro->name, name, MAX_LINE_LENGTH - 1);
	   	new_macro->name[MAX_LINE_LENGTH] = '\0'; /* Ensure null termination*/
		new_macro->info = info;
		
	    	/*new_macro->info = (char *)malloc(strlen(info) + 1);
		if (new_macro->info==NULL)
		{
			perror("error allocating memory for macros info");
			free(new_macro);
			exit(1);
		}

	    	strcpy(new_macro->info, info);*/
	    	new_macro->next = NULL;/* Set the next pointer to NULL*/

	   	return new_macro;
}


void add_macro(macro_node **head,char *name_from_line, char* info) 
{
	    macro_node *new_macro = create_macro(name_from_line, info);
   
	    if (new_macro == NULL) 
	    {
		return;
	    }

	    if (*head == NULL) 
	    {
	    	*head = new_macro;
	    } 
	    else 
	    {
		macro_node *current = *head;
		while (current->next != NULL) 
		{
			    current = current->next;
		}
		current->next = new_macro;

	    }
}


void print_macro_list(macro_node *head) {
    macro_node *current = head;
    while (current != NULL) {
        printf("Name: %s, Info: %s\n", current->name, current->info);
        current = current->next;
    }
}





void free_macro_list(macro_node *head) {
    macro_node *current = head;
    while (current != NULL) {
        macro_node *temp = current;
        current = current->next;
        free(temp->info);
	free(temp);
    }
}







