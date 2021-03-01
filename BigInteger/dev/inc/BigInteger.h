#ifndef _BIG_INTEGER_H_
#define _BIG_INTEGER_H_

#include <stdint.h>

typedef struct
{
    uint8_t  *pu8Value;
    uint32_t u32Length;
} T_BIG_INTEGER;

#endif // _BIG_INTEGER_H_