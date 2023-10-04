#include <Servo.h>

/*
Simple code for moving a servo back and forth one time triggered by a RF 433 relay.
Developed by: Luca Di Iorio Casellas, for: EPIC Grup SL
Date: 04/10/2023
*/

#define DEBUG 1

Servo myservo;

int lastAnalogValue = 0;
unsigned long lastDebounceTime = 0;

const int analogPin = A1;
const int servoPin = 3;
unsigned long debounceDelay = 10;
int analogThreshold = 100;

bool servoMoved = false;

void setup() {
  if (DEBUG) Serial.begin(9600);
  
  myservo.attach(3);
  myservo.write(45); // Initialize servo position
  pinMode(analogPin, INPUT);

  servoMoved = false;
}

void loop() {
  int reading = analogRead(analogPin);

  // Check if the analog value has changed
  if (abs(reading - lastAnalogValue) > analogThreshold) {
    lastDebounceTime = millis();
  }

  // Check if the analog value has remained stable for the debounce delay
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading >= 1023) {
      if (DEBUG) Serial.println("MOVING");
      if (DEBUG) Serial.println(reading);
      myservo.write(130);
      delay(1000);
      servoMoved = true;
    }
    else if ((reading < 1000) && servoMoved) {
      if (DEBUG) Serial.println("RETURNING");
      if (DEBUG) Serial.println(reading);
      myservo.write(45);
      delay(1000);
      servoMoved = false;
    }
  }

  // Update the last analog value
  lastAnalogValue = reading;  
}
