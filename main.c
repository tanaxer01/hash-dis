#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b + (c&d),  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b + (c|d),  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))
#define ROUNDS 10


char *AddPadding(char const *msg, size_t msg_len, size_t new_len);
uint32_t *GenState(char *msg);
uint32_t *UpdateState(uint8_t msg[16]);
void ChaChaState(uint32_t out[16], uint32_t const in[16]);

// aux
static uint32_t pack4(const uint8_t *a);

int main(){ 

    char *msg = malloc( 33*sizeof(char) );
    //msg = "holaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholaholahola"; 
    msg = "ba";
    if ( strlen(msg) < 33 )
       msg = AddPadding(msg, strlen(msg), 32);

    printf("%s \n", msg);
    uint32_t *state = GenState(msg);

    uint32_t input[16];//512
    for(int i=0;i<8;++i){ 
        input[i] = pack4(msg+(i*4));
        input[i+8] = pack4(msg+(i*4));
    }

    ChaChaState(input, state);
    for(int i=0;i<8;i++)
        printf("%2x",input[i]);
    printf("\n");
}

// ** asume que msg_len >= 1
char *AddPadding(char const *msg, size_t msg_len, size_t new_len)
{
    /* 
        Si el mensaje tiene un largo menor a 256 entonces le agregamos padding,
        compuesto por el mensaje cifrado en cesar con el largo del mensaje.
    */

    size_t faltan = new_len-msg_len;
    char *pad = malloc( faltan*sizeof(char) );
    char *res = malloc( (new_len+1)*sizeof(char) );

    for(;strlen(pad)!=faltan;)
        strncat(pad,msg, (faltan-strlen(pad)<msg_len)?faltan-strlen(pad):msg_len);

    for(int i=0;i<faltan;i++)
        pad[i] ^= msg_len;

    strcpy(res, msg);
    return strcat(res, pad);
}


uint32_t *GenState(char *msg)
{
    uint32_t *state = malloc(16*sizeof(uint32_t));
    const uint8_t *constant = (uint8_t *)"expand 32-byte k";
    const uint8_t *mensaje  = (uint8_t *)msg;

    for(int i=0;i<4;++i) // constant
        state[i] = pack4(constant+(i*4));
    for(int i=0;i<8;++i) // key
        state[i+4] = pack4(mensaje+(i*4));

    //counter parte en 0
    state[12] = 0; 
    // nonce 

    return state;
}

void ChaChaState(uint32_t out[16], uint32_t const in[16]){
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


static uint32_t pack4(const uint8_t *a){
    uint32_t res = 0;
    res |= (uint32_t)a[0];
    res |= (uint32_t)a[1] << 8 ;
    res |= (uint32_t)a[2] << 16;
    res |= (uint32_t)a[3] << 24;

    return
}