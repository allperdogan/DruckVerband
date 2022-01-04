#ifndef BMP280_H_
#define BMP280_H_


void BMP280_if_init( void );
void BMP280_force_conversions( void );

unsigned BMP280_readID( void );
unsigned BMP280_readStatus( void );
unsigned BMP280_readTemperature( void );
unsigned BMP280_readPressure( void );

#endif /* BMP280_H_ */
