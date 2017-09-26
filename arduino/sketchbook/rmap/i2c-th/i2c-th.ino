/**********************************************************************
Copyright (C) 2017  Marco Baldinetti <m.baldinetti@digiteco.it>
authors:
Marco Baldinetti <m.baldinetti@digiteco.it>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

/**********************************************************************
* DEBUG
*********************************************************************/
/*! \file i2c-th2.h
\brief i2c-th include file

i2c-th include file
*/
#include <debug_config.h>

/*!
\def SERIAL_TRACE_LEVEL
Debug level for sketch and library.
*/
#define SERIAL_TRACE_LEVEL I2C_TH_SERIAL_TRACE_LEVEL

#include "i2c-th.h"

void setup() {
   init_wdt(WDT_TIMER);
   SERIAL_BEGIN(115200);
   init_pins();
   load_configuration();
   init_buffers();
   init_wire();
   init_spi();
   init_rtc();
   init_system();
}

void loop() {
   switch (state) {
      case INIT:
         init_tasks();
         init_sensors();
         state = TASKS_EXECUTION;
         wdt_reset();
      break;

      #if (USE_POWER_DOWN)
      case ENTER_POWER_DOWN:
         power_down(&awakened_event_occurred_time_ms, DEBOUNCING_POWER_DOWN_TIME_MS);
         state = TASKS_EXECUTION;
         init_wdt(WDT_TIMER);
      break;
      #endif

      case TASKS_EXECUTION:
         if (is_event_sensors_reading) {
            sensors_reading_task();
            wdt_reset();
         }

         if (is_event_command_task) {
            command_task();
            wdt_reset();
         }

         wdt_reset();

         if (ready_tasks_count == 0) {
            state = END;
         }
      break;

      case END:
         #if (USE_POWER_DOWN)
         state = ENTER_POWER_DOWN;
         #else
         state = TASKS_EXECUTION;
         #endif
         wdt_reset();
      break;
   }
}

void init_wdt(uint8_t wdt_timer) {
   wdt_disable();
   wdt_reset();
   wdt_enable(wdt_timer);
}

void init_buffers() {
   readable_data_read_ptr = &readable_data_1;
   readable_data_write_ptr = &readable_data_2;
   writable_data_ptr = &writable_data;

   readable_data_write_ptr->module_type = MODULE_TYPE;
   readable_data_write_ptr->module_version = MODULE_VERSION;
   memset((void *) &readable_data_write_ptr->humidity, UINT16_MAX, sizeof(value_t));
   memset((void *) &readable_data_write_ptr->temperature, UINT16_MAX, sizeof(value_t));
   memcpy((void *) readable_data_read_ptr, (const void*) readable_data_write_ptr, sizeof(readable_data_t));

   reset_samples_buffer();
   reset_observations_buffer();
}

void init_tasks() {
   noInterrupts();
   ready_tasks_count = 0;

   is_event_command_task = false;
   is_event_sensors_reading = false;

   sensors_reading_state = SENSORS_READING_INIT;

   // #if ((REPORT_MINUTES / OBSERVATIONS_MINUTES) % 2 == 0)
   // samples_count = SAMPLE_COUNT_MAX;
   // #else
   samples_count = SAMPLE_COUNT_MIN;
   // #endif

   // is_continuous = true;
   // is_start = true;
   // is_stop = true;
   // commands();

   interrupts();
}

void init_pins() {
   pinMode(CONFIGURATION_RESET_PIN, INPUT_PULLUP);
}

void init_wire() {
   uint8_t i2c_bus_state = I2C_ClearBus(); // clear the I2C bus first before calling Wire.begin()

   if (i2c_bus_state) {
      SERIAL_ERROR("I2C bus error: Could not clear!!!\r\n");
      while(1);
   }

   switch (i2c_bus_state) {
      case 1:
         SERIAL_ERROR("SCL clock line held low\r\n");
      break;

      case 2:
         SERIAL_ERROR("SCL clock line held low by slave clock stretch\r\n");
      break;

      case 3:
         SERIAL_ERROR("SDA data line held low\r\n");
      break;
   }

   Wire.begin(configuration.i2c_address);
   Wire.setClock(I2C_BUS_CLOCK);
   Wire.onRequest(i2c_request_interrupt_handler);
   Wire.onReceive(i2c_receive_interrupt_handler);
}

