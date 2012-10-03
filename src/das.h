/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains all the functions required to start
 *different drivers like I2C, SPI and USART.
 */

#include "das_conf.h"

#ifndef DAS_H_
#define DAS_H_

#include "ch.h"
#include "ff.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"

#include "utils.h"
#include "fsInit.h"
#include "RCInput.h"
#include "PWMInit.h"
#include "IMUData.h"
#include "Calibrate.h"
#include "PWMEnable.h"
#include "das_conf.h"
#include "shellCommands.h"
#include "BarometerData.h"
#include "MagnetometerData.h"
#include "MS4515.h"

typedef struct {
#if DAS_USE_IMU
  IMUConfig   imucfg   ;
  IMUData   *imudata ;
#endif  /*DAS_USE_IMU */

#if DAS_USE_MAGNETOMETER
  MagConfig   magcfg   ;
  MagData   *magdata ;
#endif  /*DAS_USE_MAGNETOMETER*/

#if DAS_USE_BAROMETER
  uint8_t   barocfg  ;
  BaroData   *barodata ;
#endif  /*DAS_USE_BAROMETER */
} Sensors;

/*Only done as MMC needs this */
#if DAS_USE_FATFS
extern const SPIConfig ls_spicfg ;

extern const SPIConfig hs_spicfg ;

/*Initializes SPI2 Driver */
void SPI2Init(void) ;
#endif  /*DAS_USE_FATFS */

#if DAS_USE_MAGNETOMETER || DAS_USE_BAROMETER || DAS_USE_IMU
/*Initializes I2C Drivers 1 and 3 */
void I2CInitialize(void) ;

void SensorInitialize(Sensors *sensor) ;
#endif  /*DAS_USE_MAGNETOMETER | DAS_USE_BAROMETER | DAS_USE_IMU */

#if DAS_USE_SCANNER
void i2cScanner(I2CDriver *FindI2C, const char *driverName) ;
#endif  /*DAS_USE_SCANNER */

/*Initializes SerialDriver1 for Output and Input */
void OUTPUTInit(void) ;

/* PID function for controlling output to motors */
void control(BaseSequentialStream* bss);

#endif /* DAS_H_ */
