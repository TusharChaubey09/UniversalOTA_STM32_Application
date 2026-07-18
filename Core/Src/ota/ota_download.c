#include "ota_download.h"

OTA_Download_t gOtaDownload =
{
    0,
    0,
    1024
};

void OTA_DownloadInit(uint32_t totalSize)
{
    gOtaDownload.currentOffset = 0;

    gOtaDownload.totalSize = totalSize;

    gOtaDownload.chunkSize = 1024;

    gOtaDownload.remainingBytes = totalSize;

    gOtaDownload.downloadComplete = 0;
}

uint32_t OTA_DownloadGetOffset(void)
{
    return gOtaDownload.currentOffset;
}

void OTA_DownloadUpdateOffset(uint32_t bytesDownloaded)
{
    gOtaDownload.currentOffset += bytesDownloaded;

    if(gOtaDownload.remainingBytes >= bytesDownloaded)
    {
        gOtaDownload.remainingBytes -= bytesDownloaded;
    }

    if(gOtaDownload.currentOffset >= gOtaDownload.totalSize)
    {
        gOtaDownload.downloadComplete = 1;
    }
}

uint8_t OTA_DownloadComplete(void)
{
    return gOtaDownload.downloadComplete;
}
