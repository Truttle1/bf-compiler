#include "stdio.h"

//Very basic brainfuck compiler written in C, for reference
int main(int argc, char* argv[]) {
    int loop_stk[4096];
    int loop_stk_ptr = 0;
    int loop_count = 0;

    if(argc != 3) {
        printf("Usage: bf [input (bf)] [output (asm)]\n");
        return -1;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    fprintf(output,"section .bss\n");
    fprintf(output,"data resb 4096\n");

    fprintf(output,"section .text\n");
    fprintf(output,"global _start\n");

    fprintf(output,"_start:\n");

    // Zero the data
    fprintf(output,"mov r8, 0\n");
    fprintf(output,"mov rdi, data\n");
    fprintf(output,"mov rcx, 4096\n");
    fprintf(output,"zero_loop:\n");
    fprintf(output,"mov byte [rdi], 0\n");
    fprintf(output,"inc rdi\n");
    fprintf(output,"loop zero_loop\n");
    fprintf(output,"mov r8, 0\n");


    // Stuff

    char c;
    while ((c = fgetc(input)) != EOF) {
        switch(c){
            case '>':
                fprintf(output, "add r8, 1\n");
                fprintf(output, "and r8, 0xFFF\n");
                break;

            case '<':
                fprintf(output, "sub r8, 1\n");
                fprintf(output, "and r8, 0xFFF\n");
                break;

            case '+':
                fprintf(output, "add byte [data + r8], 1\n");
                fprintf(output, "and byte [data + r8], 0xFF\n");
                break;

            case '-':
                fprintf(output, "sub byte [data + r8], 1\n");
                fprintf(output, "and byte [data + r8], 0xFF\n");
                break;

            case '.':
                fprintf(output, "call print_char\n");
                break;

            case ',':
                fprintf(output, "call read_char\n");
                break;

            case '[':
                fprintf(output, "start_%d:\n", loop_count);
                loop_stk[loop_stk_ptr] = loop_count;
                loop_stk_ptr += 1;
                fprintf(output, "cmp byte [data + r8], 0\n");
                fprintf(output, "jz end_%d\n", loop_count);
                loop_count++;
                break;

            case ']':
                fprintf(output, "jmp start_%d\n", loop_stk[loop_stk_ptr - 1]);
                fprintf(output, "end_%d:\n", loop_stk[loop_stk_ptr - 1]);
                loop_stk_ptr -= 1;
                break;
        }
    }

    fprintf(output,"mov rax, 60\n");
    fprintf(output,"xor rdi, rdi\n");
    fprintf(output,"syscall\n");



    // Print character
    fprintf(output,"print_char:\n");
    fprintf(output,"mov rax, 1  ; write\n");
    fprintf(output,"mov rdi, 1  ; stdout\n");
    fprintf(output,"lea rsi, [data + r8]\n");
    fprintf(output,"mov rdx, 1\n");
    fprintf(output,"syscall\n");
    fprintf(output,"ret\n");

    // Read character
    fprintf(output,"read_char:\n");
    fprintf(output,"mov rax, 0  ; read\n");
    fprintf(output,"mov rdi, 0  ; stdin\n");
    fprintf(output,"lea rsi, [data + r8]\n");
    fprintf(output,"mov rdx, 1\n");
    fprintf(output,"syscall\n");
    fprintf(output,"ret\n");
    return 0;
}