/**
* ir_speed_sensor.h
*/

#ifndef IR_SPEED_SENSOR_H
#define IR_SPEED_SENSOR_H

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

typedef struct IR_Speed_Sensor {
    uint16_t rpm_avg;   /* Average RPM recorded for this reading */
    uint16_t rpm_max;   /* Maximum RPM recorded for this reading */
} IR_Speed_Sensor;

typedef struct IR_Speed_Sensor_Data {
    uint32_t lrt;       /* Last Reading Time: Time of the last reading */
    uint32_t sum;       /* Sum of the ir speed sensor readings */
    uint16_t count;     /* Count of the ir speed sensor readings */
    uint16_t max;       /* Maximum of the ir speed sensor readings */
    uint8_t blade_num;  /* Number of blades */
} IR_Speed_Sensor_Data;

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void ir_speed_sensor_init(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc);
IR_Speed_Sensor ir_speed_sensor_read(void);
void ir_speed_sensor_reset(void);
void ir_speed_sensor_init_record(uint8_t blade_num);
void ir_speed_sensor_enable(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc);
void ir_speed_sensor_disable(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc);

#endif /* IR_SPEED_SENSOR_H */