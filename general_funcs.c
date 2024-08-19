#include "general_funcs.h"

char *continue_on_blanks(char *line)
{
    while ((*line == ' ') || (*line == '\r') || (*line == '\t'))
    {
        line++;
    }
    return line;
}

int continue_till_blanks(char *line)
{
    char *chr = line;
    int counter = 0;
    while ((*chr != '\0') && (*chr != ' ') && (*chr != '\r') && (*chr != '\t'))
    {
        chr++;
        counter++;
    }
    return counter;
}

char *char_to_ascii(char *data)
{
    int i;
    int length = strlen(data);
    char buffer[4];
    char *ascii_str = (char *)calloc(length * 4 + 1, sizeof(char));
    if (!ascii_str)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("data %s\n", data);

    while (!isalpha(*data))
    {
        *data++;
    }

    printf("data 2%s\n", data);

    for (i = 0; i < length && isalpha(data[i]); i++)
    {
        sprintf(buffer, "%d ", (int)data[i]);
        strcat(ascii_str, buffer);
    }

    if (length > 0)
    {
        ascii_str[strlen(ascii_str)] = '\0';
    }

    return ascii_str;
}

int int_to_binary(int data)
{
    int binary = 0;
    int place = 1;
    while (data > 0)
    {
        int remainder = data % 2;
        binary += remainder * place;
        place *= 10;
        data /= 2;
    }
    return binary;
}

void string_to_binary(char *str, char *binary_str)
{
    /* char* binary_str = (char*)malloc(MAX_OP_BIN_LENGTH + 1);*/
    int num = atoi(str);
    int i = MAX_OP_BIN_LENGTH;
    binary_str[i + 1] = '\0';

    while (i >= 0)
    {
        binary_str[i] = (num & 1) + '0';
        num >>= 1;
        i--;
    }
     printf("binary: %s\n", binary_str);
}

/*char *char_To_Binary(char *data)
{
    int i;
    int start;
    int decimal;
    unsigned int absDecimal;
    char *binary = (char *)malloc(MAX_OP_BIN_LENGTH + 1);

    if (!binary)
    {
        return NULL;
    }

    memset(binary, '0', MAX_OP_BIN_LENGTH);
    binary[MAX_OP_BIN_LENGTH] = '\0';

    decimal = atoi(data);
    printf("decimal: %d\n", decimal);

    if (decimal == 0)
    {
        strcpy(binary, "0");
        return binary;
    }

    absDecimal = (unsigned int)decimal;
    if (decimal < 0)
    {
        absDecimal = -decimal;
    }

    for (i = MAX_OP_BIN_LENGTH - 1; i >= 0 && absDecimal > 0; i--)
    {
        binary[i] = (absDecimal & 1) ? '1' : '0';
        absDecimal >>= 1;
    }

    if (decimal < 0)
    {

        for (i = 0; i < MAX_OP_BIN_LENGTH; i++)
        {
            binary[i] = (binary[i] == '0') ? '1' : '0';
        }

        for (i = MAX_OP_BIN_LENGTH - 1; i >= 0; i--)
        {
            if (binary[i] == '0')
            {
                binary[i] = '1';
                break;
            }
            else
            {
                binary[i] = '0';
            }
        }
    }

    binary[MAX_OP_BIN_LENGTH] = '\0';

    printf("binary: %s\n", binary);
    return binary;
}
*/

