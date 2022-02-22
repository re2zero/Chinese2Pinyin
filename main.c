#include <stdio.h>
#include <stdlib.h>
#include "sds.h"
#include "functions.h"
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <limits.h>

int main(int argc, char** argv)
{
    if(argc != 2) {
        fprintf(stderr, "Usage: ./Chinese2Pinyin words\n");
        exit(1);
    }

    sds words = sdsnew(argv[1]);
    int len = sdslen(words);
    if(!is_text_utf8(words, len)) {
        printf("%s\n", words);
        exit(1);
    }
    struct timeval s, e;
    FILE* fp;
    char *dict = calloc(DICT_MAX_LEN, sizeof(char));
    if(NULL == (fp = fopen("PinyinData.txt", "r"))) {
        fprintf(stderr, "open file error\n");
        exit(1);
    }
    fread(dict, DICT_MAX_LEN, 1, fp);
    sds out = sdsempty();

    int max_len = 1531;//NAME_MAX * MAX_PINYIN_LEN + 1;
    char pinyin_out[max_len];// = calloc(255 * MAX_PINYIN_LEN + 1, sizeof(char));
    char words_in[1024];
    memset(pinyin_out, 0, max_len);
    memset(words_in, 0, 1024);
    strncpy(words_in, argv[1], len);
    printf("input words %s \n", words_in);

    gettimeofday(&s, 0);
    // utf8_to_pinyin(words, out, fp);
    chars_to_pinyin(words_in, pinyin_out, dict);
    // get_to_pinyin(words, out, dict);
    gettimeofday(&e, 0);

    printf("pinyin_out=%s!, out=%s\n", pinyin_out, out);
    uint64_t dur = (e.tv_usec + e.tv_sec * 1000000) - (s.tv_usec + s.tv_sec * 1000000);
    // printf("%s\n", out);
    printf("  take time %'lu us\n", dur);
    sdsfree(words);
    sdsfree(out);
    fclose(fp);
    return 0;
}

