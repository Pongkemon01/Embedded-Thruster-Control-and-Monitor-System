EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
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
LIBS:etcam
LIBS:etcam-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L STM32F303xD/E-LQFP64 U?
U 1 1 5CBAA0DB
P 6250 3400
F 0 "U?" H 5250 5250 60  0000 C CNN
F 1 "STM32F303xD/E-LQFP64" H 7200 1550 60  0000 C CNN
F 2 "Housings_QFP:LQFP-64_10x10mm_Pitch0.5mm" H 7700 1450 60  0001 C CNN
F 3 "" H 5250 5250 60  0001 C CNN
	1    6250 3400
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 5CBAA0EE
P 6500 5500
F 0 "#PWR?" H 6500 5250 50  0001 C CNN
F 1 "GNDA" H 6500 5350 50  0000 C CNN
F 2 "" H 6500 5500 50  0001 C CNN
F 3 "" H 6500 5500 50  0001 C CNN
	1    6500 5500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAA0F4
P 6150 5500
F 0 "#PWR?" H 6150 5250 50  0001 C CNN
F 1 "GND" H 6150 5350 50  0000 C CNN
F 2 "" H 6150 5500 50  0001 C CNN
F 3 "" H 6150 5500 50  0001 C CNN
	1    6150 5500
	1    0    0    -1  
$EndComp
$Comp
L Crystal Y?
U 1 1 5CBAA0FA
P 4100 2900
F 0 "Y?" H 4100 3050 50  0000 C CNN
F 1 "8MHz" H 4100 2750 50  0000 C CNN
F 2 "Crystals:Crystal_SMD_Abracon_ABM3-2pin_5.0x3.2mm_HandSoldering" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAA101
P 3800 3100
F 0 "C?" H 3810 3170 50  0000 L CNN
F 1 "22pF" H 3810 3020 50  0000 L CNN
F 2 "" H 3800 3100 50  0001 C CNN
F 3 "" H 3800 3100 50  0001 C CNN
	1    3800 3100
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAA108
P 4400 3100
F 0 "C?" H 4410 3170 50  0000 L CNN
F 1 "22pF" H 4410 3020 50  0000 L CNN
F 2 "" H 4400 3100 50  0001 C CNN
F 3 "" H 4400 3100 50  0001 C CNN
	1    4400 3100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAA10F
P 4100 3300
F 0 "#PWR?" H 4100 3050 50  0001 C CNN
F 1 "GND" H 4100 3150 50  0000 C CNN
F 2 "" H 4100 3300 50  0001 C CNN
F 3 "" H 4100 3300 50  0001 C CNN
	1    4100 3300
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5CBAA115
P 4700 2450
F 0 "R?" V 4780 2450 50  0000 C CNN
F 1 "10k" V 4700 2450 50  0000 C CNN
F 2 "" V 4630 2450 50  0001 C CNN
F 3 "" H 4700 2450 50  0001 C CNN
	1    4700 2450
	0    1    1    0   
$EndComp
$Comp
L SW_Push SW?
U 1 1 5CBAA11C
P 3100 2250
F 0 "SW?" H 3150 2350 50  0000 L CNN
F 1 "RESET" H 3100 2190 50  0000 C CNN
F 2 "Buttons_Switches_THT:SW_PUSH_6mm" H 3100 2450 50  0001 C CNN
F 3 "" H 3100 2450 50  0001 C CNN
	1    3100 2250
	-1   0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAA123
P 3350 2400
F 0 "C?" H 3360 2470 50  0000 L CNN
F 1 "100nF" H 3360 2320 50  0000 L CNN
F 2 "" H 3350 2400 50  0001 C CNN
F 3 "" H 3350 2400 50  0001 C CNN
	1    3350 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAA12B
P 2850 2600
F 0 "#PWR?" H 2850 2350 50  0001 C CNN
F 1 "GND" H 2850 2450 50  0000 C CNN
F 2 "" H 2850 2600 50  0001 C CNN
F 3 "" H 2850 2600 50  0001 C CNN
	1    2850 2600
	1    0    0    -1  
