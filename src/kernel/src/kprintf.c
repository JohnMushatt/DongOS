//
// Created by john on 6/6/21.
//
#include <stdbool.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include "../include/kstdio.h"
#include "../include/kstring.h"
/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param char [description]
 * @param len [description]
 * 
 * @return [description]
 */
static bool print(const char *data, size_t len) {
	const unsigned char *bytes = (const unsigned char *) data;
	for(size_t index = 0; index < len; index++) {
		if(kputchar(bytes[index]) == EOF) {
			return false;
		}
	}
	return true;
}
/**
 * @brief Kernel printf variadic function
 * @details Kernel variant of the C standard library function printf that accepts 
 * variable # of format options and arguments
 * 
 * @param restrict format Format string
 * @param ... Variadic arguments?
 * @return Number of bytes successfully written to terminal
 */
int kprintf(const char * restrict format, ...) {
    va_list	params;
    va_start(params,format);

    int BytesWritten = 0;

    while(*format != '\0') {
    	size_t MaxRemaining = INT_MAX - BytesWritten;
        if(format[0] != '%' || format[1] == '%') {
            if (format[0] == '%') {
                format++;
            }
            size_t amount = 1;

            while(format[amount] && format[amount] != '%') {
                amount++;
            }
            if(MaxRemaining < amount) {
                return -1;
            }

            if(!print(format,amount)) {
                return -1;
            }
            format += amount;
            BytesWritten += amount;
        }
        const char *format_begun_at  = format++;

        if(*format == 'c') {
            format++;

            char c = (char) va_arg(params, int /* char promotes to int */);
            //Overflow
            if(!MaxRemaining) {
                return -1;
            }
            if(!print(&c, sizeof(c))) {
                return -1;
            }
            BytesWritten++;

        }
        else if(*format == 's') {
            format++;
            const char *str = va_arg(params, const char *);

            size_t len = strlen(str);
            //Overflow
            if(MaxRemaining < len) {
                return -1;
            }

            if(!print(str,len)) {
                return -1;
            }
            BytesWritten++;
        }
        else {
            format = format_begun_at;
            size_t len = strlen(format);

            //Overflow
            if(MaxRemaining < len) {
                return -1;
            }

            if(!print(format,len)) {
                return -1;
            }

            BytesWritten += len;
            format += len;
        }
    }
    va_end(params);
    return BytesWritten;
}