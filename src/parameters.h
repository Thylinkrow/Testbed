/**
* parameters.h
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>

/* Custom libraries */
#include "config.h"

/*******************************************************************
 * Constants
 ******************************************************************/

#define PARAMETERS_SIZE                 4

/* Parameters ID */
#define PARAMETERS_READ_TIME            0
#define PARAMETERS_NB_BLADES            1
#define PARAMETERS_PRESSURE_FACT        2
#define PARAMETERS_READ_MODE            3

/* Parameters Name "pretty print" */
#define PARAMETERS_NPP_READ_TIME        "Read Time (ms)"
#define PARAMETERS_NPP_NB_BLADES        "Number of Blades"
#define PARAMETERS_NPP_PRESSURE_FACT    "Pressure factor"
#define PARAMETERS_NPP_READ_MODE        "Read mode\tPower\tSpeed"

/* Parameters Name */
#define PARAMETERS_N_READ_TIME          "reading_time"
#define PARAMETERS_N_NB_BLADES          "nb_blades"
#define PARAMETERS_N_PRESSURE_FACT      "pressure_fact"
#define PARAMETERS_N_READ_MODE          "read_mode"

/* Parameters */
#define PARAMETERS_MODE_VALUE           0
#define PARAMETERS_MODE_BOOL            1

/*******************************************************************
 * Types
 ******************************************************************/

typedef struct Parameter {
    uint8_t name_pp[32];
    uint8_t name[16];
    uint8_t value;
    uint8_t default_value;
    uint8_t min;
    uint8_t max;
    uint8_t factor;
    uint8_t param_mode;
} Parameter;

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void parameters_init_parameters();

/*******************************************************************
 * Exported variables
 ******************************************************************/

extern Parameter parameters[PARAMETERS_SIZE];

#endif /* PARAMETERS_H */