/*! \mainpage STIMA Readme
\section introduction Introduction
software to collect weather data contributed by citizens; to make
these data available for weather services and homeland security; to
provide feedback to the data contributors so that they have the tools
to check and improve their data quality

http://rmap.cc

\section howto Howto

\subsection report_eth STIMA Report over Ethernet:

1) open sketch arduino/sketchbook/rmap/rmap/rmap.ino

2) in arduino/sketchbook/rmap/rmap/rmap-config.h set STIMA_MODULE_TYPE_REPORT_ETH in MODULE_VERSION define

3) open arduino/sketchbook/libraries/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor's driver and library

\subsection report_gsm STIMA Report over GSM/GPRS:

1) open sketch arduino/sketchbook/rmap/rmap/rmap.ino

2) in arduino/sketchbook/rmap/rmap/rmap-config.h set STIMA_MODULE_TYPE_REPORT_GSM in MODULE_VERSION define

3) open arduino/sketchbook/libraries/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor's driver and library

\subsection i2c-th STIMA I2C-TH:

1) open sketch arduino/sketchbook/rmap/i2c-th/i2c-th.ino

2) open arduino/sketchbook/libraries/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor's driver and library

\subsection i2c-rain STIMA I2C-Rain:

1) open sketch arduino/sketchbook/rmap/i2c-rain/i2c-rain.ino

2) open arduino/sketchbook/libraries/RmapConfig/sensors_config.h and set false
in all sensors's define and json's define

\section library Project Library

For details, look at the specific library files.

\subsection rmapconfig RmapConfig

This library contains the definitions that are useful for configuring some default values.
Below is a list of the files contained therein.

debug_config.h: Enable or disable debug in sketch and library

ethernet_config.h: Ethernet configuration's parameters

gsm_config.h: GSM configuration's parameters

hardware_config.h: Hardware configuration's parameters

json_config.h: JSON configuration's parameters

lcd_config.h: LCD configuration's parameters

mqtt_config.h: MQTT configuration's parameters

ntp_config.h: NTP configuration's parameters

sdcard_config.h: SDCARD configuration's parameters

sensors_config.h: Enable or disable sensor driver sensors for specific sketch

\subsection rmap Rmap

This library contains generic utility features. Below is a list of the files contained therein.

debug.h debug.cpp: Debugging functions for print debug message on serial port or LCD

eeprom_utility.h eeprom_utility.cpp: EEPROM utility for write and read eeprom

i2c_utility.h i2c_utility.cpp: I2C utility

registers.h: General register's define

registers-th.h: I2C-TH register's define

registers-rain.h: I2C-Rain register's define

rmap_utility.h rmap_utility.cpp: RMAP useful functions

sdcard_utility.h sdcard_utility.cpp: SD-Card useful functions

stima_module.h: STIMA station's definition

typedef.h: Useful project typedef

\subsection sensordriver SensorDriver

This library is provided to read measurements from I2C sensors.

SensorDriverSensors.h: define list with sensor names in SensorDriver

SensorDriver.h SensorDriver.cpp: SensorDriver library files

\subsection hyt2x1 HYT2X1

This library implements functions for read and configure HYT271 and HYT221 sensors.

hyt2x1.h hyt2x1.cpp: HYT2X1 library files

\subsection ntp NTP

This library implements NTP functions for read time over NTP server with ethernet client or sim800 client.

ntp.h ntp.cpp: NTP library files

\subsection pcf8563 PCF8563

This library implements PCF8563 functions for communicate with pcf8563 real time clock.

pcf8563.h pcf8563.cpp: PCF8563 library files

\subsection sim800 SIM800

This library implements SIM800 functions for communicate with SIM800C/SIM800L GSM/GPRS module.

sim800.h sim800.cpp: SIM800 library files

sim800Client.h: SIM800 library interface for Arduino Client.

SIM800C is fully supported, SIM800L is partially supported (coming soon...)

\subsection implemented Implemented features

\subsubsection transport Transport

o) Serial: yes

o) Ethernet: partial (basic functions are present but need to interface with Ethernet Client)

o) MQTT: partial (subscribe functions are present but need to interface with rpc process function)

See stream_task and rpc_process functions in rmap.ino

\subsubsection files SD-Card files

On the sdcard there is a file called mqtt_ptr.txt containing a binary data in uint32_t format
corresponding to the seconds passed since 00:00:00 01/01/1970 indicating the last data sent by MQTT.

The data is recorded on files (one file for each recording day) named in the format yyyy_mm_dd.txt
and each data recorded on sd card is MQTT_SENSOR_TOPIC_LENGTH + MQTT_MESSAGE_LENGTH bytes long (look at the mqtt_config.h file).

Each recorded data has the format of the type: TRANGE/LEVEL/VAR { “v”: VALUE, “t”: TIME}

\subsubsection sensordriversensors SensorDriver's sensors

o) HYT221 and HYT271: Temperature and humidity sensors

o) DigitecoPower: Power parameters sensor (battery voltage, current and charge percentage, source voltage and current, load voltage)

o) I2C-TH: oneshot and continuous mode

o) I2C-Rain: oneshot mode

other sensors can be easily integrated (see SensorDriver library).
