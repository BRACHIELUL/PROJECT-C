#include "extern_list.h"

externs * create_extern(char* info)
{
	
		externs *new_externs = (externs *)malloc(sizeof(externs));
		if(new_externs==NULL)
		{
			perror("error alocating memory for externs");/*not sure how to do this error messege*/
			exit(1);
		}
		
		new_externs->info = info;	
	    	new_externs->next = NULL;

	   	return new_externs;
}


void insert_to_extern_table(externs **head, char* info) 
{
	    externs *new_externs = create_extern(info);
   
	    if (new_externs == NULL) 
	    {
	    	return;
	    }

	    if (*head == NULL) 
	    {
	    	*head = new_externs;
	    } 
	    else 
	    {
		externs *current = *head;

		while (current->next != NULL) 
		{
			    current = current->next;
		}
		current->next = new_externs;
	

	    }
	
}

void print_extern_list(externs *head) 
{
    externs *current = head;

    while (current != NULL) 
    {
        printf("externs Info: %s\n",  current->info);
        current = current->next;
    }
}


void free_extern_list(externs *head) 
{
    externs *current = head;

    while (current != NULL) {
        externs *temp = current;
        current = current->next;
        free(temp->info);
	free(temp);
    }
}



