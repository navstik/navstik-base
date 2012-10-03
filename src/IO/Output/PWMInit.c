/*Created By - Rohit Rangan
 *Created On - 25-06-2012
 *
 *This file contains all the functions to initialize the PWM driver.
 */

#include "das.h"

#if HAL_USE_PWM
/*
 *PWM configuration structures.
 */
/*pwmcfg1 - to be used for PWM1. */
#if STM32_PWM_USE_TIM1
static PWMConfig pwmcfg1 = {
  PWM_CLK_FREQUENCY,
  PWM_PERIOD,
  NULL,
  {                      /* CH3 of Timer1 for is available for PWM. Enable it and disable the rest */
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_DISABLED, NULL}
  },
  /*HW Dependent Part */
  0,
  0
};
#endif  /*STM32_PWM_USE_TIM1 */
/*pwmcfg2 - to be used for PWM2. */
#if STM32_PWM_USE_TIM2
static PWMConfig pwmcfg2 = {
  PWM_CLK_FREQUENCY,
  PWM_PERIOD,
  NULL,
  {                      /* CH4 of Timer for is available for PWM. Enable it and disable the rest. */
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  /*HW Dependent Part*/
  0,
#if STM32_PWM_USE_ADVANCED
  0
#endif  /*STM32_PWM_USE_ADVANCED */
};
#endif  /*STM32_PWM_USE_TIM2 */
/*pwmcfg3 - to be used for PWM3. */
#if STM32_PWM_USE_TIM3
static PWMConfig pwmcfg3 = {
  PWM_CLK_FREQUENCY,
  PWM_PERIOD,
  NULL,
  {                      /* CH2, CH3 and CH4 of Timer for are available for PWM. Enable them and disable the rest. */
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
  },
  /*HW Dependent Part */
  0,
#if STM32_PWM_USE_ADVANCED
  0
#endif  /*STM32_PWM_USE_ADVANCED */
};
#endif  /*STM32_PWM_USE_TIM3 */
/*pwmcfg8 - to be used for PWM8..i.e timer 8 */
#if STM32_PWM_USE_TIM8
static PWMConfig pwmcfg8 = {
  PWM_CLK_FREQUENCY,
  PWM_PERIOD,
  NULL,
  {                      /*CH3 of Timer 8 are available for PWM. Enable it and disable the rest. */
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_DISABLED, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_DISABLED, NULL}
  },
  /* HW dependent part.*/
  0,
  0   /* STM32_PWM_USE_ADVANCED is enabled which adds an additional field. */
};
#endif  /*STM32_PWM_USE_TIM8 */

/*
 * This function initializes Servo Output Pins and Connects them to PMW outputs.
 * SERVO1 (PB5 ) --> Timer 3 Channel 2 (Alternate Function 2)
 * SERVO2 (PA10) --> Timer 1 Channel 3 (Alternate Function 1)
 * SERVO3 (PC8 ) --> Timer 8 Channel 3 (Alternate Function 3)
 * SERVO4 (PB11) --> Timer 2 Channel 4 (Alternate Function 1)
 * SERVO5 (PB1 ) --> Timer 3 Channel 4 (Alternate Function 2)
 * SERVO6 (PB0 ) --> Timer 3 Channel 3 (Alternate Function 2)
 */

void initPWM(void){

  /*
   *Start PWM1 function associated with Timer 1.
   */
#if STM32_PWM_USE_TIM1
  pwmStart(&PWMD1, &pwmcfg1) ;
  /* palSetPadMode(SERVO2_PORT, SERVO2_PIN, PAL_MODE_ALTERNATE(1)) ; */
  chThdSleepMilliseconds(10) ;
#endif  /*STM32_PWM_USE_TIM1 */
  /*
   * Start PWM2 function associated with Timer 2.
   */
#if STM32_PWM_USE_TIM2
  pwmStart(&PWMD2, &pwmcfg2) ;
  /* palSetPadMode(SERVO4_PORT, SERVO4_PIN, PAL_MODE_ALTERNATE(1)) ; */
  chThdSleepMilliseconds(10) ;
#endif  /*STM32_PWM_USE_TIM2 */
  /*
   * Start PWM3 function associated with Timer 3.
   */
#if STM32_PWM_USE_TIM3
  pwmStart(&PWMD3, &pwmcfg3) ;
  /* palSetPadMode(SERVO1_PORT, SERVO1_PIN, PAL_MODE_ALTERNATE(2)) ; */
  /* palSetPadMode(SERVO5_PORT, SERVO5_PIN, PAL_MODE_ALTERNATE(2)) ; */
  /* palSetPadMode(SERVO6_PORT, SERVO6_PIN, PAL_MODE_ALTERNATE(2)) ; */
  chThdSleepMilliseconds(10) ;
#endif  /*STM32_PWM_USE_TIM3 */
  /*
   * Start PWM8 function associated with Timer 8.
   */
#if STM32_PWM_USE_TIM8
  pwmStart(&PWMD8, &pwmcfg8) ;
  /* palSetPadMode(SERVO3_PORT, SERVO3_PIN, PAL_MODE_ALTERNATE(3)) ; */
  chThdSleepMilliseconds(10) ;
#endif  /*STM32_PWM_USE_TIM1 */
}
#endif  /*HAL_USE_PWM */