void init_spi() {
}

void init_rtc() {
}

void start_timer() {
   TCCR1A = 0x00;    // Normal timer operation
   TCCR1B = 0x04;    // prescaler for 1:256
   TIMSK1 = 0x01;    // Enable interrupt
   // interrupt every: prescaler * 2^16 / 8 MHz = 2097 ms
}

void stop_timer() {
   TCCR1B = 0x00;    // stop
   TIMSK1 = 0x00;    // disable interrupt
   TIFR1 = 0xFF;     // Clear interrupt flag register
   TCNT1 = 0x0000;   // Clear timer counter register
}

void init_system() {
   #if (USE_POWER_DOWN)
   set_sleep_mode(SLEEP_MODE_IDLE);
   awakened_event_occurred_time_ms = millis();
   #endif
   state = INIT;
}

void print_configuration() {
   char stima_name[20];
   getStimaNameByType(stima_name, configuration.module_type);
   SERIAL_INFO("--> type: %s\r\n", stima_name);
   SERIAL_INFO("--> version: %d\r\n", configuration.module_version);
   SERIAL_INFO("--> i2c address: 0x%x (%d)\r\n", configuration.i2c_address, configuration.i2c_address);
   SERIAL_INFO("--> oneshot: %s\r\n", configuration.is_oneshot ? "on" : "off");
   SERIAL_INFO("--> continuous: %s\r\n", configuration.is_continuous ? "on" : "off");
   SERIAL_INFO("--> i2c temperature address: 0x%x (%d)\r\n", configuration.i2c_temperature_address, configuration.i2c_temperature_address);
   SERIAL_INFO("--> i2c humidity address: 0x%x (%d)\r\n\r\n", configuration.i2c_humidity_address, configuration.i2c_temperature_address);
}

void save_configuration(bool is_default) {
   if (is_default) {
      SERIAL_INFO("Save default configuration... [ OK ]\r\n");
      configuration.module_type = MODULE_TYPE;
      configuration.module_version = MODULE_VERSION;
      configuration.i2c_address = CONFIGURATION_DEFAULT_I2C_ADDRESS;
      configuration.is_oneshot = CONFIGURATION_DEFAULT_IS_ONESHOT;
      configuration.is_continuous = CONFIGURATION_DEFAULT_IS_CONTINUOUS;
      configuration.i2c_temperature_address = CONFIGURATION_DEFAULT_TEMPERATURE_ADDRESS;
      configuration.i2c_humidity_address = CONFIGURATION_DEFAULT_HUMIDITY_ADDRESS;

      #if (USE_SENSOR_ADT)
      configuration.i2c_temperature_address = 0x28;
      #endif

      #if (USE_SENSOR_HIH)
      configuration.i2c_humidity_address = 0x28;
      #endif

      #if (USE_SENSOR_HYT)
      configuration.i2c_temperature_address = HYT2X1_DEFAULT_ADDRESS;
      configuration.i2c_humidity_address = HYT2X1_DEFAULT_ADDRESS;
      #endif
   }
   else {
      SERIAL_INFO("Save configuration... [ OK ]\r\n");
      configuration.i2c_address = writable_data.i2c_address;
      configuration.is_oneshot = writable_data.is_oneshot;
      configuration.is_continuous = writable_data.is_continuous;
      configuration.i2c_temperature_address = writable_data.i2c_temperature_address;
      configuration.i2c_humidity_address = writable_data.i2c_humidity_address;
   }

   ee_write(&configuration, CONFIGURATION_EEPROM_ADDRESS, sizeof(configuration));

   print_configuration();
}

void load_configuration() {
   ee_read(&configuration, CONFIGURATION_EEPROM_ADDRESS, sizeof(configuration));

   if (configuration.module_type != MODULE_TYPE || configuration.module_version != MODULE_VERSION || digitalRead(CONFIGURATION_RESET_PIN) == LOW) {
      save_configuration(CONFIGURATION_DEFAULT);
   }
   else {
      SERIAL_INFO("Load configuration... [ OK ]\r\n");
      print_configuration();
   }

   writable_data.i2c_address = configuration.i2c_address;
   writable_data.is_oneshot = configuration.is_oneshot;
}

