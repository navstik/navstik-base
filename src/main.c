/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *The file which contains the main function.
 */

#include "das.h"
#if DAS_USE_ZIGBEE
/* Serial Driver for Output. */
#define OUTPUT          SD5
#else
#define OUTPUT          SD1
#endif /* DAS_USE_ZIGBEE*/

/*
 * Application entry point.
 */

int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit() ;
  chSysInit() ;

  /*
   * Activates the SerialDriver for Output and I2C Drivers.
   */
  OUTPUTInit() ;
#if DAS_USE_ZIGBEE
  chThdSleepMilliseconds(500) ; /* needs more time for Zigbee handshake */ /*TODO move these hard coded values to header file */
#else
  chThdSleepMilliseconds(10) ;
#endif
  chprintf((BaseSequentialStream *)&OUTPUT, "\r\nInitializing...\r\n") ;
#if DAS_USE_IMU || DAS_USE_BAROMETER || DAS_USE_MAGNETOMETER
  Sensors init = {
#if DAS_USE_IMU
    {
      FS_SEL_250,
      AFS_SEL_2g,
      0x09
    },
    &IMUD1,
#endif  /*DAS_USE_IMU */

#if DAS_USE_MAGNETOMETER
    {
      AVERAGE4,
      ODR6,
      MODE_NORMAL,
      RANGE_880mGa,
      OP_MODE_SINGLE
    },
    &MD1,
#endif  /*DAS_USE_MAGNETOMETER */

#if DAS_USE_BAROMETER
    ULTRA_HIGH_RESOLUTION,
    &BD1
#endif  /*DAS_USE_BAROMETER*/
  };
  I2CInitialize() ;
  chThdSleepMilliseconds(10) ;
  SensorInitialize(&init) ;
  chThdSleepMilliseconds(10) ;
#endif  /*DAS_USE_IMU || DAS_USE_BAROMETER || DAS_USE_MAGNETOMETER */

#if DAS_USE_RC
  initInput() ;
  chThdSleepMilliseconds(10) ;
#endif  /*HAL_USE_ICU */

#if HAL_USE_PWM
  initPWM() ;
  chThdSleepMilliseconds(10) ;
#endif  /*HAL_USE_PWM */

#if DAS_USE_FATFS
  startMMC() ;
  chThdSleepMilliseconds(10) ;
#endif  /*DAS_USE_FATFS */
  /*
   * Shell manager initialization.
   */
#if DAS_USE_SHELL
  Thread *shelltp = NULL ;
  shellInit() ;
#endif  /*DAS_USE_SHELL */

  while(TRUE) {

#if DAS_USE_SHELL
    if (!shelltp)
      shelltp = shellCreate(&shell_cfg1, SHELL_WA_SIZE, NORMALPRIO) ;
    else if (chThdTerminated(shelltp)) {
      chThdRelease(shelltp) ; /* Recovers memory of the previous shell.   */
      shelltp = NULL ; /* Triggers spawning of a new shell.        */
    }
#endif  /*DAS_USE_SHELL */


  }

  return 0 ;
}
