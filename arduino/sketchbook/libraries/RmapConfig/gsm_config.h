/**@file gsm_config.h */

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

#ifndef _GSM_CONFIG_H
#define _GSM_CONFIG_H

#define GSM_APN_TIM                       ("ibox.tim.it")
#define GSM_APN_WIND                      ("internet.wind")
#define GSM_APN_VODAFONE                  ("m2mbis.vodafone.it")

#define GSM_DEFAULT_APN                   (GSM_APN_WIND)
#define GSM_DEFAULT_USERNAME              ("")
#define GSM_DEFAULT_PASSWORD              ("")

#define GSM_APN_LENGTH                    (20)
#define GSM_USERNAME_LENGTH               (20)
#define GSM_PASSWORD_LENGTH               (20)

#define USE_SIM_800C                      (true)
#define USE_SIM_800L                      (false)

#if (USE_SIM_800C == true && USE_SIM_800L == true)
#error What SIM800 do you want to use? specific it in gsm_config.h

#elif (USE_SIM_800C == true)
#define SIM800_ON_OFF_PIN                 (5)

#elif (USE_SIM_800L == true)
#define SIM800_ON_OFF_PIN                 (7)
#define SIM800_RESET_PIN                  (6)

#endif

#endif
