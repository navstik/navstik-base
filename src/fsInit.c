/*Created By - Rohit Rangan
 *Created On - 02-06-2012
 *
 *This file contains all the FAT FS related functions
 *for using the MicroSD Card.
 */

#include <stdio.h>
#include <string.h>

#include "das.h"

#if DAS_USE_FATFS
/**
 * @brief FS object.
 */
FATFS MMC_FS;

/**
 * MMC driver instance.
 */
MMCDriver MMCD1;

/* FS mounted and ready.*/
bool_t fs_ready = FALSE;

/* Generic large buffer.*/
uint8_t fbuff[1024];

/* MMC/SD over SPI driver configuration.*/
static MMCConfig mmccfg = {&SPID2, &ls_spicfg, &hs_spicfg};

/*Function to scan files present on the MicroSD Card
 *and display them.
 */
FRESULT scan_files(BaseSequentialStream *bss, char *path) {
  FRESULT res;
  FILINFO fno;
  DIR dir;
  int i;
  char *fn;
  res = f_opendir(&dir, path);

  if(res == FR_OK) {
    i = strlen(path);
    for( ; ; ) {
      res = f_readdir(&dir, &fno);
      if(res != FR_OK || fno.fname[0] == 0)
        break;
      if(fno.fname[0] == '.')
        continue;
      fn = fno.fname;
      if(fno.fattrib & AM_DIR) {
        path[i++] = '/';
        strcpy(&path[i], fn);
        sprintf(&path[i], "/%s", fn);
        res = scan_files(bss, path);
        if(res != FR_OK)
          break;
        path[i] = 0;
      }
      else {
        chprintf(bss, "%s/%s\r\n", path, fn);
      }
    }
  }
  return res;
}

/*Starts the SPI2 Driver and the MMC object */
void startMMC(void) {
    /*
     * Initializes the MMC driver to work with SPI2.
     */
    SPI2Init() ;
    mmcObjectInit(&MMCD1);
    mmcStart(&MMCD1, &mmccfg);
}
#endif
