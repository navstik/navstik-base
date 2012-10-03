/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *DAS (Data Acquisition System) Features can be enabled and disabled in this file.
 */

#ifndef DASCONF_H_
#define DASCONF_H_

/*For using MicroSD Card with a FAT filesystem */
#define DAS_USE_FATFS           TRUE

/*To use the onboard IMU */
#define DAS_USE_IMU             TRUE

/*To use the onboard barometer */
#define DAS_USE_BAROMETER       TRUE

/*To use the onboard magnetometer */
#define DAS_USE_MAGNETOMETER    TRUE

/*To use the onboard pressure transducer */
#define DAS_USE_DIFFP           TRUE

/*To use the onboard GPS */
#define DAS_USE_GPS	            TRUE

/*To use the shell for carrying out commands (DO NOT DISABLE) */
#define DAS_USE_SHELL           TRUE

/*To list all the I2C Sensors on board for debugging.(Default should be FALSE) */
#define DAS_USE_SCANNER         TRUE

/*To check whether the onboard FPU works */
#define DAS_USE_FPUTEST         TRUE

/*To calibrate the IMU */
#define DAS_CALIBRATE_IMU       FALSE

/*To use the RC Controller for input */
#define DAS_USE_RC              TRUE

/*To use the ZigBee protocol for serial communication */
#define DAS_USE_ZIGBEE          FALSE

#endif  /* DASCONF_H_ */
