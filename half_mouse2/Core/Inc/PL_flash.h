/*
 * PL_flash.h
 *
 *  Created on: Jan 12, 2023
 *      Author: sf199
 */

#ifndef INC_PL_FLASH_H_
#define INC_PL_FLASH_H_

extern const uint32_t start_address; //sentor11 start address
extern const uint32_t end_adress; // sector11 end address

extern uint8_t *flash_test;


void eraseFlash();
void writeFlash(uint32_t , uint64_t *, uint32_t , uint8_t);
void loadFlash(uint32_t, uint64_t *, uint32_t );

#endif /* INC_PL_FLASH_H_ */