void init_sensors () {
   is_first_run = true;
   sensors_count = 0;

   SERIAL_INFO("Sensors...\r\n");

   #if (USE_SENSOR_ADT)
   SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_ADT, configuration.i2c_temperature_address, sensors, &sensors_count);
   SERIAL_INFO("--> %u: %s-%s: %s\t [ %s ]\r\n", sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_ADT, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
   #endif

   #if (USE_SENSOR_HIH)
   SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_HIH, configuration.i2c_humidity_address, sensors, &sensors_count);
   SERIAL_INFO("--> %u: %s-%s: %s\t [ %s ]\r\n", sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_HIH, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
   #endif

   #if (USE_SENSOR_HYT)
   SensorDriver::createAndSetup(SENSOR_DRIVER_I2C, SENSOR_TYPE_HYT, configuration.i2c_temperature_address, sensors, &sensors_count);
   SERIAL_INFO("--> %u: %s-%s: %s\t [ %s ]\r\n", sensors_count, SENSOR_DRIVER_I2C, SENSOR_TYPE_HYT, "", sensors[sensors_count-1]->isSetted() ? OK_STRING : FAIL_STRING);
   #endif

   if (configuration.is_continuous) {
      // #if (REPORT_MINUTES != OBSERVATIONS_MINUTES)
      SERIAL_INFO("--> acquiring %u~%u samples in %u minutes\r\n\r\n", SAMPLE_COUNT_MIN, SAMPLE_COUNT_MAX, OBSERVATIONS_MINUTES);
      // #else
      // SERIAL_INFO("--> acquiring %u samples in %u minutes\r\n\r\n", SAMPLE_COUNT_MIN, OBSERVATIONS_MINUTES);
      // #endif
      SERIAL_INFO("T-IST\tT-MIN\tT-MED\tT-MAX\tH-IST\tH-MIN\tH-MED\tH-MAX\tT-CNT\tH-CNT\r\n");
   }
}

ISR(TIMER1_OVF_vect) {
   timer_counter += TIMER1_VALUE_S;

   if (executeTimerTaskEach(timer_counter, SAMPLE_SECONDS, TIMER1_VALUE_S) && configuration.is_continuous && is_continuous && is_start) {
      if (!is_event_sensors_reading) {
         noInterrupts();
         is_event_sensors_reading = true;
         ready_tasks_count++;
         interrupts();
      }
   }

   if (timer_counter >= TIMER1_VALUE_MAX_S) {
      timer_counter = 0;
   }
}

void i2c_request_interrupt_handler() {
   Wire.write((uint8_t *)readable_data_read_ptr+readable_data_address, readable_data_length);
}

void i2c_receive_interrupt_handler(int rx_data_length) {
   for (uint8_t i=0; i<rx_data_length; i++) {
      i2c_rx_data[i] = Wire.read();
   }

   if (rx_data_length == 2 && is_readable_register(i2c_rx_data[0])) {
      readable_data_address = i2c_rx_data[0];
      readable_data_length = i2c_rx_data[1];
   }
   else if (rx_data_length == 2 && is_command(i2c_rx_data[0])) {
      noInterrupts();
      if (!is_event_command_task) {
         is_event_command_task = true;
         ready_tasks_count++;
      }
      interrupts();
   }
   else if (is_writable_register(i2c_rx_data[0])) {
      for (uint8_t i=1; i<rx_data_length; i++)
      ((uint8_t *)writable_data_ptr)[i2c_rx_data[0] - I2C_WRITE_REGISTER_START_ADDRESS] = i2c_rx_data[i];
   }
}

