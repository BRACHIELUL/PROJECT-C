#include "data_list.h"

data * create_data(char* info, int DC)
{
		data *new_data = (data *)malloc(sizeof(data));
        new_data->info = (char*)malloc(strlen(info)+1);
		if(new_data==NULL)
		{
			perror("error alocating memory for data");/*not sure how to do this error messege*/
			exit(1);
		}
		
		strcpy(new_data->info,info);
	    	new_data->DC = DC;
	    	new_data->next = NULL;/* Set the next pointer to NULL*/
	
	   	return new_data;
}


void insert_to_data_table(data **head, char* info, int DC) 
{
	data *new_data = create_data(info,DC);
	data *current = *head;

	if (*head == NULL) 
   	{
		*head = new_data;
    	} 
	else 
    	{
		while (current!=NULL && current->next != NULL) 
		{
			    current = current->next;
		}
	
		current->next = new_data;
    }	
}


void print_data_list(data *head) {
	
	data *current = head;
	while (current != NULL) 
	{
       		printf("DC: %d, Info: %s\n", current->DC, current->info);
        	current = current->next;
    	}
}

void free_data_list(data *head) {
    data *current = head;
    while (current != NULL) {
        data *temp = current;
        current = current->next;
        free(temp->info);
	free(temp);
    }
}











