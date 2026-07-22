#ifndef EC200U_H
#define EC200U_H

#include <stdint.h>

#define EC200U_RX_BUFFER_SIZE 256
#define OTA_PACKAGE_BUFFER_SIZE    2048

extern uint8_t otaPackageBuffer[OTA_PACKAGE_BUFFER_SIZE];

extern uint8_t ec200uRxBuffer[EC200U_RX_BUFFER_SIZE];
extern volatile uint16_t ec200uRxIndex;

extern uint8_t ec200uRxByte;


void EC200U_Init(void);

void EC200U_SendAT(const char *cmd);

uint8_t EC200U_WaitForResponse(const char *expected);

uint8_t EC200U_TestAT(void);

uint8_t EC200U_CheckNetwork(void);

uint8_t EC200U_GetSignalStrength(void);

uint8_t EC200U_HTTPInit(void);

uint8_t EC200U_HTTPGet(const char *url);

uint8_t EC200U_HTTPExecute(void);

uint32_t EC200U_HTTPRead(uint8_t *buffer,
                         uint32_t maxLength);
#endif
