#ifndef _FLASH_IF_H
#define _FLASH_IF_H

#include "stm32f4xx_hal.h"

uint8_t flash_if_read(uint32_t addr, uint32_t *buf, uint32_t size);
uint8_t flash_if_erase(uint32_t addr, uint32_t size);
uint8_t flash_if_write(uint32_t addr, const uint32_t *buf, uint32_t size);

#endif
