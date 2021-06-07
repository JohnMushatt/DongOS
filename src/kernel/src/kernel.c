#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "../include/kterminal.h"
#include "../include/kernel.h"
#include "../include/kstdio.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 

 

 

 


 
void kernel_main(void) {
    /* Initialize terminal interface */
    kterminal_initialize();
 
    /* Newline support is left as an exercise. */

    kterminal_setcolor(VGA_COLOR_RED);
    kterminal_writestring("kernel terminal initialized");
    kterminal_setcolor(VGA_COLOR_WHITE);

    kprintf("\n%s\n","Testing kprintf");

}