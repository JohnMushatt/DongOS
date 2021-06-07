#ifndef DONGOS_KSTDIO_H
#define DONGOS_KSTDIO_H


//#include <sys/cdefs.h>

#define EOF (-1)
#ifdef _cplusplus
extern "C" {
#endif


/**
 * @brief Kernel printf variadic function
 * @details Kernel variant of the C standard library function printf that accepts
 * variable # of format options and arguments
 *
 * @param restrict format Format string
 * @param ... Variadic arguments?
 * @return Number of bytes successfully written to terminal
 */
int kprintf(const char * restrict format, ...);
int kputchar(int);
int kputs(const char*);
#ifdef _cplusplus
}
#endif
#endif //DONGOS_KSTDIO_H