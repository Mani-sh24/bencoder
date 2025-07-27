#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parse_int(char *str);
int parse_bytes(char *str);
int main() {
  char *str = "i42e";
  char *byte_string = "44:hello";
  return 0;
}

int parse_int(char *str) {
  int str_len = strlen(str);
  for (size_t i = 1; i < str_len; i++) {
    if (str[i] == 'e') {
      break;
    } else {
      if (isdigit(str[i]) || str[i] == '-') {
        printf("%c", str[i]);
      } else {
        printf("Error at col:%d '%c' not an integer corrupted string!", i,
               str[i]);
        break;
      }
    }
  }
  printf("\n");
  return 0;
}

int parse_bytes(char *str) {
  char *pos = strchr(str, ':');
  if (pos == NULL) {
    fprintf(stderr, "Error: Invalid format\n");
    return -1;
  }
  size_t temp_len = pos - str;
  char temp_str[pos - str + 1];
  strncpy(temp_str, str, temp_len);
  temp_str[temp_len] = '\0';
  int byte_len = atoi(temp_str);
  if (byte_len == 0) {
    fprintf(stderr, "Error: Invalid format\n");
    return -1;
  }

  char *new_str = pos + 1;
  for (size_t i = 0; i < byte_len; i++) {
    printf("%c", new_str[i]);
  }
  return 0;
}