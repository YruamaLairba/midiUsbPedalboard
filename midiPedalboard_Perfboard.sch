EESchema Schematic File Version 4
LIBS:midiPedalboard_Perfboard-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L arduino_micro_shield:ARDUINO_MICRO_SHIELD U1
U 1 1 5CAB7C4F
P 4750 2650
F 0 "U1" V 4600 3200 60  0000 R CNN
F 1 "ARDUINO_MICRO_SHIELD" V 4700 3600 60  0000 R CNN
F 2 "midiPedalboard_Perfboard:ARDUINO_MICRO_SHIELD" H 5150 2600 60  0001 C CNN
F 3 "" H 5150 2600 60  0000 C CNN
	1    4750 2650
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5CAB7EC8
P 2500 2500
F 0 "C1" H 2592 2546 50  0000 L CNN
F 1 "C" H 2592 2455 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 2500 2500 50  0001 C CNN
F 3 "~" H 2500 2500 50  0001 C CNN
	1    2500 2500
	1    0    0    -1  
$EndComp
Text Label 4150 3800 0    50   ~ 0
rotary_a
Text Label 4150 3900 0    50   ~ 0
rotary_b
Text Label 4150 3500 0    50   ~ 0
screen_cs
Wire Wire Line
	4150 3800 4550 3800
Wire Wire Line
	4150 3900 4550 3900
Wire Wire Line
	4150 3500 4550 3500
Wire Wire Line
	4150 3400 4550 3400
Wire Wire Line
	4150 3300 4550 3300
Wire Wire Line
	4150 3600 4550 3600
Wire Wire Line
	4150 3700 4550 3700
Wire Wire Line
	4150 4000 4550 4000
Wire Wire Line
	4150 4100 4550 4100
Wire Wire Line
	4150 4200 4550 4200
Wire Wire Line
	4150 4300 4550 4300
Text Label 4150 3400 0    50   ~ 0
screen_dc
Text Label 4150 3300 0    50   ~ 0
screen_res
Text Label 4150 3600 0    50   ~ 0
btn_ok
Text Label 4150 3700 0    50   ~ 0
btn_cancel
Text Label 4150 4000 0    50   ~ 0
fs_0
Text Label 4150 4100 0    50   ~ 0
fs_1
Text Label 4150 4200 0    50   ~ 0
fs_2
Text Label 4150 4300 0    50   ~ 0
fs_3
NoConn ~ 5900 3300
NoConn ~ 5900 3400
Text Label 6300 4000 2    50   ~ 0
fsled_0
Text Label 6300 3700 2    50   ~ 0
fsled_3
Text Label 6300 3900 2    50   ~ 0
fsled_1
Text Label 6300 3800 2    50   ~ 0
fsled_2
Wire Wire Line
	5900 3700 6300 3700
Wire Wire Line
	5900 3800 6300 3800
Wire Wire Line
	5900 3900 6300 3900
Wire Wire Line
	5900 4000 6300 4000
Text Label 7750 5000 2    50   ~ 0
exp
Wire Wire Line
	5900 3000 6300 3000
Wire Wire Line
	5900 3200 6300 3200
Text Label 6300 3200 2    50   ~ 0
VCC
Text Label 6300 3000 2    50   ~ 0
GND
Wire Wire Line
	4150 2700 4550 2700
Text Label 4150 2700 0    50   ~ 0
screen_sda
Wire Wire Line
	5900 2700 6300 2700
Text Label 6300 2700 2    50   ~ 0
screen_sck
$Comp
L Device:C_Small C2
U 1 1 5CABB741
P 3000 2500
F 0 "C2" H 3092 2546 50  0000 L CNN
F 1 "C" H 3092 2455 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 3000 2500 50  0001 C CNN
F 3 "~" H 3000 2500 50  0001 C CNN
	1    3000 2500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J1
U 1 1 5CABBB87
P 2500 2000
F 0 "J1" V 2440 1912 50  0000 R CNN
F 1 "wire" V 2349 1912 50  0000 R CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 2500 2000 50  0001 C CNN
F 3 "~" H 2500 2000 50  0001 C CNN
	1    2500 2000
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Female J2
U 1 1 5CABBC7E
P 3000 2000
F 0 "J2" V 2940 1912 50  0000 R CNN
F 1 "wire" V 2849 1912 50  0000 R CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3000 2000 50  0001 C CNN
F 3 "~" H 3000 2000 50  0001 C CNN
	1    3000 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2500 2400 2500 2300
