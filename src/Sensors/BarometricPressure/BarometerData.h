/*Created By - Rohit Rangan
 *Created On - 23-06-2012
 *
 *This file contains the functions to get data from
 *the barometer.
 */

#ifndef BAROMETERDATA_H_
#define BAROMETERDATA_H_

#include "BMP180.h"

#if DAS_USE_BAROMETER
/*Calibration Coefficients for the pressure Sensor.
 *These are read each time the board is initialized.
 */

#define BARO_TEMP_DATA    1
#define  BARO_PRESSURE_DATA  2

#define EXPONENT      0.190294957f
#define SEA_LEVEL_PRESSURE  101325.0f

/*If mode is 1, the function returns the temperature value
 *in degrees Celsius. If mode is 2, the function returns
 *the pressure value in Pascals. No sleeps need to be given
 *when calling this function.
 */
void readBarometerData(BaroData *baro, uint8_t mode) ;

/*This function returns the absolute altitude above sea level
 *in meters.
 */
float getAltitude(BaroData *baro) ;
#endif  /*DAS_USE_BAROMETER */

#endif  /*BAROMETERDATA_H_ */
