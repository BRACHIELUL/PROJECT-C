#include "label_list.h"

label * create_label(char *name, char* before,int position)
{
		label *new_label = (label *)malloc(sizeof(label));
		if(new_label==NULL)
		{
			perror("error alocating memory for label");/*not sure how to do this error messege*/
			exit(1);/*what could i de besides exit??*/
		}
		strncpy(new_label->name, name, MAX_LINE_LENGTH -1);
	   	new_label->name[MAX_LINE_LENGTH-1] = '\0'; /* Ensure null termination*/
		strncpy(new_label->before, before, MAX_LINE_LENGTH);
		new_label->before[MAX_LINE_LENGTH - 1] = '\0';
	    	/*new_label->info = (char *)malloc(strlen(info) + 1);
		if (new_label->info==NULL)
		{
			perror("error allocating memory for labels info");
			free(new_label);
			exit(1);
		}

	    	strcpy(new_label->info, info);*/
		new_label->position=position;
	    	new_label->next = NULL;/* Set the next pointer to NULL*/

	   	return new_label;
}


void insert_to_label_table(label **head,char *name, char* before,int position) 
{
	    printf("111");
	    label *new_label = create_label(name, before,position);
	    if(new_label==NULL)
	    {
			perror("error alocating memory for label");/*not sure how to do this error messege*/
			exit(1);/*what could i de besides exit??*/
    	    }
 	    printf("2222");
	    if (new_label == NULL) 
	    {
			return;
	    }
	    printf("333333");
	    if (*head == NULL) 
	    {
	    		*head = new_label;
	    } 
	    else 
	    {		
			printf("4444");
			label *current = *head;
			while (current->next != NULL) 
			{
				    current = current->next;
			}
			current->next = new_label;
	    }
}

void print_label_list(label *head) {
    label *current = head;
    while (current != NULL) {
        printf("pos : %d, Name: %s, before: %s\n",current->position, current->name, current->before);
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



