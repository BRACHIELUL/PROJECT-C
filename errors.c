#include "errors.h"


void print_errors(int line_num, error_type error)
{
	char* error_messege[]={"invalid macro name","extra chars on macro call line","extra chars after endmac", "missing quotation markes","already existing label" , "opcode not valid", "invalid register" };

	FILE *error_file = fopen(ERROR_LOG_FILE, "a"); /*Open in append mode*/

        if (error_file == NULL) { /*If the file cannot be opened*/
        	printf("Failed to open or create error log file.\n");
        	exit(1);
    	}

   	fprintf(error_file,"error: %s at line: %d\n", error_messege[error],line_num);
   
   	 fclose(error_file);

	
}
