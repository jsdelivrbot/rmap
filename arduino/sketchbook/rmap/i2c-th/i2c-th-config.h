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

#include <sensors_config.h>

/**********************************************************************
* MODULE
*********************************************************************/
/*!
\def MODULE_VERSION
Module version.
*/
#define MODULE_VERSION                                (3)

/*!
\def MODULE_TYPE
Type of module. It is defined in registers.h
*/
#define MODULE_TYPE                                   (STIMA_MODULE_TYPE_TH)

/*!
\def USE_POWER_DOWN
Enable or disable power down.
*/
#define USE_POWER_DOWN                                (true)

/*!
\def DEBOUNCING_POWER_DOWN_TIME_MS
Debounce power down ms.
*/
#define DEBOUNCING_POWER_DOWN_TIME_MS                 (100)

/**********************************************************************
* CONFIGURATION
*********************************************************************/
/*!
\def CONFIGURATION_DEFAULT_IS_ONESHOT
Default oneshot modality.
*/
#define CONFIGURATION_DEFAULT_IS_ONESHOT              (false)

/*!
\def CONFIGURATION_DEFAULT_IS_CONTINUOUS
Default oneshot modality.
*/
#define CONFIGURATION_DEFAULT_IS_CONTINUOUS           (true)

/*!
\def CONFIGURATION_DEFAULT_I2C_ADDRESS
Default i2c address.
*/
#define CONFIGURATION_DEFAULT_I2C_ADDRESS             (I2C_TH_DEFAULT_ADDRESS)

/*!
\def CONFIGURATION_DEFAULT_TEMPERATURE_ADDRESS
Default i2c address.
*/
#define CONFIGURATION_DEFAULT_TEMPERATURE_ADDRESS     (I2C_TH_TEMPERATURE_DEFAULT_ADDRESS)

/*!
\def CONFIGURATION_DEFAULT_HUMIDITY_ADDRESS
Default i2c address.
*/
#define CONFIGURATION_DEFAULT_HUMIDITY_ADDRESS        (I2C_TH_HUMIDITY_DEFAULT_ADDRESS)

/*!
\def RESET_CONFIGURATION_PIN
Input pin for reset configuration at startup.
*/
#define CONFIGURATION_RESET_PIN                       (8)

/**********************************************************************
* WATCHDOG
*********************************************************************/
/*!
\def WDT_TIMER
Timer for generating watchdog interrupt for: periodically check to avoid malfunctions

Possible value for WDT_TIMER are:
WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS,
WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S

High values correspond to high energy savings.
*/
#define WDT_TIMER                                     (WDTO_8S)

/**********************************************************************
* TIMER
*********************************************************************/

#define TIMER1_VALUE_S                                (2)
#define TIMER1_ERROR_MS                               (97)
#define TIMER1_VALUE_MAX_S                            (8)

/**********************************************************************
* HUMIDITY AND TEMPERATURE SENSORS
*********************************************************************/

// sampling every 3-15 seconds --> watchdog timer (SAMPLE_SECONDS in relative modules)
// observations with processing every 1-10 minutes (minutes for processing sampling)
// report every 5-60 minutes (> OBSERVATIONS_MINUTES)

/*!
\def SAMPLE_SECONDS
Seconds for sampling sensors.
*/
#define SAMPLE_SECONDS                                (4)
#define SAMPLE_ERROR                                  (TIMER1_ERROR_MS * 0.002)

// #define SAMPLE_COUNT_MIN                              (2)

#define SAMPLE_COUNT_MIN                              (uint8_t)(OBSERVATIONS_MINUTES * 60 / (SAMPLE_SECONDS + SAMPLE_ERROR))
#define SAMPLE_COUNT_MAX                              (SAMPLE_COUNT_MIN+1)
#define SAMPLE_COUNT_TOLLERANCE                       (2)

#define USE_SENSORS_COUNT                             (USE_SENSOR_ADT + USE_SENSOR_HIH + USE_SENSOR_HYT)
#if (USE_SENSORS_COUNT == 0)
#error No sensor used. Are you sure? If not, enable it in RmapConfig/sensors_config.h
#endif
