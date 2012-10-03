/*Created By - Rohit Rangan
 *Created On - 22-06-2012
 *
 *This file contains the functions to get data from
 *the magnetometer.
 */

#ifndef MAGNETOMETERDATA_H_
#define MAGNETOMETERDATA_H_

#include "HMC5883.h"
#include "das_conf.h"

#if DAS_USE_MAGNETOMETER
#define MAG_RANGE hmc_range

/*The raw values are stored in val. To convert to microTesla,
 *multiply val[i] by MAG_RANGE.
 */
void readMagnetometerData(MagData *magd) ;

#if DAS_USE_IMU
/*Returns the heading of the board in degrees.
 *000 -> North.
 *090 -> East.
 *180 -> South.
 *270 -> West.
 */
float getHeading(IMUData *imudata, MagData *magd) ;
#endif /*DAS_USE_IMU */

#endif /*DAS_USE_MAGNETOMETER */

#endif /*MAGNETOMETERDATA_H_ */
