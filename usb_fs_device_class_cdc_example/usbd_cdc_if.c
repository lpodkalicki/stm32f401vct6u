/**
  ******************************************************************************
  * @file    usbd_cdc_if.c
  * @author  MCD Application Team
  * @version V2.4.1
  * @date    19-June-2015
  * @brief   Generic media access Layer.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"
#include "log.h"	

#define CDC_RX_BUFSIZE  	(1024)
#define CDC_TX_BUFSIZE  	(512)

USBD_HandleTypeDef  		hUSBDDevice;

uint8_t CDC_RxBuf[CDC_RX_BUFSIZE];  
uint8_t CDC_TxBuf[CDC_TX_BUFSIZE];

volatile uint16_t CDC_RxBufCur = 0; // points to next available character in UserRxBuffer
volatile uint16_t CDC_RxBufLen = 0; // counts number of valid characters in UserRxBuffer

static int8_t CDC_Init     (void);
static int8_t CDC_DeInit   (void);
static int8_t CDC_Control  (uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive  (uint8_t* pbuf, uint32_t *Len);


USBD_CDC_ItfTypeDef USBD_CDC_fops = 
{
	CDC_Init,
	CDC_DeInit,
	CDC_Control,
	CDC_Receive
};

USBD_CDC_LineCodingTypeDef linecoding =
{
	115200, /* baud rate*/
	0x00,   /* stop bits-1*/
	0x00,   /* parity - none*/
	0x08    /* nb. of bits 8*/
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  CDC_Init
  *         Initializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init(void)
{

	USBD_CDC_SetTxBuffer(&hUSBDDevice, CDC_TxBuf, 0);
	USBD_CDC_SetRxBuffer(&hUSBDDevice, CDC_RxBuf);
	
	CDC_RxBufCur = 0;
	CDC_RxBufLen = 0;
  
	return USBD_OK;
}

/**
  * @brief  CDC_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit(void)
{
	
	return USBD_OK;
}


/**
  * @brief  CDC_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code            
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control  (uint8_t cmd, uint8_t* pbuf, uint16_t length)
{ 
  switch (cmd)
  {
  case CDC_SEND_ENCAPSULATED_COMMAND:
    /* Add your code here */
    break;

  case CDC_GET_ENCAPSULATED_RESPONSE:
    /* Add your code here */
    break;

  case CDC_SET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_GET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_CLEAR_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_SET_LINE_CODING:
    linecoding.bitrate    = (uint32_t)(pbuf[0] | (pbuf[1] << 8) |\
                            (pbuf[2] << 16) | (pbuf[3] << 24));
    linecoding.format     = pbuf[4];
    linecoding.paritytype = pbuf[5];
    linecoding.datatype   = pbuf[6];
    
    /* Add your code here */
    break;

  case CDC_GET_LINE_CODING:
    pbuf[0] = (uint8_t)(linecoding.bitrate);
    pbuf[1] = (uint8_t)(linecoding.bitrate >> 8);
    pbuf[2] = (uint8_t)(linecoding.bitrate >> 16);
    pbuf[3] = (uint8_t)(linecoding.bitrate >> 24);
    pbuf[4] = linecoding.format;
    pbuf[5] = linecoding.paritytype;
    pbuf[6] = linecoding.datatype;     
    
    /* Add your code here */
    break;

  case CDC_SET_CONTROL_LINE_STATE:
    /* Add your code here */
    break;

  case CDC_SEND_BREAK:
     /* Add your code here */
    break;    
    
  default:
    break;
  }

  return USBD_OK;
}

/**
  * @brief  CDC_Receive
  *         Data received over USB OUT endpoint are sent over CDC interface 
  *         through this function.
  *           
  *         @note
  *         This function will issue a NAK packet on any OUT packet received on 
  *         USB endpoint untill exiting this function. If you exit this function
  *         before transfer is complete on CDC interface (ie. using DMA controller)
  *         it will result in receiving more data while previous ones are still 
  *         not sent.
  *                 
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive (uint8_t* Buf, uint32_t *Len)
{
	
	if (hUSBDDevice.dev_state != USBD_STATE_CONFIGURED) {
		return USBD_FAIL;
	}

	if (((Buf == NULL) || (Len == NULL)) || (*Len == 0)) {
		return USBD_FAIL;
	}
	
	if (CDC_RxBufLen > 0) {
		if (CDC_RxBufLen == CDC_RxBufCur)
			CDC_RxBufLen = CDC_RxBufCur = 0;
	}
	
	if ((CDC_RxBufLen + *Len) > CDC_RX_BUFSIZE) {
		return USBD_FAIL;
	}
	
	// Initiate next USB packet transfer
	USBD_CDC_SetRxBuffer(&hUSBDDevice, CDC_RxBuf + CDC_RxBufLen);
	USBD_CDC_ReceivePacket(&hUSBDDevice);
	
	CDC_RxBufLen += *Len;
	
	return USBD_OK;
}


int
CDC_IntfReceive(uint8_t *buffer, uint32_t buffsize)
{
	uint32_t len;
	
	if (CDC_RxBufLen == 0 || CDC_RxBufLen == CDC_RxBufCur) {
		return (0);
	}
	
	len = CDC_RxBufLen - CDC_RxBufCur;
	if (len > buffsize) {
		len = buffsize;
	}
	
	memcpy(buffer, CDC_RxBuf + CDC_RxBufCur, len);
	CDC_RxBufCur += len;
	
	return len;
}

int
CDC_IntfTransmit(const uint8_t *data, uint32_t len)
{
	memcpy(CDC_TxBuf, data, len);
	USBD_CDC_SetTxBuffer(&hUSBDDevice, CDC_TxBuf, len);
	return USBD_CDC_TransmitPacket(&hUSBDDevice);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

