/**
* user_interface.c
*/

#include "user_interface.h"

unsigned long lastButtonPressed;
User_Interface_Data user_interface_data;
uint8_t user_interface_selected_option;
uint8_t user_interface_button_pressed;

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void user_interface_init_graphical(void);
void user_interface_init_buttons(void);
void user_interface_enable_dir_buttons(void);
void user_interface_disable_dir_buttons(void);
void user_interface_button_enter_interupt_handler(void);
void user_interface_button_left_interupt_handler(void);
void user_interface_button_right_interupt_handler(void);
void user_interface_display_loading_screen(void);
void user_interface_display_main_screen(void);
void user_interface_display_record_screen(void);
void user_interface_display_onInput_screen(void);
void user_interface_display_config_screen(void);
void user_interface_display_option_screen(void);
void user_interface_display_clear_screen(void);

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Initializes the graphical components of the user interface
 * @param  None
 * @retval None
 */
void user_interface_init_graphical(){

  User_Interface_Loading loading;
  User_Interface_Master master;
  User_Interface_Main main;
  User_Interface_Record record;
  User_Interface_OnInput onInput;
  User_Interface_Config config;
  User_Interface_Clear clear;
  OLED_Screen_Button_Rectangle loading_title;
  OLED_Screen_Button_Rectangle master_title;
  OLED_Screen_Button_Rectangle main_record, main_onInput, main_config, main_clear;
  OLED_Screen_Button_Rectangle record_rpm_title, record_rpm_val, record_rpm_max, record_pressure_title, record_pressure_val, record_pressure_max;
  OLED_Screen_Button_Rectangle onInput_title;
  OLED_Screen_Button_Rectangle config_exit;
  OLED_Screen_Button_Rectangle clear_title;
  uint8_t main_button_width, main_button_height, main_button_height_s;
  uint8_t option_title[16];
  uint8_t i, j;

  main_button_width = OLED_SCREEN_WIDTH / 2 - USER_INTERFACE_MAIN_BUTTON_OFFSET;
  main_button_height = (OLED_SCREEN_HEIGHT - USER_INTERFACE_MASTER_HEIGHT) / 2 - USER_INTERFACE_MAIN_BUTTON_OFFSET;
  main_button_height_s = (OLED_SCREEN_HEIGHT - USER_INTERFACE_MASTER_HEIGHT) / 3 - USER_INTERFACE_MAIN_BUTTON_OFFSET;

  /* Master components */
  master_title = oled_screen_init_button_rectangle(0, 0, OLED_SCREEN_WIDTH, USER_INTERFACE_MASTER_HEIGHT, "Testbed", OLED_SCREEN_STATE_UNACTIVE_W, OLED::DOUBLE_SIZE);
  master.title = master_title;

  /* Main screen components */
  main_record = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_height, "Record", OLED_SCREEN_STATE_SELECTED, OLED::NORMAL_SIZE);
  main_onInput = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_height, "On Input", OLED_SCREEN_STATE_UNSELECTED, OLED::NORMAL_SIZE);
  main_config = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_height, USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height, "Config", OLED_SCREEN_STATE_UNSELECTED, OLED::NORMAL_SIZE);
  main_clear = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_height, USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height, "Clear", OLED_SCREEN_STATE_UNSELECTED, OLED::NORMAL_SIZE);
  main.menus[0] = main_record;
  main.menus[1] = main_onInput;
  main.menus[2] = main_config;
  main.menus[3] = main_clear;
  
  /* Recording screen components */
  record_rpm_title = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_height_s, "RPM", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record_rpm_val = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_height_s, USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height_s, "0", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record_rpm_max = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height_s, USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_width, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*main_button_height_s, "0", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record_pressure_title = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET/2+main_button_height_s, "Pressure", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record_pressure_val = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_height_s, USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_width, USER_INTERFACE_MASTER_HEIGHT+USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height_s, "psi", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record_pressure_max = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET+main_button_width, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height_s, USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_width, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*main_button_height_s, "0PSI", OLED_SCREEN_STATE_UNACTIVE_B, OLED::NORMAL_SIZE);
  record.rpm_title = record_rpm_title;
  record.rpm_val = record_rpm_val;
  record.rpm_max = record_rpm_max;
  record.pressure_title = record_pressure_title;
  record.pressure_val = record_pressure_val;
  record.pressure_max = record_pressure_max;

  /* On input screen components */
  onInput_title = oled_screen_init_button_rectangle(0, USER_INTERFACE_MASTER_HEIGHT, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, "On Input", OLED_SCREEN_STATE_UNACTIVE_B, OLED::DOUBLE_SIZE);
  onInput.title = onInput_title;

  /* Configuration screen components */
  for(i=0;i<PARAMETERS_SIZE;i++){
    j = 0;
    while(parameters[i].name_pp[j] != '\0' && parameters[i].name_pp[j] != '\t'){
      option_title[j] = parameters[i].name_pp[j];
      j++;
    }
    option_title[j] = '\0';
    oled_screen_init_button_rectangle_m(config.parameters+i,USER_INTERFACE_MAIN_BUTTON_OFFSET/2,0,OLED_SCREEN_WIDTH-USER_INTERFACE_MAIN_BUTTON_OFFSET/2, 0,(char *)option_title,OLED_SCREEN_STATE_UNSELECTED,OLED::NORMAL_SIZE);
  }
  config_exit = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2,USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+2*main_button_height_s,OLED_SCREEN_WIDTH-USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*main_button_height_s,"Exit",OLED_SCREEN_STATE_UNSELECTED,OLED::NORMAL_SIZE);
  config.exit = config_exit;

  /* Clearing screen components */
  clear_title = oled_screen_init_button_rectangle(0, USER_INTERFACE_MASTER_HEIGHT, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, "Clearing", OLED_SCREEN_STATE_UNACTIVE_B, OLED::DOUBLE_SIZE);
  clear.title = clear_title;

  /* Init loading components */
  loading_title = oled_screen_init_button_rectangle(0, 0, OLED_SCREEN_WIDTH, OLED_SCREEN_HEIGHT, "Hovestrad", OLED_SCREEN_STATE_UNACTIVE_B, OLED::DOUBLE_SIZE);
  loading.title = loading_title;

  user_interface_data.loading = loading;
  user_interface_data.master = master;
  user_interface_data.main = main;
  user_interface_data.record = record;
  user_interface_data.onInput = onInput;
  user_interface_data.config = config;
  user_interface_data.clear = clear;
}

