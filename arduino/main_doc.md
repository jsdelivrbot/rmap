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

2) in rmap-config.h set STIMA_MODULE_TYPE_REPORT_ETH in MODULE_VERSION define

3) open arduino/sketchbook/library/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor driver and library

\subsection report_gsm STIMA Report over GSM/GPRS:

1) open sketch arduino/sketchbook/rmap/rmap/rmap.ino

2) in rmap-config.h set STIMA_MODULE_TYPE_REPORT_GSM in MODULE_VERSION define

3) open arduino/sketchbook/library/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor driver and library

\section RmapConfig RmapConfig library

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

\section Rmap Rmap library

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
