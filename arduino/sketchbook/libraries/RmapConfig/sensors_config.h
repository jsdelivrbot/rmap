/**@file sensors_config.h */

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

#ifndef SENSOR_CONFIG_H
#define SENSOR_CONFIG_H

#define USE_JSON                    (true)   // use json library for json response

#define USE_SENSOR_ADT              (false)   // ADT7420
#define USE_SENSOR_HIH              (false)   // HIH6100
#define USE_SENSOR_HYT              (false)   // HYT271 - HYT221
#define USE_SENSOR_DEP              (true)   // DigitEco Power
#define USE_SENSOR_HI7              (false)   // SI7021
#define USE_SENSOR_BMP              (false)   // Bmp085
#define USE_SENSOR_DW1              (false)   // DW1
#define USE_SENSOR_TBS              (false)   // Tipping bucket rain gauge
#define USE_SENSOR_TBR              (true)   // Tipping bucket rain gauge
#define USE_SENSOR_STH              (false)   // Temperature and humidity oneshot
#define USE_SENSOR_ITH              (true)   // Temperature and humidity continuous istantaneous
#define USE_SENSOR_NTH              (true)   // Temperature and humidity continuous minium
#define USE_SENSOR_MTH              (true)   // Temperature and humidity continuous average
#define USE_SENSOR_XTH              (true)   // Temperature and humidity continuous maximum
#define USE_SENSOR_SSD              (false)   // SSD011 oneshot
#define USE_SENSOR_ISD              (false)   // SSD011 report istantaneous
#define USE_SENSOR_NSD              (false)   // SSD011 report minium
#define USE_SENSOR_MSD              (false)   // SSD011 report average
#define USE_SENSOR_XSD              (false)   // SSD011 report maximum
#define USE_SENSOR_SMI              (false)   // MICS4514 oneshot
#define USE_SENSOR_IMI              (false)   // MICS4514 report istantaneous
#define USE_SENSOR_NMI              (false)   // MICS4514 report minium
#define USE_SENSOR_MMI              (false)   // MICS4514 report average
#define USE_SENSOR_XMI              (false)   // MICS4514 report maximum
#define USE_SENSOR_RF24             (false)   // Radio RF24

#define RAIN_FOR_TIP                (2)

/*!
\def VALUES_TO_READ_FROM_SENSOR_COUNT
Maximum number of values to be read by the sensors.
*/
#define VALUES_TO_READ_FROM_SENSOR_COUNT     (3)

// sampling every 3-15 seconds --> watchdog timer (SENSORS_SAMPLE_TIME_S in relative modules)
// observations with processing every 1-10 minutes (minutes for processing sampling)
// report every 5-60 minutes (> OBSERVATIONS_MINUTES)
// reported data is calulate by moving average on STATISTICAL_DATA_MINUTES window

// observations every 1-10 minutes (minutes for processing samples)
// report every 5-60 minutes (minutes for report. > n * OBSERVATIONS_MINUTES)
#define OBSERVATIONS_MINUTES                 (1)
#define STATISTICAL_DATA_COUNT               (15)  // count for generating statistical processing: refers to OBSERVATIONS_MINUTES

#define OBSERVATION_COUNT                    (60)
#define OBSERVATION_COUNT_TOLLERANCE         (2)

#if (OBSERVATION_COUNT < STATISTICAL_DATA_COUNT)
#error OBSERVATION_COUNT must be major of STATISTICAL_DATA_COUNT !!!
#endif

#endif
