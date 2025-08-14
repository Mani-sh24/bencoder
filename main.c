#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parse_int(char *str, char *arr, int start);
int parse_bytes(char *str);
int parse_list(char *str);
int main() {
  char *str = "i343543534534534534ei33435345345345345343ei23453453450el2:hie";
  char res[1024] = {0};
  int offset = 0;
  int i = 0;
  int start = 0;
  int len = strlen(str);
  while (i == offset) {
    if (str[i] == 'i') {
      int parsed_len = parse_int(&str[offset], res, start);
      start = strlen(res);
      offset += parsed_len;
      i = offset;
      
    } else {
      i++;
    }
  }
  // printf("string:%s\ni=%d\noffset=%d\noriginal string length=%d\nstr in res
  // array=%d\nstart=%d\n", res , i, offset, strlen(str), strlen(res) , start);

  printf("next elem is %c\n", str[offset]);
  return 0;
}

int parse_int(char *str, char *arr, int start) {
  int str_len = strlen(str);
  int j = start;
  size_t i;
  for (i = 1; i < str_len; i++) {
    if (str[i] == 'e') {
      break;
    } else {
      if (isdigit(str[i]) || str[i] == '-') {
        arr[j++] = str[i];
      } else {
        printf("Error at col:%d '%c' not an integer corrupted string!", i,
               str[i]);
        break;
      }
    }
  }
  arr[j] = '\0';
  return i + 1;
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
  int i = 0;
  while (i < res.length) {
    printf("%c", new_str[i]);
    i++;
  }
}

int parse_list(char *str) {
  
}