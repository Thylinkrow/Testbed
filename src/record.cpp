/**
* record.c
*/

#include "record.h"

unsigned long lastReadTime;

Data data;

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void record_update_data(uint16_t ir_speed_sensor_value, uint16_t pressure_sensor_value);
void record_log_data();

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Updates the data
 * @param  ir_speed_sensor_value the value of the IR speed sensor
 * @param  pressure_sensor_value the value of the presusre sensor
 * @retval None
 */
void record_update_data(uint16_t ir_speed_sensor_value, uint16_t ir_speed_sensor_max, uint16_t pressure_sensor_value){

  /* Applying pressure factor TODO Change */
  pressure_sensor_value = pressure_sensor_value * parameters[PARAMETERS_PRESSURE_FACT].value * parameters[PARAMETERS_PRESSURE_FACT].factor;
  
  /* Updates the current readings */
  data.pressure_sensor_value_cur = pressure_sensor_value;
  data.ir_speed_sensor_value_cur = ir_speed_sensor_value;

  /* Updates the max and min for the pressure sensor */
  if(data.pressure_sensor_value_max < pressure_sensor_value){
    data.pressure_sensor_value_max = pressure_sensor_value;
  } else if(data.pressure_sensor_value_min > pressure_sensor_value){
    data.pressure_sensor_value_min = pressure_sensor_value;
  }

  /* Udpates the max and min for the IR speed sensor */
  if(data.ir_speed_sensor_value_max < ir_speed_sensor_max){
    data.ir_speed_sensor_value_max = ir_speed_sensor_max;
  } else if(data.ir_speed_sensor_value_min > ir_speed_sensor_value){
    data.ir_speed_sensor_value_min = ir_speed_sensor_value;
  }

}

/**
 * @brief  Logs the data
 * @param  None
 * @retval None
 */
void record_log_data(){

  uint8_t sd_card_file_name[16], sd_card_file_data[16], file_name_base[16];

  /* Manages different behaviour depending on the reading mode */
  switch (parameters[PARAMETERS_READ_MODE].value)
  {
  case 1:
    /* Speed */
    memcpy(file_name_base,"/speed_%hd.csv\0",16);
    break;
  case 0:
  default:
    /* Power */
    memcpy(file_name_base,"/power_%hd.csv\0",16);
    break;
  }

  sprintf((char *)sd_card_file_name,(char *)file_name_base,data.record_id);
  sprintf((char *)sd_card_file_data,"%hu,%hu\r\n",data.ir_speed_sensor_value_cur,data.pressure_sensor_value_cur);
  sd_card_append(sd_card_file_name,sd_card_file_data);

}

/*******************************************************************
 * Public functions 
 ******************************************************************/

uint8_t record_loop(){
  unsigned long esptime;
  uint16_t pressure_sensor_value;
  IR_Speed_Sensor ir_speed_sensor_value;
  uint8_t updated;

  updated = RECORD_NOT_UPDATED;

  /* Time since boot of the ESP32 */
  esptime = millis();

  if(esptime - lastReadTime > parameters[PARAMETERS_READ_TIME].value * parameters[PARAMETERS_READ_TIME].factor){
    lastReadTime = esptime;
    
    /* Reads from the pressure sensor */
    pressure_sensor_read();

    /* Reads from the ir speed sensor */
    ir_speed_sensor_value = ir_speed_sensor_read();

    /* Reads the average value of the pressure sensor */
    pressure_sensor_value = pressure_sensor_read_avg();

    /* Updates the data */
    record_update_data(ir_speed_sensor_value.rpm_avg, ir_speed_sensor_value.rpm_max, pressure_sensor_value);

    /* Logs the data onto the SD card */
    record_log_data();

    Serial.printf("Speed: %hurpm (%hu)\t- Pressure: %hupsi (%hu)\n", 
      data.ir_speed_sensor_value_cur, data.ir_speed_sensor_value_max,
      data.pressure_sensor_value_cur, data.pressure_sensor_value_max);

    updated = RECORD_UPDATED;
  }

  return updated;
}

/**
 * @brief  Initializes the data
 * @param  data the data struct to be initialized
 * @retval None
 */
void record_init_data(uint8_t record_id){

  /* Initializes / resets the data */
  data.pressure_sensor_value_cur = RECORD_MIN_U16_SENSOR_VALUE;
  data.ir_speed_sensor_value_cur = RECORD_MIN_U16_SENSOR_VALUE;
  data.pressure_sensor_value_max = RECORD_MIN_U16_SENSOR_VALUE;
  data.ir_speed_sensor_value_max = RECORD_MIN_U16_SENSOR_VALUE;
  data.pressure_sensor_value_min = RECORD_MAX_U16_SENSOR_VALUE;
  data.ir_speed_sensor_value_min = RECORD_MAX_U16_SENSOR_VALUE;
  data.record_id = record_id;

  ir_speed_sensor_reset();
  pressure_sensor_read();

}