/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for STMicroelectronics STM32F4-Discovery board.
 */

/*
 * Board identifier.
 */
#define BOARD_NAVSTIK
#define BOARD_NAME              "NAVSTIK"

/*
 * Board frequencies.
 * NOTE: The LSE crystal is not fitted by default on the board.
 */
#define STM32_LSECLK            0
#define STM32_HSECLK            25000000

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD               300

/*
 * MCU type as defined in the ST header file stm32f4xx.h.
 */
#define STM32F4XX

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_2M(n)            (0U << ((n) * 2))
#define PIN_OSPEED_25M(n)           (1U << ((n) * 2))
#define PIN_OSPEED_50M(n)           (2U << ((n) * 2))
#define PIN_OSPEED_100M(n)          (3U << ((n) * 2))
#define PIN_PUDR_FLOATING(n)        (0U << ((n) * 2))
#define PIN_PUDR_PULLUP(n)          (1U << ((n) * 2))
#define PIN_PUDR_PULLDOWN(n)        (2U << ((n) * 2))
#define PIN_AFIO_AF(n, v)           ((v##U) << ((n % 8) * 4))

/*
 * IO pins assignments.
 */
/*
 * Port A setup.
 */
#define GPIOA_CS_SDCARD         0 /* GPIOA_CS_SDCARD or GPIOA_CS_SPI_FLASH */
#define GPIOA_BATTERY_CURRENT   1 /* ADC ADC123_IN2 */
#define GPIOA_GPS_UART_TX       2 /* UART2 (AF7) */
#define GPIOA_GPS_UART_RX       3 /* UART2 (AF7) */
#define GPIOA_GPS_PWR_ENABLE    4
#define GPIOA_CS_SPI_FLASH      5 /* GPIOA_CS_SDCARD or GPIOA_CS_SPI_FLASH */
#define GPIOA_RC2               6 /* PWM RC Input from controller TIMER 3 channel 1 (AF2)*/
#define GPIOA_RC1               7 /* PWM RC Input from controller TIMER 3 channel 2 (AF2)*/
#define GPIOA_I2C3_SCL          8 /* I2C 3 clock (AF4)*/
#define GPIOA_USB_FS_VBUS       9
#define GPIOA_SERVO2            10/* PWM output for Servo2 TIMER 1 channel 3 (AF1) */
#define GPIOA_USB_FS_DM         11/* AF(10) */
#define GPIOA_USB_FS_DP         12/* AF(10) */
#define GPIOA_SWDIO             13/* AF(0) */
#define GPIOA_SWCLK             14/* AF(0) */
#define GPIOA_JTDI              15/* AF(0) */

/* Port A mode setup */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(GPIOA_CS_SDCARD) |      \
                                     PIN_MODE_ANALOG(GPIOA_BATTERY_CURRENT) |\
                                     PIN_MODE_ALTERNATE(GPIOA_GPS_UART_TX) | \
                                     PIN_MODE_ALTERNATE(GPIOA_GPS_UART_RX) | \
                                     PIN_MODE_OUTPUT(GPIOA_GPS_PWR_ENABLE) | \
                                     PIN_MODE_OUTPUT(GPIOA_CS_SPI_FLASH) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_RC2) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_RC1) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_I2C3_SCL) |    \
                                     PIN_MODE_INPUT(GPIOA_USB_FS_VBUS) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SERVO2) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_FS_DM) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_FS_DP) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |       \
                                     PIN_MODE_ALTERNATE(GPIOA_JTDI))
#define VAL_GPIOA_OTYPER            PIN_OTYPE_OPENDRAIN(GPIOA_I2C3_SCL)
#define VAL_GPIOA_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOA_PUPDR             (PIN_PUDR_PULLDOWN(GPIOA_CS_SDCARD) |       \
                                     PIN_PUDR_FLOATING(GPIOA_BATTERY_CURRENT) | \
                                     PIN_PUDR_FLOATING(GPIOA_GPS_UART_TX) |     \
                                     PIN_PUDR_FLOATING(GPIOA_GPS_UART_RX) |     \
                                     PIN_PUDR_PULLUP(GPIOA_GPS_PWR_ENABLE) |    \
                                     PIN_PUDR_PULLDOWN(GPIOA_CS_SPI_FLASH) |    \
                                     PIN_PUDR_PULLDOWN(GPIOA_RC2) |             \
                                     PIN_PUDR_PULLDOWN(GPIOA_RC1) |             \
                                     PIN_PUDR_FLOATING(GPIOA_I2C3_SCL) |        \
                                     PIN_PUDR_FLOATING(GPIOA_USB_FS_VBUS) |     \
                                     PIN_PUDR_PULLDOWN(GPIOA_SERVO2) |          \
                                     PIN_PUDR_FLOATING(GPIOA_USB_FS_DM) |       \
                                     PIN_PUDR_PULLUP(GPIOA_USB_FS_DP) |         \
                                     PIN_PUDR_FLOATING(GPIOA_SWDIO) |           \
                                     PIN_PUDR_FLOATING(GPIOA_SWCLK) |           \
                                     PIN_PUDR_FLOATING(GPIOA_JTDI))
