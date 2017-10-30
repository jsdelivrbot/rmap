/*! \mainpage STIMA Readme
\section introduction Introduction
software to collect weather data contributed by citizens; to make
these data available for weather services and homeland security; to
provide feedback to the data contributors so that they have the tools
to check and improve their data quality

http://rmap.cc

\section howto Howto

\subsection report_eth STIMA Report over Ethernet:

\subsubsection report_eth_1 1)
open sketch arduino/sketchbook/rmap/rmap/rmap.ino

\subsubsection report_eth_2 2)
in rmap-config.h set STIMA_MODULE_TYPE_REPORT_ETH in MODULE_VERSION define

\subsubsection report_eth_3 3)
open arduino/sketchbook/library/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor driver and library

\subsection report_gsm STIMA Report over GSM:

\subsubsection report_gsm_1 1)
open sketch arduino/sketchbook/rmap/rmap/rmap.ino

\subsubsection report_gsm_2 2)
in rmap-config.h set STIMA_MODULE_TYPE_REPORT_GSM in MODULE_VERSION define

\subsubsection report_gsm_3 3)
open arduino/sketchbook/library/RmapConfig/sensors_config.h and set true or false
sensors's define and json's define in order to enable or disable relative sensor driver and library

\section RmapConfig RmapConfig library

\subsection debug_config debug_config.h:
Enable or disable debug in sketch and library

\subsection ethernet_config ethernet_config.h:
Ethernet configuration's parameters

\subsection gsm_config gsm_config.h:
GSM configuration's parameters

\subsection hardware_config hardware_config.h:
Hardware configuration's parameters

\subsection json_config json_config.h:
JSON configuration's parameters

\subsection lcd_config lcd_config.h:
LCD configuration's parameters

\subsection mqtt_config mqtt_config.h:
MQTT configuration's parameters

\subsection ntp_config ntp_config.h:
NTP configuration's parameters

\subsection sdcard_config sdcard_config.h:
SDCARD configuration's parameters

\subsection sensors_config sensors_config.h:
Enable or disable sensor driver sensors for specific sketch

\section Rmap Rmap library

\subsection debug debug:
Debugging functions for print debug message on serial port or LCD

\subsection eeprom_utility eeprom_utility:
EEPROM utility for write and read eeprom

\subsection i2c_utility i2c_utility:
I2C utility

\subsection registers registers:
General register's define

\subsection registers-th registers-th:
I2C-TH register's define

\subsection registers-rain registers-rain:
I2C-Rain register's define

\subsection rmap_utility rmap_utility:
RMAP useful functions

\subsection sdcard_utility sdcard_utility:
SD-Card useful functions

\subsection stima_module stima_module:
STIMA station's definition

\subsection typedef typedef:
Useful project typedef
