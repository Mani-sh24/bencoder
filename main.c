#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int parse_int(char *str, char *arr, int start);
int parse_bytes(char *str, char *res_buff, int start);
int parse_list(char *str, char *resbuf, int start);
int main() {
  char *str = "l1:ali42el1:me5:helloe1:b1:ce";
  char res[1024] = {0};
  int offset = 0;

  int start = 0;
  int len = strlen(str);
  while (offset < len) {
    if (str[offset] == 'i') {
      int parsed_len = parse_int(&str[offset], res, start);
      start = strlen(res);
      offset += parsed_len;

    } else if (isdigit(str[offset])) {
      int parsed_len = parse_bytes(&str[offset], res, start);
      start = strlen(res);
      offset += parsed_len;
    } else if (str[offset] == 'l') {
      int parsed_len = parse_list(&str[offset], res, start);
      start = strlen(res);
      offset += parsed_len;
    } else {
      break;
    }
  }
  printf("string:%s\noffset=%d\noriginal string length=%d\nstr in res "
         "array=%d\nstart=%d\n",
         res, offset, strlen(str), strlen(res), start);

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
        printf("\nError at col:%d '%c' not an integer corrupted string!\n", i,
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

int parse_bytes(char *str, char *res_buff, int start) {
  struct ParseResult res = get_len(str);
  if (res.message_start == NULL) {
    fprintf(stderr, "Error: Invalid format\n");
    return -1;
  }

  char *new_str = res.message_start + 1;
  int prefix_lenght = res.message_start - str + 1;
  // printf("new %s\n" , new_str);
  int i = 0;
  int j = start;
  while (i < res.length) {
    res_buff[j++] = new_str[i];
    i++;
  }
  res_buff[j] = '\0';
  // printf("\n");
  int total_len = prefix_lenght + res.length;
  return total_len;
}

int parse_list(char *str, char *resbuf, int start) {
  int i = 1;
  while (i < strlen(str)) // do str-start to get sliced remaining str lenght
  {
    if (str[i] == 'e') {
      i++;
      break;
    } else if (str[i] == 'i') {
      int parsed_len = parse_int(&str[i], resbuf, start);
      i += parsed_len;
      if (parsed_len <= 0)
        return -1;
      start = strlen(resbuf);
    } else if (isdigit(str[i])) {
      int parsed_len = parse_bytes(&str[i], resbuf, start);
      i += parsed_len;
      if (parsed_len <= 0)
        return -1;
      start = strlen(resbuf);
    } else if (str[i] == 'l') {
      int parsed_len = parse_list(&str[i], resbuf, start);
      i += parsed_len;
      if (parsed_len <= 0)
        return -1;
      start = strlen(resbuf);
    } else {
      fprintf(stderr, "Invalid format at pos%d char%c\n", i, str[i]);
    }
  }
  int consumed = i;
  return consumed; // bytes consumed
}