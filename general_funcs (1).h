#ifndef GENERAL_FUNCS_H
#define GENERAL_FUNCS_H

#define MAX_LINE_LENGTH 80

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errors.h"
#include "word_list.h"

char *continue_on_blanks(char *line);
int continue_till_blanks(char *line);
char *char_To_Binary(char *data);
char *char_to_ascii(char *data); /*might need more משתנים*/
int int_to_binary(int data);
void string_to_binary(char *str, char *binary_str);
#endif

