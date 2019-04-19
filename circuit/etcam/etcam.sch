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
Sheet 1 6
Title "Embedded_thruster_Control_And_Monitor_system"
Date "2019-04-19"
Rev "0.90"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L USB_OTG J2
U 1 1 5CB65AE5
P 1350 1300
F 0 "J2" H 1150 1750 50  0000 L CNN
F 1 "USB_connector" H 1150 1650 50  0000 L CNN
F 2 "Connectors:USB_Mini-B" H 1500 1250 50  0001 C CNN
F 3 "" H 1500 1250 50  0001 C CNN
	1    1350 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5CB68809
P 1250 1900
F 0 "#PWR01" H 1250 1650 50  0001 C CNN
F 1 "GND" H 1250 1750 50  0000 C CNN
F 2 "" H 1250 1900 50  0001 C CNN
F 3 "" H 1250 1900 50  0001 C CNN
	1    1250 1900
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 5CB7C656
P 1950 1600
F 0 "C1" H 1960 1670 50  0000 L CNN
F 1 "0.01uF" H 1960 1520 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1950 1600 50  0001 C CNN
F 3 "" H 1950 1600 50  0001 C CNN
	1    1950 1600
	1    0    0    -1  
$EndComp
$Sheet
S 2950 1000 1100 500 
U 5CB9D4CB
F0 "usb_to_serial" 60
F1 "usb_to_serial.sch" 60
F2 "TX" O R 4050 1100 60 
F3 "RX" I R 4050 1200 60 
F4 "DP" B L 2950 1300 60 
F5 "DM" B L 2950 1400 60 
F6 "+5V_USB" I L 2950 1100 60 
$EndSheet
$Comp
L Conn_01x06 J1
U 1 1 5CBB4E7B
P 1150 5200
F 0 "J1" H 1150 5500 50  0000 C CNN
F 1 "SWD_connector" H 1150 4800 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x06_Pitch2.54mm" H 1150 5200 50  0001 C CNN
F 3 "" H 1150 5200 50  0001 C CNN
	1    1150 5200
	-1   0    0    -1  
$EndComp
Text Label 1600 5000 0    60   ~ 12
+3.3V_SWD
$Comp
L GND #PWR02
U 1 1 5CBB4E85
P 1450 5650
F 0 "#PWR02" H 1450 5400 50  0001 C CNN
F 1 "GND" H 1450 5500 50  0000 C CNN
F 2 "" H 1450 5650 50  0001 C CNN
F 3 "" H 1450 5650 50  0001 C CNN
	1    1450 5650
	1    0    0    -1  
$EndComp
Text Label 1600 5300 0    60   ~ 12
TMS_SWDIO
Text Label 1600 5500 0    60   ~ 12
TDO_SWO
Text Label 1600 5400 0    60   ~ 12
~RST
Text Label 1600 5100 0    60   ~ 12
TMS_SWCLK
Text Label 4200 1100 0    60   ~ 12
FTDI-->MCU
Text Label 4200 1200 0    60   ~ 12
FTDI<--MCU
Text Label 2150 850  0    60   ~ 12
+5V_USB
$Comp
L GND #PWR03
U 1 1 5CB880E3
P 6600 7050
F 0 "#PWR03" H 6600 6800 50  0001 C CNN
F 1 "GND" H 6600 6900 50  0000 C CNN
F 2 "" H 6600 7050 50  0001 C CNN
F 3 "" H 6600 7050 50  0001 C CNN
	1    6600 7050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG04
U 1 1 5CB880E4
P 6600 6800
F 0 "#FLG04" H 6600 6875 50  0001 C CNN
F 1 "PWR_FLAG" H 6600 6950 50  0000 C CNN
F 2 "" H 6600 6800 50  0001 C CNN
F 3 "" H 6600 6800 50  0001 C CNN
	1    6600 6800
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x08 J4
U 1 1 5CB880E9
P 5150 6850
F 0 "J4" H 5150 7250 50  0000 C CNN
F 1 "ESC_GND_connector" H 5150 6350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 5150 6850 50  0001 C CNN
F 3 "" H 5150 6850 50  0001 C CNN
	1    5150 6850
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x08_Odd_Even J3
U 1 1 5CB880EA
P 2250 6900
F 0 "J3" H 2300 7300 50  0000 C CNN
F 1 "ESC_signal_connector" H 2300 6400 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x08_Pitch2.54mm" H 2250 6900 50  0001 C CNN
F 3 "" H 2250 6900 50  0001 C CNN
	1    2250 6900
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR05
U 1 1 5CB880EB
P 4650 7350
F 0 "#PWR05" H 4650 7150 50  0001 C CNN
F 1 "GNDPWR" H 4650 7220 50  0000 C CNN
F 2 "" H 4650 7300 50  0001 C CNN
F 3 "" H 4650 7300 50  0001 C CNN
	1    4650 7350
	-1   0    0    -1  