Wire Wire Line
	3000 2400 3000 2300
Text Label 2500 2300 2    50   ~ 0
rotary_a
Wire Wire Line
	2400 2300 2500 2300
Connection ~ 2500 2300
Wire Wire Line
	2500 2300 2500 2200
Wire Wire Line
	3000 2300 3100 2300
Connection ~ 3000 2300
Wire Wire Line
	3000 2300 3000 2200
Text Label 3100 2300 0    50   ~ 0
rotary_b
$Comp
L Connector:Conn_01x01_Female J6
U 1 1 5CABD334
P 3950 3600
F 0 "J6" H 4000 3550 50  0000 C CNN
F 1 "wire" H 3850 3550 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 3600 50  0001 C CNN
F 3 "~" H 3950 3600 50  0001 C CNN
	1    3950 3600
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J7
U 1 1 5CABD51F
P 3950 3700
F 0 "J7" H 4000 3650 50  0000 C CNN
F 1 "wire" H 3850 3650 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 3700 50  0001 C CNN
F 3 "~" H 3950 3700 50  0001 C CNN
	1    3950 3700
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J8
U 1 1 5CABD547
P 3950 4000
F 0 "J8" H 4000 3950 50  0000 C CNN
F 1 "wire" H 3850 3950 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 4000 50  0001 C CNN
F 3 "~" H 3950 4000 50  0001 C CNN
	1    3950 4000
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J9
U 1 1 5CABD56D
P 3950 4100
F 0 "J9" H 4000 4050 50  0000 C CNN
F 1 "wire" H 3850 4050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 4100 50  0001 C CNN
F 3 "~" H 3950 4100 50  0001 C CNN
	1    3950 4100
	-1   0    0    1   
$EndComp
NoConn ~ 5900 4100
NoConn ~ 5900 4200
NoConn ~ 5900 4300
NoConn ~ 5900 3100
NoConn ~ 4550 3100
Wire Wire Line
	4550 2900 4150 2900
Wire Wire Line
	4550 3000 4150 3000
NoConn ~ 4550 2800
NoConn ~ 5900 2800
NoConn ~ 5900 2900
Text Label 4150 2900 0    50   ~ 0
UART_TX
Text Label 4150 3000 0    50   ~ 0
UART_RX
$Comp
L Connector:Conn_01x01_Female J11
U 1 1 5CAC0E85
P 6500 3700
F 0 "J11" H 6550 3750 50  0000 C CNN
F 1 "wire" H 6400 3750 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 6500 3700 50  0001 C CNN
F 3 "~" H 6500 3700 50  0001 C CNN
	1    6500 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J12
U 1 1 5CAC0F05
P 6500 3800
F 0 "J12" H 6550 3850 50  0000 C CNN
F 1 "wire" H 6400 3850 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 6500 3800 50  0001 C CNN
F 3 "~" H 6500 3800 50  0001 C CNN
	1    6500 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J13
U 1 1 5CAC0F4C
P 6500 3900
F 0 "J13" H 6550 3950 50  0000 C CNN
F 1 "wire" H 6400 3950 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 6500 3900 50  0001 C CNN
F 3 "~" H 6500 3900 50  0001 C CNN
	1    6500 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J14
U 1 1 5CAC0F7D
P 6500 4000
F 0 "J14" H 6550 4050 50  0000 C CNN
F 1 "wire" H 6400 4050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 6500 4000 50  0001 C CNN
F 3 "~" H 6500 4000 50  0001 C CNN
	1    6500 4000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Jt10
U 1 1 5CAC0FB0
P 8050 5000
F 0 "Jt10" H 8100 5050 50  0000 C CNN
F 1 "wire" H 7950 5050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8050 5000 50  0001 C CNN
F 3 "~" H 8050 5000 50  0001 C CNN
	1    8050 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J17
U 1 1 5CAC184A
P 9300 1300
F 0 "J17" H 9350 1350 50  0000 C CNN
F 1 "MIDI_4" H 9200 1350 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 9300 1300 50  0001 C CNN
F 3 "~" H 9300 1300 50  0001 C CNN
	1    9300 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J18