#define VAL_GPIOA_ODR               0xFFFFFFFF
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_GPS_UART_TX, 7) | \
                                     PIN_AFIO_AF(GPIOA_GPS_UART_RX, 7) | \
                                     PIN_AFIO_AF(GPIOA_RC2, 2) |         \
                                     PIN_AFIO_AF(GPIOA_RC1, 2))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_I2C3_SCL, 4) |    \
                                     PIN_AFIO_AF(GPIOA_SERVO2, 1) |      \
                                     PIN_AFIO_AF(GPIOA_USB_FS_DM, 10) |  \
                                     PIN_AFIO_AF(GPIOA_USB_FS_DP, 10) |  \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0) | 	     \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0) | 	     \
                                     PIN_AFIO_AF(GPIOA_JTDI, 0))
/*
 * Port B setup.
 */
#define GPIOB_SERVO6            0 /* PWM output for Servo6 TIMER 3 channel 3 (AF2) */
#define GPIOB_SERVO5            1 /* PWM output for Servo5 TIMER 3 channel 4 (AF2) */
#define GPIOB_BOOT1             2 /* Boot mode 0 or 1 */
#define GPIOB_JTDO              3 /* JTAG (AF0) */
#define GPIOB_NJTRST            4 /* JTAG (AF0) */
#define GPIOB_SERVO1            5 /* PWM output for Servo1 TIMER 3 channel 2 (AF2) */
#define GPIOB_UART1_TX          6 /* Console - (AF7) */
#define GPIOB_UART1_RX          7 /* Console - (AF7) */
#define GPIOB_I2C1_SCL          8 /* I2C1 clock - (AF4) */
#define GPIOB_I2C1_SDA          9 /* I2C1 data  - (AF4) */
#define GPIOB_SPI2_SCK          10/* SPI2 SCK SDCARD or SPIFLASH - (AF5) */
#define GPIOB_SERVO4            11/* PWM output for Servo4 TIMER 2 channel 4 (AF1) */
#define GPIOB_USB_HS_ID         12/* (AF12) */
#define GPIOB_USB_HS_VBUS       13
#define GPIOB_RC3               14/* RC4 TIMER 12 channel 1 (AF9) */ /* or GPIOB_USB_HS_DM (AF12) */
#define GPIOB_RC4               15/* RC5 TIMER 12 channel 2 (AF9) */ /* or GPIOB_USB_HS_DP (AF12) */

/* Port B mode setup */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_SERVO6) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO5) |     \
                                     PIN_MODE_INPUT(GPIOB_BOOT1) |          \
                                     PIN_MODE_ALTERNATE(GPIOB_JTDO) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_NJTRST) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO1) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_UART1_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_UART1_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SCL) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_I2C1_SDA) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_SPI2_SCK) |   \
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO4) |     \
                                     PIN_MODE_ALTERNATE(GPIOB_USB_HS_ID) |  \
                                     PIN_MODE_INPUT(GPIOB_USB_HS_VBUS) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_RC3) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_RC4))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SCL) |  \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_I2C1_SDA))
#define VAL_GPIOB_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOB_PUPDR             (PIN_PUDR_PULLDOWN(GPIOB_SERVO6) |      \
                                     PIN_PUDR_PULLDOWN(GPIOB_SERVO5) |      \
                                     PIN_PUDR_PULLUP(GPIOB_BOOT1) |         \
                                     PIN_PUDR_FLOATING(GPIOB_JTDO) |        \
                                     PIN_PUDR_FLOATING(GPIOB_NJTRST) |      \
                                     PIN_PUDR_PULLDOWN(GPIOB_SERVO1) |      \
                                     PIN_PUDR_FLOATING(GPIOB_UART1_TX) |    \
                                     PIN_PUDR_FLOATING(GPIOB_UART1_RX) |    \
                                     PIN_PUDR_FLOATING(GPIOB_I2C1_SCL) |    \
                                     PIN_PUDR_FLOATING(GPIOB_I2C1_SDA) |    \
                                     PIN_PUDR_FLOATING(GPIOB_SPI2_SCK) |    \
                                     PIN_PUDR_PULLDOWN(GPIOB_SERVO4) |      \
                                     PIN_PUDR_FLOATING(GPIOB_USB_HS_ID) |   \
                                     PIN_PUDR_FLOATING(GPIOB_USB_HS_VBUS) | \
                                     PIN_PUDR_PULLDOWN(GPIOB_RC3) |         \
                                     PIN_PUDR_PULLDOWN(GPIOB_RC4))
