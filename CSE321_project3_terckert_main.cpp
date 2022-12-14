/**
 * File         : CSE321_project3_terckert_main.cpp
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : This program is going to "save the world!" Its purpose to help someone hone their fine motor
 *                skills. It is a simple digital level with LED and sound alarms to alert a user when it has begun
 *                tipping to much forward, backward, left, or right. They can use these indicators to bring it back
 *                to level.
 * 
 * Modules      : lcd1602.h
 * 
 * Inputs       : 4xTilt Sensors, 4x4 membrane keypad
 * 
 * Outputs      : 1602 LCD display, 4xLEDs, Buzzer 
 * 
 * Constraints  : 
 * 
 * References   :
 * Nucleo manual: https://www.st.com/resource/en/reference_manual/dm00310109-stm32l4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 * Nucleo API documentation: https://os.mbed.com/docs/mbed-os/v6.15/apis/index.html 
 * 
 * Created on   : 11/18/2022
 * Changelist   :
 */

/***********************************************         Includes       **********************************************/
#include "mbed.h"
#include "lcd1602.h"

/***********************************************    Global Variables    **********************************************/
enum highlow {                                      // Making 1s and 0s human readable
    low = 0,
    high
};

// LCD globals
CSE321_LCD lcd(16,2, LCD_5x8DOTS, PF_0, PF_1);

// Buzzer globals - Buzzer is active low.
Mutex buzzer_lock;                                  // Protects regions that write to the buzzer control signal.
Thread buzzer_thread;                               // Thread that polls tilt_sensors
DigitalOut buzzer_VCC(PE_12);                       // Supplies power to buzzer
DigitalOut buzzer_sound(PE_14);                     // Buzzer sound control signal

// Enum that pulls double duty. Buzzer is active low so sound is on when signal is 0. It is also used to control
// the sound mode state. User sets the sound mode state with the keypad to turn on and off the audible warning
enum sound_mode {                                   
    sound_on = 0,
    sound_off
};
sound_mode current_sound_mode = sound_on;           // Default sound mode is on
Watchdog &wd = Watchdog::get_instance();            // Watchdog timer

// Keypad globals
DigitalOut row_1(PF_13);                            // Controls power to keypad row 1
InterruptIn column_one(PE_13, PullDown);            // Set keypad interrupt column 1 (1 key)
InterruptIn column_two(PF_15, PullDown);            // Set keypad interrupt column 2 (2 key)

// Event queue used by keypad interrupts. They call functions with mutexes so have to queue them up to avoid errors.
EventQueue keypad_event(10*(EVENTS_EVENT_SIZE + sizeof(sound_mode)));
Thread keypad_thread;                               // Thread for keypad_event queue


// Tilt sensor input pins. Pin high - sensor is level. Pin low - sensor is askew.
DigitalIn tilt_sensor_1(PA_7);                       // Reads signal from tilt sensor 1
DigitalIn tilt_sensor_2(PD_14);                      // Reads signal from tilt sensor 2
DigitalIn tilt_sensor_3(PD_15);                      // Reads signal from tilt sensor 3
DigitalIn tilt_sensor_4(PF_12);                      // Reads signal from tilt sensor 4

/***********************************************  Function Declarations **********************************************/
// LCD Function definitions
void initialize_1602();

// Keypad function definitions
void debounce_falling_edge();
void process_column_one_interrupt();
void process_column_two_interrupt();

// Buzzer control variables
void change_sound_mode(sound_mode);
void check_tilt_sensors();

/***********************************************          Main          **********************************************/
int main()
{
    initialize_1602();                              // Start LCD
    lcd.clear();                                    // Clear LCD screen and set cursor to home
    lcd.print("Sound is ON ");                      // Display current sound mode on row one
    lcd.setCursor(0,1);                             // Move cursor to second row
    lcd.print("1: ON     2: OFF");                  // Display keypad options on row 2:

    // Start up buzzer
    buzzer_sound = sound_off;                       // Set buzzer I/O to high (no sound)
    buzzer_VCC = high;                              // Turn on buzzer.

    // Start up keypad
    row_1 = high;                                   // Set keypad row 1 (1,2,3,A) to high. Will stay high throughout
                                                    // program since only 1 and 2 are used.
    keypad_thread.start(callback(&keypad_event, &EventQueue::dispatch_forever));
    
    // Set rising edge interrupt two read which button is pressed.
    column_one.rise(&process_column_one_interrupt);
    column_two.rise(&process_column_two_interrupt);

    // Set debounce function on falling edge
    column_one.fall(&debounce_falling_edge);
    column_two.fall(&debounce_falling_edge);

    // Start thread that polls the tilt sensors, never ends
    wd.start(120);
    buzzer_thread.start(callback(check_tilt_sensors));
    
    while (true) {
        // Keep program alive
        // printf("Column 1: %d\t Column 2: %d\n", column_one.read(), column_two.read());
        // ThisThread::sleep_for(200ms);
    }
    return 0;
}

/***********************************************  Function Definitions  **********************************************/
/**
 * Function     : initialize_1602
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : Provides power to the lcd and calls the LCD begin function, which initialize the LCD for use.
 * 
 * Parameters   : none
 * 
 * Returns      : none
 * 
 * Physical Inputs  : none
 * 
 * Physical Outputs : Pin F2
 * 
 * Constraints  : none
 * Changelist   : 
 */
