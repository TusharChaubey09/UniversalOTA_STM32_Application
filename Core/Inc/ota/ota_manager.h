#ifndef OTA_MANAGER_H
#define OTA_MANAGER_H

typedef enum
{
    OTA_IDLE = 0,

    OTA_CHECK_UPDATE,

    OTA_DOWNLOAD,

    OTA_VERIFY,

    OTA_SET_FLAG,

    OTA_REBOOT,

    OTA_ERROR

} OTA_State_t;


typedef enum
{
    OTA_ERROR_NONE = 0,

    OTA_ERROR_NETWORK,

    OTA_ERROR_DOWNLOAD,

    OTA_ERROR_VERIFY

} OTA_Error_t;
void OTA_Init(void);

void OTA_Task(void);

#endif
