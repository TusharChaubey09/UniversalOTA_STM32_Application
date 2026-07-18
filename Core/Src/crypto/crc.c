#include "crc.h"

uint32_t CRC_Calculate(uint8_t *data,
                       uint32_t length)
{
    uint32_t crc = 0;

    for(uint32_t i = 0; i < length; i++)
    {
        crc += data[i];
    }

    return crc;
}
