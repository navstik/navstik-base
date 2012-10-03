/*
 * HMC5883.c
 *
 *  Created on: Apr 26, 2012
 *      Author: sapan
 */

#include "das.h"

#if DAS_USE_MAGNETOMETER
MagData MD1 ;

/*
 * average = No. of samples to be average per measurement
 * ODR = Output Data Rate
 * Mode = Normal, Positive Bias or Negative Bias...Refer to Data Sheet for further details
 * Gain = Range of Magnetic Field
 * OP_Mode = Continuous, Single measurement or Idle mode
 */

void initialize_HMC(MagData *magd, MagConfig *magcfg) {
  uint8_t hmc_txbuf[2], hmc_rxbuf[1] ;
  hmc_txbuf[0] = CONFIG_A ;
  hmc_txbuf[1] = 0x00 ;
  /*Set value for CONFIG_A register */
  hmc_txbuf[1] |= magcfg->SAMPLE_AVG ;
  hmc_txbuf[1] = hmc_txbuf[1] << 5 ;
  hmc_txbuf[1] |= (magcfg->ODR << 2) ;
  hmc_txbuf[1] |= magcfg->MODE ;
  i2cAcquireBus(&I2C_HMC) ;
  i2cMasterTransmit(&I2C_HMC, HMC_ADDR, hmc_txbuf, 2, hmc_rxbuf, 0) ;
  i2cReleaseBus(&I2C_HMC) ;

  hmc_txbuf[0] = CONFIG_B ;
  hmc_txbuf[1] = 0x00 ;
  /*Set value for CONFIG_B register */
  hmc_txbuf[1] |= (magcfg->RANGE << 5) ;
  i2cAcquireBus(&I2C_HMC) ;
  i2cMasterTransmit(&I2C_HMC, HMC_ADDR, hmc_txbuf, 2, hmc_rxbuf, 0) ;
  i2cReleaseBus(&I2C_HMC) ;

  /*Put Address of MODE register in hmc_txbuf[0] */
  hmc_txbuf[0] = OP_MODE ;
  /*Set value for MODE register */
  hmc_txbuf[1] = magcfg->MEASUREMENT_MODE ;
  i2cAcquireBus(&I2C_HMC) ;
  i2cMasterTransmit(&I2C_HMC, HMC_ADDR, hmc_txbuf, 2, hmc_rxbuf, 0) ;
  i2cReleaseBus(&I2C_HMC) ;

  if(magcfg->RANGE == 0)
    magd->RANGE = 0.73 ;
  if(magcfg->RANGE == 1)
    magd->RANGE = 0.92 ;
  if(magcfg->RANGE == 2)
    magd->RANGE = 1.22 ;
  if(magcfg->RANGE == 3)
    magd->RANGE = 1.52 ;
  if(magcfg->RANGE == 4)
    magd->RANGE = 2.27 ;
  if(magcfg->RANGE == 5)
    magd->RANGE = 2.56 ;
  if(magcfg->RANGE == 6)
    magd->RANGE = 3.03 ;
  if(magcfg->RANGE == 7)
    magd->RANGE = 4.35 ;

  magcfg->MEASUREMENT_MODE = magd->MEASUREMENT_MODE ;
}
#endif  /*DAS_USE_MAGNETOMETER */
