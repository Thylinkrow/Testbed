/**
* sd_card.c
*/

#include "sd_card.h"

/*******************************************************************
 * Private functions declarations 
 ******************************************************************/

void sd_card_append_file(fs::FS &fs, const char * path, const char * message);
void sd_card_write_file(fs::FS &fs, const char * path, const char * message);
uint8_t sd_card_delete_File(fs::FS &fs, const char * path);

/*******************************************************************
 * Private functions
 ******************************************************************/

/**
 * @brief  Appends data to a file
 * @param  fs the file system
 * @param  path the path of the file
 * @param  msg the message to be appened
 * @retval None
 */
void sd_card_append_file(fs::FS &fs, const char * path, const char * msg) {
  File file;

  file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  if(!file.print(msg)) {
    Serial.println("Append failed");
  }

  file.close();
}

/**
 * @brief  Writes data to a file
 * @param  fs the file system
 * @param  path the path of the file
 * @param  msg the message to be written 
 * @retval None
 */
void sd_card_write_file(fs::FS &fs, const char * path, const char * msg) {
  File file;

  file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  if(!file.print(msg)) {
    Serial.println("Write failed");
  }

  file.close();
}

/**
 * @brief  Deletes a file
 * @param  fs the file system
 * @param  path the path of the file
 * @retval Deletion status
 */
uint8_t sd_card_delete_File(fs::FS &fs, const char * path){
    return fs.remove(path);
}

/*******************************************************************
 * Public functions 
 ******************************************************************/

/**
 * @brief  Initializes the SD card module
 * @param  sd_card_module_pin the SD card module pin
 * @retval None
 */
void sd_card_init(uint8_t sd_card_pin){

  uint8_t cardType;

  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }

  cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return; 
  }

}

/**
 * @brief  Tries to open/create a file
 * @param  file_name name of the file
 * @retval 0 if the file doesn't already exist, 1 if it does
 */
uint8_t sd_card_open(uint8_t *file_name){

  uint8_t file_exist;
  File file;

  file_exist = 1;

  file = SD.open((char *)file_name);
  if(!file) {
    file_exist = 0;
    sd_card_write_file(SD, (char *)file_name, "");
  }

  file.close();

  return file_exist;

}

/**
 * @brief  Appends a message to the SD card
 * @param  file_name name of the file
 * @param  msg the message to append
 * @retval None
 */
void sd_card_append(uint8_t *file_name, uint8_t *msg){

  sd_card_append_file(SD, (char *)file_name, (char *)msg);
}

/**
 * @brief  Writes a message to the SD card
 * @param  file_name name of the file
 * @param  msg the message to write
 * @retval None
 */
void sd_card_write(uint8_t *file_name, uint8_t *msg){

  sd_card_write_file(SD, (char *)file_name, (char *)msg);
}
