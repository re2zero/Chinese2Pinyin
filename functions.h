#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "sds.h"

#define MAX_PINYIN_WORD 20902
#define MAX_PINYIN_LEN 6

#define DICT_MAX_LEN (MAX_PINYIN_WORD * MAX_PINYIN_LEN + 1)

void chars_to_pinyin(char *in, char *out, char *dict);
void get_to_pinyin(sds in, sds out, char *dict);
void utf8_to_pinyin(sds in, sds out, FILE *fp);
int is_text_utf8(const char* str, long length);

#endif // FUNCTIONS_H_INCLUDED
