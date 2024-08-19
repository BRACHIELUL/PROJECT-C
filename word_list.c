
#include "word_list.h"

instdecode *create_instdecode(instdecode* new_instdecode, int opcode, int dest, int sorc)
{

	new_instdecode->opcode =opcode;
	new_instdecode->dest = bit_mask(dest);
	new_instdecode->sorc = bit_mask(sorc);
	new_instdecode->are =ARE;


	return new_instdecode;
}

int bit_mask(int opcode)
{
	int num = 1;
	int index = 1;
	if (opcode == 0)
		return 0;
	while (index < opcode)
	{
		num <<= 1;
		index++;
	}
	return num;
}
void create_operand_code(opCode *info, int sorc, int dest)
{
	info->are = ARE;
	info->dest = dest;
	info->sorc = sorc;
	info->num = 0;

}

void create_simple_code(simple *info, int data)
{
	info->are = ARE;
	info->data = data;

}

word *create_word(instdecode *info, int IC)
{

	word *new_word = (word *)malloc(sizeof(word));
	if (new_word == NULL)
	{
		perror("error alocating memory for word"); /*not sure how to do this error messege*/
		exit(1);
	}
	new_word->info.inst_info = info;
	new_word->IC = IC;
	new_word->next = NULL; /* Set the next pointer to NUL*/

	return new_word;
}
void insert_to_opcode_word_table(word **head, int opecode, int dest, int sorc,int IC)
{
	instdecode *info = (instdecode *)malloc(sizeof(instdecode));
	word *new_word;

	info = create_instdecode(info, opecode, dest, sorc);

	new_word = create_word(info, IC);
	new_word->is_instdecode = 1;
	new_word->data = opecode;
	if (new_word == NULL)
	{
		return;
	}

	if (*head == NULL)
	{
		*head = new_word;
	}
	else
	{

		word *current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_word;
	}
}

void insert_to_address_word_table(word **head, int sorc, int dest, int IC, addressingMode type)
{
	int data1 = dest == 0 ? sorc : dest;
	int is = 0;
	char * info = (char*)malloc(sizeof(char) * 15);
	if (type == INDIRECT_REGISTER_ADDRESSING || type == DIRECT_REGISTER_ADDRESSING)
	{
		create_operand_code(info, sorc, dest);

	}
	else
	{
		create_simple_code(info, data1);
	is = 2;
	}
	word *new_word = create_word(info, IC);
		new_word->is_instdecode = is;
		new_word->data = data1;


	if (new_word == NULL)
	{
		return;
	}

	if (*head == NULL)
	{
		*head = new_word;
	}
	else
	{
		word *current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_word;
	}
}

void print_word_list(word *head)
{

	word *current = head;

	while (current != NULL)
	{
		printf("-------------------------------------------------------\n");
		if (current->is_instdecode == 1)
		{
			printf("optcode!!!!!!!!! IC: %d, info: %d data %d\n", current->IC, current->info, current->data);
			printf("optcode:");
			printf("(opt %d)\n", current->info.inst_info->opcode);
			printf("bin: %d,%d,%d,%d:\n", int_to_binary(current->info.inst_info->opcode), int_to_binary(current->info.inst_info->sorc), int_to_binary(current->info.inst_info->dest), int_to_binary(current->info.inst_info->are));
		}
		else if (current->is_instdecode == 0)
		{
			printf(" operad!!!!!! IC: %d, info: %d, data %d\n", current->IC, current->info, current->data);
			printf("operad:\n");
			printf("bin: %d,%d,%d,%d:\n", int_to_binary(current->info.other_info->num), int_to_binary(current->info.other_info->sorc), int_to_binary(current->info.other_info->dest), int_to_binary(current->info.other_info->are));
		}
		else
		{
			printf("data!!!!!!! IC: %d, info: %d data %d \n", current->IC,current->info.simple_info->data, current->data);
            printf("data:\n");
            printf("bin: %d,%d:\n", int_to_binary(current->info.simple_info->data),int_to_binary( current->info.simple_info->are));
		}

		current = current->next;
	}
}

void free_word_list(word *head)
{
	word *current = head;
	while (current != NULL)
	{
		word *temp = current;
		current = current->next;
		free(temp);
	}
}

