//
// Created by john on 6/4/21.
//

#include "../include/kstring.h"


size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}