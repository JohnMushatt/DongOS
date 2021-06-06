#include "../include/kterminal.h"
#include <stdint.h>
#include "../include/kstring.h"
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;



void kterminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xC03FF000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}






void kterminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {

    unsigned char uc = c;
    /**
     * This solution feels janky af, TODO check if the terminal is supposed to write the newline character
     * (I don't think its supposed to tho?)
     */
    if (c == '\n') {
        terminal_column=0;
        terminal_row++;
    }
    else {
        terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);

        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {

                for(int32_t LineIndex = 1; LineIndex < VGA_HEIGHT -1; LineIndex) {
                    kterminal_scroll(LineIndex);
                }
                kterminal_delete_last_line();
                terminal_row = VGA_HEIGHT-1;
            }
        }
    }

}
void kterminal_delete_last_line() {
    int32_t x;
    int32_t *ptr;

    for(x = 0; x < VGA_WIDTH *2; x++) {
        //Get the VGA buffer position
        const int32_t VGABufferIndex = (VGA_WIDTH*2) * (VGA_HEIGHT - 1) + x;
        //Set ptr to base buffer address + index;
        ptr=  0xB8000 + VGABufferIndex;
        //Zero the value
        *ptr = 0;
    }
}
void kterminal_scroll(int LineNum) {
    int *LoopIndex;
    char c;

    for (LoopIndex = LineNum * (VGA_WIDTH * 2) + 0xB8000;
     LoopIndex < VGA_WIDTH *2; LoopIndex++) {
        
        c = *LoopIndex;
        *(LoopIndex - (VGA_WIDTH *2)) = c;
    }
}
void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void kterminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}