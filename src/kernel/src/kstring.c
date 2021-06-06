//
// Created by john on 6/4/21.
//

#include "../include/kstring.h"

void *memcpy(void *__restrict dst, const void *__restrict src, size_t size) {

}
size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}