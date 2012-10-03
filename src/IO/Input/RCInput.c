/*Created By - Rohit Rangan
 *Created On - 06-07-2012
 *
 *This file contains all the functions to capture input from
 *the RC.
 */

#include "das.h"

#if DAS_USE_ZIGBEE
/* Serial Driver for Output. */
#define OUTPUT          SD5
#else
#define OUTPUT          SD1
#endif /* DAS_USE_ZIGBEE*/

#if DAS_USE_RC
#define RC_IN_RANGE(x) ((x >= 0.9) && (x <= 2.3))

float RCInput[4] ;
uint32_t start[4] = {0, 0, 0, 0} ;

/*Callback function for the interrupt on RC Channel 1.
 */
static void extcb1(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC1_PORT, RC1_PIN) == PAL_HIGH) {
    start[0] = halGetCounterValue() ;
  }
  else if((start[0] != 0) && (palReadPad(RC1_PORT, RC1_PIN) == PAL_LOW)) {
    float tmp = convertCounterToMilliseconds(start[0], halGetCounterValue()) ;
    if(RC_IN_RANGE(tmp))
      RCInput[0] = tmp ;
    start[0] = 0 ;
  }
  chSysUnlockFromIsr() ;
}

/*Callback function for the interrupt on RC Channel 2.
 */
static void extcb2(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC2_PORT, RC2_PIN) == PAL_HIGH) {
    start[1] = halGetCounterValue() ;
  }
  else if(start[1] && (palReadPad(RC2_PORT, RC2_PIN) == PAL_LOW)) {
    float tmp = convertCounterToMilliseconds(start[1], halGetCounterValue()) ;
    if(RC_IN_RANGE(tmp))
      RCInput[1] = tmp ;
    start[1] = 0 ;
  }
  chSysUnlockFromIsr() ;
}

/*Callback function for the interrupt on RC Channel 3.
 */
static void extcb3(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC3_PORT, RC3_PIN) == PAL_HIGH) {
    start[2] = halGetCounterValue() ;
  }
  else if(start[2] && (palReadPad(RC3_PORT, RC3_PIN) == PAL_LOW)) {
    float tmp = convertCounterToMilliseconds(start[2], halGetCounterValue()) ;
    if(RC_IN_RANGE(tmp))
      RCInput[2] = tmp ;
    start[2] = 0 ;
  }
  chSysUnlockFromIsr() ;
}

/*Callback function for the interrupt on RC Channel 4.
 */
static void extcb4(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC4_PORT, RC4_PIN) == PAL_HIGH) {
    start[3] = halGetCounterValue() ;
  }
  else if(start[3] && (palReadPad(RC4_PORT, RC4_PIN) == PAL_LOW)) {
    float tmp = convertCounterToMilliseconds(start[3], halGetCounterValue()) ;
    if(RC_IN_RANGE(tmp))
      RCInput[3] = tmp ;
    start[3] = 0 ;
  }
  chSysUnlockFromIsr() ;
}

/*static void extcb5(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC5_PORT, RC5_PIN) == PAL_HIGH) {
    start[4] = halGetCounterValue() ;
  }
  else if(start[4] && (palReadPad(RC5_PORT, RC5_PIN) == PAL_LOW)) {
    float tmp = halGetCounterValue() - start[4] ;
    tmp /= STM32_SYSCLK ;
    tmp *= 1000 ;
    if(RC_IN_RANGE(tmp))
      RCInput[4] = tmp ;
    start[4] = 0 ;
  }
  chSysUnlockFromIsr() ;
}

static void extcb6(EXTDriver *extp, expchannel_t channel) {
  (void)extp ;
  (void)channel ;

  chSysLockFromIsr() ;
  if(palReadPad(RC6_PORT, RC6_PIN) == PAL_HIGH) {
    start[5] = halGetCounterValue() ;
  }
  else if(start[1] && (palReadPad(RC6_PORT, RC6_PIN) == PAL_LOW)) {
    float tmp = halGetCounterValue() - start[5] ;
    tmp /= STM32_SYSCLK ;
    tmp *= 1000 ;
    if(RC_IN_RANGE(tmp))
      RCInput[5] = tmp ;
    start[5] = 0 ;
  }
  chSysUnlockFromIsr() ;
}*/

/*The EXTConfig Structure. Interrupts are monitored on RC1, RC2, RC3
 *and RC4 channels and on both edges.
 */
static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, extcb2},  /*For RC2 */
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, extcb1},  /*For RC1 */
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb3},  /*For RC3 */
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOB, extcb4},  /*For RC4 */
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

/*All the pin assignments and the initialization of the Input
 *Capture is done in this function.
 */
void initInput(void) {
  extStart(&EXTD1, &extcfg) ;
}

/*Function for debugging only. Prints all the values of the
 *input.
 */
void printValues(void) {
  chprintf((BaseSequentialStream *)&OUTPUT, "Val1:- %f\r\n", RCInput[0]) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Val2:- %f\r\n", RCInput[1]) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Val3:- %f\r\n", RCInput[2]) ;
  chprintf((BaseSequentialStream *)&OUTPUT, "Val4:- %f\r\n", RCInput[3]) ;
}

/*The input values are stored in the variable input. The first
 *element stores the input from channel 1, second from channel 2
 *and so on.
 */
void InputValues(float input[4]) {
  input[0] = RCInput[0] * 1000.0f ;
  input[1] = RCInput[1] * 1000.0f ;
  input[2] = RCInput[2] * 1000.0f ;
  input[3] = RCInput[3] * 1000.0f ;
}
#endif  /*DAS_USE_RC */
