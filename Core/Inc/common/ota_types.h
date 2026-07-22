#ifndef OTA_TYPES_H
#define OTA_TYPES_H

#include <stdint.h>

typedef struct
{
    uint32_t magicNumber;

    uint16_t metadataVersion;

    uint16_t headerSize;

    char firmwareVersion[32];

    uint32_t firmwareSize;

    uint32_t mcuFamilyID;

    uint8_t forceOverride;

    uint8_t encryptionType;

    uint8_t hashType;

    uint8_t reservedFlags;

    uint8_t iv[16];

    uint8_t hmac[32];

    uint8_t reservedExtension[28];
} OTA_Metadata_t;

#endif
