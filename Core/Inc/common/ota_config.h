#ifndef OTA_CONFIG_H
#define OTA_CONFIG_H

#define CURRENT_FIRMWARE_VERSION      "20260703_V1.0"

#define OTA_MAGIC_NUMBER              0x4F544131UL
#define OTA_METADATA_VERSION          1U
#define OTA_HEADER_SIZE               128U

#define OTA_MCU_FAMILY_ID             0x00000001UL

#define OTA_ENCRYPTION_AES256_CBC     1U
#define OTA_HASH_HMAC_SHA256          1U

#define OTA_METADATA_ADDRESS          0x00000000UL
#define OTA_FIRMWARE_ADDRESS          0x00000080UL

#define OTA_PENDING_FLAG              0xA5A5A5A5UL
#define OTA_FLAG_ADDRESS              0x000F0000UL

#define OTA_SERVER_URL \
"https://github.com/TusharChaubey09/UniversalOTA_STM32_Firmware-Packaging-Tool/releases/download/v1.0/20260723_V1.0.ota"
#endif
