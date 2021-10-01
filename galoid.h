// galoid.h
#include <stdint.h>
typedef uint8_t gal8;

const gal8 min_poly = 0b1101;

gal8 gal_add(gal8 a, gal8 b);
gal8 gal_mul(gal8 a, gal8 b);
