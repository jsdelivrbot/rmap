/**@file mqtt_config.h */

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

#ifndef _MQTT_CONFIG_H
#define _MQTT_CONFIG_H

#define MQTT_ROOT_TOPIC_LENGTH         (50)
#define MQTT_SUBSCRIBE_TOPIC_LENGTH    (50)
#define MQTT_SENSOR_TOPIC_LENGTH       (30)
#define MQTT_MESSAGE_LENGTH            (50)
#define MQTT_SERVER_LENGTH             (30)
#define MQTT_USERNAME_LENGTH           (30)
#define MQTT_PASSWORD_LENGTH           (30)

#define MQTT_TIMEOUT_MS                (6000)

#define MQTT_DEFAULT_SERVER            ("rmap.cc")
#define MQTT_DEFAULT_PORT              (1883)
#define MQTT_DEFAULT_ROOT_TOPIC        ("")   // 1132822,4450078 arpae 1162336,4465346 spcap
#define MQTT_DEFAULT_SUBSCRIBE_TOPIC   ("")      // 1100000,4400000 eth 1100001,4400001 gsm
#define MQTT_DEFAULT_USERNAME          ("")
#define MQTT_DEFAULT_PASSWORD          ("")

#if (MQTT_ROOT_TOPIC_LENGTH + MQTT_SENSOR_TOPIC_LENGTH > 100)
#error MQTT root/sensor topic is too big!
#endif

#endif
