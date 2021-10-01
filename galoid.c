#include "galoid.h"

//typedef uint8_t gal8;

//const gal8 min_poly = 0b1101;


gal8 gal_add(gal8 a, gal8 b){ return a^b; }
gal8 gal_mul(gal8 a, gal8 b)
{
    gal8 res = 0;
    for(;b;b >>= 1){
        if( b&1 )
            res ^= a;
        if( a&0x80 )
            a = (a << 1) ^ min_poly;
        else
            a <<= 1; 
    }

    return res; 
}

