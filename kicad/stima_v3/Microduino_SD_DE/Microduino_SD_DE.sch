EESchema Schematic File Version 2
LIBS:Libreria_SCH_mia
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Microduino_SD_DE-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Microduino SD DE"
Date "30 luglio 2017"
Rev "0.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 9450 2650
NoConn ~ 9550 2650
NoConn ~ 9150 2650
NoConn ~ 9050 2650
NoConn ~ 8950 2650
NoConn ~ 8850 2650
NoConn ~ 8750 2650
NoConn ~ 10200 3600
NoConn ~ 10200 3700
NoConn ~ 10200 3900
$Comp
L GND #PWR01
U 1 1 58D4FFFC
P 9950 4150
F 0 "#PWR01" H 9950 3900 50  0001 C CNN
F 1 "GND" H 9950 4000 50  0000 C CNN
F 2 "" H 9950 4150 50  0000 C CNN
F 3 "" H 9950 4150 50  0000 C CNN
	1    9950 4150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR02
U 1 1 58D50BEE
P 8000 4000
F 0 "#PWR02" H 8000 3850 50  0001 C CNN
F 1 "+5V" H 8000 4140 50  0000 C CNN
F 2 "" H 8000 4000 50  0000 C CNN
F 3 "" H 8000 4000 50  0000 C CNN
	1    8000 4000
	1    0    0    1   
$EndComp
$Comp
L +3.3V #PWR03
U 1 1 58D50CA7
P 8000 3900
F 0 "#PWR03" H 8000 3750 50  0001 C CNN
F 1 "+3.3V" H 8000 4040 50  0000 C CNN
F 2 "" H 8000 3900 50  0000 C CNN
F 3 "" H 8000 3900 50  0000 C CNN
	1    8000 3900
	1    0    0    -1  
$EndComp
Text Label 8200 3800 0    60   ~ 0
CS
Text Label 8200 3700 0    60   ~ 0
D8
Text Label 8200 3600 0    60   ~ 0
D9
Text Label 8200 3500 0    60   ~ 0
D10
Text Label 8200 3400 0    60   ~ 0
DI
Text Label 8200 3300 0    60   ~ 0
DO
Text Label 8200 3200 0    60   ~ 0
CLK
NoConn ~ 8200 3600
NoConn ~ 8200 3500
Text Label 8750 2650 3    60   ~ 0
AREF
Text Label 8850 2650 3    60   ~ 0
A0
Text Label 8950 2650 3    60   ~ 0
A1
Text Label 9050 2650 3    60   ~ 0
A2
Text Label 9150 2650 3    60   ~ 0
A3
Text Label 9250 2650 3    60   ~ 0
SDA
Text Label 9350 2650 3    60   ~ 0
SCL
Text Label 9450 2650 3    60   ~ 0
A6
Text Label 9550 2650 3    60   ~ 0
A7
Text Label 10200 3200 2    60   ~ 0
D0
Text Label 10200 3300 2    60   ~ 0
D1
Text Label 10200 3400 2    60   ~ 0
D2
Text Label 10200 3500 2    60   ~ 0
D3
Text Label 10200 3600 2    60   ~ 0
D4
Text Label 10200 3700 2    60   ~ 0
D5
Text Label 10200 3800 2    60   ~ 0
D6
Text Label 10200 3900 2    60   ~ 0
RESET
Text Notes 8800 4400 0    118  ~ 24
UPIN 27
$Comp
L CONN_1x27 P1
U 1 1 58E8C7EF
P 8650 4000
F 0 "P1" H 8650 3900 50  0000 C CNN
F 1 "CONN_1x27" V 9550 4400 50  0000 C CNN
F 2 "Libreria_PCB_mia:Upin_27" H 9650 4400 50  0001 C CNN
F 3 "" H 9650 4400 50  0000 C CNN
	1    8650 4000
	1    0    0    -1  
$EndComp
Text Notes 7150 6950 0    236  Italic 47
DigitEco s.r.l.
NoConn ~ 9250 2650
NoConn ~ 9350 2650
NoConn ~ 8200 3700
$Comp
L C C1
U 1 1 594FDE58
P 5600 4900
F 0 "C1" H 5625 5000 50  0000 L CNN
F 1 "100nF" H 5625 4800 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805" H 5638 4750 50  0001 C CNN
F 3 "" H 5600 4900 50  0000 C CNN
	1    5600 4900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 59504BBA
P 5600 5200
F 0 "#PWR04" H 5600 4950 50  0001 C CNN
F 1 "GND" H 5600 5050 50  0000 C CNN
F 2 "" H 5600 5200 50  0000 C CNN
F 3 "" H 5600 5200 50  0000 C CNN
	1    5600 5200
	1    0    0    -1  
