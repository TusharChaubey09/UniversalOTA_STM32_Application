#include "main.h"
#include "ota_manager.h"
#include "ec200u.h"
#include "ota/ota_metadata.h"
#include <string.h>
#include "ota/ota_config.h"
#include "w25q128.h"
#include "crc.h"
#include "ota_package.h"
#include "ota_chunk.h"
#include "ota_download.h"
static OTA_State_t otaState;
static OTA_Error_t otaError = OTA_ERROR_NONE;
static uint8_t otaRetryCount = 0;
static uint8_t downloadRetryCount = 0;
static uint8_t verifyRetryCount = 0;
static uint8_t firmwareBuffer[256];
static uint8_t verifyBuffer[256];
static uint32_t calculatedCRC;
static uint32_t verifyCRC;
void OTA_Init(void)
{
    otaState = OTA_CHECK_UPDATE;
    /* TODO:
        * Replace with metadata received
        * from the downloaded OTA package.
        */

    OTA_MetadataLoadDummy();
}
void OTA_Task(void)
{
    switch(otaState)
    {
        case OTA_IDLE:
        {
            break;
        }

        case OTA_CHECK_UPDATE:
        {
            if(EC200U_TestAT() &&
               EC200U_CheckNetwork() &&
               EC200U_GetSignalStrength())
            {
                otaRetryCount = 0;

                if(gOtaMetadata.forceOverride)
                {
                    OTA_DownloadInit(gOtaMetadata.firmwareSize);

                    otaState = OTA_DOWNLOAD;
                }
                else
                {
                    OTA_DownloadInit(gOtaMetadata.firmwareSize);

                    otaState = OTA_DOWNLOAD;
                }
            }
            else
            {
                otaRetryCount++;

                if(otaRetryCount >= 3)
                {
                    otaState = OTA_IDLE;
                }
            }

            break;
        }
        case OTA_DOWNLOAD:
        {
            if(EC200U_HTTPInit() &&
               EC200U_HTTPGet(gOtaMetadata.firmwareURL) &&
               EC200U_HTTPExecute())
            {
                downloadRetryCount = 0;

                if(EC200U_HTTPRead(otaChunkBuffer,
                                   OTA_CHUNK_SIZE))
                {
                    W25Q128_WriteChunk(
                        OTA_FIRMWARE_ADDRESS +
                        OTA_DownloadGetOffset(),
                        otaChunkBuffer,
                        OTA_CHUNK_SIZE);

                    OTA_DownloadUpdateOffset(
                        OTA_CHUNK_SIZE);

                    if(OTA_DownloadComplete())
                    {
                        otaState = OTA_VERIFY;
                    }
                }
            }
            else
            {
                downloadRetryCount++;

                if(downloadRetryCount >= 3)
                {
                    otaError = OTA_ERROR_DOWNLOAD;

                    otaState = OTA_ERROR;
                }
            }

            break;
        }
        case OTA_VERIFY:
        {
            OTA_Metadata_t metadata;

            OTA_MetadataRead(&metadata);

            if(metadata.magicNumber != OTA_MAGIC_NUMBER)
            {
                otaError = OTA_ERROR_VERIFY;
                otaState = OTA_ERROR;
                break;
            }

            if(metadata.firmwareSize == 0)
            {
                otaError = OTA_ERROR_VERIFY;
                otaState = OTA_ERROR;
                break;
            }

            if(metadata.headerSize != sizeof(OTA_Metadata_t))
            {
                otaError = OTA_ERROR_VERIFY;
                otaState = OTA_ERROR;
                break;
            }

            otaState = OTA_SET_FLAG;

            break;
        }
        case OTA_SET_FLAG:
        {
            uint32_t otaFlag = OTA_PENDING_FLAG;

            W25Q128_EraseSector(OTA_FLAG_ADDRESS);

            W25Q128_WriteData(OTA_FLAG_ADDRESS,
                              (uint8_t*)&otaFlag,
                              sizeof(otaFlag));

            otaState = OTA_REBOOT;

            break;
        }

        case OTA_REBOOT:
        {
            NVIC_SystemReset();

            break;
        }
        case OTA_ERROR:
        {
            switch(otaError)
            {
                case OTA_ERROR_DOWNLOAD:
                {
                    break;
                }

                case OTA_ERROR_VERIFY:
                {
                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }
        default:
        {
            break;
        }
    }
}
