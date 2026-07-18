#ifndef OTA_DOWNLOAD_H
#define OTA_DOWNLOAD_H

#include <stdint.h>

typedef struct
{
    uint32_t currentOffset;

    uint32_t totalSize;

    uint32_t chunkSize;

    uint32_t remainingBytes;

    uint8_t downloadComplete;

} OTA_Download_t;

void OTA_DownloadInit(uint32_t totalSize);

uint32_t OTA_DownloadGetOffset(void);

void OTA_DownloadUpdateOffset(uint32_t bytesDownloaded);

uint8_t OTA_DownloadComplete(void);

extern OTA_Download_t gOtaDownload;

#endif
