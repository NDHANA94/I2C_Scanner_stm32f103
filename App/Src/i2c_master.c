/* 
Created: Dec 02, 2022
        Author: Nipun Dhananjaya -> nipun.dhananjaya@gmail.com
*/

#include "i2c_master.h"

uint8_t Buffer[25] = {0};
uint8_t Space[] = " - ";
uint8_t StartMSG[] = "Starting I2C Scanning.... \r\n";
uint8_t EndMsg[] = "\r\n.......Done!....... \r\n\r\n";
uint8_t NewLine[] = "\r\n";

void scan_device()
{
    uint8_t i = 0, ret;
    HAL_UART_Transmit(&huart1, StartMSG, sizeof(StartMSG), 10000);
    for(i=0; i<128; i++){
        ret = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i<<1), 3, 5);
        if (ret != HAL_OK) // No ACK received at the address
        {
            HAL_UART_Transmit(&huart1, Space, sizeof(Space), 10000);
        }
        else if (ret == HAL_OK)
        {
            sprintf(Buffer, "0x%X", i);
            HAL_UART_Transmit(&huart1, Buffer, sizeof(Buffer), 10000);
        }
        if(i%9 == 0){
        	HAL_UART_Transmit(&huart1, NewLine, sizeof(NewLine), 10000);
        }

    }
    HAL_UART_Transmit(&huart1, EndMsg, sizeof(EndMsg), 10000);
}