/**
 * @brief  Initializes the buttons
 * @param  None
 * @retval None
 */
void user_interface_init_buttons(){

  /* Initialize the up button pin */
  pinMode(BUTTON_ENTER, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_ENTER), user_interface_button_enter_interupt_handler, RISING);

  /* Initialize the left button pin */
  pinMode(BUTTON_LEFT, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT), user_interface_button_left_interupt_handler, RISING);

  /* Initialize the right button pin */
  pinMode(BUTTON_RIGHT, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT), user_interface_button_right_interupt_handler, RISING);
}

/**
 * @brief  Enables the direction buttons
 * @param  None
 * @retval None
 */
void user_interface_enable_dir_buttons(){

  /* Enables the left button pin */
  attachInterrupt(digitalPinToInterrupt(BUTTON_LEFT), user_interface_button_left_interupt_handler, RISING);

  /* Enables the right button pin */
  attachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT), user_interface_button_right_interupt_handler, RISING);

}

/**
 * @brief  Disables the direction buttons
 * @param  None
 * @retval None
 */
void user_interface_disable_dir_buttons(){

  /* Disables the left button pin */
  detachInterrupt(digitalPinToInterrupt(BUTTON_LEFT));

  /* Disables the right button pin */
  detachInterrupt(digitalPinToInterrupt(BUTTON_RIGHT));

}

/**
 * @brief  Handles an input interupt for the enter button
 * @param  None
 * @retval None
 */
void user_interface_button_enter_interupt_handler(){

  unsigned long esptime;

  /* Software debouncing logic... */
  esptime = millis();
  if(esptime - lastButtonPressed > USER_INTERFACE_BUTTON_COOLDOWN){
    lastButtonPressed = esptime;
    user_interface_button_pressed = USER_INTERFACE_BUTTON_ENTER;
  }
}

/**
 * @brief  Handles an input interupt for the left button
 * @param  None
 * @retval None
 */
void user_interface_button_left_interupt_handler(){

  unsigned long esptime;

  /* Software debouncing logic... */
  esptime = millis();
  if(esptime - lastButtonPressed > USER_INTERFACE_BUTTON_COOLDOWN){
    lastButtonPressed = esptime;
    user_interface_button_pressed = USER_INTERFACE_BUTTON_LEFT;
  }
}

