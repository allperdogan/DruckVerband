#include <msp430.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "ssd1306_lib.h"
#include <bmp280_config.h>
#include <BMP280.h>

static unsigned Temp, Pressure, Id;
char printNum[80];
char print_p[16];
char print_t[16];
unsigned char num = 5;
int p = 76.13;
int t = 21.12;
const unsigned char ti_logo[] = {
//   0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15    16    17    18    19    20    21    22    23    24    25    26    27
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x80, 0x00, 0x00, 0x80, 0x98, 0x08, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00,
//  28    29    30    31    32    33    34    35    36    37    38    39    40    41    42    43    44    45    46    47    48    49    50    51    52    53    54    55
  0x00, 0x10, 0x30, 0x70, 0xF0, 0xF0, 0xF0, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xE7, 0x61, 0x01, 0x00, 0xF0, 0x3F, 0x01, 0x00, 0xE0, 0xE1, 0xF9, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
//  56    57    58    59    60    61    62    63    64    65    66    67    68    69    70    71    72    73    74    75    76    77    78    79    80    81    82    83
  0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x07, 0x03, 0x03, 0x03, 0x07, 0x1F, 0x60, 0xE0, 0xE0, 0xE1, 0xE0, 0xE0, 0x61, 0x31, 0x1F, 0x0F, 0x07, 0x07, 0x03, 0x03, 0x00,
//  84    85    86    87    88    89    90    91    92    93    94    95    96    97    98    99   100   101   102   103   104   105   106   107   108   109   110   111
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void softDelay( void )
{
    volatile unsigned ix = 500;
    do
    {
        ix--;
    }
    while ( ix );
}

int main(void) {
    volatile uint32_t i;

    WDTCTL = WDTPW + WDTHOLD;

    BMP280_if_init();
    ssd1306Init();
    Id = BMP280_readID(); // Id _should_ be 0x58

    fillDisplay (0x00);
//    sprintf (print_p, "%d", p);
//    sprintf (print_t, "%d", t);
//    darwPixel(5, 5, 1);

//    draw12x16Str(0,  0, "HelloWorld", 1);
    draw6x8Str(0, 0, "Pressure: ", 1, 0);
//    draw12x16Str(4,  12, print_p, 1);
    draw6x8Str(0, 4, "Temperature: ", 1, 0);
//    draw12x16Str(4,  44, print_t, 1);
    //drawImage(100, 30, 28, 28, ti_logo, 1);
    for(;;)
    {
        BMP280_force_conversions();

        // always delay a few milliseconds
        softDelay();

        // now wait until conversion has definitely completed,
        // which will be when the 'measuring' bit (bit 3) in the
        // status register is false
        do {} while (BMP280_readStatus() & MEASURING_BIT_MASK);

        // get conversion results
        Pressure = BMP280_readPressure();
        Temp = BMP280_readTemperature();

        sprintf (print_p, "%d", Pressure);
        draw12x16Str(4,  12, print_p, 1);
        sprintf (print_t, "%d", Temp);
        draw12x16Str(4,  44, print_t, 1);
    }
    while (0) {
        for (num = 0; num < 10; num++){
            sprintf (printNum, "%d", num);
            draw12x16Str(0,  0, printNum, 1);
            for (i = 50000; i > 0; i--);
        }
        num = 0;
    }

}
