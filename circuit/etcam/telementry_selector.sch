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
Sheet 4 6
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
L 74HC251 U6
U 1 1 5CBC62FC
P 6000 3800
F 0 "U6" H 6000 3800 50  0000 C CNN
F 1 "74HC251" H 6000 3650 50  0000 C CNN
F 2 "Housings_SOIC:SOIC-16_3.9x9.9mm_Pitch1.27mm" H 6000 3800 50  0001 C CNN
F 3 "" H 6000 3800 50  0001 C CNN
	1    6000 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 5CBC6303
P 6000 4750
F 0 "#PWR029" H 6000 4500 50  0001 C CNN
F 1 "GND" H 6000 4600 50  0000 C CNN
F 2 "" H 6000 4750 50  0001 C CNN
F 3 "" H 6000 4750 50  0001 C CNN
	1    6000 4750
	1    0    0    -1  
$EndComp
NoConn ~ 6550 3400
$Comp
L C_Small C15
U 1 1 5CBC630A
P 6650 2850
F 0 "C15" H 6660 2920 50  0000 L CNN
F 1 "0.1uF" H 6660 2770 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6650 2850 50  0001 C CNN
F 3 "" H 6650 2850 50  0001 C CNN
	1    6650 2850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR030
U 1 1 5CBC6311
P 6650 3000
F 0 "#PWR030" H 6650 2750 50  0001 C CNN
F 1 "GND" H 6650 2850 50  0000 C CNN
F 2 "" H 6650 3000 50  0001 C CNN
F 3 "" H 6650 3000 50  0001 C CNN
	1    6650 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4650 6000 4750
Wire Wire Line
	6000 4700 5350 4700
Wire Wire Line
	5350 4700 5350 4450
Wire Wire Line
	5350 4450 5450 4450
Connection ~ 6000 4700
Wire Wire Line
	6650 2700 6650 2750
Wire Wire Line
	6650 2950 6650 3000
Wire Wire Line
	4900 2700 6650 2700
Text HLabel 4900 2700 0    60   Input ~ 0
+3.3V_USB
Text HLabel 4900 3150 0    60   Input ~ 0
TELEMENTRY1
Text HLabel 4900 3250 0    60   Input ~ 0
TELEMENTRY2
Text HLabel 4900 3350 0    60   Input ~ 0
TELEMENTRY3
Text HLabel 4900 3450 0    60   Input ~ 0
TELEMENTRY4
Text HLabel 4900 3550 0    60   Input ~ 0
TELEMENTRY5
Text HLabel 4900 3650 0    60   Input ~ 0
TELEMENTRY6
Text HLabel 4900 3750 0    60   Input ~ 0
TELEMENTRY7
Text HLabel 4900 3850 0    60   Input ~ 0
TELEMENTRY8
Text HLabel 4900 4050 0    60   Input ~ 0
TELEMENTRY_SEL0
Text HLabel 4900 4150 0    60   Input ~ 0
TELEMENTRY_SEL1
Text HLabel 4900 4250 0    60   Input ~ 0
TELEMENTRY_SEL2
Wire Wire Line
	4900 4050 5450 4050
Wire Wire Line
	4900 4150 5450 4150
Wire Wire Line
	4900 4250 5450 4250
Wire Wire Line
	4900 3150 5450 3150
Wire Wire Line
	5450 3250 4900 3250
Wire Wire Line
	4900 3350 5450 3350
Wire Wire Line
	5450 3450 4900 3450
Wire Wire Line
	4900 3550 5450 3550
Wire Wire Line
	4900 3650 5450 3650
Wire Wire Line
	5450 3750 4900 3750
Wire Wire Line
	4900 3850 5450 3850
Wire Wire Line
	6000 2700 6000 2950
Connection ~ 6000 2700
Text HLabel 7100 3300 2    60   Output ~ 0
SELECTED_TELEMENTRY
Wire Wire Line
	6550 3300 7100 3300
$EndSCHEMATC