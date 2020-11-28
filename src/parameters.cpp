/**
* parameters.c
*/

#include "parameters.h"

Parameter parameters[PARAMETERS_SIZE];

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void parameters_init_parameter(Parameter *p, uint8_t value, uint8_t min, uint8_t max, uint8_t factor, uint8_t param_mode, uint8_t *name_pp, uint8_t *name);

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Initializes a parameter
 * @param  p address of the parameter
 * @param  value
 * @param  min
 * @param  max
 * @param  factor
 * @param  name_pp Name in "pretty print"
 * @param  name
 * @retval None
 */
void parameters_init_parameter(Parameter *p, uint8_t value, uint8_t min, uint8_t max, uint8_t factor, uint8_t param_mode, uint8_t *name_pp, uint8_t *name){
  
  Parameter parameter;
  uint8_t name_pp_size, name_size;

  name_pp_size = 0;
  while (name_pp[name_pp_size] != '\0') {
    name_pp_size++;
  }

  name_size = 0;
  while (name[name_size] != '\0') {
    name_size++;
  }
  
  parameter.value = value;
  parameter.default_value = value;
  parameter.min = min;
  parameter.max = max;
  parameter.factor = factor;
  parameter.param_mode = param_mode;
  memcpy(parameter.name_pp,name_pp,name_pp_size+1);
  memcpy(parameter.name,name,name_size+1);

  memcpy(p,&parameter,sizeof(Parameter));
}

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the parameters
 * @param  None
 * @retval None
 */
void parameters_init_parameters(){

  parameters_init_parameter(parameters+PARAMETERS_READ_TIME,25,2,100,10,PARAMETERS_MODE_VALUE,(uint8_t *)PARAMETERS_NPP_READ_TIME,(uint8_t *)PARAMETERS_N_READ_TIME);
  parameters_init_parameter(parameters+PARAMETERS_NB_BLADES,4,1,16,1,PARAMETERS_MODE_VALUE,(uint8_t *)PARAMETERS_NPP_NB_BLADES,(uint8_t *)PARAMETERS_N_NB_BLADES);
  parameters_init_parameter(parameters+PARAMETERS_PRESSURE_FACT,1,1,255,1,PARAMETERS_MODE_VALUE,(uint8_t *)PARAMETERS_NPP_PRESSURE_FACT,(uint8_t *)PARAMETERS_N_PRESSURE_FACT);
  parameters_init_parameter(parameters+PARAMETERS_READ_MODE,0,0,1,1,PARAMETERS_MODE_BOOL,(uint8_t *)PARAMETERS_NPP_READ_MODE,(uint8_t *)PARAMETERS_N_READ_MODE);
}