$EndComp
Text Label 1850 6600 2    60   ~ 12
ISOLATED_DSHOT1
$Comp
L CP_Small C2
U 1 1 5CB880FA
P 4300 2700
F 0 "C2" H 4310 2770 50  0000 L CNN
F 1 "1uF" H 4310 2620 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 4300 2700 50  0001 C CNN
F 3 "" H 4300 2700 50  0001 C CNN
	1    4300 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 5CB880FD
P 4300 2850
F 0 "#PWR06" H 4300 2600 50  0001 C CNN
F 1 "GND" H 4300 2700 50  0000 C CNN
F 2 "" H 4300 2850 50  0001 C CNN
F 3 "" H 4300 2850 50  0001 C CNN
	1    4300 2850
	1    0    0    -1  
$EndComp
$Sheet
S 7100 3100 2000 2100
U 5CB95D60
F0 "isolation_barrier" 60
F1 "isolation_barrier.sch" 60
F2 "ISOLATDE_TELEMENTRY1" I R 9100 3500 60 
F3 "ISOLATDE_TELEMENTRY2" I R 9100 3600 60 
F4 "ISOLATDE_TELEMENTRY3" I R 9100 3700 60 
F5 "ISOLATDE_TELEMENTRY4" I R 9100 3800 60 
F6 "ISOLATDE_TELEMENTRY5" I R 9100 3900 60 
F7 "ISOLATDE_TELEMENTRY6" I R 9100 4000 60 
F8 "ISOLATDE_TELEMENTRY8" I R 9100 4200 60 
F9 "ISOLATED_DSHOT1" O R 9100 4400 60 
F10 "ISOLATED_DSHOT2" O R 9100 4500 60 
F11 "ISOLATED_DSHOT3" O R 9100 4600 60 
F12 "ISOLATED_DSHOT4" O R 9100 4700 60 
F13 "ISOLATED_DSHOT5" O R 9100 4800 60 
F14 "ISOLATED_DSHOT6" O R 9100 4900 60 
F15 "ISOLATED_DSHOT7" O R 9100 5000 60 
F16 "ISOLATED_DSHOT8" O R 9100 5100 60 
F17 "DSHOT1" I L 7100 4400 60 
F18 "DSHOT2" I L 7100 4500 60 
F19 "DSHOT3" I L 7100 4600 60 
F20 "DSHOT4" I L 7100 4700 60 
F21 "DSHOT5" I L 7100 4800 60 
F22 "DSHOT6" I L 7100 4900 60 
F23 "DSHOT7" I L 7100 5000 60 
F24 "DSHOT8" I L 7100 5100 60 
F25 "TELEMENTRY1" O L 7100 3500 60 
F26 "TELEMENTRY2" O L 7100 3600 60 
F27 "TELEMENTRY3" O L 7100 3700 60 
F28 "TELEMENTRY4" O L 7100 3800 60 
F29 "TELEMENTRY5" O L 7100 3900 60 
F30 "TELEMENTRY6" O L 7100 4000 60 
F31 "TELEMENTRY7" O L 7100 4100 60 
F32 "TELEMENTRY8" O L 7100 4200 60 
F33 "+3.3V_ISOLATOR" I L 7100 3300 60 
F34 "+3.3V_USB" I L 7100 3200 60 
F35 "ISOLATDE_TELEMENTRY7" I R 9100 4100 60 
$EndSheet
$Sheet
S 4800 3100 1950 1200
U 5CBC5EBB
F0 "telementry_selector" 60
F1 "telementry_selector.sch" 60
F2 "+3.3V_USB" I L 4800 3200 60 
F3 "TELEMENTRY1" I R 6750 3500 60 
F4 "TELEMENTRY2" I R 6750 3600 60 
F5 "TELEMENTRY3" I R 6750 3700 60 
F6 "TELEMENTRY4" I R 6750 3800 60 
F7 "TELEMENTRY5" I R 6750 3900 60 
F8 "TELEMENTRY6" I R 6750 4000 60 
F9 "TELEMENTRY7" I R 6750 4100 60 
F10 "TELEMENTRY8" I R 6750 4200 60 
F11 "TELEMENTRY_SEL0" I L 4800 3850 60 
F12 "TELEMENTRY_SEL1" I L 4800 3950 60 
F13 "TELEMENTRY_SEL2" I L 4800 4050 60 
F14 "SELECTED_TELEMENTRY" O L 4800 3550 60 
$EndSheet
$Sheet
S 2750 3100 1650 2100
U 5CBA9AB7
F0 "controller" 60
F1 "controller.sch" 60
F2 "~RST" B L 2750 3500 60 
F3 "TX" O L 2750 3800 60 
F4 "RX" I L 2750 3700 60 
F5 "TMS_SWDIO" B L 2750 4100 60 
F6 "TCK_SWCLK" I L 2750 4000 60 
F7 "TDO_SWO" B L 2750 4200 60 
F8 "TX_TELEMENTRY" I R 4400 3700 60 
F9 "TELEMENTRY_SEL0" O R 4400 4000 60 
F10 "TELEMENTRY_SEL1" O R 4400 4100 60 
F11 "TELEMENTRY_SEL2" O R 4400 4200 60 
F12 "DSHOT6" O R 4400 4900 60 
F13 "DSHOT7" O R 4400 5000 60 
F14 "DSHOT8" O R 4400 5100 60 
F15 "DSHOT5" O R 4400 4800 60 
F16 "DSHOT1" O R 4400 4400 60 
F17 "DSHOT2" O R 4400 4500 60 
F18 "DSHOT3" O R 4400 4600 60 
F19 "DSHOT4" O R 4400 4700 60 
F20 "+3.3V_USB" I L 2750 3200 60 
F21 "+3.3V_SWD" I L 2750 3300 60 
$EndSheet
Text Label 1850 6700 2    60   ~ 12
ISOLATED_DSHOT2
Text Label 1850 6800 2    60   ~ 12
ISOLATED_DSHOT3
Text Label 1850 6900 2    60   ~ 12
ISOLATED_DSHOT4
Text Label 1850 7000 2    60   ~ 12
ISOLATED_DSHOT5
Text Label 1850 7100 2    60   ~ 12
ISOLATED_DSHOT6
Text Label 1850 7200 2    60   ~ 12
ISOLATED_DSHOT7
Text Label 1850 7300 2    60   ~ 12
ISOLATED_DSHOT8
Text Label 2750 6600 0    60   ~ 12
ISOLATED_TELEMENTRY1
Text Label 2750 6700 0    60   ~ 12
ISOLATED_TELEMENTRY2
Text Label 2750 6800 0    60   ~ 12
ISOLATED_TELEMENTRY3
Text Label 2750 6900 0    60   ~ 12
ISOLATED_TELEMENTRY4
Text Label 2750 7000 0    60   ~ 12
ISOLATED_TELEMENTRY5
Text Label 2750 7100 0    60   ~ 12
ISOLATED_TELEMENTRY6
Text Label 2750 7200 0    60   ~ 12
ISOLATED_TELEMENTRY7
Text Label 2750 7300 0    60   ~ 12
ISOLATED_TELEMENTRY8
Text Label 9700 3500 0    60   ~ 12
ISOLATED_TELEMENTRY1
Text Label 9700 3600 0    60   ~ 12
ISOLATED_TELEMENTRY2
Text Label 9700 3700 0    60   ~ 12
ISOLATED_TELEMENTRY3
Text Label 9700 3800 0    60   ~ 12
ISOLATED_TELEMENTRY4
Text Label 9700 3900 0    60   ~ 12
ISOLATED_TELEMENTRY5
Text Label 9700 4000 0    60   ~ 12
ISOLATED_TELEMENTRY6
Text Label 9700 4100 0    60   ~ 12
ISOLATED_TELEMENTRY7
Text Label 9700 4200 0    60   ~ 12
ISOLATED_TELEMENTRY8
Text Label 9700 4400 0    60   ~ 12
ISOLATED_DSHOT1
Text Label 9700 4500 0    60   ~ 12
ISOLATED_DSHOT2
Text Label 9700 4600 0    60   ~ 12
ISOLATED_DSHOT3
Text Label 9700 4700 0    60   ~ 12
ISOLATED_DSHOT4
Text Label 9700 4800 0    60   ~ 12
ISOLATED_DSHOT5
Text Label 9700 4900 0    60   ~ 12
ISOLATED_DSHOT6
Text Label 9700 5000 0    60   ~ 12
ISOLATED_DSHOT7
Text Label 9700 5100 0    60   ~ 12
ISOLATED_DSHOT8
$Sheet
S 6350 950  1500 700 
U 5CC65A6A
F0 "dc_dc_converter" 60
F1 "dc_dc_converter.sch" 60
F2 "+5V_USB" I L 6350 1300 60 
F3 "+3.3V_USB" O R 7850 1250 60 
F4 "+3.3V_ISOLATOR" O R 7850 1350 60 
$EndSheet
Text Label 6000 1300 2    60   ~ 12
+5V_USB
Text Label 8200 1250 0    60   ~ 12
+3.3V_USB
Text Label 8200 1350 0    60   ~ 12
+3.3V_ISOLATOR
Text Label 1800 3200 2    60   ~ 12
+3.3V_USB
Text Label 1800 3300 2    60   ~ 12
+3.3V_SWD
Text Label 4000 2500 2    60   ~ 12
+3.3V_USB
Connection ~ 1250 1800
Connection ~ 1350 1800
Wire Wire Line
	1250 1700 1250 1900