$EndComp
NoConn ~ 10200 3800
NoConn ~ 10200 3500
NoConn ~ 10200 3400
NoConn ~ 10200 3300
NoConn ~ 10200 3200
Wire Wire Line
	8200 3300 8450 3300
Wire Wire Line
	8450 3500 8200 3500
Wire Wire Line
	8450 3900 8000 3900
Wire Wire Line
	10200 3700 9850 3700
Wire Wire Line
	10200 3900 9850 3900
Wire Wire Line
	9950 4000 9950 4150
Wire Wire Line
	8000 4000 8450 4000
Wire Wire Line
	8450 3800 8200 3800
Wire Wire Line
	8450 3200 8200 3200
Wire Wire Line
	8450 3400 8200 3400
Wire Wire Line
	8450 3600 8200 3600
Wire Wire Line
	9550 2900 9550 2650
Wire Wire Line
	9350 2650 9350 2900
Wire Wire Line
	9150 2650 9150 2900
Wire Wire Line
	8950 2650 8950 2900
Wire Wire Line
	8750 2650 8750 2900
Wire Wire Line
	9450 2650 9450 2900
Wire Wire Line
	9050 2650 9050 2900
Wire Wire Line
	8850 2650 8850 2900
Wire Wire Line
	9850 3600 10200 3600
Wire Wire Line
	9250 2650 9250 2900
Wire Wire Line
	9850 3800 10200 3800
Wire Wire Line
	9950 4000 9850 4000
Wire Wire Line
	8200 3700 8450 3700
Wire Wire Line
	5600 5050 5600 5200
Wire Wire Line
	5600 4600 5600 4750
Wire Wire Line
	9850 3200 10200 3200
Wire Wire Line
	10200 3300 9850 3300
Wire Wire Line
	9850 3400 10200 3400
Wire Wire Line
	10200 3500 9850 3500
$Comp
L 4050 U1
U 6 1 597B84E5
P 4450 4900
F 0 "U1" H 4645 5015 50  0000 C CNN
F 1 "4050" H 4640 4775 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 4450 4900 60  0001 C CNN
F 3 "" H 4450 4900 60  0001 C CNN
	6    4450 4900
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 5 1 597B84AA
P 2750 4900
F 0 "U1" H 2945 5015 50  0000 C CNN
F 1 "4050" H 2940 4775 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 2750 4900 60  0001 C CNN
F 3 "" H 2750 4900 60  0001 C CNN
	5    2750 4900
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 4 1 597B845F
P 2750 2000
F 0 "U1" H 2945 2115 50  0000 C CNN
F 1 "4050" H 2940 1875 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 2750 2000 60  0001 C CNN
F 3 "" H 2750 2000 60  0001 C CNN
	4    2750 2000
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 3 1 597B83EC
P 2750 2500
F 0 "U1" H 2945 2615 50  0000 C CNN
F 1 "4050" H 2940 2375 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 2750 2500 60  0001 C CNN
F 3 "" H 2750 2500 60  0001 C CNN
	3    2750 2500
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 2 1 597B83B9
P 2750 3000
F 0 "U1" H 2945 3115 50  0000 C CNN
F 1 "4050" H 2940 2875 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 2750 3000 60  0001 C CNN
F 3 "" H 2750 3000 60  0001 C CNN
	2    2750 3000
	1    0    0    -1  
$EndComp
$Comp
L 4050 U1
U 1 1 597B8320
P 2750 3500
F 0 "U1" H 2945 3615 50  0000 C CNN
F 1 "4050" H 2940 3375 50  0000 C CNN
F 2 "Housings_SSOP:TSSOP-16_4.4x5mm_Pitch0.65mm" H 2750 3500 60  0001 C CNN
F 3 "" H 2750 3500 60  0001 C CNN
	1    2750 3500
	1    0    0    -1  
$EndComp
$Comp
L Micro_SD_Card CARD1
U 1 1 597B85A1
P 5450 3200
F 0 "CARD1" H 4800 3800 50  0000 C CNN
F 1 "Micro_SD_Card" H 6100 3800 50  0000 R CNN
F 2 "Connectors:microSD_Card_Receptacle_Wuerth_693072010801" H 6600 3500 50  0001 C CNN
F 3 "" H 5450 3200 50  0000 C CNN
	1    5450 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3500 3400 3500
Wire Wire Line
	3400 3500 3400 3300
Wire Wire Line
	3400 3300 4550 3300
Wire Wire Line
	1800 3500 2300 3500
Wire Wire Line
	2300 3000 1800 3000
Wire Wire Line
	2300 2500 1800 2500
Wire Wire Line
	2300 2000 1500 2000
Wire Wire Line
	3200 3000 3900 3000
Wire Wire Line
	3900 3000 3900 3100
Wire Wire Line
	3900 3100 4550 3100
Wire Wire Line
	4100 3000 4550 3000
Wire Wire Line
	4100 2400 4100 3000
