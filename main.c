#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Matrix ops
char **CreateMatrix(char *input);
char *RotateRight(char *word);


// Difusion funcs

// Confusion funcs
// (?)



int main(int argc, char *argv[])
{
    char *input = "abcdefghabcdefghabcdefghabcdefgh"; //256 bits
    char **matriz = CreateMatrix(input); 

    printf("-> %s = %d\n", input, strlen(input));
    for(int i=0;i<4;i++){ printf("- %s\n", matriz[i] ); }

    //rotate
    printf("---\n");

    for(int i=1;i<4;i++){
        for(int j=0;j<4-i;j++){
            matriz[i] = RotateRight( matriz[i] );
        } 
    }
    for(int i=0;i<4;i++){ printf("- %s\n", matriz[i] ); }



    return 0;
}

char **CreateMatrix(char *input){
    char **matriz = malloc(4 * sizeof(char *)); 
    for (int i=0;i<4;i++) {
        matriz[i] = malloc(8* sizeof(char));    
        memcpy( matriz[i], &input[i*8],8 );
    }

    return matriz;
}

char *RotateRight(char *word){
    char *result = malloc( 8*sizeof(char) );
    result[0] = word[7];
    return strncat(result, word, 7);

}

