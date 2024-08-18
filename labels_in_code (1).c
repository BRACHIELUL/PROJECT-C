#include "labels_in_code.h"

label_name * create_label_name(char *name)/*not sure abt the third argument but it says what line we are in*/
{
	
		label_name *new_label_name = (label_name *)malloc(sizeof(label_name));
		if(new_label_name==NULL)
		{
			perror("error alocating memory for label_name");/*not sure how to do this error messege*/
			exit(1);/*what could i de besides exit??*/
		}
		strncpy(new_label_name->name, name, MAX_LINE_LENGTH -1);
	   	new_label_name->name[MAX_LINE_LENGTH-1] = '\0'; /* Ensure null termination*/

	    	/*new_label->info = (char *)malloc(strlen(info) + 1);
		if (new_label->info==NULL)
		{
			perror("error allocating memory for labels info");
			free(new_label);
			exit(1);
		}

	    	strcpy(new_label->info, info);*/
	    	new_label_name->next = NULL;/* Set the next pointer to NULL*/

	   	return new_label_name;
}


void insert_to_labels_in_code(label **head,char *name) 
{
	
    label_name *new_label_name = create_label_name (name);
    
    if (new_label_name == NULL) 
    {
        return;
    }

    if (*head == NULL) 
    {
    	*head = new_label_name;
    } 
    else 
    {
	label_name *current = *head;
	while (current->next != NULL) 
	{
		    current = current->next;
	}
	current->next = new_label_name;
	

    }
	
}

void print_labels_in_code(label_name *head) {
    label_name *current = head;
    while (current != NULL) {
        printf("Name: %s ", current->label_name);
        current = current->next;
    }
}





void free_label_list(label *head) {
    label *current = head;
    label *temp;
    while (current != NULL) {
         temp= current;
         current = current->next;
        free(temp);/*i dont think i alocated a memory for this???*/
    }
}


