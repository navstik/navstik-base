/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains the functions to get data from
 *the accelerometer.
 */

#ifndef IMUDATA_H_
#define IMUDATA_H_

#include "MPU60X0.h"
#include "das_conf.h"

#if DAS_USE_IMU
/*Regression Coefficients for the Accelerometer and
 *the Gyroscope.
 */
#define ACCEL_X_A    reg_coeffs[0]
#define ACCEL_X_B    reg_coeffs[1]
#define ACCEL_Y_A    reg_coeffs[2]
#define ACCEL_Y_B    reg_coeffs[3]
#define ACCEL_Z_A    reg_coeffs[4]
#define ACCEL_Z_B    reg_coeffs[5]
#define GYRO_X_A     reg_coeffs[6]
#define GYRO_X_B     reg_coeffs[7]
#define GYRO_Y_A     reg_coeffs[8]
#define GYRO_Y_B     reg_coeffs[9]
#define GYRO_Z_A     reg_coeffs[10]
#define GYRO_Z_B     reg_coeffs[11]

/*To get data from the different sensors on the IMU.
 */
#define ACCEL_DATA     1
#define GYRO_DATA      2
#define IMU_TEMP_DATA  3

/*If Mode is ACCEL_DATA then the accelerometer values
 *are read, mode is GYRO_DATA then gyroscope values
 *are read, if mode is TEMP_DATA then the temperature
 *value is read. val stores the values of the sensor
 *data.
 */
void readIMUData(uint8_t mode, IMUData *imudata) ;

/*To read all the accelerometer and gyroscope values
 *at the same time for calculating attitude.
 *USE THIS FUNCTION ONLY WHEN ATTITUDE CALCULATION IS
 *REQUIRED.
 */
void readAllIMUData(IMUData *imudata) ;
/*This function calculates the pitch, roll and yaw. It
 *calls readAccelerometerData inside. The angles are
 *stored in the order pitch, roll and yaw.
 */
void eulerAngles(IMUData *imudata, float angles[3]) ;

void displayCoeffs(void) ;
#endif  /*DAS_USE_IMU */

#endif  /*IMUDATA_H_ */
