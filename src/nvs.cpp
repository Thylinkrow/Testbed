/**
* nvs.c
*/

#include "nvs.h"

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the NVS
 * @param  None
 * @retval None
 */
void nvs_init(){

  NVS.begin();
}

/**
 * @brief  Write parameters to the NVS
 * @param  None
 * @retval None
 */
void nvs_write_parameters(){

  uint8_t i;

  for(i=0; i<PARAMETERS_SIZE; i++){
    NVS.setBlob((char *)parameters[i].name,(uint8_t *)&parameters[i],sizeof(Parameter));
  }
}

/**
 * @brief  Read parameters from the NVS
 * @param  None
 * @retval None
 */
void nvs_read_parameters(){

  uint8_t i;
  uint8_t holder[sizeof(Parameter)];

  for(i=0; i<PARAMETERS_SIZE; i++){
    if(NVS.getBlob((char *)parameters[i].name,holder,sizeof(Parameter))){
      memcpy(&parameters[i],holder,sizeof(Parameter));
    } else {
      Serial.printf("NVS failled for: %s\n",(char *)parameters[i].name);
    }
  }
}