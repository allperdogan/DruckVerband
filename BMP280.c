#include <bmp280_config.h>
#include <bmp280_spi.h>
#include <BMP280.h>
#include <msp430.h>


#define SELECT_L    CS_OUTPORT &= ~CS_BIT_MASK  // active-LOW signal
#define DESELECT    CS_OUTPORT |= CS_BIT_MASK
#define MOSI_LO     MOSI_OUTPORT &= ~MOSI_BIT_MASK
#define MOSI_HI     MOSI_OUTPORT |= MOSI_BIT_MASK
#define SCLK_HI     CLK_OUTPORT |= CLK_BIT_MASK
#define SCLK_LO     CLK_OUTPORT &= ~CLK_BIT_MASK


static unsigned Word, WordMask;


static void regWrite( unsigned Reg, unsigned Value)
{

    WordMask = 0x8000;
    Word = (Reg << 8) | Value;

    SELECT_L;

    do
    {
        SCLK_LO;
        if (WordMask & Word)
          MOSI_HI;
        else
          MOSI_LO;
        SCLK_HI;
        WordMask = WordMask >> 1;
    } while (WordMask);

    DESELECT;
}

static unsigned char regRead( unsigned Reg )
{
    unsigned Count;

    // send 8 bits to define the register and READ as the action
    // the MSB is transmitted first
    WordMask = 0x80;
    Word = (Reg | REG_READ); // for read, make sure MSB of register value is SET

    SELECT_L;

    do
    {
        SCLK_LO;
        if (WordMask & Word)
          MOSI_HI;
        else
          MOSI_LO;
        SCLK_HI;
        WordMask = WordMask >> 1;
    }
    while (WordMask);

    // make sure MOSI is low
    MOSI_LO;

    // now read the MISO line 8 times to get the contents of the register
    Word = 0;
    for ( Count = 8; Count > 0; Count--)
    {
       Word = Word << 1;
       SCLK_LO;
       SCLK_HI;
       if (MISO_INPORT & MISO_BIT_MASK)
           Word |= 1;
    }

    DESELECT;

    return (unsigned char)Word;

}

void BMP280_if_init( void )
{
    // set three bits HI in port OUTPUT register so
    // that states for CS, SCLK, SDA will all be HIGH as pin
    // mode is set to OUTPUT
    DESELECT;
    MOSI_HI;
    SCLK_HI;

    // now set pin mode to OUTPUT for CS, SCL, MOSI
    CS_DIRPORT   |= CS_BIT_MASK;
    CLK_DIRPORT  |= CLK_BIT_MASK;
    MOSI_DIRPORT |= MOSI_BIT_MASK;

    // reset the BMP280
    regWrite( RESET_REG, 0xB6);


}

unsigned BMP280_readID( void )
{
    return (unsigned)regRead(ID_REG);
}

unsigned BMP280_readStatus( void )
{
    return (unsigned)regRead(STATUS_REG);
}

unsigned BMP280_readTemperature( void )
{
    return (unsigned)(regRead(TEMP_HIGH) << 8) | regRead(TEMP_MID);
}

unsigned BMP280_readPressure( void )
{
    return (unsigned)(regRead(PRESS_HIGH) << 8) | regRead(PRESS_MID);
}

void BMP280_force_conversions( void )
{
    // write 0x25 to reg 0x74 to force a conversion for both temp and pressure
    // the device will enter sleep mode after the conversions are done
    regWrite(CTL_MEAS_REG, 0x25);
}

