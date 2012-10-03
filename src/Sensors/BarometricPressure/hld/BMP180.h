/*
 * BMP180.h
 *
 *  Created on: Apr 28, 2012
 *      Author: Sapan, Rohit Rangan
 */

#ifndef BMP180_H_
#define BMP180_H_

#include "das_conf.h"

#if DAS_USE_BAROMETER
#define BMP_ADDR  0b1110111
#define I2C_BMP    I2CD3

#define BOSCH_CTL        0xF4 // Measurement Control Register.
#define BOSCH_ADC_MSB      0xF6 // Read Only Register. Contains Output Data.
#define BOSCH_ADC_LSB      0xF7 // Read Only Register. Contains Output Data.
#define BOSCH_ADC_XLSB      0xF8 // Read Only Register. Contains Output Data.
#define BOSCH_ID        0xD0 // Read Only Register. Value is 0x55 can be used to check communication.
#define SOFT_RESET        0xE0 // Write Only Register. If sets to 0xB6 performs same sequence as power on reset

#define BOSCH_TEMP        0x2E // Value of Control Register for temperature measurment
#define BOSCH_OSS0        0x34 // Value of Control Register for Conversion time 4.5ms
#define BOSCH_OSS1        0x74 // Value of Control Register for Conversion time 7.5ms
#define BOSCH_OSS2        0xB4 // Value of Control Register for Conversion time 13.5ms
#define BOSCH_OSS3        0xF4 // Value of Control Register for Conversion time 25.5ms

#define BOSCH_PRES        0xF4 // pressure with OSRS=3 (page 17 in manual)

#define ULTRA_LOW_POWER     0
#define STANDARD        1
#define HIGH_RESOLUTION      2
#define ULTRA_HIGH_RESOLUTION  3

extern int16_t delay_bmp180, delay_bmp180_temperature, reg1[8] ;
extern uint8_t oss, measurement_mode ;
extern uint16_t reg2[3] ;

typedef struct {
  uint8_t OSS ;
  int16_t DELAY_PRESSURE ;
  int16_t DELAY_TEMP ;
  int16_t MEASUREMENT_MODE ;
  int16_t AC1 ;
  int16_t AC2 ;
  int16_t AC3 ;
  uint16_t AC4 ;
  uint16_t AC5 ;
  uint16_t AC6 ;
  int16_t B1  ;
  int16_t B2  ;
  int16_t MB  ;
  int16_t MC  ;
  int16_t MD  ;
  float PRESSURE ;
  float TEMP ;
}BaroData;

extern BaroData BD1 ;

void initialize_bmp180(BaroData *baro, uint8_t operating_mode) ;
void read_bmp180_coefficient(BaroData *baro) ;
#endif  /*DAS_USE_BAROMETER */

#endif /* BMP180_H_ */
