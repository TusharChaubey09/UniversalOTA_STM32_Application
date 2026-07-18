#ifndef W25Q128_H
#define W25Q128_H

#include <stdint.h>

void W25Q128_Init(void);

uint32_t W25Q128_ReadID(void);

uint8_t W25Q128_ReadStatus(void);

void W25Q128_WaitBusy(void);

void W25Q128_EraseSector(uint32_t address);

void W25Q128_WriteData(uint32_t address,
                       uint8_t *data,
                       uint16_t length);
void W25Q128_ReadData(uint32_t address,
                      uint8_t *data,
                      uint16_t length);
uint8_t W25Q128_WriteChunk(uint32_t address,
                           uint8_t *buffer,
                           uint32_t length);

uint8_t W25Q128_ReadChunk(uint32_t address,
                          uint8_t *buffer,
                          uint32_t length);
#endif
