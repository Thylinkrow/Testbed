/**
* record.h
*/

#ifndef RECORD_H
#define RECORD_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>

/* Custom libraries */
#include "config.h"
#include "parameters.h"
#include "sd_card.h"
#include "ir_speed_sensor.h"
#include "pressure_sensor.h"

/*******************************************************************
 * Constants
 ******************************************************************/

#define RECORD_MIN_U16_SENSOR_VALUE     0
#define RECORD_MAX_U16_SENSOR_VALUE     65535

#define RECORD_NOT_UPDATED              0
#define RECORD_UPDATED                  1

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

uint8_t record_loop(void);
void record_init_data(uint8_t record_id);

/*******************************************************************
 * Exported variables
 ******************************************************************/

extern Data data;

#endif /* RECORD_H */