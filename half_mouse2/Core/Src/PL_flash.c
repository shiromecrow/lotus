/*
 * PL_flash.c
 *
 *  Created on: Jan 12, 2023
 *      Author: sf199
 */


#include "stm32g4xx_hal.h"
#include "PL_flash.h"
#include <string.h>
#include <stdint.h>
#include "stdio.h"
#include "define.h"




const uint32_t start_address = 0x807F000; //bank1 page last start address
const uint32_t end_adress = 0x807FFFF; // bank1 page last end address

void test_flash(void){
		  record_out();
		  maze_display();
		  flash_record_init();
		  record_in();
}


void eraseFlash( void )
{
	FLASH_EraseInitTypeDef erase;
	erase.TypeErase = FLASH_TYPEERASE_PAGES;	// select page
	erase.Banks = FLASH_BANK_1;		       // set bank1
	erase.Page = 254;// set page254(127)
	erase.NbPages = 1;//delete page
	uint32_t pageError = 0;

	HAL_FLASHEx_Erase(&erase, &pageError);	// erase sector
//	printf("page=%x\n\r", pageError);

//	for (int i=0;i<10;i++){
//		printf("nowpage%x=%x\n\r",((start_address+i)&65535), (*(uint8_t*)(start_address+i)));
//	}

}


void writeFlash(uint32_t address, uint64_t *data, uint32_t size,uint8_t erasemode)
{
	HAL_FLASH_Unlock();		// unlock flash
	if(erasemode==1){eraseFlash();}

	for ( uint32_t add = address; add < (address + size); add+=8 ){
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, add, (uint64_t *)data); // write byte
		data=data+4;  // add data pointer
	}

	HAL_FLASH_Lock();		// lock flash

}

void loadFlash(uint32_t address, uint64_t *data, uint32_t size )
{
	memcpy(data, (uint64_t*)address,size); // copy data

}


void record_in(void) {
	int t = 0;
	uint32_t address=start_address;

	while (t <= 14) {
		record.row[t] = wall.row[t];
		record.column[t] = wall.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		record.row_look[t] = wall.row_look[t];
		record.column_look[t] = wall.column_look[t];
		t++;
	}
	t = 0;

	writeFlash(address, (uint64_t*) record.row[0], 1, ON);
	address+=16;
	t=1;

	while (t <= 14) {
	writeFlash(address, (uint64_t*) record.row[t], 1, OFF);
	address+=16;
	t++;
	}

	t=0;
	while (t <= 14) {
	writeFlash(address, (uint64_t*) record.column[t], 1, OFF);
	address+=16;
	t++;
	}

	t=0;
	while (t <= 14) {
	writeFlash(address, (uint64_t*) record.row_look[t], 1, OFF);
	address+=16;
	t++;
	}

	t=0;
	while (t <= 14) {
	writeFlash(address, (uint64_t*) record.column_look[t], 1, OFF);
	address+=16;
	t++;
	}
//	writeFlash(start_address + sizeof(record.row), (uint64_t*) record.column,
//			sizeof(record.column), OFF);
//	writeFlash(start_address + 2 * sizeof(record.row),
//			(uint64_t*) record.row_look, sizeof(record.row_look),
//			OFF);
//	writeFlash(start_address + 3 * sizeof(record.row),
//			(uint64_t*) record.column_look, sizeof(record.column_look),
//			OFF);

//	for (int i=0;i<200;i++){
//		printf("nowpage%x=%x\n\r",((start_address+i)&65535), (*(uint8_t*)(start_address+i)));
//	}

}


void record_out(void) {
//	for (int i=0;i<200;i++){
//		printf("nowpage%x=%x\n\r",((start_address+i)&65535), (*(uint8_t*)(start_address+i)));
//	}

	int t=0;
	uint32_t address=start_address;
	while (t <= 14) {
	loadFlash(address, (uint64_t*)&record.row[t], 2);
	address+=16;
	t++;
	}

	t=0;
	while (t <= 14) {
	loadFlash(address, (uint64_t*)&record.column[t], 2);
	address+=16;
	t++;
	}

	t=0;
	while (t <= 14) {
		loadFlash(address, (uint64_t*)&record.row_look[t], 2);
		address+=16;
		t++;
	}

	t=0;
	while (t <= 14) {
		loadFlash(address, (uint64_t*)&record.column_look[t], 2);
		address+=16;
		t++;
	}
//	loadFlash(start_address, (uint64_t*) record.row, sizeof(record.row));
//	loadFlash(start_address + sizeof(record.row), (uint64_t*) record.column,
//			sizeof(record.column));
//	loadFlash(start_address + 2 * sizeof(record.row),
//			(uint64_t*) record.row_look, sizeof(record.row_look));
//	loadFlash(start_address + 3 * sizeof(record.row),
//			(uint64_t*) record.column_look, sizeof(record.column_look));
	t = 0;
	while (t <= 14) {
		wall.row[t] = record.row[t];
		wall.column[t] = record.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		wall.row_look[t] = record.row_look[t];
		wall.column_look[t] = record.column_look[t];
		t++;
	}

	t = 0;

}

void flash_record_init(void){
	int t = 0;
	while (t <= 14) {
		wall.row[t] = 0b111100011;
		wall.column[t] = t*2;
		t++;
	}
	t = 0;
	while (t <= 14) {
		wall.row_look[t] = t*4;
		wall.column_look[t] = t*8;
		t++;
	}

}