bool make_observation_from_samples(bool is_force_processing, sample_t *sample, observation_t *observation) {
   uint8_t i;
   uint32_t value = UINT16_MAX;

   bool is_processing_end;

   if (is_force_processing && samples_count == SAMPLE_COUNT_MAX) {
      is_processing_end = (sample->count + sample->error_count >= (SAMPLE_COUNT_MAX - SAMPLE_COUNT_TOLLERANCE));
   }
   else if (is_force_processing && samples_count == SAMPLE_COUNT_MIN) {
      is_processing_end = (sample->count + sample->error_count >= (SAMPLE_COUNT_MIN - SAMPLE_COUNT_TOLLERANCE));
   }
   else is_processing_end = (sample->count + sample->error_count == samples_count);

   bool is_no_error = (sample->error_count < SAMPLE_COUNT_TOLLERANCE);
   bool is_processing_ok = (is_processing_end && is_no_error);

   if (is_processing_ok) {
      value = 0;

      for (i=0; i<sample->count; i++) {
         if (sample->values[i] != UINT16_MAX) {
            value += sample->values[i];
         }
      }

      // average
      value = round(value / sample->count);
   }

   *observation->write_ptr = (uint16_t) value;

   return is_processing_end;
}

void samples_processing(bool is_force_processing) {
   bool is_processing_temperature = make_observation_from_samples(is_force_processing, &temperature_samples, &temperature_observations);
   bool is_processing_humidity = make_observation_from_samples(is_force_processing, &humidity_samples, &humidity_observations);

   if (is_processing_temperature || is_processing_humidity) {
      SERIAL_DEBUG("------------------------------------------------------------------------------\r\n");
      SERIAL_DEBUG("%u\t \t \t \t%u\t \t \t \t%u/%u\t%u/%u\r\n", *temperature_observations.write_ptr, *humidity_observations.write_ptr, temperature_samples.count, samples_count, humidity_samples.count, samples_count);
      SERIAL_DEBUG("------------------------------------------------------------------------------\r\n");

      if (is_force_processing) {
         samples_count = SAMPLE_COUNT_MAX;
      }
      else samples_count = (samples_count == SAMPLE_COUNT_MAX ? SAMPLE_COUNT_MIN : SAMPLE_COUNT_MAX);

      // #if (REPORT_MINUTES != OBSERVATIONS_MINUTES)
      // samples_count = (samples_count == SAMPLE_COUNT_MAX ? SAMPLE_COUNT_MIN : SAMPLE_COUNT_MAX);
      // #endif
      observations_processing();
   }
}

bool make_value_from_samples_and_observations(sample_t *sample, observation_t *observation, volatile value_t *value) {
   int32_t read_ptr;
   uint16_t *write_ptr_temp;
   uint32_t value_temp = UINT16_MAX;
   uint16_t value_count = 0;
   uint16_t error_count = 0;
   float sigma = 0;

   // count
   if (observation->count <= OBSERVATION_COUNT) {
      observation->count++;
   }

   bool is_processing = (observation->count >= STATISTICAL_DATA_COUNT);

   write_ptr_temp = observation->write_ptr;

   // increment write_ptr
   if ((observation->write_ptr - observation->med) >= OBSERVATION_COUNT-1) {
      observation->write_ptr = observation->med;
   }
   else observation->write_ptr++;

   if (is_processing) {
      memset((void *) value, UINT16_MAX, sizeof(value_t));
      value->max = 0;
      value_temp = 0;

      while ((observation->read_ptr - observation->med) != (observation->write_ptr - observation->med)) {
         if (*observation->read_ptr != UINT16_MAX) {
            value_temp += *observation->read_ptr;
            value->min = min(value->min, *observation->read_ptr);
            value->max = max(value->max, *observation->read_ptr);
            value_count++;
         } else error_count++;

         // increment read_ptr
         if ((observation->read_ptr - observation->med) >= OBSERVATION_COUNT-1) {
            observation->read_ptr = observation->med;
         }
         else observation->read_ptr++;
      }

      // observation->write_ptr + 1 for precalculate next processing
      read_ptr = (observation->write_ptr + 1 - observation->med) - STATISTICAL_DATA_COUNT;

      // reset read_ptr
      if (read_ptr < 0) {
         observation->read_ptr = &observation->med[OBSERVATION_COUNT+read_ptr];
      }
      else observation->read_ptr = &observation->med[read_ptr];

      // last sample
      value->sample = sample->values[sample->count-1];

      // last observation
      value->med60 = *(write_ptr_temp);

      // average
      if (error_count < OBSERVATION_COUNT_TOLLERANCE) {
         value->med = round(value_temp / value_count);
      }

      // standard deviation: TO CHECK!!!
      value_count = 0;
      error_count = 0;

      while ((observation->read_ptr - observation->med) != (observation->write_ptr - observation->med)) {
         if (value->med != UINT16_MAX) {
            sigma += pow(*observation->read_ptr - value->med, 2);
            value_count++;
         } else error_count++;

         // increment read_ptr
         if ((observation->read_ptr - observation->med) >= OBSERVATION_COUNT-1) {
            observation->read_ptr = observation->med;
         }
         else observation->read_ptr++;
      }

      if (error_count < OBSERVATION_COUNT_TOLLERANCE) {
         sigma = sqrt(sigma / value_count);
         value->sigma = sigma * 100;
      }

      // observation->write_ptr + 1 for precalculate next processing
      read_ptr = (observation->write_ptr + 1 - observation->med) - STATISTICAL_DATA_COUNT;

      // reset read_ptr
      if (read_ptr < 0) {
         observation->read_ptr = &observation->med[OBSERVATION_COUNT+read_ptr];
      }
      else observation->read_ptr = &observation->med[read_ptr];
   }

   return is_processing;
}