Wire Wire Line
	1350 1800 1350 1700
Wire Wire Line
	1250 1800 1950 1800
Wire Wire Line
	1950 1100 1950 1500
Wire Wire Line
	1950 1800 1950 1700
Connection ~ 1950 1100
Wire Wire Line
	1650 1300 2950 1300
Wire Wire Line
	1650 1400 2950 1400
Wire Wire Line
	1650 1100 2950 1100
Wire Wire Line
	1350 5200 1450 5200
Wire Wire Line
	1450 5200 1450 5650
Wire Wire Line
	1800 4000 2750 4000
Wire Wire Line
	1800 4200 2750 4200
Wire Wire Line
	1800 4100 2750 4100
Wire Wire Line
	6600 6800 6600 7050
Wire Wire Line
	4650 7250 4950 7250
Wire Wire Line
	4650 6550 4650 7350
Wire Wire Line
	4650 7150 4950 7150
Connection ~ 4650 7250
Wire Wire Line
	4650 7050 4950 7050
Connection ~ 4650 7150
Wire Wire Line
	4650 6950 4950 6950
Connection ~ 4650 7050
Wire Wire Line
	4650 6850 4950 6850
Connection ~ 4650 6950
Wire Wire Line
	4650 6750 4950 6750
Connection ~ 4650 6850
Wire Wire Line
	4650 6650 4950 6650
