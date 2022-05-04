// Originally based on several default serial display sketch
// C group IOT Project

// Declare basic variables
// The number of the pushbutton pin
const int buttonPin = 5;
// Variable for reading the pushbutton status

// Include libraries and lcd
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;


// Set up
void setup()
{
    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // initialize the serial communications:
    Serial.begin(9600);
}

// Main loop
void loop()
{
    // Check if the serial if available
    if (Serial.available())
    {
        // wait a bit for the entire message to arrive
        delay(100);
        // clear the screen
        lcd.clear();
        // read all the available characters
        while (Serial.available() > 0)
        {
            int buttonState = digitalRead(buttonPin);
            if (buttonState == 1)
            {
                // Display GPU data
                // Split string         
                String inputData = Serial.readStringUntil('\n');
                // Display CPU string data
                lcd.print(inputData);
                // Move the cursor to the second line
                lcd.setCursor(0,1);
                // Set display to blue
                lcd.setRGB(0, 0, 255);
            }
            if (buttonState == 0)
            {
                // Display CPU data
                // Split string
                String inputData = Serial.readStringUntil('\n');
                inputData.remove(56);
                // Get CPU temp as an int
                String cpuTempS = (String)inputData.charAt(10);
                int cpuTemp = cpuTempS.toInt();
                // Cpu temp if statment
                if (cpuTemp > 4)
                {
                    lcd.setRGB(255, 0, 0);
                }
                else
                {
                    lcd.setRGB(0, 255, 0);
                }
                // Display CPU string data
                lcd.print(inputData);
                // Move the cursor to the second line
                lcd.setCursor(0,1);
            }
        }
    }
}
