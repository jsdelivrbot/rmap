#include <debug_config.h>

#define SERIAL_TRACE_LEVEL SERIAL_TRACE_LEVEL_INFO

#include <SensorDriver.h>
#include <ArduinoJson.h>
#include <sdcard_config.h>
#include <mqtt_config.h>
#include <rmap_utility.h>
#include <sdcard_utility.h>
#include <typedef.h>
#include <sensors_config.h>
#include <json_config.h>

#define I2C_BUS_CLOCK                                 (50000L)
#define USE_SENSORS_COUNT                             (10)
#define SENSORS_RETRY_COUNT_MAX                       (3)
#define SENSORS_RETRY_DELAY_MS                        (50)
#define DATA_SAVING_RETRY_COUNT_MAX                   (3)
#define DATA_SAVING_DELAY_MS                          (100)

uint8_t sensors_count;
SensorDriver *sensors[USE_SENSORS_COUNT];
value_t temperature;
value_t humidity;
rain_t rain;
bool is_event_sensors_reading;
bool is_event_data_saving;

typedef enum {
   SENSORS_READING_INIT,
   SENSORS_READING_PREPARE,
   SENSORS_READING_IS_PREPARED,
   SENSORS_READING_GET,
   SENSORS_READING_IS_GETTED,
   SENSORS_READING_READ,
   SENSORS_READING_NEXT,
   SENSORS_READING_END,
   SENSORS_READING_WAIT_STATE
} sensors_reading_state_t;

typedef enum {
   DATA_SAVING_INIT,          //!<
   DATA_SAVING_OPEN_SDCARD,   //!<  if not already open
   DATA_SAVING_OPEN_FILE,     //!<
   DATA_SAVING_SENSORS_LOOP,  //!<  loop from 0 to readable_configuration->sensors_count
   DATA_SAVING_DATA_LOOP,     //!< loop from 0 to data_count
   DATA_SAVING_WRITE_FILE,    //!<
   DATA_SAVING_CLOSE_FILE,    //!<
   DATA_SAVING_END,           //!<
   DATA_SAVING_WAIT_STATE     //!<
} data_saving_state_t;

sensors_reading_state_t sensors_reading_state;
data_saving_state_t data_saving_state;
uint32_t acquiring_sensors_delay_ms;

void init_sensors () {
  sensors_count = 0;

  SERIAL_INFO(F("Sensors...\r\n"));

  #if (USE_SENSOR_ADT)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_ADT, 0x48, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_ADT, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_HIH)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_HIH, 0x27, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_HIH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_HYT)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_HYT, 0x28, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_HYT, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_DW1)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_DW1, 0x22, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_DW1, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_TBS)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_TBS, 0x21, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_TBS, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_TBR)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_TBR, 0x21, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_TBR, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_ITH)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_ITH, 0x23, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_ITH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_MTH)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_MTH, 0x23, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_MTH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_NTH)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_NTH, 0x23, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_NTH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_XTH)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_XTH, 0x23, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_XTH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif

  #if (USE_SENSOR_DEP)
  SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_DEP, 0x30, sensors, &sensors_count);
  SERIAL_INFO(F("--> %u: %s-%s: %s\t [ %s ]\r\n"), sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_DEP, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
  #endif
}

char json_sensors_data[USE_SENSORS_COUNT][JSON_BUFFER_LENGTH];
uint8_t data_count;
tmElements_t sensor_reading_time;

char topic_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_SENSOR_TOPIC_LENGTH];
char message_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_MESSAGE_LENGTH];

