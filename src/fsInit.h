/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains the definitons for fsInit.c
 */

#include "das.h"

#ifndef FSINIT_H_
#define FSINIT_H_

#if DAS_USE_FATFS
/**
 * @brief FS object.
 */
extern FATFS MMC_FS;

/**
 * MMC driver instance.
 */
extern MMCDriver MMCD1;

/* FS mounted and ready.*/
extern bool_t fs_ready;

/* Generic large buffer.*/
extern uint8_t fbuff[1024];

/*Function to scan files present on the MicroSD Card
 *and display them.
 */
FRESULT scan_files(BaseSequentialStream *chp, char *path) ;

/*Starts the SPI2 Driver and the MMC object */
void startMMC(void) ;

#endif  /*DAS_USE_FATFS */

#endif  /*FSINIT_H_ */
