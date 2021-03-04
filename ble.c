/**
 * @file  ble.c
 * @authors iffameah
 * @copyright [copy write statement]
 *
 * @brief These are BLE algorithm for wake up,scanning and filtering
 */

/*********************************************************************
* Includes
**********************************************************************/

#include "ble.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

/*********************************************************************
* Global Variables
**********************************************************************/

uint8_t BLEtx[10];
uint8_t BLErx[300];
uint8_t BLEchck[20];
uint8_t BLEwake[4] = "AT\r\n";
uint8_t BLEat[9] = "AT+SCAN\r\n";
uint8_t RSSI[2];
uint8_t RSSI2[2];
uint8_t RSSI3[2];
uint8_t RSSI4[2];
uint8_t RSSI5[2];
uint8_t MAC[12];
uint8_t MAC2[12];
uint8_t MAC3[12];
uint8_t MAC4[12];
uint8_t MAC5[12];

uint8_t tx_beacon1[50];
uint8_t tx_beacon2[50];
uint8_t tx_beacon3[50];
uint8_t tx_beacon4[50];
uint8_t tx_beacon5[50];

int FOUND;
int n1;
int n2;
int n3;
int n4;
int n5;
int f;
int nrx;
uint8_t BLEpm[13]="AT+PWMODE=2\r\n";
extern UART_HandleTypeDef huart2;
extern int BLE_done;

/*********************************************************************
* Static Variables
**********************************************************************/
static char BLE_Oled[15];
static char respok[15];


/*********************************************************************
* Functions
**********************************************************************/

void BLE_RESET_PIN (GPIO_PinState Pinstate)
{
	HAL_GPIO_WritePin (GPIOH, GPIO_PIN_1, Pinstate);
}

void BLEwakecall(void)
{		
	HAL_UART_DMAStop(&huart2);
	HAL_UART_Transmit_DMA(&huart2, BLEwake, 4);
}

void BLEInit()
{
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_1,GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_1,GPIO_PIN_SET);
	HAL_Delay(300);
	HAL_UART_Transmit(&huart2, BLEwake, 4,100);
    
	HAL_Delay(100);
	HAL_UART_Transmit(&huart2, BLEpm, 13,100);
}

void BLEscan(void)
{
	
	memset(BLErx,0,sizeof(BLErx));
	memset(MAC,0,sizeof(MAC));
	memset(MAC2,0,sizeof(MAC2));
	memset(MAC3,0,sizeof(MAC3));
	memset(MAC4,0,sizeof(MAC4));
	memset(MAC5,0,sizeof(MAC5));

	memset(RSSI,0,sizeof(RSSI));
	memset(RSSI2,0,sizeof(RSSI2));
	memset(RSSI3,0,sizeof(RSSI3));
	memset(RSSI4,0,sizeof(RSSI4));
	memset(RSSI5,0,sizeof(RSSI5));

	n1=0;
	n2=0;
	n3=0;
	n4=0;
	n5=0;
	FOUND=0;
	HAL_UART_DMAStop(&huart2);
//	HAL_UART_Transmit_DMA(&huart2, BLEwake, 4);
	HAL_Delay(300);
	HAL_UART_Transmit(&huart2, BLEat, 9,100);
	HAL_UART_Receive_DMA(&huart2,BLErx,500);
//HAL_Delay(300);
	BLE_done=1;
}

