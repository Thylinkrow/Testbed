/**
* user_interface.h
*/

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>
#include <oled.h>

/* Custom libraries */
#include "config.h"
#include "oled_screen.h"
#include "parameters.h"
#include "record.h"
#include "sd_card.h"
#include "nvs.h"

/*******************************************************************
 * Constants
 ******************************************************************/

#define USER_INTERFACE_BUTTON_COOLDOWN     500
#define USER_INTERFACE_MASTER_HEIGHT       16
#define USER_INTERFACE_MAIN_BUTTON_OFFSET  4

#define USER_INTERFACE_DISPLAY_LOADING     0
#define USER_INTERFACE_DISPLAY_MAIN        1
#define USER_INTERFACE_DISPLAY_RECORD      2
#define USER_INTERFACE_DISPLAY_ON_INPUT    3
#define USER_INTERFACE_DISPLAY_CONFIG      4
#define USER_INTERFACE_DISPLAY_CLEAR       5

#define USER_INTERFACE_MENU_START          0
#define USER_INTERFACE_MENU_ON_INPUT       1
#define USER_INTERFACE_MENU_CONFIG         2
#define USER_INTERFACE_MENU_CLEAR          3

#define USER_INTERFACE_BUTTON_ENTER        1
#define USER_INTERFACE_BUTTON_LEFT         2
#define USER_INTERFACE_BUTTON_RIGHT        3

/*******************************************************************
 * Types
 ******************************************************************/

typedef struct User_Interface_Loading {
    OLED_Screen_Button_Rectangle title;
} User_Interface_Loading;

typedef struct User_Interface_Master {
    OLED_Screen_Button_Rectangle title;
} User_Interface_Master;

typedef struct User_Interface_Main {
    OLED_Screen_Button_Rectangle menus[4];
} User_Interface_Main;

typedef struct User_Interface_Record {
    OLED_Screen_Button_Rectangle rpm_title;
    OLED_Screen_Button_Rectangle rpm_val;
    OLED_Screen_Button_Rectangle rpm_max;
    OLED_Screen_Button_Rectangle pressure_title;
    OLED_Screen_Button_Rectangle pressure_val;
    OLED_Screen_Button_Rectangle pressure_max;
} User_Interface_Record;

typedef struct User_Interface_OnInput {
    OLED_Screen_Button_Rectangle title;
} User_Interface_OnInput;

typedef struct User_Interface_Config {
    OLED_Screen_Button_Rectangle parameters[PARAMETERS_SIZE];
    OLED_Screen_Button_Rectangle exit;
} User_Interface_Config;

typedef struct User_Interface_Clear {
    OLED_Screen_Button_Rectangle title;
} User_Interface_Clear;

typedef struct User_Interface_Data {
    User_Interface_Loading loading;
    User_Interface_Master master;
    User_Interface_Main main;
    User_Interface_Record record;
    User_Interface_OnInput onInput;
    User_Interface_Config config;
    User_Interface_Clear clear;
} User_Interface_Data;

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void user_interface_init(void);
void user_interface_switch_screen(uint8_t screen);

#endif /* USER_INTERFACE_H */