$EndComp
Text Label 4750 3700 2    60   ~ 0
TX_TELEMENTRY
NoConn ~ 5000 3600
Text Label 7750 4000 0    60   ~ 0
DSHOT1
Text Label 7750 4100 0    60   ~ 0
DSHOT2
Text Label 7750 4200 0    60   ~ 0
DSHOT3
Text Label 7750 4300 0    60   ~ 0
DSHOT4
Text Label 7750 2300 0    60   ~ 0
DSHOT5
Text Label 7750 2400 0    60   ~ 0
DSHOT6
Text Label 7750 2500 0    60   ~ 0
DSHOT7
Text Label 7750 2600 0    60   ~ 0
DSHOT8
$Comp
L R R?
U 1 1 5CBAA13D
P 3750 4700
F 0 "R?" V 3830 4700 50  0000 C CNN
F 1 "10k" V 3750 4700 50  0000 C CNN
F 2 "" V 3680 4700 50  0001 C CNN
F 3 "" H 3750 4700 50  0001 C CNN
	1    3750 4700
	-1   0    0    1   
$EndComp
$Comp
L R R?
U 1 1 5CBAA144
P 4050 4700
F 0 "R?" V 4130 4700 50  0000 C CNN
F 1 "10k" V 4050 4700 50  0000 C CNN
F 2 "" V 3980 4700 50  0001 C CNN
F 3 "" H 4050 4700 50  0001 C CNN
	1    4050 4700
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAA14B
P 3900 4950
F 0 "#PWR?" H 3900 4700 50  0001 C CNN
F 1 "GND" H 3900 4800 50  0000 C CNN
F 2 "" H 3900 4950 50  0001 C CNN
F 3 "" H 3900 4950 50  0001 C CNN
	1    3900 4950
	1    0    0    -1  
$EndComp
Text Label 4750 3900 2    60   ~ 0
TELEMENTRY_SEL1
Text Label 4750 3800 2    60   ~ 0
TELEMENTRY_SEL0
Text Label 4750 4000 2    60   ~ 0
TELEMENTRY_SEL2
NoConn ~ 5000 3400
NoConn ~ 5000 3500
NoConn ~ 5000 4100
NoConn ~ 5000 4200
NoConn ~ 5000 4600
NoConn ~ 5000 4900
NoConn ~ 7500 1700
NoConn ~ 7500 1800
NoConn ~ 7500 1900
NoConn ~ 7500 2200
NoConn ~ 7500 2700
NoConn ~ 7500 2800
NoConn ~ 7500 2900
NoConn ~ 7500 3000
NoConn ~ 7500 3100
NoConn ~ 7500 3200
NoConn ~ 7500 3400
NoConn ~ 7500 3500
NoConn ~ 7500 3600
NoConn ~ 7500 3700
NoConn ~ 7500 3800
NoConn ~ 7500 3900
NoConn ~ 7500 4400
NoConn ~ 7500 4500
NoConn ~ 7500 4600
NoConn ~ 7500 4700
NoConn ~ 7500 4800
NoConn ~ 7500 4900
NoConn ~ 7500 5100
Connection ~ 6150 1350
Wire Wire Line
	6250 1350 6250 1400
Connection ~ 6100 1350
Wire Wire Line
	6150 1350 6150 1400
Connection ~ 6050 1350
Wire Wire Line
	6050 1350 6050 1400
Wire Wire Line
	5950 1350 5950 1400
Wire Wire Line
	5950 1350 6250 1350
Wire Wire Line
	6100 1200 6100 1350
Connection ~ 6550 1350
Wire Wire Line
	6400 1350 6400 1400
Wire Wire Line
	6550 1350 6400 1350
Wire Wire Line
	6550 1200 6550 1400
Wire Wire Line
	6000 5400 6000 5450
Wire Wire Line
	6000 5450 6300 5450
Wire Wire Line
	6100 5450 6100 5400
Wire Wire Line
	6200 5450 6200 5400
Connection ~ 6100 5450
Wire Wire Line
	6300 5450 6300 5400
Connection ~ 6200 5450
Wire Wire Line
	6150 5500 6150 5450
Connection ~ 6150 5450
Wire Wire Line
	6500 5500 6500 5400
