#include "ec200u.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>

uint8_t ec200uRxBuffer[EC200U_RX_BUFFER_SIZE];

uint8_t otaPackageBuffer[OTA_PACKAGE_BUFFER_SIZE];

void EC200U_Init(void)
{
	 HAL_UART_Receive_IT(&huart1,
	                        ec200uRxBuffer,
	                        1);
}

void EC200U_SendAT(const char *cmd)
{
    HAL_UART_Transmit(&huart1,
                      (uint8_t*)cmd,
                      strlen(cmd),
                      HAL_MAX_DELAY);
}

uint8_t EC200U_CheckNetwork(void)
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT+CREG?\r\n");

    HAL_Delay(1000);

    if(EC200U_WaitForResponse("+CREG: 0,1") ||
       EC200U_WaitForResponse("+CREG: 0,5"))
    {
        return 1;
    }

    return 0;
}

uint8_t EC200U_WaitForResponse(const char *expected)
{
    if(strstr((char*)ec200uRxBuffer, expected) != NULL)
    {
        return 1;
    }

    return 0;
}
uint8_t EC200U_TestAT(void)
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT\r\n");

    HAL_Delay(1000);

    return EC200U_WaitForResponse("OK");
}

uint8_t EC200U_GetSignalStrength(void)
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT+CSQ\r\n");

    HAL_Delay(1000);

    if(EC200U_WaitForResponse("+CSQ"))
    {
        return 1;
    }

    return 0;
}
uint8_t EC200U_HTTPInit(void)
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT+QHTTPCFG=\"contextid\",1\r\n");

    HAL_Delay(1000);

    return EC200U_WaitForResponse("OK");
}

uint8_t EC200U_HTTPGet(const char *url) // ec200u is about to send a URL of length N
{
    char command[128];

    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    sprintf(command,
            "AT+QHTTPURL=%d,80\r\n",
            (int)strlen(url));

    EC200U_SendAT(command);

    HAL_Delay(1000);

    if(!EC200U_WaitForResponse("CONNECT"))
    {
        return 0;
    }

    EC200U_SendAT(url);

    HAL_Delay(1000);

    return EC200U_WaitForResponse("OK");
}

uint8_t EC200U_HTTPExecute(void)  //Perform HTTP GET, Wait up to 80 seconds
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT+QHTTPGET=80\r\n");

    HAL_Delay(5000);

    return EC200U_WaitForResponse("+QHTTPGET");
}
uint8_t EC200U_HTTPRead(uint8_t *buffer,
                        uint32_t length)
{
    memset(ec200uRxBuffer, 0, EC200U_RX_BUFFER_SIZE);

    EC200U_SendAT("AT+QHTTPREAD=80\r\n");

    HAL_Delay(5000);

    if(!EC200U_WaitForResponse("+QHTTPREAD"))
    {
        return 0;
    }

    memset(buffer,
           0xAA,
           length);

    return 1;
}
