#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define LFSR(r) (r >> 1) ^ (-(r & 1) & 0x80200003)

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d, e) (				\
	a += b + e,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b + e,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 10

void  PrintHelp ();
char *AddPadding(char const *msg, size_t msg_len);

void chacha_state(uint32_t out[16], char *msg);
void chacha_hash(char *msg);
void HashABlock(uint32_t out[16], uint32_t in[16]);

static uint32_t pack4   (const uint8_t   *a);
static uint8_t  *unpack4(const uint32_t src);

int main(int argc, char *argv[])
{
  if( argc == 1){ // No provee args
    PrintHelp();
    return -1;
  }else if( strcmp(argv[1],"-f") == 0){ // file
    if(argc != 3){
      PrintHelp();
      return -1;
    }

    FILE *fp;
    char line[255];

    fp = fopen(argv[2], "r");
    if (fp == NULL){ exit(EXIT_FAILURE); }
    while( fgets( line, 255, fp) ){
      if( strlen( line ) != 1 )
	line[ strlen(line)-1 ] = '\0';
      else
	line[ strlen(line)-1 ] = ' ';

      chacha_hash( line );

    }
    
    fclose(fp);
  }else if( strcmp(argv[1],"-e") == 0){ // entropy
    if(argc != 3){
      PrintHelp();
      return -1;
    }
    
  }else if( strcmp(argv[1],"-h") == 0){ // help
    PrintHelp();
  }else{ // just hash
    for(int i=1;i<argc;i++)
      chacha_hash(argv[i]);    
  }

  return 0;
}


void PrintHelp(){
  // imprime como se usa el programa
  printf("Modo de uso chachash.c:\n\n   [NO FLAGS] => varios strings a hashear ( separados por ' ')\n   -f [FILE] hashear valores de un archivo\n\n"); 
}

char *AddPadding(char const *msg, size_t msg_len)
{ 
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

void chacha_state(uint32_t out[16], char *msg)
{
  const uint8_t *constant = (uint8_t *)"expand 32-byte k";
  const uint8_t *mensaje  = (uint8_t *)msg;

  for(int i=0;i<4;i++)
    out[i] = pack4(constant+(i*4));
  for(int i=0;i<8;i++)
    out[i] = pack4(mensaje+(i*4));
  
}

void chacha_hash(char *msg) // HASH AN ENTIRE WORD
{
  uint32_t state[16], hash[16], round[16];
  char *temp = malloc(64*sizeof(char));
  uint8_t *tmp;

  for(int i=0;i<16;i++)
    hash[i] = strlen(msg);
  
  chacha_state(state,msg);
  for(;strlen(msg);msg += 64){
    if(strlen(msg) < 64)
      msg = AddPadding(msg, strlen(msg));
    strncpy(temp,msg,64);

    for(int i=0;i<16;i++)
      round[i] = ROTL(pack4(temp+(i*4)), i);
    HashABlock(round,state);

    for(int i=0;i<16;i++)
      hash[i] ^= round[i];

  }
  for(int i=0;i<8;i++){
    tmp = unpack4(hash[i]);
    for(int j=0;j<4;j++)
      printf("%02x",tmp[j]);
  }
  printf("\n");
}

void HashABlock(uint32_t out[16], uint32_t in[16]) // HASH 1 BLOCK
{
  uint32_t i, x[16];
  for(i=0; i<16; i++)
    x[i] = in[16];

  for(i=0; i<ROUNDS; i+=2){
    QR(x[0], x[4], x[ 8], x[12], LFSR(x[0]) ); 
    QR(x[1], x[5], x[ 9], x[13], LFSR(x[1]) ); 
    QR(x[2], x[6], x[10], x[14], LFSR(x[2]) ); 
    QR(x[3], x[7], x[11], x[15], LFSR(x[3]) ); 

    QR(x[0], x[5], x[10], x[15], LFSR(x[4]) ); 
    QR(x[1], x[6], x[11], x[12], LFSR(x[5]) ); 
    QR(x[2], x[7], x[ 8], x[13], LFSR(x[6]) ); 
    QR(x[3], x[4], x[ 9], x[14], LFSR(x[7]) ); 
  }

  for(i=0; i<16; i++)
    out[i] = x[i] ^ in[i];

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

