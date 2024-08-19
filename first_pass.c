#include "first_pass.h"


void first_pass(FILE *file, label** head, externs **extern_head ,data **data_head, entry **entry_head, word **word_head, int* IC,int* DC)
{

	char line[MAX_LINE_LENGTH];
	
	int flag;
	char exEn_name[MAX_LINE_LENGTH];
	char *label_name = NULL;
	char *word_name = NULL;
	int length;
	char *sub_line;
	
	/*do i nees a instruction head?*/
	int line_count=0;
        DC=0;
	IC=100;
	file = fopen("open_macros_file.am", "r");
	if (file == NULL)
	{
		printf("Error opening file_macro\n");
		return;
	}

	rewind(file);

	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		printf("Line %d: %s", line_count, line);
		line_count++;
		sub_line = continue_on_blanks(line);
		flag = is_label(line);

		if (flag)
		{

			label_name = get_label_name(sub_line);
			length = strlen(label_name);
			sub_line += length + 1;
		}
		
		word_name = get_word(sub_line);
		length = strlen(word_name);
		sub_line += length;
		if(*sub_line =='\n')
			continue;

		if (strcmp(word_name, ".data") == 0 || strcmp(word_name, ".string") == 0)
		{
		
			if (flag)
			{
				if (is_word_a_label(head, label_name))
				{
					print_errors(line_count,ALREADY_EXISTING_LABEL);
					break;
				}
				else
				{
					insert_to_label_table(&head, label_name, "data", DC);
				}
			}

			DC = check_data_types(&data_head, sub_line, flag, DC, word_name,line_count);
		}
		else if (strcmp(word_name, ".extern") == 0 || strcmp(word_name, ".entry") == 0)
		{
			sub_line = continue_on_blanks(sub_line);
			length = continue_till_blanks(sub_line);
			strncpy(exEn_name, sub_line, length);
			exEn_name[length] = '\0';
			
			if (strcmp(word_name, ".extern") == 0)
			{
				insert_to_extern_table(&extern_head, exEn_name);
			}
			else if (strcmp(word_name, ".entry") == 0)
			{
				insert_to_entry_table(&entry_head, exEn_name);
			}
			if (flag)
			{
				if (is_word_a_label(head, label_name)) /*should i do a &*/
				{
					print_errors(line_count,ALREADY_EXISTING_LABEL);
					break;
				}
				else
				{
					insert_to_label_table(&head, label_name, "code", DC); /*do i send DC???*/
				}
			}	
		}
		else
		{
			if (flag)
			{
				insert_to_label_table(&head, label_name, "instruction", IC);
			}

			IC =instruction_code(&word_head, word_name, sub_line,IC,flag,line_count);
		}
		
		free(word_name);
		word_name = NULL;
		free(label_name);
		label_name = NULL;
	}
	if (head != NULL)
	{
		update_label_table(head,IC);
	}
	
	printf("----labels----\n");
	print_label_list(head);
	printf("----externs----\n");
	print_extern_list(extern_head);
	printf("----entrys----\n");
	print_entry_list(entry_head);
	printf("----datas----\n");
	print_data_list(data_head);
	printf("----instructions----\n");
	print_word_list(word_head);
	fclose(file);
	
}

int is_label(char *line)
{
	/*need to check if first letter in label is a letter vs. num*/
	int length;
	length = continue_till_blanks(line);
	line = line + (length - 1);
	if (*line == ':')
	{
		return 1;
	}
	return 0;
}


char *get_word(char *line)
{
	char *chr;
	int length = 0;
	char *word = (char *)malloc(MAX_LINE_LENGTH * sizeof(char) + 1);
	if (word == NULL)
	{
		perror("Failed to allocate memory for word");
		return NULL;
	}

	memset(word, 0, MAX_LINE_LENGTH);
	line = continue_on_blanks(line);
	chr = line;

	while ((*chr != ' ') && (*chr != '\r') && (*chr != '\t') && (*chr != '\n') && (chr - line < MAX_LINE_LENGTH - 1))
	{
		chr++;
		length++;
	}
	strncpy(word, line, length);
	word[length] = '\0';
	return word;
}


char *get_label_name(char *line)
{
	char *chr;
	int length = 0;
	char *label_name = (char *)malloc(MAX_LINE_LENGTH * sizeof(char) + 1);
	if (label_name == NULL)
	{
		perror("Failed to allocate memory for label_name");
		return NULL;
	}

	memset(label_name, 0, MAX_LINE_LENGTH); /*clear static array*/
	chr = line;
	while (*chr != ':' && (chr - line < MAX_LINE_LENGTH - 1))
	{
		length++;
		chr++;
	}
	strncpy(label_name, line, length);
	label_name[length] = '\0';
	return label_name;
}

int is_word_a_label(label *head, char *word)
{
	label *current = head;
	while (current != NULL)
	{
		if (strcmp(current->name, word) == 0)
		{
			return 1; /* Word found*/
		}
		current = current->next;
	}
	return 0; /* Word not found*/
}

int check_data_types(data **data_head, char *sub_line, int flag, int DC, char *word,int line_count)
{
	char data[MAX_LINE_LENGTH];
	int index=0;
	int length;
	char binaryStr[MAX_OP_BIN_LENGTH];

	sub_line = continue_on_blanks(sub_line);

	if (flag)
	{
		length = continue_till_blanks(sub_line);
		sub_line += length;
		sub_line = continue_on_blanks(sub_line);
	}

	while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0' && *sub_line != ',')
	{
		data[index] = *sub_line;
		index++;
		sub_line++;
	}

	data[index] = '\0';

	if (strcmp(word, ".data") == 0)
	{
		printf("Data:111111111111\n");
		
		string_to_binary(data, binaryStr);
		printf("Data:111111111111\n");

		DC++;
		insert_to_data_table(data_head, binaryStr, DC);
		printf("Data:111111111111\n");
		printf("sub line: %s\n", sub_line);

		while (*sub_line != '\n' && *sub_line != '\0')
		{
			printf("sub line:%ss\n", sub_line);

			sub_line = continue_on_blanks(sub_line);

			if (*sub_line == ',')
			{
				sub_line++;
				sub_line = continue_on_blanks(sub_line);
				index = 0;
				memset(data, 0, MAX_LINE_LENGTH);

				while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0' && *sub_line != ',')
				{
					data[index] = *sub_line;
					index++;
					sub_line++;
				}

				data[index] = '\0';
				string_to_binary(data, binaryStr);
				DC++;
				insert_to_data_table(data_head, binaryStr, DC);
			}
		}
	}
	else
	{
		if(data[0]!='"'||data[index-1]!='"')
		{
			print_errors(line_count,MISSING_QUOTATION);
		}
		strcpy(binaryStr, char_to_ascii(data));
		DC++;
		insert_to_data_table(data_head, binaryStr, DC);
	}

	/*free(binaryStr);*/
	return DC;
}

void update_label_table(label *head,int IC)
{
	label* current=head;
	while(current!=NULL)
	{
		if(strcmp(current->before, "data") == 0)
		{
			current->position+=IC;
			
		}
		current=current->next;
	}
}

char *my_strdup(char *s)
{
	char *copy = (char *)malloc(strlen(s) + 1);
	if (copy == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(1);
	}
	strcpy(copy, s);
	return copy;
}





