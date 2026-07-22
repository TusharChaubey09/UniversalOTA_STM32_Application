#include "ota_package.h"
#include "ota_metadata.h"
#include "w25q128.h"
#include "ota_config.h"

#include <string.h>

uint8_t OTA_PackageReadMetadata(const uint8_t *buffer,
                                OTA_Metadata_t *metadata)
{
    if(buffer == NULL || metadata == NULL)
    {
        return 0;
    }

    memcpy(metadata,
           buffer,
           sizeof(OTA_Metadata_t));

    return 1;
}

uint8_t OTA_PackageStoreMetadata(const uint8_t *buffer)
{
    OTA_Metadata_t metadata;

    if(!OTA_PackageReadMetadata(buffer, &metadata))
    {
        return 0;
    }

    OTA_MetadataSave(&metadata);

    return 1;
}

uint8_t OTA_PackageStoreFirmware(uint32_t flashAddress,
                                 uint8_t *buffer,
                                 uint32_t length)
{
    W25Q128_WriteData(flashAddress,
                      buffer,
                      length);

    return 1;
}

uint8_t OTA_PackageReadFirmware(uint8_t *buffer,
                                uint32_t length)
{
    W25Q128_ReadData(OTA_FIRMWARE_ADDRESS,
                     buffer,
                     length);

    return 1;
}
