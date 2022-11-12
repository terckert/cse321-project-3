# <center>cse321-project-3</center>
### <center>Timothy Erckert</center>
*This markdown file is included in my [repository](https://github.com/terckert/cse321-project-3). Some external file links and images may not work if not viewed from outside of the repo.*

## Table of Contents
- [About](#about)
- [Program Overview](#program-overview)
- [Features](#features)
- [Required materials](#required-materials)
- [Getting started](#getting-started)
- [Resources and references](#resources-and-references)
    - [External references](#external-references)
- [Files](#files)
    - [lcd1602.cpp | lcd1602.h](#lcd1602cpp--lcd1602h)
    - [CSE321_project2_terckert_main.cpp](#cse321_project2_terckert_maincpp)
- [Declarations (Global Variables)](#declarations-global-variables)
- [APIs and Elements](#apis-and-elements)
    - [InterruptIn](#interruptin)
    - [CSE321_LCD](#cse321_lcd)
    - [Keypad](#keypad)
    - [LCD](#lcd)
    - [LEDs](#leds)
- [Custom functions](#custom-functions)
    - [Logical functions](#logical-functions)
    - [Inline functions](#inline-functions)

## About

## Program Overview

## Features

## Required Materials

## Getting Started

## Resources and references

## External References
- [Project Repository](https://github.com/terckert/cse-321-project-2)
- [Planning Document](/CSE321_project2_stage2_part1_terckert.pdf)
- [Nucleo API documentation](https://os.mbed.com/docs/mbed-os/v6.15/apis/index.html)
- [Nucleo Reference Manual](https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)

## Files

### lcd1602.cpp | lcd1602.h
- Contains all the logic and functions necessary to use the LCD

### CSE321_project2_terckert_main.cpp
- Program driver. Contains function global variables, functions, and main that controls program logic.

## Declarations (Global Variables)

## APIs and Elements
### InterruptIn
Sets a pin as an interrupt. Program uses the following functions:
1. rise
    
    Sets the rising edge callback function.
1. fall
    
    Sets the falling edge callback function.
### CSE321_LCD
Control logic for the LCD screen. Program uses the following functions:
1. begin
    
    Setup logic for the LCD. Sets needed registers to get the LCD to display text.
1. clear
    
    Clears the LCD screen.
1. setCursor
    
    Sets the cursor to the designated spot on the LCD screen.
1. print
    
    Prints the desired string to the LED.

### Keypad

### LCD

[1602 LCD Datasheet](/1602_LCD_Datasheet.pdf)

[LCD controller class header file](/lcd1602.h)

### LEDs

## Custom functions
There are two main types of functions in the program:
1. Logical functions that contain actual program logic
2. Inline functions.  They have names that describe what the function and are generally very short (ex. a single write instruction to the ODR). They are declared inline to strike the balance between writing human readable code while not filling the stack frame with unnecessary calls. They take advantage of the fact that function body will be inserted where called by compiler during compilation. 

### Logical functions

### Inline functions

## Program flowchart

## Schematic

