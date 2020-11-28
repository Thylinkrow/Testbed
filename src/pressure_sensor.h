/**
* pressure_sensor.h
*/

#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>

/* Custom libraries */
#include "config.h"

/*******************************************************************
 * Types
 ******************************************************************/

typedef struct Pressure_Sensor {
    uint32_t sum;       /* Sum of the pressure sensor readings */
    uint16_t count;     /* Count of the pressure sensor readings */
    uint8_t pin;        /* Pin of the pressure sensor */
} Pressure_Sensor;

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void pressure_sensor_init(uint8_t pressure_sensor_pin);
uint16_t pressure_sensor_read();
uint16_t pressure_sensor_read_avg();
void pressure_sensor_reset(void);

#endif /* PRESSURE_SENSOR_H */