U 1 1 5CAC1947
P 9300 1400
F 0 "J18" H 9350 1450 50  0000 C CNN
F 1 "MIDI_2" H 9200 1450 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 9300 1400 50  0001 C CNN
F 3 "~" H 9300 1400 50  0001 C CNN
	1    9300 1400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female J19
U 1 1 5CAC1989
P 9300 1500
F 0 "J19" H 9350 1550 50  0000 C CNN
F 1 "MIDI_5" H 9200 1550 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 9300 1500 50  0001 C CNN
F 3 "~" H 9300 1500 50  0001 C CNN
	1    9300 1500
	1    0    0    -1  
$EndComp
Text Label 8900 1400 0    50   ~ 0
GND
$Comp
L Device:R_Small R2
U 1 1 5CAC273A
P 8700 1300
F 0 "R2" V 8700 1300 50  0000 C CNN
F 1 "220" V 8595 1300 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 8700 1300 50  0001 C CNN
F 3 "~" H 8700 1300 50  0001 C CNN
	1    8700 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5CAC2999
P 8700 1500
F 0 "R3" V 8700 1500 50  0000 C CNN
F 1 "220" V 8595 1500 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 8700 1500 50  0001 C CNN
F 3 "~" H 8700 1500 50  0001 C CNN
	1    8700 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 1300 8800 1300
Wire Wire Line
	9100 1500 8800 1500
Text Label 8300 1300 0    50   ~ 0
VCC
Text Label 8300 1500 0    50   ~ 0
UART_TX
Wire Wire Line
	8300 1500 8600 1500
Wire Wire Line
	8300 1300 8600 1300
Wire Wire Line
	9100 1400 8900 1400
$Comp
L pc900:PC900 U2
U 1 1 5CACCEFA
P 8750 2250
F 0 "U2" H 8750 2615 50  0000 C CNN
F 1 "PC900" H 8750 2524 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm_Socket" H 8750 2350 50  0001 C CNN
F 3 "" H 8750 2350 50  0001 C CNN
	1    8750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 2150 9250 2150
Text Label 9200 2150 2    50   ~ 0
VCC
$Comp
L Device:R_Small R4
U 1 1 5CACD7F8
P 9600 2200
F 0 "R4" V 9600 2200 50  0000 C CNN
F 1 "280" V 9495 2200 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 9600 2200 50  0001 C CNN
F 3 "~" H 9600 2200 50  0001 C CNN
	1    9600 2200
	-1   0    0    1   
$EndComp
Text Label 10050 2350 2    50   ~ 0
UART_RX
Text Label 9200 2250 2    50   ~ 0
GND
Wire Wire Line
	9050 2350 9600 2350
Wire Wire Line
	9250 2150 9250 2050
Wire Wire Line
	9250 2050 9350 2050
$Comp
L Device:C_Small C3
U 1 1 5CAD43C3
P 9350 2150
F 0 "C3" H 9350 2100 50  0000 L CNN
F 1 "0.1 uf" H 9442 2105 50  0001 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 9350 2150 50  0001 C CNN
F 3 "~" H 9350 2150 50  0001 C CNN
	1    9350 2150
	1    0    0    -1  
$EndComp
Connection ~ 9350 2050
Wire Wire Line
	9600 2050 9600 2100
Wire Wire Line
	9350 2050 9600 2050
Wire Wire Line
	9600 2300 9600 2350
Connection ~ 9600 2350
Wire Wire Line
	9600 2350 10050 2350
Wire Wire Line
	9050 2250 9350 2250
$Comp
L Connector:Conn_01x01_Female J15
U 1 1 5CAD6CA9
P 7700 2050
F 0 "J15" H 7750 2000 50  0000 C CNN
F 1 "MIDI_4" H 7600 2000 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7700 2050 50  0001 C CNN
F 3 "~" H 7700 2050 50  0001 C CNN
	1    7700 2050
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Small D1
U 1 1 5CAD7573
P 8250 2150
F 0 "D1" V 8204 2218 50  0000 L CNN
F 1 "1n914" V 8295 2218 50  0000 L CNN
F 2 "Diode_THT:D_A-405_P2.54mm_Vertical_AnodeUp" V 8250 2150 50  0001 C CNN
F 3 "~" V 8250 2150 50  0001 C CNN
	1    8250 2150
	0    1    1    0   
