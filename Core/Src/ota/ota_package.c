#include "ota_package.h"
#include <string.h>
#include "w25q128.h"
#include "ota_config.h"

uint8_t OTA_PackageDownload(void)
{
    return 1;
}

uint8_t OTA_PackageStore(void)
{
    return 1;
}

uint8_t OTA_PackageVerify(void)
{
    return 1;
}
uint8_t OTA_PackageReadMetadata(const uint8_t *buffer,
                                OTA_Metadata_t *metadata)
{
    memcpy(metadata,
    		buffer,
           sizeof(OTA_Metadata_t));


    return 1;
}

uint8_t OTA_PackageReadFirmware(uint8_t *buffer,
                                uint32_t length)
{
    W25Q128_ReadData(
        OTA_FIRMWARE_ADDRESS,
        buffer,
        length);

    return 1;
}