/**
 * @brief  Handles an input interupt for the right button
 * @param  None
 * @retval None
 */
void user_interface_button_right_interupt_handler(){

  unsigned long esptime;

  /* Software debouncing logic... */
  esptime = millis();
  if(esptime - lastButtonPressed > USER_INTERFACE_BUTTON_COOLDOWN){
    lastButtonPressed = esptime;
    user_interface_button_pressed = USER_INTERFACE_BUTTON_RIGHT;
  }
}

/**
 * @brief  Displays the loading screen
 * @param  None
 * @retval None
 */
void user_interface_display_loading_screen(){

  oled_screen_clear();

  /* Displays the loading screen */
  oled_screen_draw_button_rectangle(&(user_interface_data.loading.title));

  oled_screen_display();
}

/**
 * @brief  Displays the main screen
 * @param  None
 * @retval None
 */
void user_interface_display_main_screen(){

  uint8_t selected_menu;
  uint8_t exit_option;
  uint8_t i;

  selected_menu = 0;
  exit_option = 0;

  while(!exit_option){

    oled_screen_clear();

    /* Displays the screen features */
    for(i=0; i<4; i++){
      if(i==selected_menu){
        user_interface_data.main.menus[i].state = OLED_SCREEN_STATE_SELECTED;
      } else {
        user_interface_data.main.menus[i].state = OLED_SCREEN_STATE_UNSELECTED;
      }
      oled_screen_draw_button_rectangle(&(user_interface_data.main.menus[i]));
    }

    /* Displays the master features */
    oled_screen_draw_button_rectangle(&(user_interface_data.master.title));

    oled_screen_display();

    /* Waits for input */
    while(!user_interface_button_pressed){
      delay(100);
    }
    switch (user_interface_button_pressed)
    {
    case USER_INTERFACE_BUTTON_RIGHT:
      /* Right button pressed */
      user_interface_button_pressed = 0;
      selected_menu++;
      if(selected_menu > 3){
        selected_menu = 0;
      }
      break;
    case USER_INTERFACE_BUTTON_LEFT:
      /* Left button pressed */
      user_interface_button_pressed = 0;
      selected_menu--;
      if(selected_menu > 3){
        selected_menu = 3;
      }
      break;
    case USER_INTERFACE_BUTTON_ENTER:
      /* Enter button pressed */
      user_interface_button_pressed = 0;

      /* Access screen selected */
      switch (selected_menu)
      {
      case USER_INTERFACE_MENU_CLEAR:
        user_interface_display_clear_screen();
        break;
      case USER_INTERFACE_MENU_CONFIG:
        user_interface_display_config_screen();
        break;
      case USER_INTERFACE_MENU_ON_INPUT:
        user_interface_display_onInput_screen();
        break;
      case USER_INTERFACE_MENU_START:
      default:
        user_interface_display_record_screen();
        break;
      }
      break;
    }
    
  }

}

/**
 * @brief  Displays the recording screen
 * @param  None
 * @retval None
 */
