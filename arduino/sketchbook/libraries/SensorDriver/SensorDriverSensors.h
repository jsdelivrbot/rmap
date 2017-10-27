/**@file SensorDriverSensors.h */

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

#ifndef SensorDriverSensors_h
#define SensorDriverSensors_h

#define SENSOR_DRIVER_I2C         ("I2C")

#define SENSOR_TYPE_ADT           ("ADT")   // ADT7420
#define SENSOR_TYPE_HIH           ("HIH")   // HIH6100
#define SENSOR_TYPE_HYT           ("HYT")   // HYT271 - HYT221
#define SENSOR_TYPE_DEP           ("DEP")   // DigitEco Power
#define SENSOR_TYPE_HI7           ("HI7")   // SI7021
#define SENSOR_TYPE_BMP           ("BMP")   // Bmp085
#define SENSOR_TYPE_DW1           ("DW1")   // DW1
#define SENSOR_TYPE_TBS           ("TBS")   // Tipping bucket rain gauge
#define SENSOR_TYPE_TBR           ("TBR")   // Tipping bucket rain gauge
#define SENSOR_TYPE_STH           ("STH")   // Temperature and humidity oneshot
#define SENSOR_TYPE_ITH           ("ITH")   // Temperature and humidity oneshot report istantaneous
#define SENSOR_TYPE_MTH           ("MTH")   // Temperature and humidity oneshot report average
#define SENSOR_TYPE_NTH           ("NTH")   // Temperature and humidity oneshot report minium
#define SENSOR_TYPE_XTH           ("XTH")   // Temperature and humidity oneshot report maximum
#define SENSOR_TYPE_SSD           ("SSD")   // SSD011 oneshot
#define SENSOR_TYPE_ISD           ("ISD")   // SSD011 report istantaneous
#define SENSOR_TYPE_MSD           ("MSD")   // SSD011 report average
#define SENSOR_TYPE_NSD           ("NSD")   // SSD011 report minium
#define SENSOR_TYPE_XSD           ("XSD")   // SSD011 report maximum
#define SENSOR_TYPE_SMI           ("SMI")   // MICS4514 oneshot
#define SENSOR_TYPE_IMI           ("IMI")   // MICS4514 report istantaneous
#define SENSOR_TYPE_MMI           ("MMI")   // MICS4514 report average
#define SENSOR_TYPE_NMI           ("NMI")   // MICS4514 report minium
#define SENSOR_TYPE_XMI           ("XMI")   // MICS4514 report maximum
#define SENSOR_TYPE_RF24          ("RF24")  // Radio RF24

#endif
