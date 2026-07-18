#ifndef OTA_PACKAGE_H
#define OTA_PACKAGE_H

#include "ota_types.h"
#include <stdint.h>

uint8_t OTA_PackageReadMetadata(const uint8_t *buffer,
                                OTA_Metadata_t *metadata);

uint8_t OTA_PackageReadFirmware(uint8_t *buffer,
                                uint32_t length);
typedef struct
{
    OTA_Metadata_t metadata;

    uint8_t firmwareData[];

} OTA_Package_t;

#endif