$EndComp
Connection ~ 8250 2250
Wire Wire Line
	8250 2250 8450 2250
Wire Wire Line
	8450 2150 8450 2050
Wire Wire Line
	8450 2050 8250 2050
Connection ~ 8250 2050
Wire Wire Line
	8250 2050 8200 2050
$Comp
L Device:R_Small R1
U 1 1 5CAD9524
P 8100 2050
F 0 "R1" V 8100 2050 50  0000 C CNN
F 1 "220" V 8205 2050 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 8100 2050 50  0001 C CNN
F 3 "~" H 8100 2050 50  0001 C CNN
	1    8100 2050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7900 2250 8250 2250
Wire Wire Line
	8000 2050 7900 2050
$Comp
L Connector:Conn_01x01_Female J16
U 1 1 5CADC123
P 7700 2250
F 0 "J16" H 7750 2200 50  0000 C CNN
F 1 "MIDI_5" H 7600 2200 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7700 2250 50  0001 C CNN
F 3 "~" H 7700 2250 50  0001 C CNN
	1    7700 2250
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J21
U 1 1 5CADDDE3
P 3950 4200
F 0 "J21" H 4000 4150 50  0000 C CNN
F 1 "wire" H 3850 4150 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 4200 50  0001 C CNN
F 3 "~" H 3950 4200 50  0001 C CNN
	1    3950 4200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female J22
U 1 1 5CADDE35
P 3950 4300
F 0 "J22" H 4000 4250 50  0000 C CNN
F 1 "wire" H 3850 4250 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3950 4300 50  0001 C CNN
F 3 "~" H 3950 4300 50  0001 C CNN
	1    3950 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 2600 2500 2700
Wire Wire Line
	3000 2600 3000 2700
Text Label 2750 2700 2    50   ~ 0
GND
$Comp
L power:GND #PWR0102
U 1 1 5CAE19BD
P 2750 2850
F 0 "#PWR0102" H 2750 2600 50  0001 C CNN
F 1 "GND" H 2755 2677 50  0000 C CNN
F 2 "" H 2750 2850 50  0001 C CNN
F 3 "" H 2750 2850 50  0001 C CNN
	1    2750 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1400 8900 1600
$Comp
L power:GND #PWR0103
U 1 1 5CAE39C6
P 8900 1600
F 0 "#PWR0103" H 8900 1350 50  0001 C CNN
F 1 "GND" H 8905 1427 50  0000 C CNN
F 2 "" H 8900 1600 50  0001 C CNN
F 3 "" H 8900 1600 50  0001 C CNN
	1    8900 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 2250 9450 2250
Wire Wire Line
	9450 2250 9450 2450
Connection ~ 9350 2250
$Comp
L power:GND #PWR0104
U 1 1 5CAE483C
P 9450 2450
F 0 "#PWR0104" H 9450 2200 50  0001 C CNN
F 1 "GND" H 9455 2277 50  0000 C CNN
F 2 "" H 9450 2450 50  0001 C CNN
F 3 "" H 9450 2450 50  0001 C CNN
	1    9450 2450
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0105
U 1 1 5CAE6D33
P 4300 1800
F 0 "#PWR0105" H 4300 1650 50  0001 C CNN
F 1 "VCC" H 4317 1973 50  0000 C CNN
F 2 "" H 4300 1800 50  0001 C CNN
F 3 "" H 4300 1800 50  0001 C CNN
	1    4300 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1800 4300 1950
Wire Wire Line
	4600 1850 4600 1700
Text Label 4600 1700 3    50   ~ 0
GND
Text Label 4300 1800 3    50   ~ 0
VCC
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5CAE97F1
P 4600 1700
F 0 "#FLG0102" H 4600 1775 50  0001 C CNN
F 1 "PWR_FLAG" H 4600 1874 50  0000 C CNN
F 2 "" H 4600 1700 50  0001 C CNN
F 3 "~" H 4600 1700 50  0001 C CNN
	1    4600 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5CAE6E45
