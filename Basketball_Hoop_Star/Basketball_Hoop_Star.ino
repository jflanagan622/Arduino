
//include libraries
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"




Adafruit_7segment matrix = Adafruit_7segment();
//create Adafruit Alphanumeric Display object
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

//define integer
int score = 0;
int counter = 10;
bool inRange = false;
unsigned long Watch, _micro, time = micros();
unsigned int Clock = 0, R_clock;
boolean Reset = false, Stop = false, Paused = false, _type;
volatile boolean timeFlag = false;

#define DOWN 0
#define UP 1


void setup() {
  #ifndef __AVR_ATtiny85__
    Serial.begin(9600);
    Serial.println("7 Segment Backpack Test");
  #endif
    matrix.begin(0x70);
  
  //set sensor pin to INPUT
  pinMode(A0, INPUT);
  //set BAUD rate
  Serial.begin(9600);  
  SetTimer(0,0,10); // 1 minute 1 seconds
  StartTimer();
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
  if(score == 0){
    matrix.print(0);
    matrix.writeDisplay(); 
  }
 
  CountUpDownTimer(DOWN); // run the timer

  // this prevents the time from being constantly shown.
  if (TimeHasChanged() ) 
  {
   
    //Serial.print(ShowMinutes());
    //Serial.print(":");
    //Serial.print(ShowSeconds());
    //Serial.println();
    // This DOES NOT format the time to 0:0x when seconds is less than 10.
    // if you need to format the time to standard format, use the sprintf() function.
  }
 
  Serial.println(analogRead(A0));
  //add 1 to the score if sensor voltage is LOW
  if (analogRead(A0) > 300) {
    
    inRange = true;   
 
  //write score to display data
 /* alpha4.writeDigitAscii(3, (score%10) + '0');
  alpha4.writeDigitAscii(2, (score%100/10) + '0');
  alpha4.writeDigitAscii(1, (score%1000/100) + '0');
  alpha4.writeDigitAscii(0, (score/1000) + '0');*/
  
  //push display data to display
  alpha4.writeDisplay();
 //wait 1.5 sec to eliminate phantom reads
  
  } else {
    inRange = false;
  }
  

  if(inRange == true){
    score++;
    matrix.print(score);
    matrix.writeDisplay();   
    delay(500);
    //Serial.println("Score");
    //Serial.println(score);    
  } else {
    //Serial.println("no basket");
  }    
  
}

boolean CountUpDownTimer(boolean Type)
{
  _type = Type;
  static unsigned long duration = 1000000; // 1 second
  timeFlag = false;

  if (!Stop && !Paused) // if not Stopped or Paused, run timer
  {
    // check the time difference and see if 1 second has elapsed
    if ((_micro = micros()) - time > duration ) 
    {
      _type == UP? Clock++ : Clock--;
      timeFlag = true;

      if (_type == DOWN && Clock == 0) // check to see if the clock is 0
        Stop = true; // If so, stop the timer

     // check to see if micros() has rolled over, if not,
     // then increment "time" by duration
      _micro < time ? time = _micro : time += duration; 
    }
  }
  return !Stop; // return the state of the timer
}

void ResetTimer()
{
  if(_type) 
    Clock = 0;
  else
    SetTimer(R_clock);

  Stop = false;
}

void StartTimer()
{
  Watch = micros(); // get the initial microseconds at the start of the timer
  Stop = false;
  Paused = false;
  if(_type == UP) 
    Clock = 0;
}

void StopTimer()
{
  Stop = true;
}

void StopTimerAt(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
  if (TimeCheck(hours, minutes, seconds) )
    Stop = true;
}

void PauseTimer()
{
  Paused = true;
}

void ResumeTimer() // You can resume the timer if you ever stop it.
{
  Paused = false;
}

void SetTimer(unsigned int hours, unsigned int minutes, unsigned int seconds)
{
  // This handles invalid time overflow ie 1(H), 0(M), 120(S) -> 1, 2, 0
  unsigned int _S = (seconds / 60), _M = (minutes / 60);
  if(_S) minutes += _S;
  if(_M) hours += _M;

  Clock = (hours * 3600) + (minutes * 60) + (seconds % 60);
  R_clock = Clock;
  Stop = false;
}

void SetTimer(unsigned int seconds)
{
 // StartTimer(seconds / 3600, (seconds / 3600) / 60, seconds % 60);
 Clock = seconds;
 R_clock = Clock;
 Stop = false;
}

int ShowHours()
{
  return Clock / 3600;
}

int ShowMinutes()
{
  return (Clock / 60) % 60;
}

int ShowSeconds()
{
  return Clock % 60;
}

unsigned long ShowMilliSeconds()
{
  return (_micro - Watch)/ 1000.0;
}

unsigned long ShowMicroSeconds()
{
  return _micro - Watch;
}

boolean TimeHasChanged()
{
  return timeFlag;
}

// output true if timer equals requested time
boolean TimeCheck(unsigned int hours, unsigned int minutes, unsigned int seconds) 
{
  return (hours == ShowHours() && minutes == ShowMinutes() && seconds == ShowSeconds());
}
