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

#ifndef _SLEEP_UTILITY_H
#define _SLEEP_UTILITY_H

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <hardware_config.h>

// void wdt_init(uint8_t);
void power_down(uint32_t *, uint32_t);

#define executeTimerTaskEach(current, desidered, offset) (desidered % offset == 0 ? (current % desidered == 0 ? 1 : 0) : 0)

#endif
