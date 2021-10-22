#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b + (c&d),  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b + (c|d),  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 10
// Funciones =======================================================================
// --> input sht
void  PrintHelp ();
char *AddPadding(char const *msg, size_t msg_len);

// --> hash sht
uint32_t *chacha_init  (char    *msg);
void      chacha_update(uint32_t out[16], uint32_t const in[16]);
void      chacha_hash  (char    *msg);

// --> aux sht
static uint32_t pack4   (const uint8_t   *a);
static uint8_t  *unpack4(const uint32_t src);

int main(int argc, char *argv[]){
  // Revisa si el input es un archivo (flag -f) o si es un input por
  // stdin y ejecuta la funcion correspondiente
  if( argc == 1 || (argc ==2 && strcmp(argv[1],"-f") == 0) ){
    PrintHelp();
    return 1;
  }
    
  if( argc == 3 && strcmp(argv[1],"-f") == 0 ){
    // hash file
    FILE *fp;
    char line[255];

    fp = fopen(argv[2], "r");

    if (fp == NULL){ exit(EXIT_FAILURE); }
    while( fgets( line, 255, fp) ){
      if( strlen( line ) != 1 )
	line[ strlen(line)-1 ] = '\0';
      else
	line[ strlen(line)-1 ] = ' ';
	
      //      printf("%s\n", line );
      chacha_hash( line );

    }
    //   while( fgets(ch,100,fp) ){
    //      ch[strlen(ch)-1] = '\0';
    //      chacha_hash( ch );
    //    }

    fclose(fp);
  }else{
    for( int i =1;i<argc;i++ )
      chacha_hash( argv[i] );
  }

 

  return 0;
}

// ===============================================================================
void PrintHelp(){
  // imprime como se usa el programa
  printf("Modo de uso chachash.c:\n\n   [NO FLAGS] => varios strings a hashear ( separados por ' ')\n   -f [FILE] hashear valores de un archivo\n\n"); 
}

char *AddPadding(char const *msg, size_t msg_len)
{
  //Si el mensaje tiene un largo menor a 512 entonces le agregamos padding,
  //compuesto por el mensaje cifrado en cesar con el largo del mensaje.


  
    size_t faltan = 64-msg_len;
    char *pad = malloc( faltan*sizeof(char) );
    char *res = malloc( (65)*sizeof(char) );

    for(;strlen(pad)!=faltan;)
        strncat(pad,msg, (faltan-strlen(pad)<msg_len)?faltan-strlen(pad):msg_len);

    for(int i=0;i<faltan;i++)
      pad[i] ^= msg_len;
      

    strcpy(res, msg);
    return strcat(res, pad);
}

uint32_t *chacha_init  (char    *msg)
{
  // Recibe un mensaje ya paddeado y genera una matriz de uint32_t 4x4 llamada state 
  // TODO - tmb se podria agregar un salt 
  uint32_t *state = malloc(16*sizeof(uint32_t));
  const uint8_t *constant = (uint8_t *)"expand 32-byte k";
  const uint8_t *mensaje  = (uint8_t *)msg;

  for(int i=0;i<4;++i) // constant
    state[i] = pack4(constant+(i*4));
  for(int i=0;i<8;++i) // key
    state[i+4] = pack4(mensaje+(i*4));

  //counter parte en 0 (por ahora no cambia nunca)
  state[12] = 0; 
  // nonce 
  
  return state;

}

void chacha_update(uint32_t out[16], uint32_t const in[16]){
  // Se hacen las operaciones matriciales, divididas en 10 rondas dobles ( 1 parte en columnas
  //y la otra en diagonales ) para mezclar la info.
  
  int i;
  uint32_t x[16];

  for (i = 0; i < 16; ++i)	
    x[i] = in[i];
  // 10 loops × 2 rounds/loop = 20 rounds
  for (i = 0; i < ROUNDS; i += 2) {
    // Odd round
    QR(x[0], x[4], x[ 8], x[12]); // column 0
    QR(x[1], x[5], x[ 9], x[13]); // column 1
    QR(x[2], x[6], x[10], x[14]); // column 2
    QR(x[3], x[7], x[11], x[15]); // column 3
    // Even round
    QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
    QR(x[1], x[6], x[11], x[12]); // diagonal 2
    QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
    QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
  }
  for (i = 0; i < 16; ++i)
    out[i] = x[i] + in[i];
}

void      chacha_hash  (char    *msg){
   // hash words
    char *curr = malloc(65*sizeof(char));

    uint32_t  input[16];//512
    uint32_t *state;
    
    uint8_t cover = 0;
    uint8_t *tmp;
  
    while( strlen(msg) - cover > 64 ){
      strncpy(curr, msg+cover, 64);
      if(cover == 0)
	state = chacha_init(curr);

      for(int i=0;i<16;++i){
	if(cover == 0)
	  input[i] = pack4(curr+(i*4));
	else
	  input[i] ^= pack4(curr+(i*4));
      }
      chacha_update(input,state);
      cover += 64;
    }
    
    curr = AddPadding(msg+cover, strlen(msg+cover));
    state = chacha_init(curr);
      
    for(int i=0;i<16;++i)
      input[i] ^= pack4(curr+(i*4));
    
    chacha_update(input,state);

    printf("%s - ",msg);
    tmp = malloc(4*sizeof(uint8_t));
    for(int i=0;i<8;i++){
      tmp = unpack4(input[i]);
      for(int j=0;j<4;j++)
	printf("%02x",tmp[j]);
    }
    printf("\n");
}

uint32_t pack4(const uint8_t *a){
    uint32_t res = 0;
    res |= (uint32_t)a[0];
    res |= (uint32_t)a[1] << 8 ;
    res |= (uint32_t)a[2] << 16;
    res |= (uint32_t)a[3] << 24;

    return res;
}

uint8_t *unpack4(const uint32_t src){
    uint8_t *dst = malloc(4*sizeof(uint8_t)); 
    dst[0] = (src >> 0 * 8) & 0xff;
    dst[1] = (src >> 1 * 8) & 0xff;
    dst[2] = (src >> 2 * 8) & 0xff;
    dst[3] = (src >> 3 * 8) & 0xff;

    return dst;
}