Wire Wire Line
	3950 2900 3800 2900
Wire Wire Line
	3800 2650 3800 3000
Wire Wire Line
	4250 2900 4400 2900
Wire Wire Line
	4400 2750 4400 3000
Wire Wire Line
	4100 3250 4100 3300
Connection ~ 4100 3250
Wire Wire Line
	4400 2750 5000 2750
Connection ~ 4400 2900
Wire Wire Line
	5000 2650 3800 2650
Connection ~ 3800 2900
Wire Wire Line
	3800 3200 3800 3250
Wire Wire Line
	3800 3250 4400 3250
Wire Wire Line
	4400 3250 4400 3200
Wire Wire Line
	4850 2450 5000 2450
Wire Wire Line
	3650 2450 4550 2450
Wire Wire Line
	3300 2250 5000 2250
Wire Wire Line
	2900 2250 2850 2250
Wire Wire Line
	2850 2250 2850 2600
Wire Wire Line
	3350 2300 3350 2250
Connection ~ 3350 2250
Wire Wire Line
	3350 2500 3350 2550
Wire Wire Line
	3350 2550 2850 2550
Connection ~ 2850 2550
Wire Wire Line
	1350 4300 5000 4300
Wire Wire Line
	1350 4400 5000 4400
Wire Wire Line
	4750 3700 5000 3700
Wire Wire Line
	7500 4000 7750 4000
Wire Wire Line
	7750 4300 7500 4300
Wire Wire Line
	7500 4200 7750 4200
Wire Wire Line
	7750 4100 7500 4100
Wire Wire Line
	7750 2300 7500 2300
Wire Wire Line
	7750 2400 7500 2400
Wire Wire Line
	7500 2500 7750 2500
Wire Wire Line
	7750 2600 7500 2600
Wire Wire Line
	4050 4550 4050 4500
Wire Wire Line
	3750 4500 3750 4550
Wire Wire Line
	3750 4850 3750 4900
Wire Wire Line
	3750 4900 4050 4900
Wire Wire Line
	3900 4900 3900 4950
Wire Wire Line
	4050 4900 4050 4850
Connection ~ 3900 4900
Wire Wire Line
	5000 3800 4750 3800
Wire Wire Line
	4750 3900 5000 3900
Wire Wire Line
	5000 4000 4750 4000
Wire Wire Line
	4300 4700 5000 4700
Wire Wire Line
	4400 4800 5000 4800
Wire Wire Line
	3750 4500 5000 4500
Connection ~ 4050 4500
NoConn ~ 7500 2100
$Comp
L Conn_01x03 J?
U 1 1 5CBAC8B8
P 1200 1950
F 0 "J?" H 1200 2150 50  0000 C CNN
F 1 "MCU_PWR_SRC" H 1200 1750 50  0000 C CNN
F 2 "" H 1200 1950 50  0001 C CNN
F 3 "" H 1200 1950 50  0001 C CNN
	1    1200 1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1600 2050 1400 2050
Wire Wire Line
	1500 1850 1400 1850
Wire Wire Line
	1500 1000 1500 1850
$Comp
L Jumper_NO_Small JP?
U 1 1 5CBACE06
P 1750 2850
F 0 "JP?" H 1750 2930 50  0000 C CNN
F 1 "BOOT_MODE" H 1760 2790 50  0000 C CNN
F 2 "" H 1750 2850 50  0001 C CNN
F 3 "" H 1750 2850 50  0001 C CNN
	1    1750 2850
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBACE0D
P 1750 3600
F 0 "#PWR?" H 1750 3350 50  0001 C CNN
F 1 "GND" H 1750 3450 50  0000 C CNN
F 2 "" H 1750 3600 50  0001 C CNN
F 3 "" H 1750 3600 50  0001 C CNN
	1    1750 3600
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 5CBACE13
P 1750 3400
F 0 "R?" V 1830 3400 50  0000 C CNN
F 1 "10k" V 1750 3400 50  0000 C CNN
F 2 "" V 1680 3400 50  0001 C CNN
F 3 "" H 1750 3400 50  0001 C CNN
	1    1750 3400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1750 2950 1750 3250
