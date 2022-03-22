#include <Wire.h> 
#include "rgb_lcd.h"

rgb_lcd lcd;
// can change backlight colour
const int colorR = 255;
const int colorG = 0;
const int colorB = 100;
// string variable to hold serial input
String inData;
// setup lcd and our serial input
void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);
}

void loop() {

    while (Serial.available() > 0)
    {
        // latency means we shouldn't send data directly as a string so we send it as a char and add it to our string variable above
        char recieved = Serial.read();
        inData += recieved;  
        // if arduino receives GPU data, prints the data on lcd
        if (recieved == '*')
        {
            inData.remove(inData.length() - 1, 1);
            lcd.setCursor(0,0);
            lcd.print("GPU Temp.: " + inData + char(223)+"C ");
            inData = ""; 
            // if arduino can't get GPU data, prints error message
            if(inData == "DIS")
            {   
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("Disconnected!");
            }
        } 
        // if arduino receives CPU data, prints CPU data to LCD
        if (recieved == '#')
        {
            inData.remove(inData.length() - 1, 1);
            lcd.setCursor(0,1);
            lcd.print("CPU Temp.: " + inData + char(223)+"C ");
            inData = ""; 
        }
    }
}