void user_interface_display_record_screen(){

  OLED_Screen_Button_Rectangle title;
  uint8_t exit_option;
  uint8_t updated;
  uint8_t rpm_val_str[16], rpm_max_str[16], pressure_val_str[16], pressure_max_str[16];
  uint8_t rpm_val_len, rpm_max_len, pressure_val_len, pressure_max_len;
  uint8_t record_id;
  uint8_t file_name_base[16], sd_card_file_name[16], file_end[32];
  uint8_t ui_ir_speed_sensor_pin, ui_ir_speed_sensor_vcc_pin;

  exit_option = 0;
  updated = 0;

  /* Manages different behaviour depending on the reading mode */
  switch (parameters[PARAMETERS_READ_MODE].value)
  {
  case 1:
    /* Speed */
    ui_ir_speed_sensor_pin = IR_SPEED_SENSOR_SPEED;
    ui_ir_speed_sensor_vcc_pin = IR_SPEED_SENSOR_SPEED_VCC;
    memcpy(file_name_base,"/speed_%hd.csv\0",16);
    break;
  case 0:
  default:
    /* Power */
    ui_ir_speed_sensor_pin = IR_SPEED_SENSOR_POWER;
    ui_ir_speed_sensor_vcc_pin = IR_SPEED_SENSOR_POWER_VCC;
    memcpy(file_name_base,"/power_%hd.csv\0",16);
    break;
  }

  /* Init new file on the SD card */
  record_id = 0;
  do {
    sprintf((char *)sd_card_file_name,(char *)file_name_base,record_id);
    record_id++;
  } while(sd_card_open(sd_card_file_name));
  record_id--;
  sd_card_write(sd_card_file_name, (uint8_t *)"rpm,pressure\r\n");
  record_init_data(record_id);

  /* Initializes the ir speed sensor */
  ir_speed_sensor_init_record((uint8_t)(parameters[PARAMETERS_NB_BLADES].value * parameters[PARAMETERS_NB_BLADES].factor));
  ir_speed_sensor_enable(ui_ir_speed_sensor_pin,ui_ir_speed_sensor_vcc_pin);

  /* Initializes the title button */
  title = oled_screen_init_button_rectangle(0, 0, OLED_SCREEN_WIDTH, USER_INTERFACE_MASTER_HEIGHT, (char *)sd_card_file_name+1, OLED_SCREEN_STATE_UNACTIVE_W, OLED::NORMAL_SIZE);

  while (!exit_option) {

    /* Record loop */
    updated = record_loop();

    if(updated){
      /* Updates values */
      rpm_val_len = rpm_max_len = pressure_val_len = pressure_max_len = 0;

      /* RPM current */
      sprintf((char *)rpm_val_str,"%hu",data.ir_speed_sensor_value_cur);
      while(rpm_val_str[rpm_val_len] != '\0'){
        rpm_val_len++;
      }
      memcpy(user_interface_data.record.rpm_val.s,rpm_val_str,rpm_val_len+1);
      user_interface_data.record.rpm_val.s_size = rpm_val_len;

      /* RPM max */
      sprintf((char *)rpm_max_str,"%hu",data.ir_speed_sensor_value_max);
      while(rpm_max_str[rpm_max_len] != '\0'){
        rpm_max_len++;
      }
      memcpy(user_interface_data.record.rpm_max.s,rpm_max_str,rpm_max_len+1);
      user_interface_data.record.rpm_max.s_size = rpm_max_len;

      /* Pressure current */
      sprintf((char *)pressure_val_str,"%huPSI",data.pressure_sensor_value_cur);
      while(pressure_val_str[pressure_val_len] != '\0'){
        pressure_val_len++;
      }
      memcpy(user_interface_data.record.pressure_val.s,pressure_val_str,pressure_val_len+1);
      user_interface_data.record.pressure_val.s_size = pressure_val_len;

      /* Pressure max */
      sprintf((char *)pressure_max_str,"%huPSI",data.pressure_sensor_value_max);
      while(pressure_max_str[pressure_max_len] != '\0'){
        pressure_max_len++;
      }
      memcpy(user_interface_data.record.pressure_max.s,pressure_max_str,pressure_max_len+1);
      user_interface_data.record.pressure_max.s_size = pressure_max_len;
    
      oled_screen_clear();

      /* Displays the screen features */
      oled_screen_draw_button_rectangle(&(user_interface_data.record.rpm_title));
      oled_screen_draw_button_rectangle(&(user_interface_data.record.rpm_val));
      oled_screen_draw_button_rectangle(&(user_interface_data.record.rpm_max));
      oled_screen_draw_button_rectangle(&(user_interface_data.record.pressure_title));
      oled_screen_draw_button_rectangle(&(user_interface_data.record.pressure_val));
      oled_screen_draw_button_rectangle(&(user_interface_data.record.pressure_max));

      /* Displays the name of the file */
      oled_screen_draw_button_rectangle(&title);

      oled_screen_display();
    }

    /* Checks for exit */
    if(user_interface_button_pressed){
      user_interface_button_pressed = 0;
      exit_option = 1;
    }
  }

  /* Writes the maximums */
  sprintf((char *)file_end,"===,===\r\n%hd,%hd",data.ir_speed_sensor_value_max,data.pressure_sensor_value_max);
  sd_card_append(sd_card_file_name, file_end);

  /* Disbles the IR speed sensor */
  ir_speed_sensor_disable(ui_ir_speed_sensor_pin,ui_ir_speed_sensor_vcc_pin);
}

/**
 * @brief  Displays the on input screen
 * @param  None
 * @retval None
 */
