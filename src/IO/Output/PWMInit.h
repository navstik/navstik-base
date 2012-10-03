/*Created By - Rohit Rangan
 *Created On - 25-06-2012
 *
 *This file contains all the functions to initialize
 *the PWM driver.
 */

#ifndef PWMINIT_H_
#define PWMINIT_H_

#if HAL_USE_PWM
/*The definition of the servo outputs and which pins they are mapped to.
 *
 *SERVO1 (PB5 ) --> Timer 3 Channel 2 (Alternate Function 2)
 *SERVO2 (PA10) --> Timer 1 Channel 3 (Alternate Function 1)
 *SERVO3 (PC8 ) --> Timer 8 Channel 3 (Alternate Function 3)
 *SERVO4 (PB11) --> Timer 2 Channel 4 (Alternate Function 1)
 *SERVO5 (PB1 ) --> Timer 3 Channel 4 (Alternate Function 2)
 *SERVO6 (PB0 ) --> Timer 3 Channel 3 (Alternate Function 2)
 */
#define SERVO1_PORT			GPIOB
#define SERVO1_PIN			5
#define SERVO2_PORT			GPIOA
#define SERVO2_PIN			10
#define SERVO3_PORT			GPIOC
#define SERVO3_PIN			8
#define SERVO4_PORT			GPIOB
#define SERVO4_PIN			11
#define SERVO5_PORT			GPIOB
#define SERVO5_PIN			1
#define SERVO6_PORT			GPIOB
#define SERVO6_PIN			0

#define PWM_CLK_FREQUENCY			1000000 /* Clock Frequency of PWM Timer. Higher Frequency better resolution. 100000 = 0.1MHz */
#define PWM_PERIOD					20000	/* Time Period of PWM Cycle. 20000 = 20 ms with PWM_Clock_Frequency = 0.1 MHz */

/*The channels on which the PWM output will be found.
 *
 *SERVO1 --> Channel 2
 *SERVO2 --> Channel 3
 *SERVO3 --> Channel 3
 *SERVO4 --> Channel 4
 *SERVO5 --> Channel 4
 *SERVO6 --> Channel 3
 */
#define SERVO1_CH		1
#define SERVO2_CH		2
#define SERVO3_CH		2
#define SERVO4_CH		3
#define SERVO5_CH		3
#define SERVO6_CH		2

/*The definitions for the servos for giving the PWM output.
 */
#define SERVO1		1
#define SERVO2		2
#define SERVO3		3
#define SERVO4		4
#define SERVO5		5
#define SERVO6		6

void initPWM(void) ;

#endif 	/*HAL_USE_PWM */

#endif 	/* PWMINIT_H_ */
