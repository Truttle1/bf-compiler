#include "stdio.h"

//Strip non-bf commands from input
int main(int argc, char* argv[]) {
    FILE* input = fopen("input.bf", "r");
    FILE* output = fopen("output.bf", "w");

    char c;
    while ((c = fgetc(input)) != EOF) {
        switch(c){
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                fprintf(output, "%c", c);
                break;
        }
    }

    return 0;
}