P 4600 1850
F 0 "#PWR0106" H 4600 1600 50  0001 C CNN
F 1 "GND" H 4605 1677 50  0000 C CNN
F 2 "" H 4600 1850 50  0001 C CNN
F 3 "" H 4600 1850 50  0001 C CNN
	1    4600 1850
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5CAE96FB
P 4300 1950
F 0 "#FLG0101" H 4300 2025 50  0001 C CNN
F 1 "PWR_FLAG" H 4300 2123 50  0000 C CNN
F 2 "" H 4300 1950 50  0001 C CNN
F 3 "~" H 4300 1950 50  0001 C CNN
	1    4300 1950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4550 3200 4150 3200
Text Label 4150 3200 0    50   ~ 0
GND
$Comp
L Connector:Conn_01x01_Female Jg1
U 1 1 5CAEFDF0
P 3350 3800
F 0 "Jg1" H 3400 3750 50  0000 C CNN
F 1 "wire" H 3250 3750 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 3800 50  0001 C CNN
F 3 "~" H 3350 3800 50  0001 C CNN
	1    3350 3800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg7
U 1 1 5CAEFE58
P 3350 3900
F 0 "Jg7" H 3400 3850 50  0000 C CNN
F 1 "wire" H 3250 3850 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 3900 50  0001 C CNN
F 3 "~" H 3350 3900 50  0001 C CNN
	1    3350 3900
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg8
U 1 1 5CAEFEC2
P 3350 4000
F 0 "Jg8" H 3400 3950 50  0000 C CNN
F 1 "wire" H 3250 3950 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 4000 50  0001 C CNN
F 3 "~" H 3350 4000 50  0001 C CNN
	1    3350 4000
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg9
U 1 1 5CAEFF2E
P 3350 4100
F 0 "Jg9" H 3400 4050 50  0000 C CNN
F 1 "wire" H 3250 4050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 4100 50  0001 C CNN
F 3 "~" H 3350 4100 50  0001 C CNN
	1    3350 4100
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg21
U 1 1 5CAEFF9C
P 3350 4200
F 0 "Jg21" H 3400 4150 50  0000 C CNN
F 1 "wire" H 3250 4150 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 4200 50  0001 C CNN
F 3 "~" H 3350 4200 50  0001 C CNN
	1    3350 4200
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg22
U 1 1 5CAF000C
P 3350 4300
F 0 "Jg22" H 3400 4250 50  0000 C CNN
F 1 "wire" H 3250 4250 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 3350 4300 50  0001 C CNN
F 3 "~" H 3350 4300 50  0001 C CNN
	1    3350 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 3800 3550 3900
Connection ~ 3550 3900
Wire Wire Line
	3550 3900 3550 4000
Connection ~ 3550 4000
Wire Wire Line
	3550 4000 3550 4100
Connection ~ 3550 4100
Wire Wire Line
	3550 4100 3550 4200
Connection ~ 3550 4200
Wire Wire Line
	3550 4200 3550 4300
Connection ~ 3550 4300
Wire Wire Line
	3550 4300 3550 4450
$Comp
L power:GND #PWR0107
U 1 1 5CAF0F67
P 3550 4450
F 0 "#PWR0107" H 3550 4200 50  0001 C CNN
F 1 "GND" H 3555 4277 50  0000 C CNN
F 2 "" H 3550 4450 50  0001 C CNN
F 3 "" H 3550 4450 50  0001 C CNN
	1    3550 4450
	1    0    0    -1  
$EndComp
Text Label 3550 4300 3    50   ~ 0
GND
$Comp
L Connector:Conn_01x01_Female Jg11
U 1 1 5CAF4A7B
P 7250 3700
F 0 "Jg11" H 7300 3750 50  0000 C CNN
F 1 "wire" H 7150 3750 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7250 3700 50  0001 C CNN
F 3 "~" H 7250 3700 50  0001 C CNN
	1    7250 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg12
U 1 1 5CAF4AF5
P 7250 3800
F 0 "Jg12" H 7300 3850 50  0000 C CNN
F 1 "wire" H 7150 3850 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7250 3800 50  0001 C CNN
F 3 "~" H 7250 3800 50  0001 C CNN
	1    7250 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg13
U 1 1 5CAF4B71
P 7250 3900
F 0 "Jg13" H 7300 3950 50  0000 C CNN
F 1 "wire" H 7150 3950 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7250 3900 50  0001 C CNN
F 3 "~" H 7250 3900 50  0001 C CNN
	1    7250 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Jg14
