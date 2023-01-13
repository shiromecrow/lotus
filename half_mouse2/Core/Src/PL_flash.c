/*
 * PL_flash.c
 *
 *  Created on: Jan 12, 2023
 *      Author: sf199
 */


#include "stm32g4xx_hal.h"
#include <string.h>
#include <stdint.h>
#include "stdio.h"


/*
 *@brief erase sector11
*/
const uint32_t start_address = 0x807F000; //bank2 start address
const uint32_t end_adress = 0x807FFFF; // bank2 end address
//0x803FFFFかも
typedef uint8_t FLASH_TEST;

FLASH_TEST *flash_test;


void eraseFlash( void )
{
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_PAGES;	// select sector
	erase.Banks = FLASH_BANK_1;		       // set bank2
	erase.Page = 127;//319;
	erase.NbPages = 1;
	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);	// erase sector
}

/*
 * @brief write flash(sector11)
 * @param uint32_t address sector11 start address
 * @param uint8_t * data write data
 * @param uint32_t size write data size
*/
void writeFlash(uint32_t address, uint64_t *data, uint32_t size,uint8_t erasemode)
{
	HAL_FLASH_Unlock();		// unlock flash
	if(erasemode==1){
	eraseFlash();
	}			// erease sector11

  for ( uint32_t add = address; add < (address + size); add+=2 ){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, add, *data); // write byte
    data++;  // add data pointer
	}

	HAL_FLASH_Lock();		// lock flash
}

/*
 * @brief write flash(sector11)
 * @param uint32_t address sector11 start address
 * @param uint8_t * data read data
 * @param uint32_t size read data size
*/
void loadFlash(uint32_t address, uint64_t *data, uint32_t size )
{
	HAL_FLASH_Unlock();
	eraseFlash();
	HAL_FLASH_Lock();//そもそもイレースできない

	memcpy(data, (uint64_t*)address, size); // copy data
//	uint32_t add;
//	uint32_t* p;
//	for(add=address;add<(address+size);add+=2){
//		p=(uint32_t*)add;
//		*data=*p;
//
//		data++;
//	}




}