void sensors_reading_task () {
   static uint8_t i;
   static uint8_t retry;
   static sensors_reading_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static int32_t values_readed_from_sensor[VALUES_TO_READ_FROM_SENSOR_COUNT];

   switch (sensors_reading_state) {
      case SENSORS_READING_INIT:
         SERIAL_INFO(F("Sensors reading...\r\n"));

         for (i=0; i<sensors_count; i++) {
            sensors[i]->resetPrepared();
         }

         i = 0;
         retry = 0;
         state_after_wait = SENSORS_READING_INIT;
         sensors_reading_state = SENSORS_READING_PREPARE;
         SERIAL_TRACE(F("SENSORS_READING_INIT ---> SENSORS_READING_PREPARE\r\n"));
      break;

      case SENSORS_READING_PREPARE:
         sensors[i]->prepare();
         delay_ms = sensors[i]->getDelay();
         start_time_ms = sensors[i]->getStartTime();

         if (delay_ms) {
            state_after_wait = SENSORS_READING_IS_PREPARED;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            SERIAL_TRACE(F("SENSORS_READING_PREPARE ---> SENSORS_READING_WAIT_STATE\r\n"));
         }
         else {
            sensors_reading_state = SENSORS_READING_IS_PREPARED;
            SERIAL_TRACE(F("SENSORS_READING_PREPARE ---> SENSORS_READING_IS_PREPARED\r\n"));
         }
      break;

      case SENSORS_READING_IS_PREPARED:
         // success
         if (sensors[i]->isPrepared()) {
            retry = 0;
            sensors_reading_state = SENSORS_READING_GET;
            SERIAL_TRACE(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_GET\r\n"));
         }
         // retry
         else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
            delay_ms = SENSORS_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = SENSORS_READING_PREPARE;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            SERIAL_TRACE(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_WAIT_STATE\r\n"));
         }
         // fail
         else {
            retry = 0;
            sensors_reading_state = SENSORS_READING_GET;
            SERIAL_TRACE(F("SENSORS_READING_IS_PREPARED ---> SENSORS_READING_GET\r\n"));
         }
      break;

      case SENSORS_READING_GET:
         sensors[i]->getJson(values_readed_from_sensor, VALUES_TO_READ_FROM_SENSOR_COUNT, &json_sensors_data[i][0]);
         delay_ms = sensors[i]->getDelay();
         start_time_ms = sensors[i]->getStartTime();

         if (delay_ms) {
            state_after_wait = SENSORS_READING_IS_GETTED;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            SERIAL_TRACE(F("SENSORS_READING_GET ---> SENSORS_READING_WAIT_STATE\r\n"));
         }
         else {
            sensors_reading_state = SENSORS_READING_IS_GETTED;
            SERIAL_TRACE(F("SENSORS_READING_GET ---> SENSORS_READING_IS_GETTED\r\n"));
         }
      break;

      case SENSORS_READING_IS_GETTED:
         // end
         if (sensors[i]->isEnd() && !sensors[i]->isReaded()) {
            // success
            if (sensors[i]->isSuccess()) {
               retry = 0;
               sensors_reading_state = SENSORS_READING_READ;
               SERIAL_TRACE(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_READ\r\n"));
            }
            // retry
            else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
               delay_ms = SENSORS_RETRY_DELAY_MS;
               start_time_ms = millis();
               state_after_wait = SENSORS_READING_GET;
               sensors_reading_state = SENSORS_READING_WAIT_STATE;
               SERIAL_TRACE(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_WAIT_STATE\r\n"));
            }
            // fail
            else {
               retry = 0;
               sensors_reading_state = SENSORS_READING_READ;
               SERIAL_TRACE(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_READ\r\n"));
            }
         }
         // not end
         else {
            sensors_reading_state = SENSORS_READING_GET;
            SERIAL_TRACE(F("SENSORS_READING_IS_GETTED ---> SENSORS_READING_GET\r\n"));
         }
      break;

      case SENSORS_READING_READ:
         sensors_reading_state = SENSORS_READING_NEXT;
         SERIAL_TRACE(F("SENSORS_READING_READ ---> SENSORS_READING_NEXT\r\n"));
      break;

      case SENSORS_READING_NEXT:
         SERIAL_INFO(F("%u: %s\r\n"), i, json_sensors_data[i]);

         // next sensor
         if ((++i) < sensors_count) {
            retry = 0;
            sensors_reading_state = SENSORS_READING_PREPARE;
            SERIAL_TRACE(F("SENSORS_READING_NEXT ---> SENSORS_READING_PREPARE\r\n"));
         }
         // end
         else {
            noInterrupts();
            // if (!is_event_data_saving) {
            //    is_event_data_saving = true;
            // }
            interrupts();
            sensors_reading_state = SENSORS_READING_END;
            SERIAL_TRACE(F("SENSORS_READING_NEXT ---> SENSORS_READING_END\r\n"));
         }
      break;

      case SENSORS_READING_END:
         noInterrupts();
         is_event_sensors_reading = false;
         interrupts();
         sensors_reading_state = SENSORS_READING_INIT;
         SERIAL_TRACE(F("SENSORS_READING_END ---> SENSORS_READING_INIT\r\n"));
      break;

      case SENSORS_READING_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            sensors_reading_state = state_after_wait;
         }
      break;
   }
}

void data_saving_task() {
   static uint8_t retry;
   static data_saving_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static uint8_t i;
   static uint8_t k;
   static uint8_t data_count;
   static uint16_t sd_data_count;
   static char sd_buffer[MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH];
   static char topic_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_SENSOR_TOPIC_LENGTH];
   static char message_buffer[VALUES_TO_READ_FROM_SENSOR_COUNT][MQTT_MESSAGE_LENGTH];
   char file_name[SDCARD_FILES_NAME_MAX_LENGTH];

   switch (data_saving_state) {
      case DATA_SAVING_INIT:
         SERIAL_INFO(F("Sensors count: %u\r\n"), sensors_count);
         retry = 0;
         sd_data_count = 0;
         // is_sdcard_open
         if (true) {
            data_saving_state = DATA_SAVING_OPEN_FILE;
            SERIAL_TRACE(F("DATA_SAVING_INIT ---> DATA_SAVING_OPEN_FILE\r\n"));
         }
         else {
            data_saving_state = DATA_SAVING_OPEN_SDCARD;
            SERIAL_TRACE(F("DATA_SAVING_INIT ---> DATA_SAVING_OPEN_SDCARD\r\n"));
         }
      break;

      case DATA_SAVING_OPEN_SDCARD:
         //sdcard_init(&SD, SDCARD_CHIP_SELECT_PIN)
         if (true) {
            retry = 0;
            // is_sdcard_open = true;
            data_saving_state = DATA_SAVING_OPEN_FILE;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_OPEN_FILE\r\n"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_OPEN_SDCARD;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_WAIT_STATE\r\n"));
         }
         // fail
         else {
            // is_sdcard_error = true;
            // is_sdcard_open = false;
            SERIAL_ERROR(F("SD Card... [ FAIL ]\r\n--> is card inserted?\r\n--> there is a valid FAT32 filesystem?\r\n\r\n"));

            data_saving_state = DATA_SAVING_END;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_END\r\n"));
         }
      break;

      case DATA_SAVING_OPEN_FILE:
         // open sdcard file: today!
         sdcard_make_filename(now(), file_name);

         // try to open file. if ok, write sensors data on it.
         // sdcard_open_file(&SD, &write_data_file, file_name, O_RDWR | O_CREAT | O_APPEND)
         if (true) {
            retry = 0;
            i = 0;
            data_saving_state = DATA_SAVING_SENSORS_LOOP;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_FILE ---> DATA_SAVING_SENSORS_LOOP\r\n"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_OPEN_FILE;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_SDCARD ---> DATA_SAVING_WAIT_STATE\r\n"));
         }
         // fail
         else {
            SERIAL_ERROR(F("SD Card open file %s... [ FAIL ]\r\n"), file_name);
            // is_sdcard_error = true;
            data_saving_state = DATA_SAVING_END;
            SERIAL_TRACE(F("DATA_SAVING_OPEN_FILE ---> DATA_SAVING_END\r\n"));
         }
      break;

      case DATA_SAVING_SENSORS_LOOP:
         if (i < sensors_count) {
            k = 0;
            data_count = jsonToMqtt(&json_sensors_data[i][0], "stopic/", topic_buffer, message_buffer, (tmElements_t *) &sensor_reading_time);
            SERIAL_INFO(F("%u: [ %u ] %s\r\n\r\n"), i, data_count, json_sensors_data[i]);
            data_saving_state = DATA_SAVING_DATA_LOOP;
            SERIAL_TRACE(F("DATA_SAVING_SENSORS_LOOP ---> DATA_SAVING_DATA_LOOP\r\n"));
         }
         else {
            SERIAL_DEBUG(F("\r\n"));
            data_saving_state = DATA_SAVING_CLOSE_FILE;
            SERIAL_TRACE(F("DATA_SAVING_SENSORS_LOOP ---> DATA_SAVING_CLOSE_FILE\r\n"));
         }
      break;

      case DATA_SAVING_DATA_LOOP:
         if (k < data_count) {
            mqttToSd(&topic_buffer[k][0], &message_buffer[k][0], sd_buffer);
            data_saving_state = DATA_SAVING_WRITE_FILE;
            SERIAL_TRACE(F("DATA_SAVING_DATA_LOOP ---> DATA_SAVING_WRITE_FILE\r\n"));
         }
         else {
            i++;
            data_saving_state = DATA_SAVING_SENSORS_LOOP;
            SERIAL_TRACE(F("DATA_SAVING_DATA_LOOP ---> DATA_SAVING_SENSORS_LOOP\r\n"));
         }
      break;

      case DATA_SAVING_WRITE_FILE:
         // sdcard success
         // write_data_file.write(sd_buffer, MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH) == (MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH)
         if (true) {
            SERIAL_DEBUG(F("SD <-- %s %s\r\n"), &topic_buffer[k][0], &message_buffer[k][0]);
            // write_data_file.flush();
            retry = 0;
            k++;
            sd_data_count++;
            data_saving_state = DATA_SAVING_DATA_LOOP;
            SERIAL_TRACE(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_DATA_LOOP\r\n"));
         }
         // retry
         else if ((++retry) < DATA_SAVING_RETRY_COUNT_MAX) {
            delay_ms = DATA_SAVING_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = DATA_SAVING_WRITE_FILE;
            data_saving_state = DATA_SAVING_WAIT_STATE;
            SERIAL_TRACE(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_WAIT_STATE\r\n"));
         }
         // fail
         else {
            SERIAL_ERROR(F("SD Card writing data on file %s... [ FAIL ]\r\n"), file_name);
            // is_sdcard_error = true;
            data_saving_state = DATA_SAVING_CLOSE_FILE;
            SERIAL_TRACE(F("DATA_SAVING_WRITE_FILE ---> DATA_SAVING_CLOSE_FILE\r\n"));
         }
      break;

      case DATA_SAVING_CLOSE_FILE:
            // is_sdcard_error =  false; //!write_data_file.close();
            data_saving_state = DATA_SAVING_END;
            SERIAL_TRACE(F("DATA_SAVING_CLOSE_FILE ---> DATA_SAVING_END\r\n"));
         break;

      case DATA_SAVING_END:
         SERIAL_INFO(F("[ %u ] data stored in sdcard... [ %s ]\r\n"), sd_data_count, false ? ERROR_STRING : OK_STRING);
         // LCD_INFO(&lcd, false, true, "sdcard %u data %s", sd_data_count, is_sdcard_error ? ERROR_STRING : OK_STRING);

         // noInterrupts();
         // if (!is_event_supervisor) {
         //    is_event_supervisor = true;
         //    ready_tasks_count++;
         // }

         noInterrupts();
         is_event_data_saving = false;
         interrupts();

         data_saving_state = DATA_SAVING_INIT;
         SERIAL_TRACE(F("DATA_SAVING_END ---> DATA_SAVING_INIT\r\n"));
      break;

      case DATA_SAVING_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            data_saving_state = state_after_wait;
         }
      break;
   }
}

#define DELAY_ACQ_MS    (10000)

void setup() {
  SERIAL_BEGIN(115200);
  Wire.begin();
  Wire.setClock(I2C_BUS_CLOCK);

  init_sensors();
  acquiring_sensors_delay_ms = -DELAY_ACQ_MS;
  is_event_sensors_reading = false;
  is_event_data_saving = false;
  sensors_reading_state = SENSORS_READING_INIT;
  data_saving_state = DATA_SAVING_INIT;
}

void loop() {
   if (is_event_sensors_reading) {
      sensors_reading_task();
   }

   if (is_event_data_saving) {
      data_saving_task();
   }

   if (!is_event_sensors_reading && !is_event_data_saving && millis() - acquiring_sensors_delay_ms >= DELAY_ACQ_MS) {
      acquiring_sensors_delay_ms = millis();
      is_event_sensors_reading = true;
   }
}