void user_interface_display_onInput_screen(){

  uint8_t input_detected;
  uint8_t rotation_count;

  input_detected = 0;
  rotation_count = 0;

  oled_screen_clear();

  /* Displays the screen features */
  oled_screen_draw_button_rectangle(&(user_interface_data.onInput.title));

  /* Displays the master features */
  oled_screen_draw_button_rectangle(&(user_interface_data.master.title));

  oled_screen_display();

  /* Waits for the input */
  // TODO
  while (!input_detected){
    
    /* Button enter pressed */
    if(user_interface_button_pressed){
      user_interface_button_pressed = 0;
      if(user_interface_button_pressed == USER_INTERFACE_BUTTON_ENTER){
        input_detected = 1;
      }
    }

    /* 10 rotation detected */
    if(1){
      /* Rotation detected */
      rotation_count++;
      if(rotation_count >= 10){
        input_detected = 1;
      }
    }

    delay(100);
  }
  

}

/**
 * @brief  Displays the configuration screen
 * @param  None
 * @retval None
 */
void user_interface_display_config_screen(){

  uint8_t height, y;
  uint8_t i;
  uint8_t exit_option;

  exit_option = 0;
  user_interface_selected_option = 0;
  height = (OLED_SCREEN_HEIGHT - USER_INTERFACE_MASTER_HEIGHT) / 3 - USER_INTERFACE_MAIN_BUTTON_OFFSET;

  while(!exit_option){

    oled_screen_clear();

    /* Displays the screen features */
    if(user_interface_selected_option == 0){
      /* Selected ID at the top */
      for(i=user_interface_selected_option;i<user_interface_selected_option+3;i++){
        if(i==user_interface_selected_option){
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_SELECTED;
        } else {
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_UNSELECTED;
        }

        y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * (.5 + i-user_interface_selected_option) + height * (i-user_interface_selected_option);
        user_interface_data.config.parameters[i].y1 = y;
        user_interface_data.config.parameters[i].y2 = y + height;
        
        oled_screen_draw_button_rectangle(&(user_interface_data.config.parameters[i]));
      }
    } else if (user_interface_selected_option == PARAMETERS_SIZE-1){
      /* Selected ID in the middle with exit at the bottom */
      for(i=user_interface_selected_option-1;i<user_interface_selected_option+1;i++){
        if(i==user_interface_selected_option){
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_SELECTED;
        } else {
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_UNSELECTED;
        }

        y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * (.5 + i-user_interface_selected_option+1) + height * (i-user_interface_selected_option+1);
        user_interface_data.config.parameters[i].y1 = y;
        user_interface_data.config.parameters[i].y2 = y + height;

        oled_screen_draw_button_rectangle(&(user_interface_data.config.parameters[i]));
      }

      /* Display exit unselected */
      user_interface_data.config.exit.state = OLED_SCREEN_STATE_UNSELECTED;
      oled_screen_draw_button_rectangle(&user_interface_data.config.exit);

    } else if(user_interface_selected_option == PARAMETERS_SIZE){
      /* Selected ID is exit and at the bottom */
      for(i=user_interface_selected_option-2;i<user_interface_selected_option;i++){
        user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_UNSELECTED;

        y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * (.5 + i-user_interface_selected_option+2) + height * (i-user_interface_selected_option+2);
        user_interface_data.config.parameters[i].y1 = y;
        user_interface_data.config.parameters[i].y2 = y + height;

        oled_screen_draw_button_rectangle(&(user_interface_data.config.parameters[i]));
      }

      /* Display exit selected */
      user_interface_data.config.exit.state = OLED_SCREEN_STATE_SELECTED;
      oled_screen_draw_button_rectangle(&user_interface_data.config.exit);

    } else {
      /* Selected ID in the middle */
      for(i=user_interface_selected_option-1;i<user_interface_selected_option+2;i++){
        if(i==user_interface_selected_option){
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_SELECTED;
        } else {
          user_interface_data.config.parameters[i].state = OLED_SCREEN_STATE_UNSELECTED;
        }

        y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * (.5 + i-user_interface_selected_option+1) + height * (i-user_interface_selected_option+1);
        user_interface_data.config.parameters[i].y1 = y;
        user_interface_data.config.parameters[i].y2 = y + height;

        oled_screen_draw_button_rectangle(&(user_interface_data.config.parameters[i]));
      }
    }

    /* Displays the master features */
    oled_screen_draw_button_rectangle(&(user_interface_data.master.title));

    oled_screen_display();

    /* Waits for input */
    while(!user_interface_button_pressed){
      delay(100);
    }
    switch (user_interface_button_pressed)
    {
    case USER_INTERFACE_BUTTON_RIGHT:
      /* Right button pressed */
      user_interface_button_pressed = 0;
      user_interface_selected_option++;
      if(user_interface_selected_option > PARAMETERS_SIZE){
        user_interface_selected_option = 0;
      }
      break;
    case USER_INTERFACE_BUTTON_LEFT:
      /* Left button pressed */
      user_interface_button_pressed = 0;
      user_interface_selected_option--;
      if(user_interface_selected_option > PARAMETERS_SIZE){
        user_interface_selected_option = PARAMETERS_SIZE;
      }
      break;
    case USER_INTERFACE_BUTTON_ENTER:
      /* Enter button pressed */
      user_interface_button_pressed = 0;
      if(user_interface_selected_option < PARAMETERS_SIZE){
        user_interface_display_option_screen();
        /* Saves the changes in the NVS */
        nvs_write_parameters();
      } else {
        exit_option = 1;
      }
      break;
    }
  }
}

