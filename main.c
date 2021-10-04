#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "galoid.h"

// Matrix ops
char **CreateMatrix(char *input);
char  *RotateRight(char *word);


// Difusion funcs
char **ShiftRows(char **matrix);
char **MixColumns(char **matrix);

// Confusion funcs
// (?)



int main(int argc, char *argv[])
{
    char *input = "abcdabcdabcdabcd"; //128 bits
    char **matriz = CreateMatrix(input); 

    printf("-> %s = %d\n", input, strlen(input));
    for(int i=0;i<4;i++){ printf("- %s\n", matriz[i] ); }

    //rotate
    printf("---\n");

    matriz = ShiftRows( matriz );
    for(int i=0;i<4;i++){ printf("- %s\n", matriz[i] ); }



    return 0;
}

char **CreateMatrix(char *input){
    /* Parseamos 1 string de 32 bytes en 4 filas de 8 bytes
       ( Osea una matriz 4x4 donde cada elemento son 2 chars) */
    char **matriz = malloc(4 * sizeof(char *)); 
    for (int i=0;i<4;i++) {
        matriz[i] = malloc(4* sizeof(char));    
        memcpy( matriz[i], &input[i*4],4 );
    }

    return matriz;
}

char *RotateRight(char *word){
    /* Coloca el utimo char al inicio de la palabra */
    char *result = malloc( 8*sizeof(char) );
    result[0] = word[7];

    return strncat(result, word, 7);
}

char **ShiftRows(char **matriz){
/* 
Rota las de la siguiente manera
  fila 1 -> 0 Shifts
  fila 2 -> 3 Shifts
  fila 3 -> 2 Shifts
  fila 4 -> 1 Shifts 
*/
    for(int i=1;i<4;i++){
        for(int j=0;j<4-i;j++){
            matriz[i] = RotateRight( matriz[i] );
        } 
    }

    return matriz;
}

char **MixColumns(char **matrix){
   char mult[4] = "2311"; 

   for(;mult[3] == 2; mult = RotateRight(mult)){

   }
}




