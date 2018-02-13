
//include libraries
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//create Adafruit Alphanumeric Display object
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

//define integer
int score = 0;

void setup() {
  
  //set sensor pin to INPUT
  pinMode(A0, INPUT);
  //set BAUD rate
  Serial.begin(9600);  
  //start display
  alpha4.begin(0x70);
  //write zeros to all positions
  alpha4.writeDigitAscii(0, '0');
  alpha4.writeDigitAscii(1, '0');
  alpha4.writeDigitAscii(2, '0');
  alpha4.writeDigitAscii(3, '0');
  //display newly written values
  alpha4.writeDisplay();
}

void loop() {

  //add 1 to the score if sensor voltage is LOW
  if (analogRead(A0) < 200) {
    score++;   
 
  //write score to display data
  alpha4.writeDigitAscii(3, (score%10) + '0');
  alpha4.writeDigitAscii(2, (score%100/10) + '0');
  alpha4.writeDigitAscii(1, (score%1000/100) + '0');
  alpha4.writeDigitAscii(0, (score/1000) + '0');
  
  //push display data to display
  alpha4.writeDisplay();
 //wait 1.5 sec to eliminate phantom reads
  delay(1500);
  }
}
