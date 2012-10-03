/*
 * hmc5883.h
 *
 *  Created on: Apr 26, 2012
 *      Author: sapan
 */

#ifndef HMC5883_H_
#define HMC5883_H_

#include "das_conf.h"

#if DAS_USE_MAGNETOMETER
#define HMC_ADDR  0b0011110
#define I2C_HMC    I2CD3

#define CONFIG_A   0x00      /* Read-Write Access. Sets Data Output rate and Measurement Configuration */
#define CONFIG_B   0x01      /* Read-Write Access. Sets Device Gain i.e. Range of Magnetic Field */
#define OP_MODE    0x02      /* Read-Write Access. Sets Operating mode of the device. Continuous, Single and Idle */
#define OUT_X_MSB  0x03      /* Read Only */
#define OUT_X_LSB  0x04      /* Read Only */
#define OUT_Z_MSB  0x05      /* Read Only */
#define OUT_Z_LSB  0x06      /* Read Only */
#define OUT_Y_MSB  0x07      /* Read Only */
#define OUT_Y_LSB  0x08      /* Read Only */
#define STATUS_MAG 0x09      /* Read Only. Indicates device status. Alternatively DRDY Pin can be used */
#define ID_A       0x10      /* Read Only. ASCII value H */
#define ID_B       0x11      /* Read Only. ASCII value 4 */
#define ID_C       0x12      /* Read Only. ASCII value 3 */

#define HMC_DRDY_PORT  GPIOC
#define HMC_DRDY_PIN   14

#define AVERAGE0  0
#define AVERAGE2  1
#define AVERAGE4  2
#define AVERAGE8  3

#define ODR0  0
#define ODR1  1
#define ODR2  2
#define ODR3  3
#define ODR4  4
#define ODR5  5
#define ODR6  6

#define MODE_NORMAL  0
#define MODE_PBIAS   1
#define MODE_NBIAS   2

#define RANGE_880mGa   0
#define RANGE_1300mGa  1
#define RANGE_1900mGa  2
#define RANGE_2500mGa  3
#define RANGE_4000mGa  4
#define RANGE_4700mGa  5
#define RANGE_5600mGa  6
#define RANGE_8100mGa  7

#define OP_MODE_CONTINUOUS  0
#define OP_MODE_SINGLE      1
#define OP_MODE_IDLE        2

typedef struct {
  uint8_t SAMPLE_AVG ;
  uint8_t ODR ;
  uint8_t MODE ;
  uint8_t RANGE ;
  uint8_t MEASUREMENT_MODE ;
}MagConfig;

typedef struct {
  float RANGE ;
  int16_t RAW_MAG_X ;
  int16_t RAW_MAG_Y ;
  int16_t RAW_MAG_Z ;
  float MAG_X ;
  float MAG_Y ;
  float MAG_Z ;
  uint8_t MEASUREMENT_MODE ;
}MagData;

extern MagData MD1 ;

void initialize_HMC(MagData *magd, MagConfig *magcfg) ;
#endif  /*DAS_USE_MAGNETOMETER */

#endif /* HMC5883_H_ */
