/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains the functions to get data from
 *the accelerometer.
 */

#include<math.h>

#include "das.h"

#if DAS_USE_ZIGBEE
/* Serial Driver for Output. */
#define OUTPUT          SD5
#else
#define OUTPUT          SD1
#endif /* DAS_USE_ZIGBEE*/

#if DAS_USE_IMU
/*If Mode is ACCEL_DATA then the accelerometer values
 *are read, mode is GYRO_DATA then gyrometer values
 *are read, if mode is TEMP_DATA then the temperature
 *value is read. val stores the values of the sensor
 *data.
 */
void readIMUData(uint8_t mode, IMUData *imudata) {
  uint8_t txbuf[1], rxbuf[6], i ;
  msg_t status = RDY_OK ;

  for(i = 0 ; i < 6 ; i++)
    rxbuf[i] = 0x00 ;

  switch(mode) {
    case ACCEL_DATA   : txbuf[0] = ACCEL_XOUT_H ;
                      i2cAcquireBus(&I2C_MPU) ;
                      status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 1, rxbuf, 6) ;
                      i2cReleaseBus(&I2C_MPU) ;

                      if(status != RDY_OK)
                        return ;

                      imudata->RAW_ACCEL_X = (rxbuf[0] << 8) + rxbuf[1] ;
                      imudata->RAW_ACCEL_Y = (rxbuf[2] << 8) + rxbuf[3] ;
                      imudata->RAW_ACCEL_Z = (rxbuf[4] << 8) + rxbuf[5] ;

                      imudata->ACCEL_X = - (float)imudata->RAW_ACCEL_X / imudata->ACCEL_SENS ; // rrangan as the direction on the device is on the reverse side.
                      imudata->ACCEL_Y = (float)imudata->RAW_ACCEL_Y / imudata->ACCEL_SENS ;
                      imudata->ACCEL_Z = - (float)imudata->RAW_ACCEL_Z / imudata->ACCEL_SENS ; // rrangan as the direction on the device is on the reverse side.
                      break ;

    case GYRO_DATA    : txbuf[0] = GYRO_XOUT_H ;
                      i2cAcquireBus(&I2C_MPU) ;
                      status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 1, rxbuf, 6) ;
                      i2cReleaseBus(&I2C_MPU) ;

                      if(status != RDY_OK)
                        return ;

                      imudata->RAW_GYRO_X = (rxbuf[0] << 8) + rxbuf[1] ;
                      imudata->RAW_GYRO_Y = (rxbuf[2] << 8) + rxbuf[3] ;
                      imudata->RAW_GYRO_Z = (rxbuf[4] << 8) + rxbuf[5] ;

                      imudata->GYRO_X = - ((float)imudata->RAW_GYRO_X / imudata->GYRO_SENS) * (M_PI / 180.0) ; // rrangan as the direction on the device is on the reverse side.
                      imudata->GYRO_Y = ((float)imudata->RAW_GYRO_Y / imudata->GYRO_SENS) * (M_PI / 180.0) ;
                      imudata->GYRO_Z = - ((float)imudata->RAW_GYRO_Z / imudata->GYRO_SENS) * (M_PI / 180.0) ; // rrangan as the direction on the device is on the reverse side.
                      break ;

    case IMU_TEMP_DATA  : txbuf[0] = TEMP_OUT_H ;
                          i2cAcquireBus(&I2C_MPU) ;
                          status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 1, rxbuf, 2) ;
                          i2cReleaseBus(&I2C_MPU) ;

                          if(status != RDY_OK)
                            return ;

                          imudata->RAW_TEMP = (rxbuf[0] << 8) + rxbuf[1] ;
                          break ;

    default           : return ;
  }
}

/*To read all the accelerometer and gyrometer values
 *at the same time for calculating attitude.
 *USE THIS FUNCTION ONLY WHEN ATTITUDE CALCULATION IS
 *REQUIRED.
 */
#define data_size 5
IMUData imudata_samples[data_size];
int current_imudata_sample = 0;
int first_time = 0;

