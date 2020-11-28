/**
* nvs.h
*/

#ifndef NVS_H
#define NVS_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>
#include "ArduinoNvs.h"

/* Custom libraries */
#include "config.h"
#include "parameters.h"

/*******************************************************************
 * Types
 ******************************************************************/

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void nvs_init();
void nvs_write_parameters();
void nvs_read_parameters();

#endif /* NVS_H */