Connection ~ 4650 6750
Wire Wire Line
	4650 6550 4950 6550
Connection ~ 4650 6650
Wire Wire Line
	1850 6600 2050 6600
Wire Wire Line
	1850 6700 2050 6700
Wire Wire Line
	1850 6800 2050 6800
Wire Wire Line
	1850 6900 2050 6900
Wire Wire Line
	1850 7300 2050 7300
Wire Wire Line
	1850 7200 2050 7200
Wire Wire Line
	1850 7100 2050 7100
Wire Wire Line
	1850 7000 2050 7000
Wire Wire Line
	2550 6600 2750 6600
Wire Wire Line
	2550 6700 2750 6700
Wire Wire Line
	2550 6800 2750 6800
Wire Wire Line
	2550 6900 2750 6900
Wire Wire Line
	2550 7300 2750 7300
Wire Wire Line
	2550 7200 2750 7200
Wire Wire Line
	2550 7100 2750 7100
Wire Wire Line
	2550 7000 2750 7000
Wire Wire Line
	4300 2800 4300 2850
Wire Wire Line
	4400 4400 7100 4400
Wire Wire Line
	4400 4500 7100 4500
Wire Wire Line
	4400 4600 7100 4600
Wire Wire Line
	4400 4700 7100 4700
Wire Wire Line
	4400 4800 7100 4800
Wire Wire Line
	4400 4900 7100 4900
Wire Wire Line
	4400 5000 7100 5000
Wire Wire Line
	4400 5100 7100 5100
Wire Wire Line
	4400 3700 4600 3700
Wire Wire Line
	4600 3700 4600 3550
Wire Wire Line
	4600 3550 4800 3550
Wire Wire Line
	4800 3850 4550 3850
Wire Wire Line
	4550 3850 4550 4000
Wire Wire Line
	4550 4000 4400 4000
