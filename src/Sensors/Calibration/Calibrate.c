/*Created By - Rohit Rangan
 *Created On - 08-07-2012
 *
 *All the function to calibrate the different sensors on DAS.
 */

#include "das.h"

#if DAS_CALIBRATE_IMU
void calibrateIMU(float coeff[12]) {
  float th[SAMPLES], pr[SAMPLES], data[3], regPara[2] ;
  uint8_t i ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Calibrating Gyroscope....Keep the board stable..\r\n") ;
  chThdSleepMilliseconds(1000) ;

  for(i = 0 ; i < SAMPLES ; i++) {
    readIMUData(GYRO_RAW_DATA, data) ;
    pr[i] = data[0] ;
    chThdSleepMilliseconds(2) ;
  }
  coeff[6] = (-1.0f * average(pr, SAMPLES)) ;
  coeff[7] = 1.0f ;

  for(i = 0 ; i < SAMPLES ; i++) {
    readIMUData(GYRO_RAW_DATA, data) ;
    pr[i] = data[1] ;
    chThdSleepMilliseconds(2) ;
  }
  coeff[8] = (-1.0f * average(pr, SAMPLES)) ;
  coeff[9] = 1.0f ;

  for(i = 0 ; i < SAMPLES ; i++) {
    readIMUData(GYRO_RAW_DATA, data) ;
    pr[i] = data[2] ;
    chThdSleepMilliseconds(2) ;
  }
  coeff[10] = (-1.0f * average(pr, SAMPLES)) ;
  coeff[11] = 1.0f ;

  coeff[0] = 0.0f ;
  coeff[1] = 1.0f ;
  coeff[2] = 0.0f ;
  coeff[3] = 1.0f ;
  coeff[4] = 0.0f ;
  coeff[5] = 1.0f ;
}
#endif  /*DAS_CALIBRATE_IMU */
