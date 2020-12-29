
#include <stdio.h>
#include <string.h>

#include "des.h"

#define DES_BLOCK_SIZE      8


uint8_t S1[] =
{
    0x0E, 0x04
};

#ifdef DEBUG
void dumpBuffer(uint8_t *pu8Buffer, uint8_t u8Size)
{
    uint8_t u8Index = 0;
    printf("Buffer: ");
    while (u8Index < u8Size)
    {
        printf("%02X ", pu8Buffer[u8Index]);
        u8Index++;
    }
    printf("\n");
}
#endif // DEBUG

/**
 ** Initial Permutation
 **
 ** 58	50	42	34	26	18	10	2
 ** 60	52	44	36	28	20	12	4
 ** 62	54	46	38	30	22	14	6
 ** 64	56	48	40	32	24	16	8
 ** 57	49	41	33	25	17	9	1
 ** 59	51	43	35	27	19	11	3
 ** 61	53	45	37	29	21	13	5
 ** 63	55	47	39	31	23	15	7
 **/
void vDesPerformInitialPermutation(uint8_t *pu8Input)
{
    uint8_t au8Output[8] = {0};
    uint8_t u8Permute;

    // Compute 1st byte,
    u8Permute = (pu8Input[7] << 1) & 0x80;
    u8Permute |= (pu8Input[6] & 0x40);
    u8Permute |= ((pu8Input[5] >> 1) & 0x20);
    u8Permute |= ((pu8Input[4] >> 2) & 0x10);
    u8Permute |= ((pu8Input[3] >> 3) & 0x08);
    u8Permute |= ((pu8Input[2] >> 4) & 0x04);
    u8Permute |= ((pu8Input[1] >> 5) & 0x02);
    u8Permute |= ((pu8Input[0] >> 6) & 0x01);
    au8Output[0] = u8Permute;

    // then 2nd byte,
    u8Permute = (pu8Input[7] << 3) & 0x80;
    u8Permute |= ((pu8Input[6] << 2) & 0x40);
    u8Permute |= ((pu8Input[5] << 1) & 0x20);
    u8Permute |= (pu8Input[4] & 0x10);
    u8Permute |= ((pu8Input[3] >> 1) & 0x08);
    u8Permute |= ((pu8Input[2] >> 2) & 0x04);
    u8Permute |= ((pu8Input[1] >> 3) & 0x02);
    u8Permute |= ((pu8Input[0] >> 4) & 0x01);
    au8Output[1] = u8Permute;

    // then 3rd byte,
    u8Permute = (pu8Input[7] << 5) & 0x80;
    u8Permute |= ((pu8Input[6] << 4) & 0x40);
    u8Permute |= ((pu8Input[5] >> 3) & 0x20);
    u8Permute |= ((pu8Input[4] << 2) & 0x10);
    u8Permute |= ((pu8Input[3] << 1) & 0x08);
    u8Permute |= (pu8Input[2] & 0x04);
    u8Permute |= ((pu8Input[1] >> 1) & 0x02);
    u8Permute |= ((pu8Input[0] >> 2) & 0x01);
    au8Output[2] = u8Permute;

    // then 4th byte,
    u8Permute = (pu8Input[7] << 7) & 0x80;
    u8Permute |= ((pu8Input[6] << 6) & 0x40);
    u8Permute |= ((pu8Input[5] << 5) & 0x20);
    u8Permute |= ((pu8Input[4] << 4) & 0x10);
    u8Permute |= ((pu8Input[3] << 3) & 0x08);
    u8Permute |= ((pu8Input[2] << 2) & 0x04);
    u8Permute |= ((pu8Input[1] << 1) & 0x02);
    u8Permute |= (pu8Input[0] & 0x01);
    au8Output[3] = u8Permute;

    // then 5th byte,
    u8Permute = pu8Input[7] & 0x80;
    u8Permute |= ((pu8Input[6] >> 1) & 0x40);
    u8Permute |= ((pu8Input[5] >> 2) & 0x20);
    u8Permute |= ((pu8Input[4] >> 3) & 0x10);
    u8Permute |= ((pu8Input[3] >> 4) & 0x08);
    u8Permute |= ((pu8Input[2] >> 5) & 0x04);
    u8Permute |= ((pu8Input[1] >> 6) & 0x02);
    u8Permute |= ((pu8Input[0] >> 7) & 0x01);
    au8Output[4] = u8Permute;

    // then 6th byte,
    u8Permute = (pu8Input[7] << 2) & 0x80;
    u8Permute |= ((pu8Input[6] << 1) & 0x40);
    u8Permute |= (pu8Input[5] & 0x20);
    u8Permute |= ((pu8Input[4] >> 1) & 0x10);
    u8Permute |= ((pu8Input[3] >> 2) & 0x08);
    u8Permute |= ((pu8Input[2] >> 3) & 0x04);
    u8Permute |= ((pu8Input[1] >> 4) & 0x02);
    u8Permute |= ((pu8Input[0] >> 5) & 0x01);
    au8Output[5] = u8Permute;

    // then 7th byte,
    u8Permute = (pu8Input[7] << 4) & 0x80;
    u8Permute |= ((pu8Input[6] << 3) & 0x40);
    u8Permute |= ((pu8Input[5] << 2) & 0x20);
    u8Permute |= ((pu8Input[4] << 1) & 0x10);
    u8Permute |= (pu8Input[3] & 0x08);
    u8Permute |= ((pu8Input[2] >> 1) & 0x04);
    u8Permute |= ((pu8Input[1] >> 2) & 0x02);
    u8Permute |= ((pu8Input[0] >> 3) & 0x01);
    au8Output[6] = u8Permute;

    // and the last, i.e., 8th byte
    u8Permute = (pu8Input[7] << 6) & 0x80;
    u8Permute |= ((pu8Input[6] << 5) & 0x40);
    u8Permute |= ((pu8Input[5] << 4) & 0x20);
    u8Permute |= ((pu8Input[4] << 3) & 0x10);
    u8Permute |= ((pu8Input[3] << 2) & 0x08);
    u8Permute |= ((pu8Input[2] << 1) & 0x04);
    u8Permute |= (pu8Input[1] & 0x02);
    u8Permute |= ((pu8Input[0] >> 1) & 0x01);
    au8Output[7] = u8Permute;

    // Now take permute bytes back in input buffer
    memcpy(pu8Input, au8Output, DES_BLOCK_SIZE);
}

