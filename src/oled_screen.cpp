/**
* oled_screen.c
*/

#include "oled_screen.h"

OLED display = OLED(SDA,SCL,NO_RESET_PIN, OLED_SCREEN_ADDR, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, 1);

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void oled_screen_draw_string_center_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t s_size, OLED::tSize scaling = OLED::NORMAL_SIZE, OLED::tColor color = OLED::WHITE);

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Draws a string a the center of a rectangle
 * @param  x1 the x coordinate of the start of the rectangle
 * @param  y1 the y coordinate of the start of the rectangle
 * @param  x2 the x coordinate of the end of the rectangle
 * @param  y2 the ycoordinate of the end of the rectangle
 * @param  s the string
 * @param  s_size the length of the string
 * @param  scalling the scalling of the string
 * @param  color the color of the string
 * @retval The generated button
 */
void oled_screen_string_center_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t s_size, OLED::tSize scaling = OLED::NORMAL_SIZE, OLED::tColor color = OLED::WHITE){
  
  uint8_t x, y;

  switch (scaling)
  {
  case OLED::DOUBLE_SIZE:
    /* 12*16 */
    x = (x1 + x2) / 2 - 12 / 2 * s_size;
    y = (y1 + y2) / 2 - 16 / 2;
    break;
  case OLED::NORMAL_SIZE:
    /* 6x8 */
  default:
    x = (x1 + x2) / 2 - 6 / 2 * s_size;
    y = (y1 + y2) / 2 - 8 / 2;
    break;
  }

  display.draw_string(x, y, s, scaling, color);

}

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the OLED screen features
 * @param  None
 * @retval None
 */
void oled_screen_init(){
  display.begin();
}

/**
 * @brief  Displays on the OLED screen
 * @param  None
 * @retval None
 */
void oled_screen_display(){
  display.display();
}

/**
 * @brief  Clears the OLED screen
 * @param  None
 * @retval None
 */
void oled_screen_clear(){
  display.clear();
}

/**
 * @brief  Draws a rectangle
 * @param  x1 the x coordinate of the start of the rectangle
 * @param  y1 the y coordinate of the start of the rectangle
 * @param  x2 the x coordinate of the end of the rectangle
 * @param  y2 the ycoordinate of the end of the rectangle
 * @param  fillMode whether the rectangle is filled or hollow
 * @param  color the color of the rectangle
 * @retval None
 */
void oled_screen_draw_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t fillMode, uint8_t color){

  display.draw_rectangle(x1,y1,x2,y2,(OLED::tFillmode)fillMode,(OLED::tColor)color);

}

/**
 * @brief  Initializes a rectangle button
 * @param  x1 the x coordinate of the start of the button
 * @param  y1 the y coordinate of the start of the button
 * @param  x2 the x coordinate of the end of the button
 * @param  y2 the ycoordinate of the end of the button
 * @param  s the text of the button
 * @param  s_size the length of the text of the button
 * @param  state the state of the button
 * @param  scalling the scalling of the text of the button
 * @retval The generated button
 */
OLED_Screen_Button_Rectangle oled_screen_init_button_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t state, OLED::tSize scaling){

  OLED_Screen_Button_Rectangle button_rectangle;
  uint8_t s_size;

  s_size = 0;
  while (s[s_size] != '\0'){
    s_size++;
  }
  

  button_rectangle.x1 = x1;
  button_rectangle.y1 = y1;
  button_rectangle.x2 = x2;
  button_rectangle.y2 = y2;
  button_rectangle.s_size = s_size;
  button_rectangle.state = state;
  button_rectangle.scaling = scaling;

  memcpy(button_rectangle.s,s,s_size+1);

  return button_rectangle;
}

/**
 * @brief  Initializes a rectangle button
 * @param  b address of the button
 * @param  x1 the x coordinate of the start of the button
 * @param  y1 the y coordinate of the start of the button
 * @param  x2 the x coordinate of the end of the button
 * @param  y2 the ycoordinate of the end of the button
 * @param  s the text of the button
 * @param  state the state of the button
 * @param  scalling the scalling of the text of the button
 * @retval The generated button
 */
void oled_screen_init_button_rectangle_m(OLED_Screen_Button_Rectangle *b, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const char *s, uint8_t state, OLED::tSize scaling){

  OLED_Screen_Button_Rectangle button_rectangle;
  uint8_t s_size;

  s_size = 0;
  while (s[s_size] != '\0'){
    s_size++;
  }

  button_rectangle.x1 = x1;
  button_rectangle.y1 = y1;
  button_rectangle.x2 = x2;
  button_rectangle.y2 = y2;
  button_rectangle.s_size = s_size;
  button_rectangle.state = state;
  button_rectangle.scaling = scaling;

  memcpy(button_rectangle.s,s,s_size+1);

  memcpy(b,&button_rectangle,sizeof(OLED_Screen_Button_Rectangle));
}

/**
 * @brief  Draws a rectangle button with its features
 * @param  button_rectangle the button to draw
 * @retval None
 */
void oled_screen_draw_button_rectangle(OLED_Screen_Button_Rectangle *button_rectangle){

  OLED::tColor text_color, background_color, outline_color;

  switch (button_rectangle->state)
  {
  case OLED_SCREEN_STATE_SELECTED:
    text_color = OLED::WHITE;
    background_color = OLED::BLACK;
    outline_color = OLED::WHITE;
    break;
  case OLED_SCREEN_STATE_UNACTIVE_B:
    text_color = OLED::WHITE;
    background_color = OLED::BLACK;
    outline_color = OLED::BLACK;
    break;
  case OLED_SCREEN_STATE_UNACTIVE_W:
    text_color = OLED::BLACK;
    background_color = OLED::WHITE;
    outline_color = OLED::WHITE;
    break;
  case OLED_SCREEN_STATE_UNSELECTED:
  default:
    text_color = OLED::WHITE;
    background_color = OLED::BLACK;
    outline_color = OLED::BLACK;
    break;
  }

  /* Draws the button's background */
  display.draw_rectangle(button_rectangle->x1, button_rectangle->y1, button_rectangle->x2, button_rectangle->y2,OLED::SOLID,background_color);

  /* Draws the button's outline */
  display.draw_rectangle(button_rectangle->x1, button_rectangle->y1, button_rectangle->x2, button_rectangle->y2,OLED::HOLLOW,outline_color);

  /* Draws the button's text */
  oled_screen_string_center_rectangle(button_rectangle->x1, button_rectangle->y1, button_rectangle->x2, button_rectangle->y2, (char *)button_rectangle->s, button_rectangle->s_size, (OLED::tSize)button_rectangle->scaling, text_color);

}