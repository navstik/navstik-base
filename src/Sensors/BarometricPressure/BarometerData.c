/*Created By - Rohit Rangan
 *Created On - 23-06-2012
 *
 *This file contains the functions to get data from
 *the barometer.
 */
#include<math.h>

#include "das.h"

#if DAS_USE_BAROMETER
/*If mode is 1, the function returns the temperature value
 *in degrees Celsius. If mode is 2, the function returns
 *the pressure value in Pascals. No sleeps need to be given
 *when calling this function.
 */
void readBarometerData(BaroData *baro, uint8_t mode) {
  uint8_t bmp_txbuf[2], bmp_rxbuf[3] ;

  if(mode == BARO_TEMP_DATA) {
    uint32_t ut ;
    int32_t x1, x2, b5 ;
    bmp_txbuf[0] = BOSCH_CTL ;
    bmp_txbuf[1] = BOSCH_TEMP ;

    i2cAcquireBus(&I2C_BMP) ;
    i2cMasterTransmit(&I2C_BMP,  BMP_ADDR, bmp_txbuf, 2, bmp_rxbuf, 0) ;
    i2cReleaseBus(&I2C_BMP) ;
    chThdSleepMilliseconds(baro->DELAY_TEMP) ;

    bmp_txbuf[0] = BOSCH_ADC_MSB ;
    i2cAcquireBus(&I2C_BMP) ;
    i2cMasterTransmit(&I2C_BMP,  BMP_ADDR, bmp_txbuf, 1, bmp_rxbuf, 2) ;
    i2cReleaseBus(&I2C_BMP) ;

    ut = (bmp_rxbuf[0] << 8) + bmp_rxbuf[1] ;
    /*All calculations here are black magic from the
     *BMP180 Datasheet. DO NOT CHANGE.
     */
    x1 = (ut - baro->AC6) * baro->AC5 >> 15 ;
    x2 = ((int32_t)baro->MC << 11) / (x1 + baro->MD) ;
    b5 = x1 + x2 ;
    baro->TEMP = (float)((b5 + 8) >> 4) / 10.0f ;
  }
  else if(mode == BARO_PRESSURE_DATA) {
    int32_t x1, x2, x3, b3, b5, b6, p ;
    uint32_t b4, b7, up, ut ;

    /*To measure temperature as it is required for
     *pressure measurement.
     */
    bmp_txbuf[0] = BOSCH_CTL ;
    bmp_txbuf[1] = BOSCH_TEMP ;

    i2cAcquireBus(&I2C_BMP) ;
    i2cMasterTransmit(&I2C_BMP,  BMP_ADDR, bmp_txbuf, 2, bmp_rxbuf, 0) ;
    i2cReleaseBus(&I2C_BMP) ;
    chThdSleepMilliseconds(baro->DELAY_TEMP) ;

    bmp_txbuf[0] = BOSCH_ADC_MSB ;
    i2cAcquireBus(&I2C_BMP) ;
    i2cMasterTransmit(&I2C_BMP,  BMP_ADDR, bmp_txbuf, 1, bmp_rxbuf, 2) ;
    i2cReleaseBus(&I2C_BMP) ;

    ut = (bmp_rxbuf[0] << 8) + bmp_rxbuf[1] ;

    /*Pressure measurement starts now */
    bmp_txbuf[0] = BOSCH_CTL ;
    bmp_txbuf[1] = baro->MEASUREMENT_MODE ;

    i2cAcquireBus(&I2C_BMP) ;
    i2cMasterTransmit(&I2C_BMP,  BMP_ADDR, bmp_txbuf, 2, bmp_rxbuf, 0) ;
    i2cReleaseBus(&I2C_BMP) ;

    /* Wait until pressure measurement is done. Time required
     *for this depends on selected mode.
     */
    chThdSleepMilliseconds(baro->DELAY_PRESSURE) ;

      bmp_txbuf[0] = BOSCH_ADC_MSB ;

      i2cAcquireBus(&I2C_BMP) ;
      i2cMasterTransmit(&I2C_BMP, BMP_ADDR, bmp_txbuf, 1, bmp_rxbuf, 3) ;
      i2cReleaseBus(&I2C_BMP) ;

      /*All calculations here are black magic from the
       *BMP180 Datasheet. DO NOT CHANGE.
       */
      up = ((bmp_rxbuf[0] << 16) + (bmp_rxbuf[1] << 8) + bmp_rxbuf[2]) >> (8 - baro->OSS) ;

      x1 = (ut - baro->AC6) * baro->AC5 >> 15 ;
      x2 = ((int32_t)baro->MC << 11) / (x1 + baro->MD) ;
      b5 = x1 + x2 ;

      b6 = b5 - 4000 ;
      x1 = (baro->B2 * (b6 * b6 >> 12)) >> 11 ;
      x2 = baro->AC2 * b6 >> 11 ;
      x3 = x1 + x2 ;
      b3 = ((((int32_t)baro->AC1 * 4 + x3) << baro->OSS) + 2) >> 2 ;

      x1 = baro->AC3 * b6 >> 13 ;
      x2 = (baro->B1 * (b6 * b6 >> 12)) >> 16 ;
      x3 = ((x1 + x2) + 2) >> 2 ;
      b4 = (baro->AC4 * (uint32_t)(x3 + 32768)) >> 15 ;
      b7 = ((uint32_t)up - b3) * (50000 >> baro->OSS) ;

      if(b7 < 0x80000000)
        p = (b7 * 2) / b4 ;
      else
        p = (b7 / b4) * 2 ;

      x1 = (p >> 8) * (p >> 8) ;
      x1 = (x1 * 3038) >> 16 ;
      x2 = (-7357 * p) >> 16 ;
      baro->PRESSURE = (float)(p + ((x1 + x2 + 3791) >> 4)) ;
  }
  else {
    return ;
  }
}

/*This function returns the absolute altitude above sea level
 *in meters.
 */
float getAltitude(BaroData *baro) {
  readBarometerData(baro, BARO_PRESSURE_DATA) ;
  return (44330.0 * (1 - (pow((baro->PRESSURE / SEA_LEVEL_PRESSURE), EXPONENT)))) ;
}
#endif  /*DAS_USE_BAROMETER */
