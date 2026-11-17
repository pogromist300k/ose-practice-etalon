#include "string.h"

size_t strlen(const char* str) {
  size_t i = 0;
  while (str[i++]);
  return i - 1;
}

char* strrev(char* str) {
  if (str[0] == '\0')
    return str;
  size_t left = 0;
  size_t right = strlen(str) - 1;
  while (left < right) {
    char tmp = str[left];
    str[left++] = str[right];
    str[right--] = tmp;
  }
  return str;
}

char* strcpy(char* dst, const char* src) {
  char* ret = dst;
  while (*(dst++) = *(src++));
  return ret;
}

char* uint_to_str(unsigned num, char* buff, byte base) {
  size_t i = 0;
  do {
    byte offset = num % base;
    buff[i++] = (offset < 10) ? '0' + offset : 'A' + offset - 10;
    num /= base;
  } while(num);
  buff[i] = '\0';
  return strrev(buff);
}
