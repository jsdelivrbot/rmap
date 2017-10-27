/**@file SensorDriver.h */

/*********************************************************************
Copyright (C) 2017  Marco Baldinetti <m.baldinetti@digiteco.it>
authors:
Paolo patruno <p.patruno@iperbole.bologna.it>
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

#ifndef SensorDriver_h
#define SensorDriver_h

#include <debug.h>
#include "SensorDriverSensors.h"
#include <sensors_config.h>
#include <Arduino.h>
#include <Wire.h>

#define SENSOR_DRIVER_ERROR       (1)
#define SENSOR_DRIVER_SUCCESS     (0)

#define SENSOR_DRIVER_C_TO_K      (27315l)

#if (USE_JSON)
#include <json_config.h>
#include <ArduinoJson.h>
#endif

class SensorDriver {
public:
  SensorDriver(const char* driver, const char* type);

  static SensorDriver *create(const char* driver, const char* type);
  static void createAndSetup(const char* driver, const char* type, uint8_t address, SensorDriver *sensors[], uint8_t *sensors_count);

  virtual void setup(const uint8_t address, const uint8_t node = 0);
  virtual void prepare();
  virtual void get(int32_t *values, uint8_t length);

  #if (USE_JSON)
  virtual void getJson(int32_t *values, uint8_t length, char *json_buffer, size_t json_buffer_length = JSON_BUFFER_LENGTH);
  #endif

  // virtual ~SensorDriver();
  const char *getDriver();
  const char *getType();
  uint8_t getAddress();
  uint8_t getNode();
  uint32_t getStartTime();
  uint32_t getDelay();
  int32_t getValues();
  bool isEnd();
  bool isSuccess();
  bool isReaded();
  virtual bool isSetted();
  virtual bool isPrepared();
  virtual void resetPrepared();

protected:
  const char* _driver;
  const char* _type;
  uint8_t _address;
  int8_t _node;
  uint32_t _delay_ms;
  uint32_t _start_time_ms;
  int32_t values[];
  bool _is_end;
  bool _is_success;
  bool _is_readed;

  static void printInfo(const char* driver, const char* type, const uint8_t address = 0, const uint8_t node = 0);
};

#if (USE_SENSOR_HYT)
#include <hyt2x1.h>
#define SENSOR_DRIVER_HYT2X1_HUMIDITY_MIN       (HYT2X1_HUMIDITY_MIN)
#define SENSOR_DRIVER_HYT2X1_HUMIDITY_MAX       (HYT2X1_HUMIDITY_MAX)
#define SENSOR_DRIVER_HYT2X1_TEMPERATURE_MIN    (SENSOR_DRIVER_C_TO_K + (HYT2X1_TEMPERATURE_MIN * 100))
#define SENSOR_DRIVER_HYT2X1_TEMPERATURE_MAX    (SENSOR_DRIVER_C_TO_K + (HYT2X1_TEMPERATURE_MAX * 100))
class SensorDriverHyt2X1 : public SensorDriver {
public:
  SensorDriverHyt2X1(const char* driver, const char* type, bool *is_setted, bool *is_prepared) : SensorDriver(driver, type) {
    _is_setted = is_setted;
    _is_prepared = is_prepared;

    *_is_setted = false;
    *_is_prepared = false;

    SensorDriver::printInfo(driver, type);
    SERIAL_DEBUG(" create... [ OK ]\r\n");
  };
  void setup(const uint8_t address, const uint8_t node = 0);
  void prepare();
  void get(int32_t *values, uint8_t length);

  #if (USE_JSON)
  void getJson(int32_t *values, uint8_t length, char *json_buffer, size_t json_buffer_length = JSON_BUFFER_LENGTH);
  #endif

  bool isSetted();
  bool isPrepared();
  void resetPrepared();

protected:
  bool *_is_setted;
  bool *_is_prepared;

  enum {
    INIT,
    READ,
    END
  } _get_state;
};
#endif

#if (USE_SENSOR_TBS || USE_SENSOR_TBR)
#include "registers-rain.h"
#define SENSOR_DRIVER_RAIN_MIN      (0)
#define SENSOR_DRIVER_RAIN_MAX      (300)
class SensorDriverRain : public SensorDriver {
public:
  SensorDriverRain(const char* driver, const char* type, bool *is_setted, bool *is_prepared) : SensorDriver(driver, type) {
    _is_setted = is_setted;
    _is_prepared = is_prepared;

    *_is_setted = false;
    *_is_prepared = false;

    SensorDriver::printInfo(driver, type);
    SERIAL_DEBUG(" create... [ OK ]\r\n");
  };
  void setup(const uint8_t address, const uint8_t node = 0);
  void prepare();
  void get(int32_t *values, uint8_t length);

  #if (USE_JSON)
  void getJson(int32_t *values, uint8_t length, char *json_buffer, size_t json_buffer_length = JSON_BUFFER_LENGTH);
  #endif

  bool isSetted();
  bool isPrepared();
  void resetPrepared();

protected:
  bool *_is_setted;
  bool *_is_prepared;

  enum {
    INIT,
    SET_RAIN_ADDRESS,
    READ_RAIN,
    END
  } _get_state;
};
#endif

#if (USE_SENSOR_STH || USE_SENSOR_ITH || USE_SENSOR_MTH || USE_SENSOR_NTH || USE_SENSOR_XTH)
#include "registers-th.h"
#define SENSOR_DRIVER_TEMPERATURE_MIN       (SENSOR_DRIVER_C_TO_K + (-50 * 100))
#define SENSOR_DRIVER_TEMPERATURE_MAX       (SENSOR_DRIVER_C_TO_K + (130 * 100))
#define SENSOR_DRIVER_HUMIDITY_MIN          (0)
#define SENSOR_DRIVER_HUMIDITY_MAX          (100)
class SensorDriverTh : public SensorDriver {
public:
  SensorDriverTh(const char* driver, const char* type, bool *is_setted, bool *is_prepared) : SensorDriver(driver, type) {
    _is_setted = is_setted;
    _is_prepared = is_prepared;

    *_is_setted = false;
    *_is_prepared = false;

    SensorDriver::printInfo(driver, type);
    SERIAL_DEBUG(" create... [ OK ]\r\n");
  };
  void setup(const uint8_t address, const uint8_t node = 0);
  void prepare();
  void get(int32_t *values, uint8_t length);

  #if (USE_JSON)
  void getJson(int32_t *values, uint8_t length, char *json_buffer, size_t json_buffer_length = JSON_BUFFER_LENGTH);
  #endif

  bool isSetted();
  bool isPrepared();
  void resetPrepared();

protected:
  bool *_is_setted;
  bool *_is_prepared;

  enum {
    INIT,
    SET_TEMPERATURE_ADDRESS,
    READ_TEMPERATURE,
    SET_HUMIDITY_ADDRESS,
    READ_HUMIDITY,
    END
  } _get_state;
};
#endif

#if (USE_SENSOR_DEP)
#include "digiteco_power.h"
#define SENSOR_DRIVER_INPUT_VOLTAGE_MIN_V       (0 * 100)
#define SENSOR_DRIVER_INPUT_VOLTAGE_MAX_V       (30 * 100)
#define SENSOR_DRIVER_INPUT_CURRENT_MIN_mA      (0)
#define SENSOR_DRIVER_INPUT_CURRENT_MAX_mA      (3000)
#define SENSOR_DRIVER_BATTERY_VOLTAGE_MIN_V     (0 * 100)
#define SENSOR_DRIVER_BATTERY_VOLTAGE_MAX_V     (16 * 100)
#define SENSOR_DRIVER_BATTERY_CURRENT_MIN_mA    (-3000)
#define SENSOR_DRIVER_BATTERY_CURRENT_MAX_mA    (3000)
#define SENSOR_DRIVER_BATTERY_PERCENTAGE_MIN    (0)
#define SENSOR_DRIVER_BATTERY_PERCENTAGE_MAX    (100)
#define SENSOR_DRIVER_OUTPUT_VOLTAGE_MIN_V      (0 * 100)
#define SENSOR_DRIVER_OUTPUT_VOLTAGE_MAX_V      (6 * 100)

class SensorDriverDigitecoPower : public SensorDriver {
public:
  SensorDriverDigitecoPower(const char* driver, const char* type, bool *is_setted, bool *is_prepared) : SensorDriver(driver, type) {
    _is_setted = is_setted;
    _is_prepared = is_prepared;

    *_is_setted = false;
    *_is_prepared = false;

    SensorDriver::printInfo(driver, type);
    SERIAL_DEBUG(" create... [ OK ]\r\n");
  };
  void setup(const uint8_t address, const uint8_t node = 0);
  void prepare();
  void get(int32_t *values, uint8_t length);

  #if (USE_JSON)
  void getJson(int32_t *values, uint8_t length, char *json_buffer, size_t json_buffer_length = JSON_BUFFER_LENGTH);
  #endif

  bool isSetted();
  bool isPrepared();
  void resetPrepared();

protected:
  bool *_is_setted;
  bool *_is_prepared;

  enum {
    INIT,
    SET_BATTERY_PERCENTAGE_ADDRESS,
    READ_BATTERY_PERCENTAGE,
    SET_BATTERY_VOLTAGE_ADDRESS,
    READ_BATTERY_VOLTAGE,
    SET_BATTERY_CURRENT_ADDRESS,
    READ_BATTERY_CURRENT,
    SET_INPUT_VOLTAGE_ADDRESS,
    READ_INPUT_VOLTAGE,
    SET_INPUT_CURRENT_ADDRESS,
    READ_INPUT_CURRENT,
    SET_OUTPUT_VOLTAGE_ADDRESS,
    READ_OUTPUT_VOLTAGE,
    END
  } _get_state;
};
#endif

#endif