#define VAL_GPIOB_ODR               0xFFFFFFFF
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_SERVO6, 2) | \
		                             PIN_AFIO_AF(GPIOB_SERVO5, 2) | \
		                             PIN_AFIO_AF(GPIOB_JTDO, 0) |   \
		                             PIN_AFIO_AF(GPIOB_NJTRST, 0) |   \
		                             PIN_AFIO_AF(GPIOB_SERVO1, 2) |   \
		                             PIN_AFIO_AF(GPIOB_UART1_TX, 7) |   \
		                             PIN_AFIO_AF(GPIOB_UART1_RX, 7))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_I2C1_SCL, 4) | \
		                             PIN_AFIO_AF(GPIOB_I2C1_SDA, 4) | \
		                             PIN_AFIO_AF(GPIOB_SPI2_SCK, 5) | \
		                             PIN_AFIO_AF(GPIOB_SERVO4, 1) |   \
		                             PIN_AFIO_AF(GPIOB_USB_HS_ID, 12) |   \
		                             PIN_AFIO_AF(GPIOB_RC3, 9) |   \
		                             PIN_AFIO_AF(GPIOB_RC3, 9))

/*
 * Port C setup.
 */
#define GPIOC_IMU_INT           0 /* IMU interrupt */
#define GPIOC_BAT_VOLT          1 /* ADC123_IN11 */
#define GPIOC_SPI2_MISO         2 /* (AF5) */
#define GPIOC_SPI2_MOSI         3 /* (AF5) */
#define GPIOC_LED1              4
#define GPIOC_LED2              5
#define GPIOC_RC5               6 /* RC5 TIMER 8 channel 1 (AF3) */ /* or SPEK_TX UART6 (AF8) */
#define GPIOC_RC6               7 /* RC6 TIMER 8 channel 2 (AF3) */ /* or SPEK_RX UART6 (AF8) */
#define GPIOC_SERVO3            8 /* PWM output for Servo2 TIMER 8 channel 3 (AF3) */
#define GPIOC_I2C3_SDA          9 /* (AF4) */
#define GPIOC_TELE_PWR_EN       10
#define GPIOC_11                11/* NOT USED Available on interface port */
#define GPIOC_TELE_TX           12/* Telemetry UART5 TX (AF8) */
#define GPIOC_DIFFP_INT         13/* Differential pressure sensor Interrupt */
#define GPIOC_MAG_INT_DRDY      14
#define GPIOC_SENSOR_PWR_EN     15

/* Port C mode setup */
#define VAL_GPIOC_MODER             (PIN_MODE_INPUT(GPIOC_IMU_INT) |      \
                                     PIN_MODE_ANALOG(GPIOC_BAT_VOLT) |    \
                                     PIN_MODE_ALTERNATE(GPIOC_SPI2_MISO) |\
                                     PIN_MODE_ALTERNATE(GPIOC_SPI2_MOSI) |\
                                     PIN_MODE_OUTPUT(GPIOC_LED1) |        \
                                     PIN_MODE_OUTPUT(GPIOC_LED2) |        \
                                     PIN_MODE_ALTERNATE(GPIOC_RC5) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_RC6) |      \
                                     PIN_MODE_ALTERNATE(GPIOC_SERVO3) |   \
                                     PIN_MODE_ALTERNATE(GPIOC_I2C3_SDA) | \
                                     PIN_MODE_OUTPUT(GPIOC_TELE_PWR_EN) | \
                                     PIN_MODE_INPUT(GPIOC_11) |           \
                                     PIN_MODE_ALTERNATE(GPIOC_TELE_TX) |  \
                                     PIN_MODE_INPUT(GPIOC_DIFFP_INT) |    \
                                     PIN_MODE_INPUT(GPIOC_MAG_INT_DRDY) | \
                                     PIN_MODE_OUTPUT(GPIOC_SENSOR_PWR_EN))
