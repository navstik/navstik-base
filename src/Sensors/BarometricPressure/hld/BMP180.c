/*
 * BMP180.c
 *
 *  Created on: Apr 28, 2012
 *      Author: Sapan, Rohit Rangan
 */

#include "das.h"

#if DAS_USE_BAROMETER
BaroData BD1 ;

/* This function takes op_mode as input and sets value of measurement_mode and
 * delay required between sending measurement command and reading data register.
 * 0 = ultra_low power mode.    delay = 6 ms (4.5 ms as per datasheet)
 * 1 = standard mode.        delay = 9 ms (7.5 ms as per datasheet)
 * 2 = high resoltuion mode.    delay = 15 ms (13.5 ms as per datasheet)
 * 3 = ultra high resolution mode.  delay = 27 ms (25.5 ms as per datasheet)
 */

void initialize_bmp180(BaroData *baro, uint8_t op_mode) {
  baro->DELAY_TEMP = 5 ;
  baro->OSS = op_mode ;
  if(op_mode == 0) {
    baro->MEASUREMENT_MODE = BOSCH_OSS0 ;
    baro->DELAY_PRESSURE = 6 ;
  }
  if(op_mode == 1) {
    baro->MEASUREMENT_MODE = BOSCH_OSS1 ;
    baro->DELAY_PRESSURE = 9 ;
  }
  if(op_mode == 2) {
    baro->MEASUREMENT_MODE = BOSCH_OSS2 ;
    baro->DELAY_PRESSURE = 15 ;
  }
  if(op_mode == 3) {
    baro->MEASUREMENT_MODE = BOSCH_OSS3 ;
    baro->DELAY_PRESSURE = 27 ;
  }
  read_bmp180_coefficient(baro) ;
}

void read_bmp180_coefficient(BaroData *baro) {
  uint8_t bmp_txbuf[1], bmp_rxbuf[22] ;
  chThdSleepMilliseconds(10) ;

  bmp_txbuf[0] = 0xAA ;
  i2cAcquireBus(&I2C_BMP) ;
  i2cMasterTransmit(&I2C_BMP, BMP_ADDR, bmp_txbuf, 1, bmp_rxbuf, 22) ;
  i2cReleaseBus(&I2C_BMP) ;

  baro->AC1 = (bmp_rxbuf[0] << 8) + bmp_rxbuf[1] ;    /*AC1 */
  baro->AC2 = (bmp_rxbuf[2] << 8) + bmp_rxbuf[3] ;    /*AC2 */
  baro->AC3 = (bmp_rxbuf[4] << 8) + bmp_rxbuf[5] ;    /*AC3 */
  baro->AC4 = (bmp_rxbuf[6] << 8) + bmp_rxbuf[7] ;    /*AC4 */
  baro->AC5 = (bmp_rxbuf[8] << 8) + bmp_rxbuf[9] ;    /*AC5 */
  baro->AC6 = (bmp_rxbuf[10] << 8) + bmp_rxbuf[11] ;    /*AC6 */
  baro->B1  = (bmp_rxbuf[12] << 8) + bmp_rxbuf[13] ;    /*B1 */
  baro->B2  = (bmp_rxbuf[14] << 8) + bmp_rxbuf[15] ;    /*B2 */
  baro->MB  = (bmp_rxbuf[16] << 8) + bmp_rxbuf[17] ;    /*MB */
  baro->MC  = (bmp_rxbuf[18] << 8) + bmp_rxbuf[19] ;    /*MC */
  baro->MD  = (bmp_rxbuf[20] << 8) + bmp_rxbuf[21] ;    /*MD */
}
#endif /*DAS_USE_BAROMETER */