//------------------------------------------------------------------------------
// I2C-TH
// STH: oneshot                   --> xxx.sample
// ITH: continuous istantaneous   --> xxx.med60
// MTH: continuous average        --> xxx.med
// NTH: continuous min            --> xxx.min
// XTH: continuous max            --> xxx.max
//------------------------------------------------------------------------------
void observations_processing() {
   bool is_processing_temperature = make_value_from_samples_and_observations(&temperature_samples, &temperature_observations, &readable_data_write_ptr->temperature);
   bool is_processing_humidty = make_value_from_samples_and_observations(&humidity_samples, &humidity_observations, &readable_data_write_ptr->humidity);
   reset_samples_buffer();

   if (is_processing_temperature || is_processing_humidty) {
      if (readable_data_write_ptr->temperature.med60 != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.med60);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->temperature.min != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.min);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->temperature.med != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.med);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->temperature.max != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.max);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->humidity.med60 != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.med60);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->humidity.min != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.min);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->humidity.med != UINT16_MAX) {
         SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.med);
      }
      else SERIAL_INFO("-----\t");

      if (readable_data_write_ptr->humidity.max != UINT16_MAX) {
         SERIAL_INFO("%u\r\n", readable_data_write_ptr->humidity.max);
      }
      else SERIAL_INFO("-----\r\n");
   }
}

void observations_processing_debug() {
   readable_data_write_ptr->temperature.med60 = 29999;
   readable_data_write_ptr->temperature.max = 30010;
   readable_data_write_ptr->temperature.med = 30000;
   readable_data_write_ptr->temperature.min = 30000;

   readable_data_write_ptr->humidity.med60 = 60;
   readable_data_write_ptr->humidity.max = 100;
   readable_data_write_ptr->humidity.med = 50;
   readable_data_write_ptr->humidity.min = 0;

   #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_INFO)
   if (readable_data_write_ptr->temperature.med60 != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.med60);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->temperature.min != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.min);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->temperature.med != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.med);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->temperature.max != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->temperature.max);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->humidity.med60 != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.med60);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->humidity.min != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.min);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->humidity.med != UINT16_MAX) {
      SERIAL_INFO("%u\t", readable_data_write_ptr->humidity.med);
   }
   else SERIAL_INFO("-----\t");

   if (readable_data_write_ptr->humidity.max != UINT16_MAX) {
      SERIAL_INFO("%u\r\n", readable_data_write_ptr->humidity.max);
   }
   else SERIAL_INFO("-----\r\n");
   #endif
}

