/*Created By - Rohit Rangan
 *Created On - 06-07-2012
 *
 *This file contains all the functions to capture input from
 *the RC.
 */

#ifndef RCINPUT_H_
#define RCINPUT_H_

#include "das_conf.h"

#if DAS_USE_RC
/*The definition of the RC inputs and which pins they are mapped to.
 *
 *RC1 (PA7 )
 *RC2 (PA6 )
 *RC3 (PB14)
 *RC4 (PB15)
 *RC5 (PC6 )
 *RC6 (PC7 )
 */
#define RC1_PORT    GPIOA
#define RC1_PIN      7
#define RC2_PORT    GPIOA
#define RC2_PIN      6
#define RC3_PORT    GPIOB
#define RC3_PIN      14
#define RC4_PORT    GPIOB
#define RC4_PIN      15
#define RC5_PORT    GPIOC
#define RC5_PIN      6
#define RC6_PORT    GPIOC
#define RC6_PIN      7

/*All the pin assignments and the initialization of the Input
 *Capture is done in this function.
 */
void initInput(void) ;
/*Function for debugging only. Prints all the values of the
 *input.
 */
void printValues(void) ;
/*The input values are stored in the variable input. The first
 *element stores the input from channel 1, second from channel 2
 *and so on.
 */
void InputValues(float input[4]) ;

#endif  /*DAS_USE_RC */

#endif  /*RCINPUT_H_ */
