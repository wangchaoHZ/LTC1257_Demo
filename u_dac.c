/*
 * @Author        : wang chao
 * @Date          : 2024-04-15 15:17:11
 * @LastEditors   : wang chao
 * @LastEditTime  : 2024-04-15 15:51:37
 * @FilePath      : \u_dac.c
 * @Description   :
 * @Copyright     : Copyright 2024 wang chao, All Rights Reserved.
 */

#include "u_dac.h"

// Pins
#define LT_DAC_SCK PORTHbits.RH0
#define LT_DAC_DIN PORTHbits.RH1
#define LT_DAC_LOAD PORTJbits.RJ4
// IO Direction
#define LT_DAC_SCK_TRIS TRISHbits.RH0
#define LT_DAC_DIN_TRIS TRISHbits.RH1
#define LT_DAC_LOAD_TRIS TRISJbits.RJ4

void u_dac_init(void) {
    LT_DAC_SCK_TRIS = 0;
    LT_DAC_DIN_TRIS = 0;
    LT_DAC_LOAD_TRIS = 0;
    LT_DAC_LOAD = 1;
    LT_DAC_SCK = 1;
    LT_DAC_DIN = 1;
}

void u_dac_set(rt_uint16_t data) {
    rt_uint8_t index = 0;
    rt_uint8_t w_bits[12] = {0};
    // get bits
    for (index = 0; index < 12; index++) {
        if (data >> (11 - index) & 0x1) {
            w_bits[index] = 1;
        } else {
            w_bits[index] = 0;
        }
    }
    //
    LT_DAC_LOAD = 1;
    LT_DAC_SCK = 0;
    __delay_us(2);
    //
    for (index = 0; index < 12; index++) {
        LT_DAC_SCK = 0;
        if (w_bits[index]) {
            LT_DAC_DIN = 1;
        } else {
            LT_DAC_DIN = 0;
        }
        __delay_us(1);
        LT_DAC_SCK = 1;
        __delay_us(2);
        LT_DAC_SCK = 0;
        __delay_us(1);
    }
    //  set load
    LT_DAC_LOAD = 0;
    __delay_us(2);
    LT_DAC_LOAD = 1;
}