void sensors_reading_task () {
   static uint8_t i;
   static uint8_t retry;
   static sensors_reading_state_t state_after_wait;
   static uint32_t delay_ms;
   static uint32_t start_time_ms;
   static int32_t values_readed_from_sensor[2];

   switch (sensors_reading_state) {
      case SENSORS_READING_INIT:
         for (i=0; i<sensors_count; i++) {
            sensors[i]->resetPrepared();
         }

         i = 0;
         retry = 0;
         state_after_wait = SENSORS_READING_INIT;
         sensors_reading_state = SENSORS_READING_PREPARE;
      break;

      case SENSORS_READING_PREPARE:
         sensors[i]->prepare();
         delay_ms = sensors[i]->getDelay();
         start_time_ms = sensors[i]->getStartTime();

         if (delay_ms) {
            state_after_wait = SENSORS_READING_IS_PREPARED;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
         }
         else {
            sensors_reading_state = SENSORS_READING_IS_PREPARED;
         }
      break;

      case SENSORS_READING_IS_PREPARED:
         // success
         if (sensors[i]->isPrepared()) {
            retry = 0;
            sensors_reading_state = SENSORS_READING_GET;
         }
         // retry
         else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
            delay_ms = SENSORS_RETRY_DELAY_MS;
            start_time_ms = millis();
            state_after_wait = SENSORS_READING_PREPARE;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
         }
         // fail
         else {
            retry = 0;
            sensors_reading_state = SENSORS_READING_GET;
         }
      break;

      case SENSORS_READING_GET:
         sensors[i]->get(values_readed_from_sensor, VALUES_TO_READ_FROM_SENSOR_COUNT);
         delay_ms = sensors[i]->getDelay();
         start_time_ms = sensors[i]->getStartTime();

         if (delay_ms) {
            state_after_wait = SENSORS_READING_IS_GETTED;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
         }
         else {
            sensors_reading_state = SENSORS_READING_IS_GETTED;
         }
      break;

      case SENSORS_READING_IS_GETTED:
         // end
         if (sensors[i]->isEnd() && !sensors[i]->isReaded()) {
            // success
            if (sensors[i]->isSuccess()) {
               retry = 0;
               sensors_reading_state = SENSORS_READING_READ;
            }
            // retry
            else if ((++retry) < SENSORS_RETRY_COUNT_MAX) {
               delay_ms = SENSORS_RETRY_DELAY_MS;
               start_time_ms = millis();
               state_after_wait = SENSORS_READING_GET;
               sensors_reading_state = SENSORS_READING_WAIT_STATE;
            }
            // fail
            else {
               retry = 0;
               #if (USE_SENSOR_HYT || USE_SENSOR_ADT)
               temperature_samples.error_count++;
               #endif

               #if (USE_SENSOR_HYT || USE_SENSOR_HIH)
               humidity_samples.error_count++;
               #endif

               sensors_reading_state = SENSORS_READING_NEXT;
            }
         }
         // not end
         else {
            sensors_reading_state = SENSORS_READING_GET;
         }
      break;

      case SENSORS_READING_READ:
         #if (USE_SENSOR_HYT)
         if (strcmp(sensors[i]->getType(), SENSOR_TYPE_HYT) == 0) {
            humidity_samples.values[humidity_samples.count++] = values_readed_from_sensor[0];
            temperature_samples.values[temperature_samples.count++] = values_readed_from_sensor[1];
         }
         #endif
         sensors_reading_state = SENSORS_READING_NEXT;
      break;

      case SENSORS_READING_NEXT:
         // next sensor
         if ((++i) < sensors_count) {
            retry = 0;
            sensors_reading_state = SENSORS_READING_PREPARE;
         }
         // end
         else {
            if (configuration.is_continuous) {
               samples_processing(false);
            }

            #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_INFO)
            delay_ms = 10;
            start_time_ms = millis();
            state_after_wait = SENSORS_READING_END;
            sensors_reading_state = SENSORS_READING_WAIT_STATE;
            #else
            sensors_reading_state = SENSORS_READING_END;
            #endif
         }
      break;

      case SENSORS_READING_END:
         noInterrupts();
         is_event_sensors_reading = false;
         ready_tasks_count--;
         interrupts();
         sensors_reading_state = SENSORS_READING_INIT;
      break;

      case SENSORS_READING_WAIT_STATE:
         if (millis() - start_time_ms > delay_ms) {
            sensors_reading_state = state_after_wait;
         }
      break;
   }
}

void exchange_buffers() {
   readable_data_temp_ptr = readable_data_write_ptr;
   readable_data_write_ptr = readable_data_read_ptr;
   readable_data_read_ptr = readable_data_temp_ptr;
}

void reset_samples_buffer() {
   memset((void *) temperature_samples.values, UINT16_MAX, SAMPLE_COUNT_MAX);
   memset((void *) humidity_samples.values, UINT16_MAX, SAMPLE_COUNT_MAX);
   humidity_samples.count = 0;
   temperature_samples.count = 0;
   humidity_samples.error_count = 0;
   temperature_samples.error_count = 0;
}