Wire Wire Line
	4400 4100 4600 4100
Wire Wire Line
	4600 4100 4600 3950
Wire Wire Line
	4600 3950 4800 3950
Wire Wire Line
	4800 4050 4650 4050
Wire Wire Line
	4650 4050 4650 4200
Wire Wire Line
	4650 4200 4400 4200
Wire Wire Line
	6750 3500 7100 3500
Wire Wire Line
	6750 3600 7100 3600
Wire Wire Line
	6750 3700 7100 3700
Wire Wire Line
	6750 3800 7100 3800
Wire Wire Line
	6750 3900 7100 3900
Wire Wire Line
	6750 4000 7100 4000
Wire Wire Line
	6750 4100 7100 4100
Wire Wire Line
	6750 4200 7100 4200
Wire Wire Line
	4600 3200 4800 3200
Wire Wire Line
	6900 3300 7100 3300
Wire Wire Line
	7100 3200 6950 3200
Wire Wire Line
	2150 850  2150 1100
Connection ~ 2150 1100
Wire Wire Line
	4050 1200 4900 1200
Wire Wire Line
	2100 3800 2750 3800
Wire Wire Line
	4050 1100 5000 1100
Wire Wire Line
	2200 3700 2750 3700
Wire Wire Line
	6000 1300 6350 1300
Wire Wire Line
	7850 1250 8200 1250
Wire Wire Line
	8200 1350 7850 1350
Wire Wire Line
	1800 3200 2750 3200
Wire Wire Line
	1350 5000 1600 5000
Wire Wire Line
	1600 5100 1350 5100
Wire Wire Line
	1350 5300 1600 5300
Wire Wire Line
	1600 5400 1350 5400
Wire Wire Line
	1350 5500 1600 5500
Wire Wire Line
	1800 3300 2750 3300
Wire Wire Line
	4600 2500 4600 3200
Wire Wire Line
	6950 3200 6950 2500
Text Label 6750 2400 2    60   ~ 12
+3.3V_ISOLATOR
Wire Wire Line
	4300 2600 4300 2500
Connection ~ 4600 2500
Connection ~ 4300 2500
Wire Wire Line
	6950 2500 4000 2500
Wire Wire Line
	4900 1200 4900 2050
Wire Wire Line
	5000 1100 5000 2150
Wire Wire Line
	5000 2150 2200 2150
Wire Wire Line
	4900 2050 2100 2050
Wire Wire Line
	2200 2150 2200 3700
Wire Wire Line
	2100 2050 2100 3800
Wire Wire Line
	6900 2400 6900 3300
Wire Wire Line
	6750 2400 6900 2400
Text Label 1800 4000 2    60   ~ 12
TMS_SWCLK
Text Label 1800 3500 2    60   ~ 12
~RST
Wire Wire Line
	1800 3500 2750 3500
Text Label 1800 4200 2    60   ~ 12
TDO_SWO
Text Label 1800 4100 2    60   ~ 12
TMS_SWDIO
Wire Wire Line
	9100 3500 9700 3500
Wire Wire Line
	9700 3600 9100 3600
Wire Wire Line
	9100 3700 9700 3700
Wire Wire Line
	9700 3800 9100 3800
Wire Wire Line
	9100 3900 9700 3900
Wire Wire Line
	9700 4000 9100 4000
Wire Wire Line
	9100 4100 9700 4100
Wire Wire Line
	9700 4200 9100 4200
Wire Wire Line
	9100 4400 9700 4400
Wire Wire Line
	9700 4500 9100 4500
Wire Wire Line
	9100 4600 9700 4600
Wire Wire Line
	9700 4700 9100 4700
Wire Wire Line
	9100 4800 9700 4800
Wire Wire Line
	9700 4900 9100 4900
Wire Wire Line
	9100 5000 9700 5000
Wire Wire Line
	9700 5100 9100 5100
NoConn ~ 1650 1500
Text Label 6150 6700 2    60   ~ 12
+5V_USB
$Comp
L PWR_FLAG #FLG07
U 1 1 5CBC4CAA
P 6150 7050
F 0 "#FLG07" H 6150 7125 50  0001 C CNN
F 1 "PWR_FLAG" H 6150 7200 50  0000 C CNN
F 2 "" H 6150 7050 50  0001 C CNN
F 3 "" H 6150 7050 50  0001 C CNN
	1    6150 7050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6150 6700 6150 7050
$EndSCHEMATC
