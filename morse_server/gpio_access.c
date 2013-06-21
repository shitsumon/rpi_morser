#include "gpio_access.h"

/**
 * @brief setup_GPIO
 */
int setup_GPIO(){

    if(( mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0){
        printf("Can't open /dev/mem \n");
        return -1;
    }

    gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
    close(mem_fd);

    if( gpio_map == MAP_FAILED){
        printf("mmap error %d\n", (int)gpio_map);
        return -1;
    }

    gpio = (volatile unsigned *)gpio_map;

    return 0;
}

/**
 * @brief init_PIN
 * @param pin
 */
void init_PIN(int pin){
    INP_GPIO(pin);
    OUT_GPIO(pin);
}

/**
 * @brief set_PIN
 * @param pin
 */
void set_PIN(int pin){
    GPIO_SET = 1 << pin;
}

/**
 * @brief unset_PIN
 * @param pin
 */
void unset_PIN(int pin){
    GPIO_CLR = 1 << pin;
}
