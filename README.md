# <center>cse321-project-3</center>
### <center>Timothy Erckert</center>
*This markdown file is included in my [repository](https://github.com/terckert/cse321-project-3). Some external file links and images may not work if not viewed from outside of the repo.*

## Table of Contents

  - [About](#about)
  - [Program Overview](#program-overview)
  - [Features](#features)
  - [Required Materials](#required-materials)
  - [Getting Started](#getting-started)
  - [Resources and References](#resources-and-references)
    - [External References](#external-references)
    - [Files](#files)
      - [lcd1602.cpp | lcd1602.h](#lcd1602cpp--lcd1602h)
    - [Declarations (Global Variables)](#declarations-global-variables)
    - [APIs and Peripherals](#apis-and-peripherals)
      - [InterruptIn](#interruptin)
      - [DigitalIn](#digitalin)
      - [Keypad](#keypad)
      - [LCD](#lcd)
      - [LEDs](#leds)
      - [Tilt Sensors](#tilt-sensors)
      - [Buzzer](#buzzer)
    - [Custom functions](#custom-functions)
  - [Program flowchart](#program-flowchart)
  - [Schematic](#schematic)

## About
This project is a prototype of a device that will "save the world!" It's purpose is to help someone hone their fine motor skills. A simple digital level with LED and sound alarms to alter a user when it has begun tipping to far foward, backward, left, or right. They can use these indicators to bring it back to level.

## Program Overview
Program will use 4 tilt sensors bent towards the four cardinal directions (with relation to the whiteboard, not magnetic) to detect whether what it has been placed on is level or not. LED's will be lit by default and will dim when skewed in that direction. This will also sound an alarm from the onboard buzzer. When the board has been brought back to level state, all lights will be lit once more and alarm will turn off.

The user has the option to silence the alarm feature by pressing 2 on the keypad, and can reactivate it by pressing 1. These options are displayed on the LCD screen. 


## Features
1. LCD screen menu
2. Visual and auditory alerts
3. Keypad input
4. Detects tilt when placed on a carried obect

## Required Materials
| Quantity | Item                                                  |
| :------: | ----------------------------------------------------- |
|    1     | Nucleo STM32L4R5ZI                                    |
|    1     | 1602 LCD                                              |
|    4     | 100ohm resistors                                      |
|    4     | LEDs                                                  |
|    1     | 4x4 Membrane Keypad                                   |
|    1     | Solderless breadboard                                 |
|    4     | Gikfun Metal Ball Tilt Shaking Position Switches      |
|    1     | Arceli Passive Low Level Trigger Buzzer Alarm, 3.3-5v |
|          | Female-to-male jumper wires                           |
|          | Male-to-male jumper wires                             |

## Getting Started

[Binary (this link does not currently work)]()

To use the program the circuit must be built as detailed in the [schematic section](#schematic) or by following pinout tables in peripheral sections. There are two ways of working with the program, building it yourself or downloading the binary and manually adding it to your Nucleo's memory.

*It is **important** that when you are adding the tilt sensors they should be bent in the direction that they are going to be checking. I found the easiest way is inserting them into the breadboard and then pushing them outwards. Through testing, I have found an angle of 30-40 degrees works best, but you can bend them to whatever angle words best for you.*

<strong>Build</strong>
1. Create a new project in Mbed Studio and include the following files:
    - lcd1602.cpp
    - lcd1602.h
    - CSE321_project2_terckert_main.cpp
1. Attach Nucleo to PC and build project or build binary and manually add to Nucleo memory.
1. Enjoy!

## Resources and References

### External References
- [Project Repository](hhttps://github.com/terckert/cse321-project-3)
- [Nucleo API documentation](https://os.mbed.com/docs/mbed-os/v6.15/apis/index.html)
- [Nucleo Reference Manual](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

### Files

#### lcd1602.cpp | lcd1602.h
- Contains all the logic and functions necessary to use the LCD

### Declarations (Global Variables)

### APIs and Peripherals
#### InterruptIn
Sets a pin as an interrupt. Program uses the following functions:
1. rise
    
    Sets the rising edge callback function.
1. fall
    
    Sets the falling edge callback function.

#### DigitalIn
Sets a pin to read in a high or low signal. These pins are used to detect input from the tilt sensors. They transmit a 1 when level and a 0 when skewed.

|Variable Name|Pin|
|---|:------:|
|tilt_sensor_1|PA_7|
|tilt_sensor_2|PD_14|
|tilt_sensor_3|PD_15|
|tilt_sensor_4|PF_12|

#### Keypad
The keypad row pin is constantly energized to capture input. When pressed, 1 and 2 will send an interrupt signal to queue a function to change sound modes.

| Row output pin | Nucleo pin |
|---|:---:|
| Row: 1,2,3,A | F13 |

| Column input pin | Nucleo pin|
|---|:---:|
| Column: 1,4,7,* | E13 |
| Column: 2,5,8,0 | F15 |

#### LCD

[1602 LCD Datasheet](/1602_LCD_Datasheet.pdf)

[LCD controller class header file](/lcd1602.h)

Control logic for the LCD screen. Program uses the following functions:
1. begin
    
    Setup logic for the LCD. Sets needed registers to get the LCD to display text.
1. clear
    
    Clears the LCD screen.
1. setCursor
    
    Sets the cursor to the designated spot on the LCD screen.
1. print
    
    Prints the desired string to the LED.
#### LEDs

LEDs are on by default when the tilt sensor is level. They turn off when the sensor detects tilt.

#### Tilt Sensors

#### Buzzer

### Custom functions

## Program flowchart
Stay tuned!
## Schematic
Stay tuned!
