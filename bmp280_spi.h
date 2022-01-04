#ifndef BMP280_SPI_H_
#define BMP280_SPI_H_


#define CLK_OUTPORT P2OUT
#define CLK_DIRPORT P2DIR
#define CLK_BIT_NUM 4
#define CLK_BIT_MASK (1 << CLK_BIT_NUM)

// MOSI is data from MCU to BMP280
#define MOSI_OUTPORT P2OUT
#define MOSI_DIRPORT P2DIR
#define MOSI_BIT_NUM 6
#define MOSI_BIT_MASK (1 << MOSI_BIT_NUM)

#define CS_OUTPORT P2OUT
#define CS_DIRPORT P2DIR
#define CS_BIT_NUM 3
#define CS_BIT_MASK (1 << CS_BIT_NUM)

// MISO is data from BMP to MCU
#define MISO_INPORT P2IN
#define MISO_DIRPORT P2DIR
#define MISO_BIT_NUM 5
#define MISO_BIT_MASK (1 << MISO_BIT_NUM)



#endif /* BMP280_SPI_H_ */
