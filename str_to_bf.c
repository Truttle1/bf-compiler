#include "stdio.h"
#include "string.h"

//Generate very inefficient in-place text
int main(int argc, char* argv[]) {
    char result[99999] = "";
    unsigned int current = 0;
    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    FILE* input = fopen(argv[1], "r");

    char c;
    while ((c = fgetc(input)) != EOF) {
        while(current > c) {
            char temp[99999];
            snprintf(temp, sizeof(temp), "%s-", result);
            strncpy(result, temp, sizeof(result));
            current--;
        }
        while(current < c) {
            char temp[99999];
            snprintf(temp, sizeof(temp), "%s+", result);
            strncpy(result, temp, sizeof(result));
            current++;
        }
        char temp[99999];
        snprintf(temp, sizeof(temp), "%s.", result);
        strncpy(result, temp, sizeof(result));
    }

    printf("%s\n", result);
}