/*
 * ms4515.h
 *
 *  Created on: Apr 27, 2012
 *      Author: Sapan, Rohit Rangan
 */

#ifndef MS4515_H_
#define MS4515_H_

#include "das_conf.h"

#if DAS_USE_DIFFP
/*Bi-directional bus lines are implemented by the devices (master and slave)
 * using open-drain output stages and a pull-up resistor connected to the
 * positive supply voltage*/

#define MS4515_ADDR    0b0101000
#define I2C_MS4515     I2CD3

void read_ms4515(void);

/*Response from sensor depends on how many clock cycles master sends after sending device address
 * i.e. when till master sends NACK and stop condition device will keep sending data.
 * First two bits of first received byte indicates status of the data (stale or valid data).
 * 00 indicates normal operation
 * 10 indicates stale data that has already been fetched
 */
#endif  /*DAS_USE_DIFFP */

#endif /* MS4515_H_ */
