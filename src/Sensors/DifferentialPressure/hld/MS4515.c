/*
 * ms4515.c
 *
 *  Created on: Apr 27, 2012
 *      Author: Sapan, Rohit Rangan
 */

#include "das.h"

#if DAS_USE_ZIGBEE
/* Serial Driver for Output. */
#define OUTPUT          SD5
#else
#define OUTPUT          SD1
#endif /* DAS_USE_ZIGBEE*/

#if DAS_USE_DIFFP
uint8_t MS4515_rxbuf[20], MS4515_txbuf[20], MS4515_status = 0;
int16_t dp_raw = 0, dT_raw = 0;

void read_ms4515(void){
  //float Differential_pressure = 0
  float Temperature_MS4515 = 0;
  //chprintf((BaseSequentialStream *)&OUTPUT, "Inside Diff open drain mode and  pressure measurement address new %x \r\n", MS4515_addr);

  /*Acquire I2C bus before starting I2C communication - Pending */
  i2cMasterReceive(&I2C_MS4515, MS4515_ADDR, MS4515_rxbuf, 4);
  /*Release I2C bus once communication is done - Pending */

  /*Isolate status, temperature and pressure data */
  MS4515_status = MS4515_rxbuf[0] >> 6;
  dp_raw = (MS4515_rxbuf[0] << 8) + MS4515_rxbuf[1];
  dp_raw = 0x3FFF & dp_raw;
  dT_raw = (MS4515_rxbuf[2] << 8) + MS4515_rxbuf[3];
  dT_raw = (0xFFE0 & dT_raw)>>5;
  Temperature_MS4515 = ((200*dT_raw)/2047) - 50;

  chprintf((BaseSequentialStream *)&OUTPUT,"MS4515 raw bytes output  %x , %x , %x , %x, %d , %d , %d \r\n", MS4515_rxbuf[0], MS4515_rxbuf[1], MS4515_rxbuf[2],MS4515_rxbuf[3], dp_raw, dT_raw, Temperature_MS4515);
}
#endif  /*DAS_USE_DIFFP */