U 1 1 5CAF4BF1
P 7250 4000
F 0 "Jg14" H 7300 4050 50  0000 C CNN
F 1 "wire" H 7150 4050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 7250 4000 50  0001 C CNN
F 3 "~" H 7250 4000 50  0001 C CNN
	1    7250 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3700 7050 3800
Connection ~ 7050 3800
Wire Wire Line
	7050 3800 7050 3900
Connection ~ 7050 3900
Wire Wire Line
	7050 3900 7050 4000
Connection ~ 7050 4000
Wire Wire Line
	7050 4000 7050 4200
$Comp
L power:GND #PWR0108
U 1 1 5CAF5CBE
P 7050 4200
F 0 "#PWR0108" H 7050 3950 50  0001 C CNN
F 1 "GND" H 7055 4027 50  0000 C CNN
F 2 "" H 7050 4200 50  0001 C CNN
F 3 "" H 7050 4200 50  0001 C CNN
	1    7050 4200
	1    0    0    -1  
$EndComp
Text Label 7050 4200 1    50   ~ 0
GND
$Comp
L Connector:Conn_01x01_Female Jr10
U 1 1 5CAF6041
P 8050 4750
F 0 "Jr10" H 8100 4800 50  0000 C CNN
F 1 "wire" H 7950 4800 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8050 4750 50  0001 C CNN
F 3 "~" H 8050 4750 50  0001 C CNN
	1    8050 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Js10
U 1 1 5CAF60E1
P 8050 5350
F 0 "Js10" H 8100 5400 50  0000 C CNN
F 1 "wire" H 7950 5400 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8050 5350 50  0001 C CNN
F 3 "~" H 8050 5350 50  0001 C CNN
	1    8050 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R5
U 1 1 5CAF65EA
P 7800 4600
F 0 "R5" V 7800 4600 50  0000 C CNN
F 1 "100" V 7695 4600 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 7800 4600 50  0001 C CNN
F 3 "~" H 7800 4600 50  0001 C CNN
	1    7800 4600
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0109
U 1 1 5CAF680A
P 7800 4400
F 0 "#PWR0109" H 7800 4250 50  0001 C CNN
F 1 "VCC" H 7817 4573 50  0000 C CNN
F 2 "" H 7800 4400 50  0001 C CNN
F 3 "" H 7800 4400 50  0001 C CNN
	1    7800 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 4400 7800 4500
Wire Wire Line
	7800 4700 7800 4750
Wire Wire Line
	7800 4750 7850 4750
Wire Wire Line
	7850 5350 7800 5350
Wire Wire Line
	7800 5350 7800 5400
$Comp
L power:GND #PWR0110
U 1 1 5CAFA231
P 7800 5400
F 0 "#PWR0110" H 7800 5150 50  0001 C CNN
F 1 "GND" H 7805 5227 50  0000 C CNN
F 2 "" H 7800 5400 50  0001 C CNN
F 3 "" H 7800 5400 50  0001 C CNN
	1    7800 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 2700 2750 2200
$Comp
L Connector:Conn_01x01_Female J10
U 1 1 5CB02EDC
P 2750 2000
F 0 "J10" V 2690 1912 50  0000 R CNN
F 1 "wire" V 2599 1912 50  0000 R CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 2750 2000 50  0001 C CNN
F 3 "~" H 2750 2000 50  0001 C CNN
	1    2750 2000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2500 2700 2750 2700
Wire Wire Line
	2750 2850 2750 2700
Connection ~ 2750 2700
Wire Wire Line
	2750 2700 3000 2700
Wire Wire Line
	7750 3300 8100 3300
Wire Wire Line
	7750 3400 8100 3400
Wire Wire Line
	7750 3500 8100 3500
Wire Wire Line
	7750 3600 8100 3600
Wire Wire Line
	7750 3700 8100 3700
Wire Wire Line
	7750 3800 8100 3800
Wire Wire Line
	7750 3900 8100 3900
