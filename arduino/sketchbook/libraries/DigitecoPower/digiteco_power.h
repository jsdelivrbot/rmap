/**@file digiteco_power.h */

/*********************************************************************
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

#ifndef _DIGITECO_POWER_H
#define _DIGITECO_POWER_H

#include <Arduino.h>
#include <Wire.h>

#define DIGITECO_POWER_DEFAULT_ADDRESS             (0x30)

#define DIGITECO_POWER_READ_DATA_LENGTH            (4)

#define DIGITECO_POWER_INPUT_VOLTAGE_ADDRESS       (0)
#define DIGITECO_POWER_INPUT_CURRENT_ADDRESS       (1)
#define DIGITECO_POWER_BATTERY_VOLTAGE_ADDRESS     (2)
#define DIGITECO_POWER_BATTERY_CURRENT_ADDRESS     (3)
#define DIGITECO_POWER_BATTERY_PERCENTAGE_ADDRESS  (4)
#define DIGITECO_POWER_OUTPUT_VOLTAGE_ADDRESS      (5)

namespace DigitecoPower {
  bool de_read(uint8_t address, float *value);
  bool de_send(uint8_t address, uint8_t data);
};

#endif
