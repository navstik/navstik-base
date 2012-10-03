/*Created By - Rohit Rangan
 *Created On - 02-07-2012
 *
 *This file contains all the functions to start
 *the PWM driver.
 */

#include "das.h"

#if HAL_USE_PWM
static WORKING_AREA(PWM_WA, 128) ;

/*This thread starts PWM on Servo 4 and varies the
 *pulse width from 1000-2000 ms in increments of 100.
 */
static msg_t PWMThread(void *arg) {
  (void)arg ;
  chRegSetThreadName("PWMTHREAD") ;

  uint32_t width = 1000 ;
  while(TRUE) {
    pwmEnableChannelI(&PWMD2, SERVO4, PWM_FRACTION_TO_WIDTH(&PWMD2, PWM_PERIOD, width)) ;
    chThdSleepMilliseconds(100) ;
    pwmDisableChannelI(&PWMD2, SERVO4) ;

    if(width > 2000)
      width = 1000 ;
    else
      width += 100 ;
  }

  return 0 ;
}

void startPWMThread(void) {
  chThdCreateStatic(PWM_WA, sizeof(PWM_WA), NORMALPRIO, PWMThread, NULL) ;
}

/*This function starts the Servo which is specified
 *by the parameter servo. The parameter wid stores the
 *width of the PWM pulse. Width is between 1000-2000 ms.
 */
void startServo(int servo, uint32_t wid) {
  switch(servo) {
#if STM32_PWM_USE_TIM3
    case SERVO1  : pwmEnableChannelI(&PWMD3, SERVO1_CH, PWM_FRACTION_TO_WIDTH(&PWMD3, PWM_PERIOD, wid)) ;
          break ;
#endif  /*STM32_PWM_USE_TIM3 */

#if STM32_PWM_USE_TIM1
    case SERVO2  : pwmEnableChannelI(&PWMD1, SERVO2_CH, PWM_FRACTION_TO_WIDTH(&PWMD1, PWM_PERIOD, wid)) ;
          break ;
#endif  /*STM32_PWM_USE_TIM1 */

#if STM32_PWM_USE_TIM8
    case SERVO3  : pwmEnableChannelI(&PWMD8, SERVO3_CH, PWM_FRACTION_TO_WIDTH(&PWMD8, PWM_PERIOD, wid)) ;
          break ;
#endif  /*STM32_PWM_USE_TIM8 */

#if STM32_PWM_USE_TIM2
    case SERVO4  : pwmEnableChannelI(&PWMD2, SERVO4_CH, PWM_FRACTION_TO_WIDTH(&PWMD2, PWM_PERIOD, wid)) ;
          break ;
#endif  /*STM32_PWM_USE_TIM2 */

#if STM32_PWM_USE_TIM3
    case SERVO5  : pwmEnableChannelI(&PWMD3, SERVO5_CH, PWM_FRACTION_TO_WIDTH(&PWMD3, PWM_PERIOD, wid)) ;
          break ;
#endif  /*STM32_PWM_USE_TIM3 */

#if STM32_PWM_USE_TIM3
    case SERVO6  : pwmEnableChannelI(&PWMD3, SERVO6_CH, PWM_FRACTION_TO_WIDTH(&PWMD3, PWM_PERIOD, wid)) ;
          break ;
#endif /*STM32_PWM_USE_TIM3 */
    default : return ;
  }
}

/*This function stops the Servo which is specified
 *by the parameter servo.
 */
void stopServo(int servo) {
  switch(servo) {
#if STM32_PWM_USE_TIM3
    case SERVO1  : pwmDisableChannelI(&PWMD3, SERVO1_CH) ;
          break ;
#endif /*STM32_PWM_USE_TIM3 */

#if STM32_PWM_USE_TIM1
    case SERVO2  : pwmDisableChannelI(&PWMD1, SERVO2_CH) ;
          break ;
#endif /*#if STM32_PWM_USE_TIM1 */

#if STM32_PWM_USE_TIM8
    case SERVO3  : pwmDisableChannelI(&PWMD8, SERVO3_CH) ;
          break ;
#endif /*STM32_PWM_USE_TIM8 */

#if STM32_PWM_USE_TIM2
    case SERVO4  : pwmDisableChannelI(&PWMD2, SERVO4_CH) ;
          break ;
#endif /*STM32_PWM_USE_TIM2*/

#if STM32_PWM_USE_TIM3
    case SERVO5  : pwmDisableChannelI(&PWMD3, SERVO5_CH) ;
          break ;
#endif  /*STM32_PWM_USE_TIM3 */

#if STM32_PWM_USE_TIM3
    case SERVO6  : pwmDisableChannelI(&PWMD3, SERVO6_CH) ;
          break ;
#endif  /*STM32_PWM_USE_TIM3 */
    default : return ;
  }
}
#endif  /*HAL_USE_PWM */