Wire Wire Line
	1750 3550 1750 3600
Wire Wire Line
	3650 3150 1750 3150
Connection ~ 1750 3150
Wire Wire Line
	1750 2550 1750 2750
$Comp
L Conn_01x02 J?
U 1 1 5CBAD84F
P 10700 6150
F 0 "J?" H 10700 6250 50  0000 C CNN
F 1 "JUMPER_PARK" H 10700 5950 50  0000 C CNN
F 2 "" H 10700 6150 50  0001 C CNN
F 3 "" H 10700 6150 50  0001 C CNN
	1    10700 6150
	1    0    0    -1  
$EndComp
NoConn ~ 10500 6150
NoConn ~ 10500 6250
$Comp
L C_Small C?
U 1 1 5CBAE57F
P 850 7000
F 0 "C?" H 860 7070 50  0000 L CNN
F 1 "100nF" H 860 6920 50  0000 L CNN
F 2 "" H 850 7000 50  0001 C CNN
F 3 "" H 850 7000 50  0001 C CNN
	1    850  7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE586
P 1450 7000
F 0 "C?" H 1460 7070 50  0000 L CNN
F 1 "100nF" H 1460 6920 50  0000 L CNN
F 2 "" H 1450 7000 50  0001 C CNN
F 3 "" H 1450 7000 50  0001 C CNN
	1    1450 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE58D
P 1750 7000
F 0 "C?" H 1760 7070 50  0000 L CNN
F 1 "100nF" H 1760 6920 50  0000 L CNN
F 2 "" H 1750 7000 50  0001 C CNN
F 3 "" H 1750 7000 50  0001 C CNN
	1    1750 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE594
P 2650 7000
F 0 "C?" H 2660 7070 50  0000 L CNN
F 1 "100nF" H 2660 6920 50  0000 L CNN
F 2 "" H 2650 7000 50  0001 C CNN
F 3 "" H 2650 7000 50  0001 C CNN
	1    2650 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE59B
P 3250 7000
F 0 "C?" H 3260 7070 50  0000 L CNN
F 1 "100nF" H 3260 6920 50  0000 L CNN
F 2 "" H 3250 7000 50  0001 C CNN
F 3 "" H 3250 7000 50  0001 C CNN
	1    3250 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5A2
P 2950 7000
F 0 "C?" H 2960 7070 50  0000 L CNN
F 1 "100nF" H 2960 6920 50  0000 L CNN
F 2 "" H 2950 7000 50  0001 C CNN
F 3 "" H 2950 7000 50  0001 C CNN
	1    2950 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5A9
P 2050 7000
F 0 "C?" H 2060 7070 50  0000 L CNN
F 1 "100nF" H 2060 6920 50  0000 L CNN
F 2 "" H 2050 7000 50  0001 C CNN
F 3 "" H 2050 7000 50  0001 C CNN
	1    2050 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5B0
P 1150 7000
F 0 "C?" H 1160 7070 50  0000 L CNN
F 1 "100nF" H 1160 6920 50  0000 L CNN
F 2 "" H 1150 7000 50  0001 C CNN
F 3 "" H 1150 7000 50  0001 C CNN
	1    1150 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5B7
P 2350 7000
F 0 "C?" H 2360 7070 50  0000 L CNN
F 1 "100nF" H 2360 6920 50  0000 L CNN
F 2 "" H 2350 7000 50  0001 C CNN
F 3 "" H 2350 7000 50  0001 C CNN
	1    2350 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5BE
P 3550 7000
F 0 "C?" H 3560 7070 50  0000 L CNN
F 1 "100nF" H 3560 6920 50  0000 L CNN
F 2 "" H 3550 7000 50  0001 C CNN
F 3 "" H 3550 7000 50  0001 C CNN
	1    3550 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5C5