/**
 ** Expansion function
 **
 ** 32	1	2	3	4	5
 ** 4	5	6	7	8	9
 ** 8	9	10	11	12	13
 ** 12	13	14	15	16	17
 ** 16	17	18	19	20	21
 ** 20	21	22	23	24	25
 ** 24	25	26	27	28	29
 ** 28	29	30	31	32	1
 **/
void vDesPerformExpansion(uint8_t *pu8Input)
{
    ;
}


/**
 ** Final Permutation
 **
 ** 40	8	48	16	56	24	64	32
 ** 39	7	47	15	55	23	63	31
 ** 38	6	46	14	54	22	62	30
 ** 37	5	45	13	53	21	61	29
 ** 36	4	44	12	52	20	60	28
 ** 35	3	43	11	51	19	59	27
 ** 34	2	42	10	50	18	58	26
 ** 33	1	41	9	49	17	57	25
 **/
void vDesPerformFinalPermutation(uint8_t *pu8Input)
{
    uint8_t au8Output[8] = {0};
    uint8_t u8Permute;

    // Compute 1st byte,
    u8Permute = (pu8Input[4] << 7) & 0x80;
    u8Permute |= ((pu8Input[0] << 6) & 0x40);
    u8Permute |= ((pu8Input[5] << 5) & 0x20);
    u8Permute |= ((pu8Input[1] << 4) & 0x10);
    u8Permute |= ((pu8Input[6] << 3) & 0x08);
    u8Permute |= ((pu8Input[2] << 2) & 0x04);
    u8Permute |= ((pu8Input[7] << 1) & 0x02);
    u8Permute |= (pu8Input[3] & 0x01);
    au8Output[0] = u8Permute;

    // then 2nd byte,
    u8Permute = (pu8Input[4] << 6) & 0x80;
    u8Permute |= ((pu8Input[0] << 5) & 0x40);
    u8Permute |= ((pu8Input[5] << 4) & 0x20);
    u8Permute |= ((pu8Input[1] << 3) & 0x10);
    u8Permute |= ((pu8Input[6] << 2) & 0x08);
    u8Permute |= ((pu8Input[2] << 1) & 0x04);
    u8Permute |= (pu8Input[7] & 0x02);
    u8Permute |= ((pu8Input[3] >> 1) & 0x01);
    au8Output[1] = u8Permute;

    // then 3rd byte,
    u8Permute = (pu8Input[4] << 5) & 0x80;
    u8Permute |= ((pu8Input[0] << 4) & 0x40);
    u8Permute |= ((pu8Input[5] << 3) & 0x20);
    u8Permute |= ((pu8Input[1] << 2) & 0x10);
    u8Permute |= ((pu8Input[6] << 1) & 0x08);
    u8Permute |= (pu8Input[2] & 0x04);
    u8Permute |= ((pu8Input[7] >> 1) & 0x02);
    u8Permute |= ((pu8Input[3] >> 2) & 0x01);
    au8Output[2] = u8Permute;

    // then 4th byte,
    u8Permute = (pu8Input[4] << 4) & 0x80;
    u8Permute |= ((pu8Input[0] << 3) & 0x40);
    u8Permute |= ((pu8Input[5] << 2) & 0x20);
    u8Permute |= ((pu8Input[1] << 1) & 0x10);
    u8Permute |= (pu8Input[6] & 0x08);
    u8Permute |= ((pu8Input[2] >> 1) & 0x04);
    u8Permute |= ((pu8Input[7] >> 2) & 0x02);
    u8Permute |= ((pu8Input[3] >> 3) & 0x01);
    au8Output[3] = u8Permute;

    // then 5th byte,
    u8Permute = (pu8Input[4] << 3) & 0x80;
    u8Permute |= ((pu8Input[0] << 2) & 0x40);
    u8Permute |= ((pu8Input[5] << 1) & 0x20);
    u8Permute |= (pu8Input[1] & 0x10);
    u8Permute |= ((pu8Input[6] >> 1) & 0x08);
    u8Permute |= ((pu8Input[2] >> 2) & 0x04);
    u8Permute |= ((pu8Input[7] >> 3) & 0x02);
    u8Permute |= ((pu8Input[3] >> 4) & 0x01);
    au8Output[4] = u8Permute;

    // then 6th byte,
    u8Permute = (pu8Input[4] << 2) & 0x80;
    u8Permute |= ((pu8Input[0] << 1) & 0x40);
    u8Permute |= (pu8Input[5] & 0x20);
    u8Permute |= ((pu8Input[1] >> 1) & 0x10);
    u8Permute |= ((pu8Input[6] >> 2) & 0x08);
    u8Permute |= ((pu8Input[2] >> 3) & 0x04);
    u8Permute |= ((pu8Input[7] >> 4) & 0x02);
    u8Permute |= ((pu8Input[3] >> 5) & 0x01);
    au8Output[5] = u8Permute;

    // then 7th byte,
    u8Permute = (pu8Input[4] << 1) & 0x80;
    u8Permute |= (pu8Input[0] & 0x40);
    u8Permute |= ((pu8Input[5] >> 1) & 0x20);
    u8Permute |= ((pu8Input[1] >> 2) & 0x10);
    u8Permute |= ((pu8Input[6] >> 3) & 0x08);
    u8Permute |= ((pu8Input[2] >> 4) & 0x04);
    u8Permute |= ((pu8Input[7] >> 5) & 0x02);
    u8Permute |= ((pu8Input[3] >> 6) & 0x01);
    au8Output[6] = u8Permute;

    // and the last, i.e., 8th byte,
    u8Permute = pu8Input[4] & 0x80;
    u8Permute |= ((pu8Input[0] >> 1) & 0x40);
    u8Permute |= ((pu8Input[5] >> 2) & 0x20);
    u8Permute |= ((pu8Input[1] >> 3) & 0x10);
    u8Permute |= ((pu8Input[6] >> 4) & 0x08);
    u8Permute |= ((pu8Input[2] >> 5) & 0x04);
    u8Permute |= ((pu8Input[7] >> 6) & 0x02);
    u8Permute |= ((pu8Input[3] >> 7) & 0x01);
    au8Output[7] = u8Permute;

    // Now take permute bytes back in input buffer
    memcpy(pu8Input, au8Output, DES_BLOCK_SIZE);
}