#define VAL_GPIOC_OTYPER            PIN_OTYPE_OPENDRAIN(GPIOC_I2C3_SDA)
#define VAL_GPIOC_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOC_PUPDR             (PIN_PUDR_FLOATING(GPIOC_IMU_INT) |      \
                                     PIN_PUDR_FLOATING(GPIOC_BAT_VOLT) |     \
                                     PIN_PUDR_FLOATING(GPIOC_SPI2_MISO) |    \
                                     PIN_PUDR_FLOATING(GPIOC_SPI2_MOSI) |    \
                                     PIN_PUDR_PULLDOWN(GPIOC_LED1) |         \
                                     PIN_PUDR_PULLDOWN(GPIOC_LED2) |         \
                                     PIN_PUDR_PULLDOWN(GPIOC_RC5) |          \
                                     PIN_PUDR_PULLDOWN(GPIOC_RC6)  |         \
                                     PIN_PUDR_PULLDOWN(GPIOC_SERVO3) |       \
                                     PIN_PUDR_FLOATING(GPIOC_I2C3_SDA) |     \
                                     PIN_PUDR_PULLUP(GPIOC_TELE_PWR_EN)  |   \
                                     PIN_PUDR_FLOATING(GPIOC_11) |           \
                                     PIN_PUDR_FLOATING(GPIOC_TELE_TX)  |     \
                                     PIN_PUDR_FLOATING(GPIOC_DIFFP_INT) |    \
                                     PIN_PUDR_FLOATING(GPIOC_MAG_INT_DRDY) | \
                                     PIN_PUDR_PULLUP(GPIOC_SENSOR_PWR_EN))
#define VAL_GPIOC_ODR               0xFFFFFFFF
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_SPI2_MISO, 5) | \
		                             PIN_AFIO_AF(GPIOC_SPI2_MOSI, 5) | \
		                             PIN_AFIO_AF(GPIOC_RC5, 3) |       \
		                             PIN_AFIO_AF(GPIOC_RC6, 3))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SERVO3, 3) |    \
		                             PIN_AFIO_AF(GPIOC_I2C3_SDA, 4) |  \
		                             PIN_AFIO_AF(GPIOC_TELE_TX, 8))

/*
 * Port D setup.
 */
#define GPIOD_TELE_RX             2 /* Telemetry UART5 RX (AF8) */

/* All input with pull-up
 */
#define VAL_GPIOD_MODER             PIN_MODE_ALTERNATE(GPIOD_TELE_RX)
#define VAL_GPIOD_OTYPER            0x00000000
#define VAL_GPIOD_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOD_PUPDR             PIN_PUDR_FLOATING(GPIOD_TELE_RX)
#define VAL_GPIOD_ODR               0xFFFFFFFF
#define VAL_GPIOD_AFRL              PIN_AFIO_AF(GPIOD_TELE_RX, 8)
#define VAL_GPIOD_AFRH              0x00000000

/*
 * Port E setup.
 * All input with pull-up
 */
#define VAL_GPIOE_MODER             0x00000000
#define VAL_GPIOE_OTYPER            0x00000000
#define VAL_GPIOE_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOE_PUPDR             0xFFFFFFFF
#define VAL_GPIOE_ODR               0xFFFFFFFF
#define VAL_GPIOE_AFRL              0x00000000
#define VAL_GPIOE_AFRH              0x00000000

/*
 * Port F setup.
 * All input with pull-up.
 */
#define VAL_GPIOF_MODER             0x00000000
#define VAL_GPIOF_OTYPER            0x00000000
#define VAL_GPIOF_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOF_PUPDR             0xFFFFFFFF
#define VAL_GPIOF_ODR               0xFFFFFFFF
#define VAL_GPIOF_AFRL              0x00000000
#define VAL_GPIOF_AFRH              0x00000000

/*
 * Port G setup.
 * All input with pull-up.
 */
#define VAL_GPIOG_MODER             0x00000000
#define VAL_GPIOG_OTYPER            0x00000000
#define VAL_GPIOG_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOG_PUPDR             0xFFFFFFFF
#define VAL_GPIOG_ODR               0xFFFFFFFF
#define VAL_GPIOG_AFRL              0x00000000
#define VAL_GPIOG_AFRH              0x00000000

/*
 * Port H setup.
 * All input with pull-up
 */
#define VAL_GPIOH_MODER             0x00000000
#define VAL_GPIOH_OTYPER            0x00000000
#define VAL_GPIOH_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOH_PUPDR             0xFFFFFFFF
#define VAL_GPIOH_ODR               0xFFFFFFFF
#define VAL_GPIOH_AFRL              0x00000000
#define VAL_GPIOH_AFRH              0x00000000

/*
 * Port I setup.
 * All input with pull-up.
 */
#define VAL_GPIOI_MODER             0x00000000
#define VAL_GPIOI_OTYPER            0x00000000
#define VAL_GPIOI_OSPEEDR           0xFFFFFFFF
#define VAL_GPIOI_PUPDR             0xFFFFFFFF
#define VAL_GPIOI_ODR               0xFFFFFFFF
#define VAL_GPIOI_AFRL              0x00000000
#define VAL_GPIOI_AFRH              0x00000000

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