P 3850 7000
F 0 "C?" H 3860 7070 50  0000 L CNN
F 1 "100nF" H 3860 6920 50  0000 L CNN
F 2 "" H 3850 7000 50  0001 C CNN
F 3 "" H 3850 7000 50  0001 C CNN
	1    3850 7000
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAE5CC
P 4150 7000
F 0 "C?" H 4160 7070 50  0000 L CNN
F 1 "4.7uF" H 4160 6920 50  0000 L CNN
F 2 "" H 4150 7000 50  0001 C CNN
F 3 "" H 4150 7000 50  0001 C CNN
	1    4150 7000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAE5D9
P 2500 7250
F 0 "#PWR?" H 2500 7000 50  0001 C CNN
F 1 "GND" H 2500 7100 50  0000 C CNN
F 2 "" H 2500 7250 50  0001 C CNN
F 3 "" H 2500 7250 50  0001 C CNN
	1    2500 7250
	1    0    0    -1  
$EndComp
Connection ~ 3850 7150
Wire Wire Line
	4150 7150 4150 7100
Connection ~ 3550 7150
Wire Wire Line
	3850 7150 3850 7100
Wire Wire Line
	2500 7150 2500 7250
Connection ~ 3250 7150
Wire Wire Line
	3550 7150 3550 7100
Connection ~ 2950 7150
Wire Wire Line
	3250 7150 3250 7100
Connection ~ 2650 7150
Wire Wire Line
	2950 7150 2950 7100
Connection ~ 2050 7150
Connection ~ 2350 7150
Connection ~ 1750 7150
Wire Wire Line
	2050 7150 2050 7100
Connection ~ 1450 7150
Wire Wire Line
	1750 7150 1750 7100
Wire Wire Line
	850  7100 850  7150
Connection ~ 2500 7150
Wire Wire Line
	2650 7150 2650 7100
Wire Wire Line
	2350 7150 2350 7100
Wire Wire Line
	850  6850 850  6900
Connection ~ 2500 6850
Wire Wire Line
	2500 6650 2500 6850
Connection ~ 1150 7150
Wire Wire Line
	1450 7150 1450 7100
Wire Wire Line
	1150 7150 1150 7100
Wire Wire Line
	850  7150 4150 7150
Connection ~ 3850 6850
Wire Wire Line
	4150 6850 4150 6900
Connection ~ 3500 6850
Wire Wire Line
	3850 6850 3850 6900
Wire Wire Line
	3500 6850 4150 6850
Connection ~ 3250 6850
Wire Wire Line
	3550 6850 3550 6900
Connection ~ 2950 6850
Wire Wire Line
	3250 6850 3250 6900
Connection ~ 2650 6850
Wire Wire Line
	2950 6850 2950 6900
Connection ~ 2350 6850
Wire Wire Line
	2650 6850 2650 6900
Connection ~ 2050 6850
Wire Wire Line
	2350 6850 2350 6900
Connection ~ 1750 6850
Wire Wire Line
	2050 6850 2050 6900
Connection ~ 1450 6850
Wire Wire Line
	1750 6850 1750 6900
Connection ~ 1150 6850
Wire Wire Line
	1450 6850 1450 6900
Wire Wire Line
	1150 6850 1150 6900
Wire Wire Line
	850  6850 3550 6850
$Comp
L C_Small C?
U 1 1 5CBAEF66
P 5950 7050
F 0 "C?" H 5960 7120 50  0000 L CNN
F 1 "1uF" H 5960 6970 50  0000 L CNN
F 2 "" H 5950 7050 50  0001 C CNN
F 3 "" H 5950 7050 50  0001 C CNN
	1    5950 7050
	1    0    0    -1  
$EndComp
$Comp
L C_Small C?
U 1 1 5CBAEF6D
P 5700 7050
F 0 "C?" H 5710 7120 50  0000 L CNN
F 1 "10nF" H 5710 6970 50  0000 L CNN
F 2 "" H 5700 7050 50  0001 C CNN
F 3 "" H 5700 7050 50  0001 C CNN
	1    5700 7050
	1    0    0    -1  
$EndComp
$Comp
L Ferrite_Bead_Small L?
U 1 1 5CBAEF7A
P 5500 6850
F 0 "L?" H 5575 6900 50  0000 L CNN
F 1 "Ferrite_Bead_Small" H 5575 6800 50  0000 L CNN
F 2 "" V 5430 6850 50  0001 C CNN
F 3 "" H 5500 6850 50  0001 C CNN
	1    5500 6850
	0    -1   -1   0   