void reset_observations_buffer() {
   temperature_observations.count = 0;
   temperature_observations.read_ptr = temperature_observations.med;
   temperature_observations.write_ptr = temperature_observations.med;

   humidity_observations.count = 0;
   humidity_observations.read_ptr = humidity_observations.med;
   humidity_observations.write_ptr = humidity_observations.med;
}

void command_task() {
   #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
   char buffer[30];
   #endif

   switch(i2c_rx_data[1]) {
      case I2C_TH_COMMAND_ONESHOT_START:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "ONESHOT START");
         #endif
         is_oneshot = true;
         is_continuous = false;
         is_start = true;
         is_stop = false;
         commands();
      break;

      case I2C_TH_COMMAND_ONESHOT_STOP:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "ONESHOT STOP");
         #endif
         is_oneshot = true;
         is_continuous = false;
         is_start = false;
         is_stop = true;
         commands();
      break;

      case I2C_TH_COMMAND_ONESHOT_START_STOP:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "ONESHOT START-STOP");
         #endif
         is_oneshot = true;
         is_continuous = false;
         is_start = true;
         is_stop = true;
         commands();
      break;

      case I2C_TH_COMMAND_CONTINUOUS_START:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "CONTINUOUS START");
         #endif
         is_oneshot = false;
         is_continuous = true;
         is_start = true;
         is_stop = false;
         commands();
      break;

      case I2C_TH_COMMAND_CONTINUOUS_STOP:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "CONTINUOUS STOP");
         #endif
         is_oneshot = false;
         is_continuous = true;
         is_start = false;
         is_stop = true;
         commands();
      break;

      case I2C_TH_COMMAND_CONTINUOUS_START_STOP:
         #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
         strcpy(buffer, "CONTINUOUS START-STOP");
         #endif
         is_oneshot = false;
         is_continuous = true;
         is_start = true;
         is_stop = true;
         commands();
      break;

      case I2C_TH_COMMAND_SAVE:
         is_oneshot = false;
         is_continuous = false;
         is_start = false;
         is_stop = false;
         SERIAL_TRACE("Execute command [ SAVE ]\r\n");
         save_configuration(CONFIGURATION_CURRENT);
      break;
   }

   #if (SERIAL_TRACE_LEVEL >= SERIAL_TRACE_LEVEL_TRACE)
   if (configuration.is_oneshot == is_oneshot || configuration.is_continuous == is_continuous) {
      SERIAL_TRACE("Execute [ %s ]\r\n", buffer);
   }
   else if (configuration.is_oneshot == is_continuous || configuration.is_continuous == is_oneshot) {
      SERIAL_TRACE("Ignore [ %s ]\r\n", buffer);
   }
   #endif

   noInterrupts();
   is_event_command_task = false;
   ready_tasks_count--;
   interrupts();
}

void commands() {
   noInterrupts();

   if (configuration.is_oneshot && is_oneshot && is_stop) {
      if (temperature_samples.count == 1) {
         readable_data_write_ptr->temperature.sample = temperature_samples.values[0];
         SERIAL_INFO("--> temperature: %u\r\n", readable_data_write_ptr->temperature.sample);
      }
      else SERIAL_INFO("--> temperature: ---\r\n");

      if (humidity_samples.count == 1) {
         readable_data_write_ptr->humidity.sample = humidity_samples.values[0];
         SERIAL_INFO("--> humidity: %u\r\n", readable_data_write_ptr->humidity.sample);
      }
      else SERIAL_INFO("--> humidity: ---\r\n");

      stop_timer();
      samples_processing(true);
      exchange_buffers();
   }
   else if (configuration.is_continuous && is_continuous && is_stop) {
      stop_timer();
      samples_processing(true);
      exchange_buffers();
   }

   if (configuration.is_oneshot && is_oneshot && is_start) {
      stop_timer();
      start_timer();

      if (!is_event_sensors_reading) {
         is_event_sensors_reading = true;
         ready_tasks_count++;
      }
   }
   else if (configuration.is_continuous && is_continuous && is_start) {
      stop_timer();
      start_timer();
   }

   interrupts();
}
