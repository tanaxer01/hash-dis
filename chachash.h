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

// input sht
char *AddPadding(char const *msg, size_t msg_len, size_t new_len);

// hash sht
uint32_t *GenState(char *msg);
uint32_t *UpdateState(uint8_t msg[16]);
void ChaChaState(uint32_t out[16], uint32_t const in[16]);

// aux sht
static uint32_t pack4(const uint8_t *a);