Wire Wire Line
	4100 2500 3200 2500
Wire Wire Line
	4550 3200 3700 3200
$Comp
L +3.3V #PWR05
U 1 1 597B9204
P 3700 3200
F 0 "#PWR05" H 3700 3050 50  0001 C CNN
F 1 "+3.3V" H 3700 3340 50  0000 C CNN
F 2 "" H 3700 3200 50  0000 C CNN
F 3 "" H 3700 3200 50  0000 C CNN
	1    3700 3200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 597B9240
P 3700 3400
F 0 "#PWR06" H 3700 3150 50  0001 C CNN
F 1 "GND" H 3700 3250 50  0000 C CNN
F 2 "" H 3700 3400 50  0000 C CNN
F 3 "" H 3700 3400 50  0000 C CNN
	1    3700 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3400 3700 3400
Wire Wire Line
	4100 3500 4100 4000
Wire Wire Line
	4100 4000 1800 4000
$Comp
L LED_ALT D1
U 1 1 597B9A82
P 4100 2250
F 0 "D1" V 4100 2350 50  0000 C CNN
F 1 "ROSSO" H 4100 2150 50  0000 C CNN
F 2 "LEDs:LED_0805" H 4100 2250 50  0001 C CNN
F 3 "" H 4100 2250 50  0000 C CNN
	1    4100 2250
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 597B9B87
P 3600 2000
F 0 "R1" V 3680 2000 50  0000 C CNN
F 1 "470" V 3600 2000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3530 2000 50  0001 C CNN
F 3 "" H 3600 2000 50  0000 C CNN
	1    3600 2000
	0    1    1    0   
$EndComp
Connection ~ 4100 2500
Wire Wire Line
	4100 2100 4100 2000
Wire Wire Line
	4100 2000 3750 2000
Wire Wire Line
	3450 2000 3200 2000
Text Label 1800 2500 0    60   ~ 0
CS
Text Label 1800 3000 0    60   ~ 0
DI
Text Label 1800 3500 0    60   ~ 0
CLK
Text Label 1800 4000 0    60   ~ 0
DO
Wire Wire Line
	1500 2000 1500 3250
Wire Wire Line
	1500 3250 2200 3250
Wire Wire Line
	2200 3250 2200 3500
Connection ~ 2200 3500
$Comp
L GND #PWR07
U 1 1 597BAB93
P 2300 5100
F 0 "#PWR07" H 2300 4850 50  0001 C CNN
F 1 "GND" H 2300 4950 50  0000 C CNN
F 2 "" H 2300 5100 50  0000 C CNN
F 3 "" H 2300 5100 50  0000 C CNN
	1    2300 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 597BABCB
P 4000 5100
F 0 "#PWR08" H 4000 4850 50  0001 C CNN
F 1 "GND" H 4000 4950 50  0000 C CNN
F 2 "" H 4000 5100 50  0000 C CNN
F 3 "" H 4000 5100 50  0000 C CNN
	1    4000 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR09
U 1 1 597BAC7D
P 2700 5100
F 0 "#PWR09" H 2700 4850 50  0001 C CNN
F 1 "GND" H 2700 4950 50  0000 C CNN
F 2 "" H 2700 5100 50  0000 C CNN
F 3 "" H 2700 5100 50  0000 C CNN
	1    2700 5100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR010
U 1 1 597BACA9
P 2700 4700
F 0 "#PWR010" H 2700 4550 50  0001 C CNN
F 1 "+3.3V" H 2700 4840 50  0000 C CNN
F 2 "" H 2700 4700 50  0000 C CNN
F 3 "" H 2700 4700 50  0000 C CNN
	1    2700 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4900 2300 4900
Wire Wire Line
	2300 4900 2300 5100
Wire Wire Line
	2700 5100 2700 5000
Wire Wire Line
	2700 4700 2700 4800
$Comp
L +3.3V #PWR011
U 1 1 597BB22F
P 5600 4600
F 0 "#PWR011" H 5600 4450 50  0001 C CNN
F 1 "+3.3V" H 5600 4740 50  0000 C CNN
F 2 "" H 5600 4600 50  0000 C CNN
F 3 "" H 5600 4600 50  0000 C CNN
	1    5600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4900 4000 5100
NoConn ~ 4550 2900
NoConn ~ 4550 3600
NoConn ~ 3200 4900
NoConn ~ 4900 4900
$Comp
L GND #PWR012
U 1 1 597BBF40
P 6250 3900
F 0 "#PWR012" H 6250 3650 50  0001 C CNN
F 1 "GND" H 6250 3750 50  0000 C CNN
F 2 "" H 6250 3900 50  0000 C CNN
F 3 "" H 6250 3900 50  0000 C CNN
	1    6250 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3800 6250 3900
Wire Wire Line
	4100 3500 4550 3500
$EndSCHEMATC
