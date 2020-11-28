/**
* ir_speed_sensor.c
*/

#include "ir_speed_sensor.h"

IR_Speed_Sensor_Data ir_speed_sensor_data;

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void ir_speed_sensor_interupt_handler(void);

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Handles an input interupt for the IR speed sensor
 * @param  None
 * @retval None
 */
void ir_speed_sensor_interupt_handler(){

  uint32_t current_time;
  uint32_t delta_reading;
  uint16_t rpm;

  current_time = millis();
  
  /* Calculates the RPM depending on the last reading time */
  if(ir_speed_sensor_data.lrt != 0){
    /* Reading taken only after the second rotation */

    /* Time difference in ms */
    delta_reading = current_time - ir_speed_sensor_data.lrt;

    /* RPM calculation (depending on the blade number) */
    rpm = 60000/delta_reading/ir_speed_sensor_data.blade_num;

    /* Store the result */
    ir_speed_sensor_data.count++;
    ir_speed_sensor_data.sum += rpm;

    if(ir_speed_sensor_data.max < rpm){
      ir_speed_sensor_data.max = rpm;
    }
  }

  /* Sets the time of the reading */
  ir_speed_sensor_data.lrt = current_time;

}

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the IR speed sensor
 * @param  ir_speed_sensor_pin the IR speed sensor out pin
 * @param  ir_speed_sensor_pin_vcc the IR speed sensor VCC pin
 * @retval None
 */
void ir_speed_sensor_init(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc){

  /* To avoid divinding by 0 */
  ir_speed_sensor_data.blade_num = 1;

  /* Initialize the IR speed sensor pin */
  pinMode(ir_speed_sensor_pin, INPUT_PULLUP);
  pinMode(ir_speed_sensor_pin_vcc, OUTPUT);
}

/**
 * @brief  Reads the current value of the IR speed sensor
 * @param  None
 * @retval IR speed sensor current value and maximum
 */
IR_Speed_Sensor ir_speed_sensor_read(){
  IR_Speed_Sensor sensor_value;

  if(ir_speed_sensor_data.count != 0){
    sensor_value.rpm_avg = ir_speed_sensor_data.sum / ir_speed_sensor_data.count;
    sensor_value.rpm_max = ir_speed_sensor_data.max;
  } else {
    sensor_value.rpm_avg = 0;
    sensor_value.rpm_max = 0;
  }

  ir_speed_sensor_reset();

  return sensor_value;
}

/**
 * @brief  Resets the IR speed sensor
 * @param  None
 * @retval None
 */
void ir_speed_sensor_reset(){

  ir_speed_sensor_data.sum = 0;
  ir_speed_sensor_data.count = 0;
  ir_speed_sensor_data.max = 0;
}

/**
 * @brief  Initializes the speed sensor for a recording
 * @param  blade_num the number of blades
 * @retval None
 */
void ir_speed_sensor_init_record(uint8_t blade_num){

  /* Resets the IR speed sensor data */
  ir_speed_sensor_reset();
  ir_speed_sensor_data.lrt = 0;

  /* Puts the number of blades in the data */
  ir_speed_sensor_data.blade_num = blade_num;
}

/**
 * @brief  Enables the IR speed sensor
 * @param  ir_speed_sensor_pin the IR speed sensor out pin
 * @param  ir_speed_sensor_pin_vcc the IR speed sensor VCC pin
 * @retval None
 */
void ir_speed_sensor_enable(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc){

  attachInterrupt(digitalPinToInterrupt(ir_speed_sensor_pin), ir_speed_sensor_interupt_handler, RISING);
  digitalWrite(ir_speed_sensor_pin_vcc, HIGH);
  Serial.printf("Enabled ir sensor at %hd with VCC at %d\n", ir_speed_sensor_pin, ir_speed_sensor_pin_vcc);
}

/**
 * @brief  Disables the IR speed sensor
 * @param  ir_speed_sensor_pin the IR speed sensor out pin
 * @param  ir_speed_sensor_pin_vcc the IR speed sensor VCC pin
 * @retval None
 */
void ir_speed_sensor_disable(uint8_t ir_speed_sensor_pin, uint8_t ir_speed_sensor_pin_vcc){

  detachInterrupt(digitalPinToInterrupt(ir_speed_sensor_pin));
  digitalWrite(ir_speed_sensor_pin_vcc, LOW);
}