Text Label 7750 3300 0    50   ~ 0
GND
Text Label 7750 3400 0    50   ~ 0
VCC
Text Label 7750 3500 0    50   ~ 0
screen_sck
Text Label 7750 3600 0    50   ~ 0
screen_sda
Text Label 7750 3700 0    50   ~ 0
screen_res
Text Label 7750 3800 0    50   ~ 0
screen_dc
Text Label 7750 3900 0    50   ~ 0
screen_cs
$Comp
L Connector:Conn_01x07_Female J3
U 1 1 5CCA11A5
P 8300 3600
F 0 "J3" H 8327 3626 50  0000 L CNN
F 1 "Screen" H 8327 3535 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Horizontal" H 8300 3600 50  0001 C CNN
F 3 "~" H 8300 3600 50  0001 C CNN
	1    8300 3600
	1    0    0    -1  
$EndComp
Text Label 8550 5000 2    50   ~ 0
exp_2
$Comp
L Connector:Conn_01x01_Female Jt11
U 1 1 5CCAFC10
P 8850 5000
F 0 "Jt11" H 8900 5050 50  0000 C CNN
F 1 "wire" H 8750 5050 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8850 5000 50  0001 C CNN
F 3 "~" H 8850 5000 50  0001 C CNN
	1    8850 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Jr11
U 1 1 5CCBBBC1
P 8850 4750
F 0 "Jr11" H 8900 4800 50  0000 C CNN
F 1 "wire" H 8750 4800 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8850 4750 50  0001 C CNN
F 3 "~" H 8850 4750 50  0001 C CNN
	1    8850 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Female Js11
U 1 1 5CCBBBC8
P 8850 5350
F 0 "Js11" H 8900 5400 50  0000 C CNN
F 1 "wire" H 8750 5400 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x01_Drill0.8mm" H 8850 5350 50  0001 C CNN
F 3 "~" H 8850 5350 50  0001 C CNN
	1    8850 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5CCBBBCF
P 8600 4600
F 0 "R6" V 8600 4600 50  0000 C CNN
F 1 "100" V 8495 4600 50  0001 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" H 8600 4600 50  0001 C CNN
F 3 "~" H 8600 4600 50  0001 C CNN
	1    8600 4600
	-1   0    0    1   
$EndComp
$Comp
L power:VCC #PWR0101
U 1 1 5CCBBBD6
P 8600 4400
F 0 "#PWR0101" H 8600 4250 50  0001 C CNN
F 1 "VCC" H 8617 4573 50  0000 C CNN
F 2 "" H 8600 4400 50  0001 C CNN
F 3 "" H 8600 4400 50  0001 C CNN
	1    8600 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4400 8600 4500
Wire Wire Line
	8600 4700 8600 4750
Wire Wire Line
	8600 4750 8650 4750
Wire Wire Line
	8650 5350 8600 5350
Wire Wire Line
	8600 5350 8600 5400
$Comp
L power:GND #PWR0111
U 1 1 5CCBBBE1
P 8600 5400
F 0 "#PWR0111" H 8600 5150 50  0001 C CNN
F 1 "GND" H 8605 5227 50  0000 C CNN
F 2 "" H 8600 5400 50  0001 C CNN
F 3 "" H 8600 5400 50  0001 C CNN
	1    8600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3500 6300 3500
Wire Wire Line
	5900 3600 6300 3600
$Comp
L Device:C_Small C11
U 1 1 5D1F9307
P 8600 5200
F 0 "C11" H 8692 5246 50  0000 L CNN
F 1 "100n" H 8692 5155 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 8600 5200 50  0001 C CNN
F 3 "~" H 8600 5200 50  0001 C CNN
	1    8600 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5D1F949D
P 7800 5200
F 0 "C10" H 7892 5246 50  0000 L CNN
F 1 "100n" H 7892 5155 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W2.0mm_P5.00mm" H 7800 5200 50  0001 C CNN
F 3 "~" H 7800 5200 50  0001 C CNN
	1    7800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 5300 7800 5350
Connection ~ 7800 5350
Wire Wire Line
	8600 5300 8600 5350
Connection ~ 8600 5350
Wire Wire Line
	8600 5000 8600 5100
Connection ~ 8600 5000
Wire Wire Line
	8600 5000 8650 5000
Wire Wire Line
	8350 5000 8600 5000
Wire Wire Line
	7800 5100 7800 5000
Connection ~ 7800 5000
Wire Wire Line
	7800 5000 7850 5000
Wire Wire Line
	7550 5000 7800 5000
Text Label 6300 3600 2    50   ~ 0
exp
Text Label 6300 3500 2    50   ~ 0
exp_2
$EndSCHEMATC
