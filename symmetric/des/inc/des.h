
#ifndef DES_H
#define DES_H

#include <stdint.h>
#ifndef DEBUG
    #define DEBUG
#endif // DEBUG

#ifdef DEBUG
void dumpBuffer(uint8_t *pu8Buffer, uint8_t u8Size);
#endif // DEBUG

void vDesPerformInitialPermutation(uint8_t *pu8Input);

void vDesPerformFinalPermutation(uint8_t *pu8Input);
#endif // DES_H
