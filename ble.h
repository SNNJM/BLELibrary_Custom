 
/** @file ble.h
 *  @brief BLE Header file
 *
 *  This contains shared variable across project & function prototypes whic related to ble
 *
 *  @author iffameah
 *	@copyright <copy write statement>
 *  @bug No known bugs.
 */


#include "stdint.h"
#include "main.h"

/*********************************************************************
* Extern Global Variables
**********************************************************************/
extern uint8_t BLEtx[10];
extern uint8_t BLErx[300];
extern uint8_t BLEchck[20];
extern int FOUND;
extern int f;
extern int n1,n2,n3,n4,n5;


/** @brief – these are function prototypes for ble
* 

	@BLEInit - ble init function prototypes
…………………………………………………………………………………………….
* @return – return value description
**/

/**
*	@brief ble scanning function prototypes
*
* Initiate AT command to BLE module for scanning nearby ble devices
*
*	@param huart2 
*	@return void
*/
void BLEscan(void);


/**
*	@brief ble filtering function prototypes
*
* Filter the results of BLE devices that are found
*
*	@param 
*	@return void
*/
void BLEfilter(void);


/**
*	@brief display on BLE symbol on OLED
*
* will occur only if BLE device is available
*
*	@param 
*	@return void
*/
void blefound_oled();


/**
*	@brief Reset ble 
*
*	@param GPIOH, GPIO_PIN_1
*	@return void
*/
void BLE_RESET_PIN (GPIO_PinState Pinstate);


/**
*	@brief ble wake up function prototypes
*
* Initiate AT command to wake up BLE module 
*
*	@param huart2 
*	@return void
*/
void BLEwakecall(void);


/**
*	@brief ble init function prototypes
*
* Initiate AT command to wake up the BLE module and set power mode
*
*	@param huart2 
*	@return void
*/
void BLEInit(void);