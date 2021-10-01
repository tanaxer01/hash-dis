#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Matrix ops
char* RotateRight(char *word);

// Difusion funcs

// Confusion funcs
// (?)

// Main functions

int main(int argc, char *argv[])
{
    char *input = "aaaaaaaabbbbbbbbccccccccdddddddd"; //256 bits
//                    1-------2-------3-------4-------
    char matrix[4][9];
    for(int i=0;i<4;i++){ 
        memcpy(matrix[i], &input[i*8], 8); 
        matrix[i][8] = '\0';
    }
    printf("-> %s = %d\n", input, strlen(input));
    for(int i=0;i<4;i++){ printf("- %s\n", matrix[i] ); }

    return 0;
}

char* RotateRight(char *word){
    char result[32] = { word[31] };
    return strncat(result, word, 31);
}