void initialize_1602() {
    // Setting clock is redundant since constructor for LCD handles it. It just makes me feel better about myself.
    RCC->AHB2ENR |=  0x20;                      // Initialize clock to F register 
    
    // Send power to LCD
    GPIOF->MODER &= ~0x30;                      // Clear pin F2 mode
    GPIOF->MODER |=  0x10;                      // Set pin for output
    GPIOF->ODR   |=  0x4;                       // Start LCD

    lcd.begin();
}

/**
 * Function     : debounce_falling_edge
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : Debounces on the falling edge by waiting. Wait time is determined by physically testing the
 *                keypad and a different keypad may have a different sweet spot.
 * 
 * Parameters   : none
 * 
 * Returns      : none
 * 
 * Physical Inputs  : Trigged by falling edge of keypad interrupt pins.
 * 
 * Physical Outputs : none
 * 
 * Constraints  : 
 * Changelist   :
 */
void debounce_falling_edge(){
    wait_us(50000);                             // Wait 20ms to debounce
}

/**
 * Function     : process_column_one_interrupt
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : Rising edge interrupt for column one. Debounces rising edge with a wait. Queues function
 *                to change sound mode with a sound_on parameter
 * 
 * Parameters   : none
 * 
 * Returns      : none
 * 
 * Physical Inputs  : Triggered by rising edge of pin E13.
 * 
 * Physical Outputs : none
 * 
 * Constraints  : 
 * Changelist   :
 */
void process_column_one_interrupt() {
    wait_us(50000);                             // Wait 50ms to debounce    
    keypad_event.call(change_sound_mode, sound_on);
}

/**
 * Function     : process_column_two_interrupt
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : Rising edge interrupt for column one. Debounces rising edge with a wait. Queues function
 *                to change sound mode with a sound_off parameter. 
 * 
 * Parameters   : none
 * 
 * Returns      : none
 * 
 * Physical Inputs  : Triggered by rising edge of pin F15.
 * 
 * Physical Outputs : none
 * 
 * Constraints  : 
 * Changelist   :
 */
void process_column_two_interrupt() {
    wait_us(50000);                             // Wait 50ms to debounce
    keypad_event.call(change_sound_mode, sound_off);
}

/**
 * Function     : Change sound mode
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : Added to an EventQueue by the keypad interrupts, this function will change the current
 *                sound mode, allowing or restricting use of the buzzer as an auditory alert.
 * 
 * Parameters   : 
 *      new_sound_mode - (sound_mode) Sound mode to be changed to 
 * 
 * Returns      : None
 * 
 * Physical Inputs  : None
 * 
 * Physical Outputs : Buzzer (potentially)
 * 
 * Constraints  : 
 * Changelist   :
 */
void change_sound_mode(sound_mode new_sound_mode) {
    // This function operates in a critical region.
    // check_tilt_sensors reads from current sound mode and writes to buzzer_sound, possible conflicts
    buzzer_lock.lock();                         // Lock critical region
    
    // Only make a change if the new mode is different then the old mode.
    if (current_sound_mode != new_sound_mode) {
        current_sound_mode = new_sound_mode;
        lcd.setCursor(9, 0);                    // Move to where current mode is displayed
        if (current_sound_mode == sound_off) {  // Logic for turning off sound mode
            lcd.print("OFF");                   // Display new mode
            buzzer_sound = sound_off;           // Turn off sound if currently on
        }
        else {                                  // Logic for turning on sound mode
            lcd.print("ON ");                   // Display new mode
        }
    }
    
    buzzer_lock.unlock();                       // Unlock critical region
}

/**
 * Function     : check_tilt_sensor
 * Author       : Timothy Erckert
 * Assignment   : Project 3
 * Purpose      : The main loop of the buzzer peripheral. Polls the inputs from the tilt sensors every
 *                10ms to determine if a sensor has detected tilt. This function also handles the watchdog
 *                timer logic. If unable to aquire the buzzer_lock mutex within 120ms, it will restart the
 *                program. This value was chosen based on the scenario that both a rising and falling edge
 *                interrupt paused the program for 50ms each at the start of a pole cycle.
 * 
 * Parameters   : 
 * 
 * Returns      : None
 * 
 * Physical Inputs  : tilt_sensor_1, tilt_sensor_2, tilt_sensor_3, tilt_sensor_4
 * 
 * Physical Outputs : buzzer_sound
 * 
 * Constraints  : 
 * Changelist   :
 */
void check_tilt_sensors() {
    // This function operates in a critical region.
    // change_sound_mode writes to current_sound_mode and buzzer_sound, possible conflicts
    while(true) {
        buzzer_lock.lock();
        wd.kick();                     // Lock critical region
        if (current_sound_mode == sound_on) {   // If sound mode is currently on
            // Tilt sensors are high when level, low when askew. Buzzer sounds when any sensor is skewed.
            // Buzzer is also active low. Assignment statement uses bitwise AND, if any tilt sensors are
            // low, buzzer will sound.
            buzzer_sound = tilt_sensor_1 & tilt_sensor_2 & tilt_sensor_3 & tilt_sensor_4;

        }
        buzzer_lock.unlock();                   // Unlock critical region
        ThisThread::sleep_for(10ms);
    }
    
}

/**
 * Function     : 
 * Author       : Timothy Erckert
 * Assignment   : 
 * Purpose      : 
 * 
 * Parameters   : 
 * 
 * Returns      : 
 * 
 * Physical Inputs  : 
 * 
 * Physical Outputs : 
 * 
 * Constraints  : 
 * Changelist   :
 */