# <center>cse321-project-3</center>
### <center>Timothy Erckert</center>
*This markdown file is included in my [repository](https://github.com/terckert/cse321-project-3). Some external file links and images may not work if not viewed from outside of the repo.*

## Table of Contents
- [<center>cse321-project-3</center>](#centercse321-project-3center)
    - [<center>Timothy Erckert</center>](#centertimothy-erckertcenter)
  - [Table of Contents](#table-of-contents)
  - [About](#about)
  - [Program Overview](#program-overview)
  - [Features](#features)
  - [Required Materials](#required-materials)
  - [Getting Started](#getting-started)
  - [Resources and references](#resources-and-references)
  - [External References](#external-references)
  - [Files](#files)
    - [lcd1602.cpp | lcd1602.h](#lcd1602cpp--lcd1602h)
  - [Declarations (Global Variables)](#declarations-global-variables)
  - [APIs and Elements](#apis-and-elements)
    - [InterruptIn](#interruptin)
    - [Keypad](#keypad)
    - [LCD](#lcd)
    - [LEDs](#leds)
  - [Custom functions](#custom-functions)
    - [Logical functions](#logical-functions)
    - [Inline functions](#inline-functions)
  - [Program flowchart](#program-flowchart)
  - [Schematic](#schematic)

## About

## Program Overview

## Features

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

## Resources and references

## External References
- [Project Repository](hhttps://github.com/terckert/cse321-project-3)
- [Nucleo API documentation](https://os.mbed.com/docs/mbed-os/v6.15/apis/index.html)
- [Nucleo Reference Manual](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## Files

### lcd1602.cpp | lcd1602.h
- Contains all the logic and functions necessary to use the LCD

## Declarations (Global Variables)

## APIs and Elements
### InterruptIn
Sets a pin as an interrupt. Program uses the following functions:
1. rise
    
    Sets the rising edge callback function.
1. fall
    
    Sets the falling edge callback function.

### Keypad

### LCD

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
### LEDs

## Custom functions
There are two main types of functions in the program:
1. Logical functions that contain actual program logic
2. Inline functions.  They have names that describe what the function and are generally very short (ex. a single write instruction to the ODR). They are declared inline to strike the balance between writing human readable code while not filling the stack frame with unnecessary calls. They take advantage of the fact that function body will be inserted where called by compiler during compilation. 

### Logical functions

### Inline functions

## Program flowchart

## Schematic

