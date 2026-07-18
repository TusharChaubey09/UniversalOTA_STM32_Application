#include "w25q128.h"
#include "main.h"
#include "spi.h"

static void W25_Select(void)
{
    HAL_GPIO_WritePin(W25_CS_GPIO_Port,
                      W25_CS_Pin,
                      GPIO_PIN_RESET);
}

static void W25_Deselect(void)
{
    HAL_GPIO_WritePin(W25_CS_GPIO_Port,
                      W25_CS_Pin,
                      GPIO_PIN_SET);
}

void W25Q128_Init(void)
{
    W25_Deselect();
}

uint32_t W25Q128_ReadID(void)
{
    uint8_t cmd = 0x9F;
    uint8_t id[3] = {0};

    W25_Select();

    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    HAL_SPI_Receive(&hspi1, id, 3, HAL_MAX_DELAY);

    W25_Deselect();

    return ((uint32_t)id[0] << 16) |
           ((uint32_t)id[1] << 8)  |
            (uint32_t)id[2];
}
void W25Q128_WriteEnable(void)
{
    uint8_t cmd = 0x06;

    W25_Select();

    HAL_SPI_Transmit(&hspi1,
                     &cmd,
                     1,
                     HAL_MAX_DELAY);

    W25_Deselect();
}
uint8_t W25Q128_ReadStatus(void)
{
    uint8_t cmd = 0x05;
    uint8_t status = 0;

    W25_Select();

    HAL_SPI_Transmit(&hspi1,
                     &cmd,
                     1,
                     HAL_MAX_DELAY);

    HAL_SPI_Receive(&hspi1,
                    &status,
                    1,
                    HAL_MAX_DELAY);

    W25_Deselect();

    return status;
}
void W25Q128_WaitBusy(void)
{
    while(W25Q128_ReadStatus() & 0x01)
    {
        HAL_Delay(1);
    }
}
void W25Q128_EraseSector(uint32_t address)
{
    uint8_t cmd[4];

    W25Q128_WriteEnable();

    cmd[0] = 0x20;

    cmd[1] = (address >> 16) & 0xFF;
    cmd[2] = (address >> 8) & 0xFF;
    cmd[3] = address & 0xFF;

    W25_Select();

    HAL_SPI_Transmit(&hspi1,
                     cmd,
                     4,
                     HAL_MAX_DELAY);

    W25_Deselect();

    W25Q128_WaitBusy();
}
void W25Q128_WriteData(uint32_t address,
                       uint8_t *data,
                       uint16_t length)
{
    uint8_t cmd[4];

    W25Q128_WriteEnable();

    cmd[0] = 0x02;

    cmd[1] = (address >> 16) & 0xFF;
    cmd[2] = (address >> 8) & 0xFF;
    cmd[3] = address & 0xFF;

    W25_Select();

    HAL_SPI_Transmit(&hspi1,
                     cmd,
                     4,
                     HAL_MAX_DELAY);

    HAL_SPI_Transmit(&hspi1,
                     data,
                     length,
                     HAL_MAX_DELAY);

    W25_Deselect();

    W25Q128_WaitBusy();
}
void W25Q128_ReadData(uint32_t address,
                      uint8_t *data,
                      uint16_t length)
{
    uint8_t cmd[4];

    cmd[0] = 0x03;

    cmd[1] = (address >> 16) & 0xFF;
    cmd[2] = (address >> 8) & 0xFF;
    cmd[3] = address & 0xFF;

    W25_Select();

    HAL_SPI_Transmit(&hspi1,
                     cmd,
                     4,
                     HAL_MAX_DELAY);

    HAL_SPI_Receive(&hspi1,
                    data,
                    length,
                    HAL_MAX_DELAY);

    W25_Deselect();
}
uint8_t W25Q128_WriteChunk(uint32_t address,
                           uint8_t *buffer,
                           uint32_t length)
{
    W25Q128_WriteData(address,
                      buffer,
                      length);

    return 1;
}

uint8_t W25Q128_ReadChunk(uint32_t address,
                          uint8_t *buffer,
                          uint32_t length)
{
    W25Q128_ReadData(address,
                     buffer,
                     length);

    return 1;
}
