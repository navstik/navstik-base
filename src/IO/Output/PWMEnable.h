/*Created By - Rohit Rangan
 *Created On - 02-07-2012
 *
 *This file contains all the functions to start
 *the PWM driver.
 */

#ifndef PWMENABLE_H_
#define PWMENABLE_H_

#if HAL_USE_PWM
void startPWMThread(void) ;

/*This function starts the Servo which is specified
 *by the parameter servo. The parameter wid stores the
 *width of the PWM pulse. Width is between 1000-2000 ms.
 */
void startServo(int servo, uint32_t wid) ;

/*This function stops the Servo which is specified
 *by the parameter servo.
 */
void stopServo(int servo) ;
#endif	/*HAL_USE_PWM */

#endif	/*PWMENABLE_H_ */
