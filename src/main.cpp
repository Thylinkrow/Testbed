/**
* main.cpp
*/

#include "main.h"

char version[8] = "2.0";

void test(){
  Serial.printf("Test\n");
}

/**
 * @brief  Main program setup
 * @param  None
 * @retval None
 */
void setup() {

  /* Initializes the serial communication */
  Serial.begin(115200);
  Serial.printf("\n\n=====// Testbed v%s \\\\=====\n\n", version);

  /* Initializes the parameters */
  Serial.printf("Initializing parameters... ");
  parameters_init_parameters();
  Serial.printf("done\n");

  /* Initializes the NVS */
  Serial.printf("Initializing the NVS... ");
  nvs_init();
  Serial.printf("done\n");

  /* Reads parameters from the NVS */
  Serial.printf("Reading parameters from the NVS... ");
  nvs_read_parameters();
  Serial.printf("done\n");

  /* Initializes the user interface (OLED screen & buttons) */
  Serial.printf("Initializing the user interface... ");
  user_interface_init();
  Serial.printf("done\n");

  /* Displays the loading screen */
  Serial.printf("Displaying loading screen... ");
  user_interface_switch_screen(USER_INTERFACE_DISPLAY_LOADING);
  Serial.printf("done\n");

  /* Initializes the IR speed sensor */
  Serial.printf("Initializing the IR speed sensors... ");
  ir_speed_sensor_init(IR_SPEED_SENSOR_POWER, IR_SPEED_SENSOR_POWER_VCC);
  ir_speed_sensor_init(IR_SPEED_SENSOR_SPEED, IR_SPEED_SENSOR_SPEED_VCC);
  Serial.printf("done\n");

  /* Initializes the pressure sensor */
  Serial.printf("Initializing the pressure sensor... ");
  pressure_sensor_init(PRESSURE_SENSOR);
  Serial.printf("done\n");

  /* Initialize SD card */
  Serial.printf("Initializing the SD card module... ");
  sd_card_init(SD_CS);
  Serial.printf("done\n");

  /* Fake delay to display the loading screen even longer */
  delay(3000);
  Serial.printf("\n\n=====// Initialization done! \\\\=====\n\n");

  /* Main menu screen */
  user_interface_switch_screen(USER_INTERFACE_DISPLAY_MAIN);

}

/**
 * @brief  Main program loop (unused)
 * @param  None
 * @retval None
 */
void loop() {
  Serial.println("You really shouldn't be there..., reboot at once");
  delay(50000);
}