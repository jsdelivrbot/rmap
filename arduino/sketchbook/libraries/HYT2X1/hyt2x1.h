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

#ifndef _HYT2X1_H
#define _HYT2X1_H

#include "Arduino.h"
#include <Wire.h>

#define HYT2X1_DEFAULT_ADDRESS      (0x28)
#define HYT2X1_READ_HT_DATA_LENGTH  (4)
#define HYT2X1_ENTER_COMMAND_MODE   (0xA0)
#define HYT2X1_EXIT_COMMAND_MODE    (0x80)
#define HYT2X1_WRITE_ADDRESS        (0x5C)
#define HYT2X1_CONVERSION_TIME_MS   (100)
#define HYT2X1_TEMPERATURE_MIN      (-40)
#define HYT2X1_TEMPERATURE_MAX      (125)
#define HYT2X1_HUMIDITY_MIN         (0)
#define HYT2X1_HUMIDITY_MAX         (100)

namespace Hyt2X1 {
  void init(uint8_t);
  void on(uint8_t);
  void off(uint8_t);
  void changeAddress(uint8_t, int8_t, int8_t);
  uint32_t initRead(uint8_t);
  bool read(int8_t, float *, float *);
  void send(int8_t, uint8_t, uint8_t, uint8_t);
};

#endif
