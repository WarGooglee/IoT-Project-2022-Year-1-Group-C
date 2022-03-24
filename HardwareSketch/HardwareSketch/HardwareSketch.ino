// Originally based on default serial display sketch
// C group IOT Project

// Include libraries
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Declare variable
String inputData = " ";

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // initialize the serial communications:
    Serial.begin(9600);
}

void loop() {
    // when characters arrive over the serial port
    if (Serial.available()) {
        // wait a bit for the entire message to arrive
        delay(100);
        // clear the screen
        lcd.clear();
        // read all the available characters
        while (Serial.available() > 0) {
            // display each character to the LCD
            inputData = Serial.readStringUntil('\n');
            lcd.print(inputData);
            lcd.setCursor(0,1);
        }
    }
}