void readAllIMUData(IMUData *filtered_imu_data) {
  uint8_t txbuf[1], rxbuf[14] ;
  msg_t status = RDY_OK ;
  IMUData imudata;

  txbuf[0] = ACCEL_XOUT_H ;
  i2cAcquireBus(&I2C_MPU) ;
  status = i2cMasterTransmit(&I2C_MPU, MPU_ADDR, txbuf, 1, rxbuf, 14) ;
  i2cReleaseBus(&I2C_MPU) ;
    int i=0;

  if(first_time == 0){
    for(i = 0; i < data_size; i++){
      imudata_samples[i].ACCEL_X = 0.0;
      imudata_samples[i].ACCEL_Y = 0.0;
      imudata_samples[i].ACCEL_Z = 0.0;

      imudata_samples[i].GYRO_X = 0.0;
      imudata_samples[i].GYRO_Y = 0.0;
      imudata_samples[i].GYRO_Z = 0.0;
    }
    first_time = 1;
  }

  if(status != RDY_OK)
    return ;

  imudata.RAW_ACCEL_X = (rxbuf[0] << 8 ) + rxbuf[1]  ;
  imudata.RAW_ACCEL_Y = (rxbuf[2] << 8 ) + rxbuf[3]  ;
  imudata.RAW_ACCEL_Z = (rxbuf[4] << 8 ) + rxbuf[5]  ;
  imudata.RAW_GYRO_X  = (rxbuf[8] << 8 ) + rxbuf[9]  ;
  imudata.RAW_GYRO_Y  = (rxbuf[10] << 8) + rxbuf[11] ;
  imudata.RAW_GYRO_Z  = (rxbuf[12] << 8) + rxbuf[13] ;

  // rrangan TODO - make seperate structure for SENS, make seperate function for filtering - restructure code
  imudata.ACCEL_X = - (float)imudata.RAW_ACCEL_X / filtered_imu_data->ACCEL_SENS ; // rrangan as the direction on the device is on the reverse side.
  imudata.ACCEL_Y = (float)imudata.RAW_ACCEL_Y / filtered_imu_data->ACCEL_SENS ;
  imudata.ACCEL_Z = - (float)imudata.RAW_ACCEL_Z / filtered_imu_data->ACCEL_SENS ; // rrangan as the direction on the device is on the reverse side.
  imudata.GYRO_X  = - ((float)imudata.RAW_GYRO_X / filtered_imu_data->GYRO_SENS) * (M_PI / 180.0) ; // rrangan as the direction on the device is on the reverse side.
  imudata.GYRO_Y  = ((float)imudata.RAW_GYRO_Y / filtered_imu_data->GYRO_SENS) * (M_PI / 180.0) ;
  imudata.GYRO_Z  = - ((float)imudata.RAW_GYRO_Z / filtered_imu_data->GYRO_SENS) * (M_PI / 180.0) ; // rrangan as the direction on the device is on the reverse side.

  imudata_samples[current_imudata_sample].ACCEL_X = imudata.ACCEL_X;
  imudata_samples[current_imudata_sample].ACCEL_Y = imudata.ACCEL_Y;
  imudata_samples[current_imudata_sample].ACCEL_Z = imudata.ACCEL_Z;

  imudata_samples[current_imudata_sample].GYRO_X = imudata.GYRO_X;
  imudata_samples[current_imudata_sample].GYRO_Y = imudata.GYRO_Y;
  imudata_samples[current_imudata_sample].GYRO_Z = imudata.GYRO_Z;

  current_imudata_sample++;
  if(current_imudata_sample == data_size){ /* We are implementing a circular buffer for moving average filter */
    current_imudata_sample = 0;
  }

  float sum[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  for(i = 0; i < data_size; i++){
    sum[0] += imudata_samples[i].ACCEL_X;
    sum[1] += imudata_samples[i].ACCEL_Y;
    sum[2] += imudata_samples[i].ACCEL_Z;
    sum[3] += imudata_samples[i].GYRO_X;
    sum[4] += imudata_samples[i].GYRO_Y;
    sum[5] += imudata_samples[i].GYRO_Z;
  }

  filtered_imu_data->RAW_ACCEL_X = imudata.RAW_ACCEL_X;
  filtered_imu_data->RAW_ACCEL_Y = imudata.RAW_ACCEL_Y;
  filtered_imu_data->RAW_ACCEL_Z = imudata.RAW_ACCEL_Z;
  filtered_imu_data->RAW_GYRO_X = imudata.RAW_GYRO_X;
  filtered_imu_data->RAW_GYRO_Y = imudata.RAW_GYRO_Y;
  filtered_imu_data->RAW_GYRO_Z = imudata.RAW_GYRO_Z;

  filtered_imu_data->ACCEL_X = sum[0] / data_size;
  filtered_imu_data->ACCEL_Y = sum[1] / data_size;
  filtered_imu_data->ACCEL_Z = sum[2] / data_size;
  filtered_imu_data->GYRO_X  = sum[3] / data_size;
  filtered_imu_data->GYRO_Y  = sum[4] / data_size;
  filtered_imu_data->GYRO_Z  = sum[5] / data_size;
}

/*This function calculates the pitch, roll and
 *yaw. It calls readAccelerometerData inside.
 *The angles are stored in the order pitch,
 *roll and yaw.
 *
 *TODO rohitrangan Merge Gyro Data.
 */
void eulerAngles(IMUData *imudata, float angles[3]) {
  readIMUData(ACCEL_DATA, imudata) ;

  angles[0] = asinf((-1.0f *imudata->ACCEL_X)) ;
  angles[0] *= 180.0 ;
  angles[0] /= M_PI ;

  angles[1] = atanf((imudata->ACCEL_Y / imudata->ACCEL_Z)) ;
  angles[1] *= 180.0 ;
  angles[1] /= M_PI ;

  angles[2] = 0.0 ;
}

void displayCoeffs(void) {
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro X a:- %f ", GYRO_X_A) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro X b:- %f ", GYRO_X_B) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro Y a:- %f ", GYRO_Y_A) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro Y b:- %f ", GYRO_Y_B) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro Z a:- %f ", GYRO_Z_A) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Gyro Z b:- %f\r\n", GYRO_Z_B) ;
}
#endif  /*DAS_USE_IMU */
