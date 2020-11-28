/**
* sd_card.h
*/

#ifndef SD_CARD_H
#define SD_CARD_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>
#include <SPI.h>
#include "FS.h"
#include "SD.h"

/* Custom libraries */
#include "config.h"

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void sd_card_init(uint8_t sd_card_pin);
uint8_t sd_card_open(uint8_t *file_name);
void sd_card_append(uint8_t *file_name, uint8_t *msg);
void sd_card_write(uint8_t *file_name, uint8_t *msg);

#endif /* SD_CARD_H */