void BLEfilter(void)
{		
		/**********************************FILTER BY NAME START***********************************************/
		if(BLErx[n1]=='G'&&(BLErx[n1+6]=='u')){
			f=0;
			FOUND=1;
			RSSI[0]=BLErx[n1+12];//20 for REYAX
			RSSI[1]=BLErx[n1+13];//21
			
			MAC[0]=BLErx[n1-13];
			MAC[1]=BLErx[n1-12];
			MAC[2]=BLErx[n1-11];
			MAC[3]=BLErx[n1-10];
			MAC[4]=BLErx[n1-9];
			MAC[5]=BLErx[n1-8];
			MAC[6]=BLErx[n1-7];
			MAC[7]=BLErx[n1-6];
			MAC[8]=BLErx[n1-5];
			MAC[9]=BLErx[n1-4];
			MAC[10]=BLErx[n1-3];
			MAC[11]=BLErx[n1-2];
			
			sprintf((char*)tx_beacon1,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":%1c%1c}",MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5],MAC[6],MAC[7],MAC[8],MAC[9],MAC[10],MAC[11],RSSI[0],RSSI[1]);

			if(BLErx[n2]=='G'&&(BLErx[n2+6]=='u'&&n2!=n1)){
			FOUND=2;
			RSSI2[0]=BLErx[n2+12];
			RSSI2[1]=BLErx[n2+13];
			
			MAC2[0]=BLErx[n2-13];
			MAC2[1]=BLErx[n2-12];
			MAC2[2]=BLErx[n2-11];
			MAC2[3]=BLErx[n2-10];
			MAC2[4]=BLErx[n2-9];
			MAC2[5]=BLErx[n2-8];
			MAC2[6]=BLErx[n2-7];
			MAC2[7]=BLErx[n2-6];
			MAC2[8]=BLErx[n2-5];
			MAC2[9]=BLErx[n2-4];
			MAC2[10]=BLErx[n2-3];
			MAC2[11]=BLErx[n2-2];

			sprintf((char*)tx_beacon1,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":\"%1c%1c\"},",MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5],MAC[6],MAC[7],MAC[8],MAC[9],MAC[10],MAC[11],RSSI[0],RSSI[1]);
			sprintf((char*)tx_beacon2,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":\"%1c%1c\"}",MAC2[0],MAC2[1],MAC2[2],MAC2[3],MAC2[4],MAC2[5],MAC2[6],MAC2[7],MAC2[8],MAC2[9],MAC2[10],MAC2[11],RSSI2[0],RSSI2[1]);
				
			if(BLErx[n3]=='G'&&(BLErx[n3+6]=='u'&&n3!=n1&&n3!=n2)){
			FOUND=3;
			RSSI3[0]=BLErx[n3+12];
			RSSI3[1]=BLErx[n3+13];
			
			MAC3[0]=BLErx[n3-13];
			MAC3[1]=BLErx[n3-12];
			MAC3[2]=BLErx[n3-11];
			MAC3[3]=BLErx[n3-10];
			MAC3[4]=BLErx[n3-9];
			MAC3[5]=BLErx[n3-8];
			MAC3[6]=BLErx[n3-7];
			MAC3[7]=BLErx[n3-6];
			MAC3[8]=BLErx[n3-5];
			MAC3[9]=BLErx[n3-4];
			MAC3[10]=BLErx[n3-3];
			MAC3[11]=BLErx[n3-2];
				
			sprintf((char*)tx_beacon1,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":\"%1c%1c\"},",MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5],MAC[6],MAC[7],MAC[8],MAC[9],MAC[10],MAC[11],RSSI[0],RSSI[1]);
			sprintf((char*)tx_beacon2,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":\"%1c%1c\"},",MAC2[0],MAC2[1],MAC2[2],MAC2[3],MAC2[4],MAC2[5],MAC2[6],MAC2[7],MAC2[8],MAC2[9],MAC2[10],MAC2[11],RSSI2[0],RSSI2[1]);
			sprintf((char*)tx_beacon3,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":\"%1c%1c\"}",MAC3[0],MAC3[1],MAC3[2],MAC3[3],MAC3[4],MAC3[5],MAC3[6],MAC3[7],MAC3[8],MAC3[9],MAC3[10],MAC3[11],RSSI3[0],RSSI3[1]);

			if(BLErx[n4]=='G'	&&	(BLErx[n4+6]=='u'	&&	n4!=n1	&&	n4!=n2	&&	n4!=n3)){
			FOUND=4;
			RSSI4[0]=BLErx[n4+12];
			RSSI4[1]=BLErx[n4+13];
			
			MAC4[0]=BLErx[n4-13];
			MAC4[1]=BLErx[n4-12];
			MAC4[2]=BLErx[n4-11];
			MAC4[3]=BLErx[n4-10];
			MAC4[4]=BLErx[n4-9];
			MAC4[5]=BLErx[n4-8];
			MAC4[6]=BLErx[n4-7];
			MAC4[7]=BLErx[n4-6];
			MAC4[8]=BLErx[n4-5];
			MAC4[9]=BLErx[n4-4];
			MAC4[10]=BLErx[n4-3];
			MAC4[11]=BLErx[n4-2];
		
			sprintf((char*)tx_beacon1,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":%1c%1c},",MAC[0],MAC[1],MAC[2],MAC[3],MAC[4],MAC[5],MAC[6],MAC[7],MAC[8],MAC[9],MAC[10],MAC[11],RSSI[0],RSSI[1]);
			sprintf((char*)tx_beacon2,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":%1c%1c},",MAC2[0],MAC2[1],MAC2[2],MAC2[3],MAC2[4],MAC2[5],MAC2[6],MAC2[7],MAC2[8],MAC2[9],MAC2[10],MAC2[11],RSSI2[0],RSSI2[1]);
			sprintf((char*)tx_beacon3,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":%1c%1c},",MAC3[0],MAC3[1],MAC3[2],MAC3[3],MAC3[4],MAC3[5],MAC3[6],MAC3[7],MAC3[8],MAC3[9],MAC3[10],MAC3[11],RSSI3[0],RSSI3[1]);
			sprintf((char*)tx_beacon4,"{\"bid\":\"%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c%1c\",\"rsi\":%1c%1c}",MAC4[0],MAC4[1],MAC4[2],MAC4[3],MAC4[4],MAC4[5],MAC4[6],MAC4[7],MAC4[8],MAC4[9],MAC4[10],MAC4[11],RSSI4[0],RSSI4[1]);

			if(BLErx[n5]=='G'	&&	(BLErx[n5+6]=='u'	&&	n5!=n1	&&	n5!=n2	&&	n5!=n3 &&	n5!=n4)){
			FOUND=5;
			RSSI5[0]=BLErx[n5+12];
			RSSI5[1]=BLErx[n5+13];
			
			MAC5[0]=BLErx[n5-13];
			MAC5[1]=BLErx[n5-12];
			MAC5[2]=BLErx[n5-11];
			MAC5[3]=BLErx[n5-10];
			MAC5[4]=BLErx[n5-9];
			MAC5[5]=BLErx[n5-8];
			MAC5[6]=BLErx[n5-7];
			MAC5[7]=BLErx[n5-6];
			MAC5[8]=BLErx[n5-5];
			MAC5[9]=BLErx[n5-4];
			MAC5[10]=BLErx[n5-3];
			MAC5[11]=BLErx[n5-2];
				
			}
			else
			{
				//test reading payload
				if(n5>=300)
				{	
					n5=0;
//					BLE_done=0;
				}
				else
				{
					n5++;
				}
			}
			}
			else
			{
				//test reading payload
				if(n4>=300){
				n4=0;
//					BLE_done=0;
				}
				else
					n4++;
			}
		}
			else
			{
				//test reading payload
				if(n3>=300){
					n3=0;
				}
				else
					n3++;
			}
		}
			else
			{
				//test reading payload
				if (n2>=300)
				{
					n2=0;
				}
				else
				{
					n2++;
				}
			}
			}
		else
		{	
			//test reading payload
			if(n1>=300)
			{
				n1=0;
			}
			else
			{
				n1++;
			}
		}
}
