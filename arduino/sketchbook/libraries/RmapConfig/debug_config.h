/**@file debug_config.h */

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

#ifndef _DEBUG_CONFIG_H
#define _DEBUG_CONFIG_H

//! Serial debug level definitions
#define SERIAL_TRACE_LEVEL_OFF            (0)
#define SERIAL_TRACE_LEVEL_ERROR          (1)
#define SERIAL_TRACE_LEVEL_WARNING        (2)
#define SERIAL_TRACE_LEVEL_INFO           (3)
#define SERIAL_TRACE_LEVEL_DEBUG          (4)
#define SERIAL_TRACE_LEVEL_TRACE          (5)

//! LCD debug level definitions
#define LCD_TRACE_LEVEL_OFF               (0)
#define LCD_TRACE_LEVEL_ERROR             (1)
#define LCD_TRACE_LEVEL_WARNING           (2)
#define LCD_TRACE_LEVEL_INFO              (3)
#define LCD_TRACE_LEVEL_DEBUG             (4)

#define OK_STRING                         ("OK")
#define ERROR_STRING                      ("ERROR")
#define FAIL_STRING                       ("FAIL")
#define YES_STRING                        ("YES")
#define NO_STRING                         ("NO")
#define ON_STRING                         ("ON")
#define OFF_STRING                        ("OFF")

//! SensorDriver
#define SENSOR_DRIVER_SERIAL_TRACE_LEVEL  (SERIAL_TRACE_LEVEL_OFF)

//! Sim800
#define SIM800_SERIAL_TRACE_LEVEL         (SERIAL_TRACE_LEVEL_INFO)

//! I2C-TH
#define I2C_TH_SERIAL_TRACE_LEVEL         (SERIAL_TRACE_LEVEL_INFO)

//! I2C-RAIN
#define I2C_RAIN_SERIAL_TRACE_LEVEL       (SERIAL_TRACE_LEVEL_INFO)

//! rmap
#define RMAP_SERIAL_TRACE_LEVEL           (SERIAL_TRACE_LEVEL_INFO)
#define RMAP_LCD_TRACE_LEVEL              (LCD_TRACE_LEVEL_INFO)

#endif
