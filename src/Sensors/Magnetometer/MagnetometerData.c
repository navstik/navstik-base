/*Created By - Rohit Rangan
 *Created On - 22-06-2012
 *
 *This file contains the functions to get data from
 *the magnetometer.
 */

#include<math.h>

#include "das.h"

#if DAS_USE_MAGNETOMETER
/*The raw values are stored in val. To convert to microTesla,
 *multiply val[i] by MAG_RANGE.
 */
void readMagnetometerData(MagData *magd) {
  uint8_t hmc_txbuf[2], hmc_rxbuf[6] ;
  /*Send Single Measurement query. Write 0x01 to MODE Register */
  hmc_txbuf[0] = OP_MODE ;
  hmc_txbuf[1] = magd->MEASUREMENT_MODE ;

  i2cAcquireBus(&I2C_HMC) ;
  i2cMasterTransmit(&I2C_HMC, HMC_ADDR, hmc_txbuf, 2, hmc_rxbuf, 0) ;
  i2cReleaseBus(&I2C_HMC) ;

  chThdSleepMicroseconds(30) ;

  hmc_txbuf[0] = OUT_X_MSB ;
  i2cAcquireBus(&I2C_HMC) ;
  i2cMasterTransmit(&I2C_HMC, HMC_ADDR, hmc_txbuf, 1, hmc_rxbuf, 6) ;
  i2cReleaseBus(&I2C_HMC) ;

  magd->RAW_MAG_X = (hmc_rxbuf[0] << 8) + hmc_rxbuf[1] ;
  magd->RAW_MAG_Z = (hmc_rxbuf[2] << 8) + hmc_rxbuf[3] ;
  magd->RAW_MAG_Y = (hmc_rxbuf[4] << 8) + hmc_rxbuf[5] ;

  magd->MAG_X = magd->RAW_MAG_X * magd->RANGE ;
  magd->MAG_Y = magd->RAW_MAG_Y * magd->RANGE ;
  magd->MAG_Z = magd->RAW_MAG_Z * magd->RANGE ;
}

#if DAS_USE_IMU
/*Returns the heading of the board in degrees.
 *000 -> North.
 *090 -> East.
 *180 -> South.
 *270 -> West.
 */
float getHeading(IMUData *imudata, MagData *magd) {
  float heading, angles[3], cosRoll, sinRoll, cosPitch, sinPitch ;

  eulerAngles(imudata, angles) ;
  angles[0] = (angles[0] * M_PI / 180) ;
  angles[1] = (angles[1] * M_PI / 180) ;
  cosPitch = cosf(angles[0]) ;
  sinPitch = sinf(angles[0]) ;
  cosRoll  = cosf(angles[1]) ;
  sinRoll  = sinf(angles[1]) ;

  readMagnetometerData(magd) ;

  /*float Xh = (magd->MAG_X * cosPitch) + (magd->MAG_Y * sinPitch * sinRoll) - (mag[2] * sinPitch * cosRoll) ;
  float Yh = (magd->MAG_Y * cosRoll) + (magd->MAG_Z * sinRoll) ;*/
  float Xh = (magd->MAG_X * cosPitch) + (magd->MAG_Z * sinPitch) ;
  float Yh = (magd->MAG_X * sinRoll * sinPitch) + (magd->MAG_Y * cosRoll) - (magd->MAG_Z * sinRoll * cosPitch) ;
  heading = my_atan2f(Yh, Xh) ;

  return (heading * 180.0 / M_PI) ;
}
#endif  /*DAS_USE_IMU */

#endif  /*DAS_USE_MAGNETOMETER */
