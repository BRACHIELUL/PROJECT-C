#include "instruction_code.h"

int instruction_code(word **head, char *opcode_word, char *sub_line, int IC, int flag, int line_count)
{
	char opcodes[NUM_OF_OPCODES][MAX_OP_LENGTH] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"};
	int operandssorc[NUM_OF_OPCODES] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0};
	int operandsdest[NUM_OF_OPCODES] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char data[2][MAX_LINE_LENGTH + 1] = {{0}, {0}};
	char dest[MAX_LINE_LENGTH] = {0};
	char sorc[MAX_LINE_LENGTH] = {0};
	int typedest = 0;
	int typesorc = 0;
	int index = 0;
	int i = 0;
	int length = 0;
	int opcode = -1;
	int j = 0;
	int register_to_code = -1;
	int num_to_code = 0;
	int opcode_bin = -1;

	sub_line = continue_on_blanks(sub_line);
	if (flag)
	{
		length = continue_till_blanks(sub_line);
		sub_line += length;
		sub_line = continue_on_blanks(sub_line);
	}

	while (i <= NUM_OF_OPCODES)
	{
		if (strcmp(opcode_word, opcodes[i]) == 0)
		{
			opcode = i;
			opcode_bin = int_to_binary(opcode);
		}
		i++;
	}
	if (opcode == -1)
	{
		print_errors(line_count, INVALID_OPCODE);
		return IC;
	}
	for (j = 0; j < operandsdest[opcode] + operandssorc[opcode]; j++)
	{
		index = 0;

		while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0' && *sub_line != ',')
		{
			data[j][index] = *sub_line;
			index++;
			*sub_line++;
		}
		data[j][index] = '\0';
		sub_line = continue_on_blanks(sub_line);
		if (*sub_line == ',')
			*sub_line++;
		sub_line = continue_on_blanks(sub_line);
	}

	if (operandsdest[opcode] && operandssorc[opcode]) /*if this is a instruction that uses both operands*/
	{
		typesorc = check_operand_type(data[0], line_count);
		typedest = check_operand_type(data[1], line_count);
		insert_to_opcode_word_table(head, opcode, typedest, typesorc, IC);
		if ((typedest == INDIRECT_REGISTER_ADDRESSING || typedest == DIRECT_REGISTER_ADDRESSING) && (typesorc == INDIRECT_REGISTER_ADDRESSING || typesorc == DIRECT_REGISTER_ADDRESSING))
		{

			IC += 2;
			copy_only_digits(data[1], dest);
			copy_only_digits(data[0], sorc);
			register_to_code = atoi(dest) + atoi(sorc);
			insert_to_address_word_table(head, atoi(sorc), atoi(dest), IC, typesorc);
		}
		else
		{
			IC += 3;

			typesorc == 1 ? strcpy(sorc, "1111") : copy_only_digits(data[0], sorc);
			typedest == 1 ? strcpy(dest, "1111") : copy_only_digits(data[1], dest);
			insert_to_address_word_table(head, atoi(sorc), 0, IC, typesorc);
			insert_to_address_word_table(head, 0, atoi(dest), IC, typedest);
		}
	}
	if (operandsdest[opcode] == 0 && operandssorc[opcode]) /*if this is a instruction that uses one operand*/
	{
		typesorc = check_operand_type(data[0], line_count);

		insert_to_opcode_word_table(head, opcode, typedest, typesorc, IC);
		IC += 2;
		typesorc == 1 ? strcpy(sorc, "1111") : copy_only_digits(data[0], sorc);

		insert_to_address_word_table(head, atoi(sorc), 0, IC, typesorc);
	}
	return IC;
}

void copy_only_digits(char *src, char *dest)
{
	int i = 0, j = 0;
	while (src[i] != '\0')
	{
		while (isdigit(src[i]) == 0 && src[i] != '-')
		{

			i++;
			continue;
		}
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

int check_operand_type(char *operand, int line_count)
{

	char *registers[NUM_OF_REISTERS] = {"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
	int length = 0;
	int index = 0;
	int i = 0;
	int operandtype;
	char dest[MAX_LINE_LENGTH] = {0};

	if (operand == NULL)
	{
		return -1;
	}

	if (*operand == '*')
	{
		*operand++;
		index = 0;
		/*while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0')
		{

			dest[index] = *sub_line;
			index++;
			sub_line++;
		}
		dest[index] = '\0';*/
		while (i <= NUM_OF_REISTERS && strcmp(operand, registers[i]) != 0) /*want to check if not equal*/
		{
			i++;
		}
		if (i == NUM_OF_REISTERS + 1)
		{
			print_errors(line_count, INVALID_REGISTER);
			return NULL;
		}
		operandtype = INDIRECT_REGISTER_ADDRESSING;
	}

	else if (*operand == '#')
	{
		index = 0;
		*operand++;
		/*while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0')
		{

			dest[index] = *sub_line;
			index++;
			sub_line++;
		}
		dest[index] = '\0';*/
		operandtype = IMMEDIATE_ADDRESSING;
	}
	else
	{
		/*while (*sub_line != ' ' && *sub_line != '\t' && *sub_line != '\n' && *sub_line != '\0')
		{

			dest[index] = *sub_line;
			index++;
			sub_line++;
		}
		dest[index] = '\0';*/
		i = 0;
		while (i < NUM_OF_REISTERS && strcmp(operand, registers[i]) != 0) /*not sure if this needs to be <=*/
		{
			i++;
		}
		if (i == NUM_OF_REISTERS) /*should this  be NUM_OF_REISTERS+1??*/
		{
			operandtype = DIRECT_ADDRESSING;
		}
		else
		{
			operandtype = DIRECT_REGISTER_ADDRESSING;
		}
	}
	return operandtype;
}

