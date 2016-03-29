/* 

display.cpp - Routines for LCD Keypad Shield 

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

#include "display.h"

byte thermometer_icon[8] = 
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

#define DROPLET_BYTE 1
byte droplet_icon[8] =  
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};


LCD_KEYPAD::LCD_KEYPAD() : LiquidCrystal(KEYPAD_LCD_PINS) {
//  _backlightTimer = 0;
   pinMode(BACKLIGHT_PIN, OUTPUT);  //Ued to control LCD backlight
}


void LCD_KEYPAD::begin(void) {
  // set up the LCD's number of columns (16) and rows (2): 
  LiquidCrystal::begin(16,2); 

  LiquidCrystal::createChar(THERMOMETER_BYTE, thermometer_icon);   
  LiquidCrystal::createChar(DROPLET_BYTE, droplet_icon);   

  LiquidCrystal::clear(); 

  LiquidCrystal::setCursor(0, 0);
  LiquidCrystal::write(byte(THERMOMETER_BYTE));    
  LiquidCrystal::print("??.??");
  LiquidCrystal::print((char)223);
  LiquidCrystal::print("C ");
  LiquidCrystal::write(byte(DROPLET_BYTE));  
  LiquidCrystal::print("??.??%");
  
  LiquidCrystal::setCursor(0, 1);
  LiquidCrystal::write(byte(THERMOMETER_BYTE));    
  LiquidCrystal::print("??.??");
  LiquidCrystal::print((char)223);
  LiquidCrystal::print("C ");
  LiquidCrystal::write(byte(DROPLET_BYTE));    
  LiquidCrystal::print("??.??%");
  
  backlightOn();
}

int LCD_KEYPAD::readButtons(void) {

  int button_value = checkButtons();

//  if (button_value = NO_BUTTON_PRESSED) { 
//    _backlightTimer -= 1;
//    if (_backlightTimer == 0) backlightOff();
//  } else {
//    backlightOn();
//    _backlightTimer = ON_DURATION;
//  }
  return button_value;
}

void LCD_KEYPAD::backlightOn(void) {
  digitalWrite(BACKLIGHT_PIN, ON);
}

void LCD_KEYPAD::backlightOff(void) {
  digitalWrite(BACKLIGHT_PIN, OFF);
}

int LCD_KEYPAD::checkButtons(void) {

 int adc_key_in = analogRead(0);   

 if (adc_key_in > 1000) return NO_BUTTON_PRESSED; // Check this first for speed

 if (adc_key_in < RIGHT_BUTTON_THRESHOLD)   return RIGHT_BUTTON_PRESSED;  
 if (adc_key_in < UP_BUTTON_THRESHOLD)      return UP_BUTTON_PRESSED; 
 if (adc_key_in < DOWN_BUTTON_THRESHOLD)    return DOWN_BUTTON_PRESSED; 
 if (adc_key_in < LEFT_BUTTON_THRESHOLD)    return LEFT_BUTTON_PRESSED; 
 if (adc_key_in < SELECT_BUTTON_THRESHOLD)  return SELECT_BUTTON_PRESSED;   

 return NO_BUTTON_PRESSED;  // when all others fail, return this...
}
