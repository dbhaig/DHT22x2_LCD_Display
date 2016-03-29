/* 

display.h - Routines for LCD Keypad Shield 

Copyright (c) 2016 Don Haig (time4tux at gmail dot com)
All rights reserved.

This program is free software: you  can redistribute it and/or modify it
under the  terms of the GNU  General Public License as  published by the
Free Software Foundation,  either version 3 of the License,  or (at your
option) any later version.

This  program  is distributed  in  the  hope  that  it will  be  useful,
but  WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy  of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define KEYPAD_LCD_PINS 8, 9, 4, 5, 6, 7

//#define LINE1 0
//#define LINE2 1
//#define COLUMN_0 0

//These thresholds work for my shield
#define RIGHT_BUTTON_THRESHOLD    50
#define UP_BUTTON_THRESHOLD      195 
#define DOWN_BUTTON_THRESHOLD    380
#define LEFT_BUTTON_THRESHOLD    555
#define SELECT_BUTTON_THRESHOLD  790

const boolean OFF = false;
const boolean ON = true;

const int BACKLIGHT_PIN = 10;       //pin 10 is used to control LCD backlight

const int NO_BUTTON_PRESSED     = 0;  //used by checkButtons()
const int RIGHT_BUTTON_PRESSED  = 1;
const int UP_BUTTON_PRESSED     = 2;
const int DOWN_BUTTON_PRESSED   = 3;
const int LEFT_BUTTON_PRESSED   = 4;
const int SELECT_BUTTON_PRESSED = 5;

#define THERMOMETER_BYTE 0

class LCD_KEYPAD : public LiquidCrystal {
  public:
   LCD_KEYPAD();
   void begin(void);
   int readButtons(void);
   void backlightOn(void);
   void backlightOff(void);
  private:
   int _backlightTimer;
   int checkButtons(void);
};
#endif
