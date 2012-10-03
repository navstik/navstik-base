/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains all the shell commands and shell
 *structures required to start the DAS shell.
 */
/* 18-06-2012 - Riya Ray - The functions fpuTest and cmd_fputest have been added */

#include "das.h"

#ifndef SHELLCOMMANDS_H_
#define SHELLCOMMANDS_H_

#if DAS_USE_SHELL
#define SHELL_WA_SIZE   THD_WA_SIZE(2048)

extern const ShellCommand commands[] ;

extern const ShellConfig shell_cfg1 ;

#if CORTEX_USE_FPU && DAS_USE_FPUTEST
float fpuTest(BaseSequentialStream *bss, char *operand1, char oper, char *operand2);

void cmd_fputest(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*CORTEX_USE_FPU && DAS_USE_FPUTEST */

void cmd_mem(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_threads(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_clear(BaseSequentialStream *bss, int argc, char *argv[]);

#if DAS_USE_FATFS
void cmd_mount(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_unmount(BaseSequentialStream *bss, int argc, char *argv[]);

void cmd_tree(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_FATFS */

#if DAS_USE_IMU
void cmd_imu(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_ACCELEROMETER */

#if DAS_USE_MAGNETOMETER
void cmd_magnetometer(BaseSequentialStream *bss, int argc, char *argv[]);
#endif /*DAS_USE_MAGNETOMETER */

#if DAS_USE_BAROMETER
void cmd_barometer(BaseSequentialStream *bss, int argc, char *argv[]);
#endif /*DAS_USE_BAROMETER */

#if HAL_USE_PWM
void cmd_pwmOut(BaseSequentialStream *bss, int argc, char *argv[]);
void cmd_pwmScan(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*HAL_USE_PWM */

#if HAL_USE_ICU
void cmd_icu(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*HAL_USE_ICU */

#if DAS_USE_DIFFP
void cmd_diffp(BaseSequentialStream *bss, int argc, char *argv[]);
#endif /*DAS_USE_DIFFP */

#if DAS_USE_SCANNER
void cmd_i2cScan(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_SCANNER */

#if DAS_USE_GPS
void cmd_gps(BaseSequentialStream *bss, int argc, char *argv[]);
#endif  /*DAS_USE_GPS */

#endif  /*DAS_USE_SHELL */

#endif  /*SHELLCOMMANDS_H_ */
