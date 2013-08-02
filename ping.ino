/*
Code to control a HC-SR04 with an Arduino Uno R3
It is little simplification of Ultrasonic.cpp - Library for HC-SR04 Ultrasonic Ranging Module.library
Created by ITead studio. Apr 20, 2010. iteadstudio.com
Modificated by Xarpe Serpe  
*/

const int trig = A0; // Pin trigger.
const int echo = A1; // Pin echo.

void setup() 
{ 
   
  Serial.begin(9600); // initialize serial communication:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
} 
  
void loop() 
{ 
  
   makePing(); //Send a sonic burst and measure the time to echo, them calculate the distance.
 
} 

void makePing()
{
// establish variables for duration of the ping, 
// and the distance result in inches and centimeters:
long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10); // The sonics burst has 0.340 cm of length.
  digitalWrite(trig, LOW);

  // A HIGH pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echo, HIGH);

  // convert the time into a distance

  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(100);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29.4117647 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  
  return (microseconds / 29.4117647 / 2.); // without calibration.
  
  // return (microseconds / 29.4117647 / 2.-1.697959)/1.257335;
  
  // The last two numbers came from the calibration of my own HC-SR04 module
  // For make that, you need to make a linear regression with real measurement
  // and the measuremente gived by the program.
}