$EndComp
$Comp
L GNDA #PWR?
U 1 1 5CBAEF87
P 5950 7300
F 0 "#PWR?" H 5950 7050 50  0001 C CNN
F 1 "GNDA" H 5950 7150 50  0000 C CNN
F 2 "" H 5950 7300 50  0001 C CNN
F 3 "" H 5950 7300 50  0001 C CNN
	1    5950 7300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5CBAEF8D
P 7300 5950
F 0 "#PWR?" H 7300 5700 50  0001 C CNN
F 1 "GND" H 7300 5800 50  0000 C CNN
F 2 "" H 7300 5950 50  0001 C CNN
F 3 "" H 7300 5950 50  0001 C CNN
	1    7300 5950
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR?
U 1 1 5CBAEF93
P 7650 5950
F 0 "#PWR?" H 7650 5700 50  0001 C CNN
F 1 "GNDA" H 7650 5800 50  0000 C CNN
F 2 "" H 7650 5950 50  0001 C CNN
F 3 "" H 7650 5950 50  0001 C CNN
	1    7650 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 6650 5950 6950
Wire Wire Line
	5600 6850 5950 6850
Connection ~ 5950 6850
Connection ~ 5950 7250
Wire Wire Line
	5950 7150 5950 7300
Wire Wire Line
	5700 7250 5950 7250
Wire Wire Line
	5700 7150 5700 7250
Connection ~ 5700 6850
Wire Wire Line
	5700 6850 5700 6950
Wire Wire Line
	5300 6850 5400 6850
Wire Wire Line
	5300 6650 5300 6850
Wire Wire Line
	7300 5950 7300 5850
Wire Wire Line
	7300 5850 7650 5850
Wire Wire Line
	7650 5850 7650 5950
Text HLabel 1350 1000 0    60   Input ~ 0
+3V3_USB
Text HLabel 1350 1150 0    60   Input ~ 0
+3V3_SWD
Wire Wire Line
	1350 1000 1500 1000
Wire Wire Line
	1600 1150 1600 2050
Wire Wire Line
	1600 1150 1350 1150
Wire Wire Line
	1850 1950 1400 1950
Text Label 1850 1950 0    60   ~ 12
+3V3_CONTROLLER
Text Label 2500 6650 0    60   ~ 12
+3V3_CONTROLLER
Text Label 5300 6650 2    60   ~ 12
+3V3_CONTROLLER
Text Label 1750 2550 2    60   ~ 12
+3V3_CONTROLLER
Text Label 6100 1200 2    60   ~ 12
+3V3_CONTROLLER
Wire Wire Line
	3650 2450 3650 3150
Text HLabel 1350 1400 0    60   BiDi ~ 0
~RST
Wire Wire Line
	4400 1400 4400 2250
Connection ~ 4400 2250
Text Label 5950 6650 0    60   ~ 12
+3V3_ANALOG
Text Label 6550 1200 0    60   ~ 12
+3V3_ANALOG
Text HLabel 1350 4300 0    60   Output ~ 0
TX
Text HLabel 1350 4400 0    60   Input ~ 0
RX
Text HLabel 1350 4700 0    60   BiDi ~ 0
TMS_SWDIO
Text HLabel 1350 4800 0    60   Input ~ 0
TCK_SWCLK
Wire Wire Line
	1350 4700 3450 4700
Wire Wire Line
	3450 5250 4300 5250
Wire Wire Line
	4300 5250 4300 4700
Wire Wire Line
	4400 4800 4400 5350
Wire Wire Line
	4400 5350 3350 5350
Wire Wire Line
	3350 4800 1350 4800
Wire Wire Line
	3450 4700 3450 5250
Wire Wire Line
	3350 5350 3350 4800
Text HLabel 8500 2000 2    60   BiDi ~ 0
TDO_SWO
Wire Wire Line
	8500 2000 7500 2000
Wire Wire Line
	1350 1400 4400 1400
Text Label 2800 3150 0    60   ~ 12
BOOT0
$EndSCHEMATC