#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
int parse_int(char *str);


int main()
{
    char *str = "i42e";
    return 0;
}

int parse_int(char *str)
{
    int str_len = strlen(str);
    for (size_t i = 1; i < str_len; i++)
    {
        if (str[i] == 'e')
        {
            break;
        }
        else
        {
            if (isdigit(str[i]) || str[i] == '-')
            {
                printf("%c", str[i]);
            }
            else
            {
                printf("Error at col:%d '%c' not an integer corrupted string!",i , str[i] );
                break;
            }
        }
    }
    printf("\n");
    return 0;
}

// int parse_bytes(char *str) {
    
// }