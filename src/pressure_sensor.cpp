/**
* pressure_sensor.c
*/

#include "pressure_sensor.h"

Pressure_Sensor pressure_sensor;

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the pressure sensor
 * @param  pressure_sensor_pin the pressure sensor data pin
 * @retval None
 */
void pressure_sensor_init(uint8_t pressure_sensor_pin){

  /* Resets the pressure sensor sum and count */
  pressure_sensor.sum = 0;
  pressure_sensor.count = 0;

  pressure_sensor.pin = pressure_sensor_pin;
}

/**
 * @brief  Reads the current value of the pressure sensor 
 * @param  None
 * @retval Pressure sensor current value
 */
uint16_t pressure_sensor_read(){

  uint16_t sensor_value = analogRead(pressure_sensor.pin);

  pressure_sensor.sum += sensor_value;
  pressure_sensor.count++;

  return sensor_value;
}

/**
 * @brief  Reads the average value of the pressure sensor
 * @param  None
 * @retval Pressure sensor average value
 */
uint16_t pressure_sensor_read_avg(){
  uint16_t sensor_value;

  if(pressure_sensor.count == 0){
    return 0;
  }

  sensor_value = pressure_sensor.sum / pressure_sensor.count;
  pressure_sensor.sum = 0;
  pressure_sensor.count = 0;

  return sensor_value;
}

/**
 * @brief  Resets the pressure sensor
 * @param  None
 * @retval None
 */
void pressure_sensor_reset(){
  pressure_sensor.sum = 0;
  pressure_sensor.count = 0;
}