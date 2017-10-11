/**@file typedef.h */

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

#ifndef _TYPEDEF_H
#define _TYPEDEF_H

#include <mqtt_config.h>

#define SENSOR_DRIVER_LENGTH  (5)
#define SENSOR_TYPE_LENGTH    (5)

typedef struct {
  char driver[SENSOR_DRIVER_LENGTH];
  char type[SENSOR_TYPE_LENGTH];
  uint8_t address;
  uint8_t node;
  char mqtt_topic[MQTT_SENSOR_TOPIC_LENGTH];
} sensor_t;

/*!
  \typedef
  \struct rain_t
  Rain data.
*/
typedef struct {
  uint16_t tips_count;  //!< rain gauge tips counter
} rain_t;

/*!
  \typedef
  \struct values_t
  Values for report
*/
typedef struct {
  uint16_t sample; // last sample
  uint16_t med60;  // last observation
  uint16_t med;    // average values of observations
  uint16_t max;    // max values of observations
  uint16_t min;    // minium values of observations
  uint16_t sigma;  // standard deviation of observations
} value_t;

#endif
