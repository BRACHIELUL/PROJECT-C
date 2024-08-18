
#ifndef ERRORS_H
#define ERRORS_H
#define MAX_LINE_LENGTH 80
#define ERROR_LOG_FILE "error_log.txt"

typedef enum{
      INVALID_MACRO_NAME,
      EXTERA_CHARS_ON_MACRO_CALL_LINE,
      EXTERA_CHARS_AFTER_ENDMACR,
      ALREADY_EXISTING_LABEL,
      MISSING_QUOTATION,
      INVALID_OPCODE,
      INVALID_REGISTER
} error_type;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_errors(int line_num,error_type error);


#endif


