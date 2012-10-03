/*
 * MPU60X0.c
 *
 *  Created on: May 1, 2012
 *      Author: Sapan, Rohit Rangan
 */

#include "das.h"

#if DAS_USE_IMU
float reg_coeffs[12] ;
IMUData IMUD1 ;
/*
 * This function sets up the MPU and the I2C driver.
 * MPU registers can be read thereafter.
 */
void set_mpu60X0(IMUData *imudat, IMUConfig *imucfg) {
  uint8_t txbuf[2], rxbuf[2] ;
  msg_t status = RDY_OK ;

  txbuf[0] = PWR_MGMT_1 ;
  txbuf[1] = 0x01 ;
  i2cAcquireBus(&I2C_MPU) ;
  status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 2, rxbuf, 0) ;
  i2cReleaseBus(&I2C_MPU) ;

  if(status != RDY_OK)
    return ;

  chThdSleepMilliseconds(35) ;

  txbuf[0] = GYRO_CONFIG ;
  txbuf[1] = 0x00 ;
  i2cAcquireBus(&I2C_MPU) ;
  status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 2, rxbuf, 0) ;
  i2cReleaseBus(&I2C_MPU) ;

  switch(imucfg->GYRO_FS_SEL) {
    case FS_SEL_250  : imudat->GYRO_SENS = 131.0f ;
                 break ;
    case FS_SEL_500  : imudat->GYRO_SENS = 65.5f ;
                 break ;
    case FS_SEL_1000 : imudat->GYRO_SENS = 32.8f ;
                 break ;
    case FS_SEL_2000 : imudat->GYRO_SENS = 16.4f ;
                 break ;
  }

  if(status != RDY_OK)
    return ;

  chThdSleepMilliseconds(35) ;

  txbuf[0] = ACCEL_CONFIG ;
  txbuf[1] = 0x00 ;
  i2cAcquireBus(&I2C_MPU) ;
  status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 2, rxbuf, 0) ;
  i2cReleaseBus(&I2C_MPU) ;

  switch(imucfg->ACCEL_FS_SEL) {
    case AFS_SEL_2g  : imudat->ACCEL_SENS = 16384.0f ;
                 break ;
    case AFS_SEL_4g  : imudat->ACCEL_SENS = 8192.0f ;
                 break ;
    case AFS_SEL_8g  : imudat->ACCEL_SENS = 4096.0f ;
                 break ;
    case AFS_SEL_16g : imudat->ACCEL_SENS = 2048.0f ;
               break ;
  }

  if(status != RDY_OK)
    return ;

  chThdSleepMilliseconds(35) ;

  txbuf[0] = SMPRT_DIV ;
  txbuf[1] = 0x09 ;
  i2cAcquireBus(&I2C_MPU) ;
  status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 2, rxbuf, 0) ;
  i2cReleaseBus(&I2C_MPU) ;

  if(status != RDY_OK)
    return ;

  imudat->ACCEL_X = 0.0f ;
  imudat->ACCEL_Y = 0.0f ;
  imudat->ACCEL_Z = 0.0f ;
  imudat->RAW_ACCEL_X = 0 ;
  imudat->RAW_ACCEL_Y = 0 ;
  imudat->RAW_ACCEL_Z = 0 ;
  imudat->GYRO_X = 0.0f ;
  imudat->GYRO_Y = 0.0f ;
  imudat->GYRO_Z = 0.0f ;
  imudat->RAW_GYRO_X = 0 ;
  imudat->RAW_GYRO_Y = 0 ;
  imudat->RAW_GYRO_Z = 0 ;
  imudat->RAW_TEMP = 0 ;

  chThdSleepMilliseconds(35) ;
#if DAS_CALIBRATE_IMU
  calibrateIMU(reg_coeffs) ;
#else
  uint8_t i ;
  for(i = 0 ; i < 11 ; i++) {
    if(i % 2 == 0)
      reg_coeffs[i] = 0.0f ;
    else
      reg_coeffs[i] = 1.0f ;
  }
#endif  /*DAS_CALIBRATE_IMU */
}
#endif  /*DAS_USE_IMU */
