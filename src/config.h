/**
* config.h
*/

#ifndef CONFIG_H
#define CONFIG_H

/*******************************************************************
 * Constants
 ******************************************************************/

/* SPI */
#define SPI_MOSI                    23
#define SPI_MISO                    19
#define SPI_SCK                     18

/* I2C */
#define SDA                         21
#define SCL                         22

/* Buttons */
#define BUTTON_ENTER                34
#define BUTTON_LEFT                 35
#define BUTTON_RIGHT                32

/* SD card module (SPI) */
#define SD_CS                       33

/* IR speed sensors (Digital) */
#define IR_SPEED_SENSOR_POWER       13
#define IR_SPEED_SENSOR_SPEED       14
#define IR_SPEED_SENSOR_POWER_VCC   12
#define IR_SPEED_SENSOR_SPEED_VCC   27

/* Pressure sensor (Analog) */
#define PRESSURE_SENSOR             15

/*******************************************************************
 * Types
 ******************************************************************/

typedef struct Data {
    uint16_t pressure_sensor_value_cur;
    uint16_t ir_speed_sensor_value_cur;
    uint16_t pressure_sensor_value_max;
    uint16_t ir_speed_sensor_value_max;
    uint16_t pressure_sensor_value_min;
    uint16_t ir_speed_sensor_value_min;
    uint8_t record_id;
} Data;

#endif /* CONFIG_H */