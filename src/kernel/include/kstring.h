//
// Created by john on 6/4/21.
//

#ifndef DONGOS_KSTRING_H
#define DONGOS_KSTRING_H


#include <stddef.h>


#ifdef _cplusplus
extern "C" {
#endif

int memcmp(const void *, const void *, size_t);
void *memcpy(void * __restrict, const void * __restrict, size_t);
void memmove(void *, const void*, size_t);
void memset(void *, int, size_t);
size_t strlen(const char* str);




#ifdef _cplusplus
}
#endif
#endif //DONGOS_KSTRING_H
