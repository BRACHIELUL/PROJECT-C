#ifndef INSTRUCTION_CODE_H
#define INSTRUCTION_CODE_H

#define MAX_LINE_LENGTH 80
#define MAX_OP_LENGTH 5
#define NUM_OF_OPCODES 17
#define NUM_OF_REISTERS 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "data_list.h"
#include "general_funcs.h"
#include "word_list.h"
#include "errors.h"



int instruction_code(word **head, char *optCode_word, char *sub_line, int IC, int flag, int line_count);
int check_operand_type(char *operand, int line_count);
#endif

