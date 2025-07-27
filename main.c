#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_int(char *str);
int parse_bytes(char *str);
int main() {
  char *str = "i42e";
  char *byte_string = "5:hello";
  parse_bytes(byte_string);
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
struct ParseResult {
  int length;
  char *message_start;
};

struct ParseResult get_len(char *str) {
  struct ParseResult result = {0, NULL};
  char *pos = strchr(str, ':');
  if (pos == NULL) {
    fprintf(stderr, "Error: Invalid format\n");
    return result;
  }
  size_t temp_len = pos - str;
  char temp_str[pos - str + 1];
  strncpy(temp_str, str, temp_len);
  temp_str[temp_len] = '\0';
  result.length = atoi(temp_str);
  result.message_start = pos;
  return result;
}

int parse_bytes(char *str) {
  struct ParseResult res = get_len(str);

  if (res.message_start == NULL) {
    fprintf(stderr, "Error: Invalid format\n");
    return -1;
  }

  char *new_str = res.message_start + 1;
  for (size_t i = 0; i < res.length; i++) {
    printf("%c", new_str[i]);
  }
  return 0;
}