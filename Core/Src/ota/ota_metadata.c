#include "ota_metadata.h"
#include "ota_config.h"
#include "w25q128.h"
#include "ota_config.h"
#include <string.h>

OTA_Metadata_t gOtaMetadata;

void OTA_MetadataSave(OTA_Metadata_t *metadata)
{
    W25Q128_EraseSector(OTA_METADATA_ADDRESS);

    W25Q128_WriteData(
        OTA_METADATA_ADDRESS,
        (uint8_t *)metadata,
        sizeof(OTA_Metadata_t));
}

void OTA_MetadataRead(OTA_Metadata_t *metadata)
{
    W25Q128_ReadData(
        OTA_METADATA_ADDRESS,
        (uint8_t *)metadata,
        sizeof(OTA_Metadata_t));
}

void OTA_MetadataLoadDummy(void)
{
    gOtaMetadata.magicNumber = OTA_MAGIC_NUMBER;

    gOtaMetadata.metadataVersion = OTA_METADATA_VERSION;

    gOtaMetadata.headerSize = OTA_HEADER_SIZE;

    strcpy(gOtaMetadata.firmwareVersion,
           "20260703_V1.1");

    gOtaMetadata.firmwareSize = 102400;

    gOtaMetadata.mcuFamilyID = OTA_MCU_FAMILY_ID;

    gOtaMetadata.forceOverride = 0;

    gOtaMetadata.encryptionType = OTA_ENCRYPTION_AES256_CBC;

    gOtaMetadata.hashType = OTA_HASH_HMAC_SHA256;

    gOtaMetadata.reservedFlags = 0;

    memset(gOtaMetadata.iv,
           0,
           sizeof(gOtaMetadata.iv));

    memset(gOtaMetadata.hmac,
           0,
           sizeof(gOtaMetadata.hmac));

    memset(gOtaMetadata.reservedExtension,
           0,
           sizeof(gOtaMetadata.reservedExtension));

    strcpy(gOtaMetadata.firmwareURL,
           "https://server.com/firmware.ota");
}
