#ifndef GPIO_ACCESS_H
#define GPIO_ACCESS_H

#include "includes.h"

//defines
#define BCM2708_PERI_BASE 0x20000000
#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000)
#define PAGE_SIZE  0x1000
#define BLOCK_SIZE PAGE_SIZE

//macros
#define INP_GPIO(g) *(gpio + ((g) / 0xa)) &= ~( 0x7 << (((g) % 0xa) * 0x3))
#define OUT_GPIO(g) *(gpio + ((g) / 0xa)) |=  ( 0x1 << (((g) % 0xa) * 0x3))
#define GPIO_SET *(gpio + 0x7)
#define GPIO_CLR *(gpio + 0xa)

int                 mem_fd;
void                *gpio_map;
volatile unsigned   *gpio;

//prototypes

/**
 * @brief setup_GPIO
 * Initializes a memory page and assigns
 * it to the GPIO ports of the Raspberry Pi
 */
int setup_GPIO(void);

/**
 * @brief init_PIN
 * @param pin
 */
void init_PIN(int pin);

/**
 * @brief set_PIN
 * @param pin
 */
void set_PIN(int pin);

/**
 * @brief unset_PIN
 * @param pin
 */
void unset_PIN(int pin);

#endif // GPIO_ACCESS_H