/**
 * @brief  Displays the option edit screen
 * @param  None
 * @retval None
 */
void user_interface_display_option_screen(){

  uint8_t x, y, width, width_bar, height;
  OLED_Screen_Button_Rectangle value, option1, option2;
  uint8_t value_str[16], option1_str[16], option2_str[16];
  uint8_t exit_option;
  uint8_t i, j;

  exit_option = 0;
  height = (OLED_SCREEN_HEIGHT - USER_INTERFACE_MASTER_HEIGHT) / 3 - USER_INTERFACE_MAIN_BUTTON_OFFSET;

  while(!exit_option){

    oled_screen_clear();

    /* Displays the option name */
    y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET /2;
    user_interface_data.config.parameters[user_interface_selected_option].y1 = y;
    user_interface_data.config.parameters[user_interface_selected_option].y2 = y + height;
    user_interface_data.config.parameters[user_interface_selected_option].state = OLED_SCREEN_STATE_UNSELECTED;
    oled_screen_draw_button_rectangle(&(user_interface_data.config.parameters[user_interface_selected_option]));

    switch(parameters[user_interface_selected_option].param_mode){
      case PARAMETERS_MODE_BOOL:
      /* Boolean type option */
        i = 0;
        while(parameters[user_interface_selected_option].name_pp[i] != '\t'){
          i++;
        }

        i++;
        j = 0;
        while(parameters[user_interface_selected_option].name_pp[i] != '\t'){
          option1_str[j] = parameters[user_interface_selected_option].name_pp[i];
          i++;
          j++;
        }
        option1_str[j] = '\0';

        i++;
        j = 0;
        while(parameters[user_interface_selected_option].name_pp[i] != '\0'){
          option2_str[j] = parameters[user_interface_selected_option].name_pp[i];
          i++;
          j++;
        }
        option2_str[j] = '\0';

        /* Displays the first option */
        option1 = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2,USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * 1.5 + height,OLED_SCREEN_WIDTH/2-USER_INTERFACE_MAIN_BUTTON_OFFSET/2,USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*height,(char *)option1_str,parameters[user_interface_selected_option].value ? OLED_SCREEN_STATE_UNSELECTED : OLED_SCREEN_STATE_SELECTED,OLED::NORMAL_SIZE);
        oled_screen_draw_button_rectangle(&option1);

        /* Displays the second option */
        option2 = oled_screen_init_button_rectangle((OLED_SCREEN_WIDTH+USER_INTERFACE_MAIN_BUTTON_OFFSET)/2,USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * 1.5 + height,OLED_SCREEN_WIDTH-USER_INTERFACE_MAIN_BUTTON_OFFSET/2,USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*height,(char *)option2_str,parameters[user_interface_selected_option].value ? OLED_SCREEN_STATE_SELECTED : OLED_SCREEN_STATE_UNSELECTED,OLED::NORMAL_SIZE);
        oled_screen_draw_button_rectangle(&option2);

        break;
      case PARAMETERS_MODE_VALUE:
      /* Value type option */
      default:
        /* Displays the option bar */
        x = USER_INTERFACE_MAIN_BUTTON_OFFSET/2;
        y = USER_INTERFACE_MASTER_HEIGHT + USER_INTERFACE_MAIN_BUTTON_OFFSET * 1.5 + height;
        width = OLED_SCREEN_WIDTH - USER_INTERFACE_MAIN_BUTTON_OFFSET;
        width_bar = (float )width / (float) (parameters[user_interface_selected_option].max-parameters[user_interface_selected_option].min) * (float) (parameters[user_interface_selected_option].value-parameters[user_interface_selected_option].min);
        /* Draws the bar's background */
        oled_screen_draw_rectangle(x, y, x+width_bar, y+height, OLED::SOLID, OLED::WHITE);
        /* Draws the bar's outline */
        oled_screen_draw_rectangle(x, y, x+width, y+height, OLED::HOLLOW, OLED::WHITE);

        /* Displays the option value */
        sprintf((char *)value_str,"%d",(int)(parameters[user_interface_selected_option].value*parameters[user_interface_selected_option].factor));
        value = oled_screen_init_button_rectangle(USER_INTERFACE_MAIN_BUTTON_OFFSET/2,USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+2*height,OLED_SCREEN_WIDTH-USER_INTERFACE_MAIN_BUTTON_OFFSET/2, USER_INTERFACE_MASTER_HEIGHT+2*USER_INTERFACE_MAIN_BUTTON_OFFSET+3*height,(char *)value_str,OLED_SCREEN_STATE_UNSELECTED,OLED::NORMAL_SIZE);
        oled_screen_draw_button_rectangle(&value);
        break;
    }

    /* Displays the master features */
    oled_screen_draw_button_rectangle(&(user_interface_data.master.title));

    oled_screen_display();

    /* Waits for input */
    while(!user_interface_button_pressed){
      delay(100);
    }
    switch (user_interface_button_pressed)
    {
    case USER_INTERFACE_BUTTON_RIGHT:
      /* Right button pressed */
      user_interface_button_pressed = 0;
      if(parameters[user_interface_selected_option].value < parameters[user_interface_selected_option].max){
        parameters[user_interface_selected_option].value++;
      }
      break;
    case USER_INTERFACE_BUTTON_LEFT:
      /* Left button pressed */
      user_interface_button_pressed = 0;
      if(parameters[user_interface_selected_option].value > parameters[user_interface_selected_option].min){
        parameters[user_interface_selected_option].value--;
      }
      break;
    case USER_INTERFACE_BUTTON_ENTER:
      /* Enter button pressed */
      user_interface_button_pressed = 0;
      exit_option = 1;
      break;
    }
    
  }
}

