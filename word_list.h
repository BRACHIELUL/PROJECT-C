#ifndef WORD_LIST_H
#define WORD_LIST_H

#define MAX_LINE_LENGTH 80
#define MAX_OP_BIN_LENGTH 15
#define ARE 2


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"
#include "general_funcs.h"

typedef struct instdecode
{
	int are : 3;
	int dest : 4;
	int sorc : 4;
	int opcode : 5;
} instdecode;

typedef struct opCode
{
	unsigned are : 3;
	unsigned dest : 3;
	unsigned sorc : 3;
	unsigned num : 6;
} opCode;

typedef struct simple
{
	int are : 3;
	int data : 12;
} simple;

typedef union info
{
	instdecode *inst_info;
	opCode *other_info;
	simple *simple_info;
} info;

typedef struct word
{

	info info;
	int is_instdecode;
	int IC;
	int data;
	struct word *next;
} word;

typedef enum addressingMode
{
	IMMEDIATE_ADDRESSING = 0,
	DIRECT_ADDRESSING = 1,
	INDIRECT_REGISTER_ADDRESSING = 2,
	DIRECT_REGISTER_ADDRESSING = 3
} addressingMode;



instdecode *create_instdecode(instdecode *new_instdecode, int opcode, int dest, int sorc);
void create_operand_code(opCode *info, int sorc, int dest);
void insert_to_opcode_word_table(word **head, int opcode, int dest, int sorc, int IC);

void insert_to_address_word_table(word **head, int sorc, int dest, int IC, addressingMode type);
void print_word_list(word *head);
void free_word_list(word *head);
word *create_word(instdecode *info, int IC);
void create_simple_code(simple *info, int data);
int bit_mask(int opcode);
#endif

