/**
* oled_screen.h
*/

#ifndef OLED_SCREEN_H
#define OLED_SCREEN_H

/*******************************************************************
 * Libraries
 ******************************************************************/

/* Default libraries */
#include <Arduino.h>
#include <oled.h>

/* Custom libraries */
#include "config.h"

/*******************************************************************
 * Constants
 ******************************************************************/

#define OLED_SCREEN_ADDR                0x3C
#define OLED_SCREEN_WIDTH               130
#define OLED_SCREEN_HEIGHT              64

#define OLED_SCREEN_STATE_UNSELECTED    0
#define OLED_SCREEN_STATE_SELECTED      1
#define OLED_SCREEN_STATE_UNACTIVE_B    2
#define OLED_SCREEN_STATE_UNACTIVE_W    3

/*******************************************************************
 * Types
 ******************************************************************/

typedef struct OLED_Screen_Button_Rectangle {
    uint8_t s[32];
    uint8_t x1;
    uint8_t y1;
    uint8_t x2;
    uint8_t y2;
    uint8_t s_size;
    uint8_t state;
    uint8_t scaling;
} OLED_Screen_Button_Rectangle;

/*******************************************************************
 * Public functions declarations 
 ******************************************************************/

void oled_screen_init(void);
void oled_screen_display(void);
void oled_screen_clear(void);
void oled_screen_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fillMode, uint8_t color);
OLED_Screen_Button_Rectangle oled_screen_init_button_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t state, OLED::tSize scaling);
void oled_screen_init_button_rectangle_m(OLED_Screen_Button_Rectangle *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t state, OLED::tSize scaling);
void oled_screen_draw_button_rectangle(OLED_Screen_Button_Rectangle *button_rectangle);

#endif /* OLED_SCREEN_H */