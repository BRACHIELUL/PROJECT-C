
#include "entry_list.h"

entry * create_entry(char* info)
{
	
		entry *new_entry = (entry *)malloc(sizeof(entry));
       		new_entry->info = (char*)malloc(strlen(info)+1);
		if(new_entry==NULL)
		{
			perror("error alocating memory for entry");/*not sure how to do this error messege*/
			exit(1);
		}
		
		strcpy(new_entry->info,info);
	   	new_entry->next = NULL;/* Set the next pointer to NULL*/

	   	return new_entry;
}


void insert_to_entry_table(entry **head, char* info) 
{
	    entry *new_entry = create_entry(info);
	
	    if (new_entry == NULL) 
	    {
		return;
	    }

	    if (*head == NULL) 
	    {
	    	*head = new_entry;
	    } 
	    else 
	    {
		entry *current = *head;
		while (current->next != NULL) 
		{
			    current = current->next;
		}
		current->next = new_entry;

	    }
}


void print_entry_list(entry *head) {
	
    entry *current = head;
    while (current != NULL) 
    {
        printf("entrys Info: %s\n",  current->info);
        current = current->next;
    }
}


void free_entry_list(entry *head) {
    entry *current = head;
    while (current != NULL) {
        entry *temp = current;
        current = current->next;
        free(temp->info);
	free(temp);
    }
}