/**
 * @brief  Displays the clearing screen
 * @param  None
 * @retval None
 */
void user_interface_display_clear_screen(){

  uint8_t i;

  oled_screen_clear();

  /* Displays the screen features */
  oled_screen_draw_button_rectangle(&(user_interface_data.clear.title));

  /* Displays the master features */
  oled_screen_draw_button_rectangle(&(user_interface_data.master.title));

  oled_screen_display();

  /* Resets the values */
  for(i=0;i<PARAMETERS_SIZE;i++){
    parameters[i].value = parameters[i].default_value;
  }

  /* Apply reset on the NVS */
  nvs_write_parameters();

  delay(2000);
}

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the user interface
 * @param  None
 * @retval None
 */
void user_interface_init(){

  /* Initializes the OLED screen */
  oled_screen_init();

  /* Initializes the graphical components */
  user_interface_init_graphical();

  /* Initializes the button control */
  user_interface_init_buttons();

  user_interface_button_pressed = 0;
}

/**
 * @brief  Switches between screens
 * @param  screen the selected screen
 * @retval None
 */
void user_interface_switch_screen(uint8_t screen){
  
  switch (screen) {
  case USER_INTERFACE_DISPLAY_CLEAR:
    user_interface_display_clear_screen();
    break;
  case USER_INTERFACE_DISPLAY_CONFIG:
    user_interface_display_config_screen();
    break;
  case USER_INTERFACE_DISPLAY_ON_INPUT:
    user_interface_display_onInput_screen();
    break;
  case USER_INTERFACE_DISPLAY_RECORD:
    user_interface_display_record_screen();
    break;
  case USER_INTERFACE_DISPLAY_MAIN:
    user_interface_display_main_screen();
    break;
  case USER_INTERFACE_DISPLAY_LOADING:
  default:
    user_interface_display_loading_screen();
    break;
  }

}