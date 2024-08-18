#include "open_macro.h"

void open_macro(FILE *file, FILE *mac_file)
{
	char line[MAX_LINE_LENGTH];
	macro_node *head = NULL;
	macro_node *current;
	char *sub_line;
	int line_count=0;

	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		line_count++;
		while(*line==';')
		{
			fgets(line, MAX_LINE_LENGTH, file);
			line_count++;
		}
		sub_line = continue_on_blanks(line);
		
		if (check_if_macro(sub_line))
		{
			line_count=is_macro(file, line, &head, sub_line,line_count);
		}
		else if (head != NULL) /*checking if the line is calling a macro*/
		{
			current = head;

			while (current != NULL)
			{
				
				if (strncmp(sub_line, current->name,LENGTH_MAC) == 0)
				{
					
					fprintf(mac_file, "%s", current->info); /*need to specify the info*/
					break;
				}
				current = current->next;
			}
			if (current == NULL) /* if we are calling a macro*/
			{
				fprintf(mac_file, "%s", line); /*need to specify the info*/
			}
		}
		else{
			fprintf(mac_file, "%s", line); 
		}
	}
	printf("----macro_list-----");
	print_macro_list(head);
	/*free_macro_list(head);*/
}


int check_if_macro(char *sub_line)
{
	char temp[LENGTH_MAC];
	strncpy(temp, sub_line, LENGTH_MAC);
	return (strncmp("macr", temp, 4) == 0); /*if is a macro*/
}


int is_macro(FILE *file, char *line, macro_node **head, char *sub_line,int line_count)
{
	int i=0;
	int length;
	char name_from_line[MAX_LINE_LENGTH];
	char *info = NULL;
	char instructions[NUM_OF_OPCODES][MAX_INSTRUCTION_LENGTH] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
	sub_line = continue_on_blanks(sub_line + LENGTH_MAC);
	memcpy(name_from_line, sub_line,MAX_LINE_LENGTH);/*copy only the macro name */

	line = continue_on_blanks(line);
	length=continue_till_blanks(line);
	line+=length;
	line = continue_on_blanks(line);
	length=continue_till_blanks(line);
	line+=length;
	line = continue_on_blanks(line);

	if (*line!='\n' && *line!='\0')
	{
		print_errors(line_count,EXTERA_CHARS_ON_MACRO_CALL_LINE);
	}

	while (i < NUM_OF_OPCODES)
	{
		if (strcmp(name_from_line, instructions[i]) == 0)  /*If match is found*/
    		{
			print_errors(line_count, INVALID_MACRO_NAME);  /*Error if the macro name is an instruction name*/
			break;
  		}
   		 i++;
	}

	
	
	while (fgets(line, MAX_LINE_LENGTH, file))
	{ 
		line_count++;
		if (strstr(line, "endmacr") != NULL)
		{
			break; /* Exit the inner while loop*/
		}
		appendLine(&info, line);
		
	}
	
	line = continue_on_blanks(line);
	length=continue_till_blanks(line);
	line+=length;
	line = continue_on_blanks(line);
	if (*line!='\n' && *line!='\0')
	{
		print_errors(line_count,EXTERA_CHARS_AFTER_ENDMACR);
	}
	add_macro(head, name_from_line, info); /* add a link to the linked list*/
	return line_count;
	
}


void appendLine(char **info, char *line)
{
	int new_size;
	if (*info == NULL)
	{ 
		/* If info is NULL, allocate enough space for the line and the null terminator*/
		*info = (char *)malloc(strlen(line) + 1);
		if (*info == NULL)
		{
			perror("Unable to allocate memory");
			return;
		}
		strcpy(*info, line);
	}
	else
	{
		/* If info is not NULL, reallocate to add space for the new line and the null terminator*/
		new_size = strlen(*info) + strlen(line) + 1;
		*info = (char *)realloc(*info, new_size);
		if (*info == NULL)
		{
			perror("Unable to reallocate memory");
			return;
		}
		strcat(*info, line);
	}
}



