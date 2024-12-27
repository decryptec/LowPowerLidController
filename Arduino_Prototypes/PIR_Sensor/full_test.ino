#include <Servo.h.>
#include "ArduinoLowPower.h"

//Pin assignments
#define PIR 2 // PIR interrupt
#define servoPin 8


//Global objects/vars
Servo myservo;
const int closedPos = 90;
const int openPos = 180;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Setup...");
  //PIR setup
  pinMode(PIR, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR), OpenLid, RISING);
  startTime = millis ();

  //Servo setup
  myservo.attach(servoPin);
  myservo.write(closedPos); // Start with the lid closed
    
  Serial.println("Setup Complete. Stabilizing PIR...");
}

void loop() {
    // Stabilization period
    if (millis() - startTime < STABILIZATION_TIME) {
        if (millis() % 1000 < 50) { // Inform user once every second
            Serial.println("Stabilizing PIR...");
        }
        return;
    }
}

void OpenLid(){
            Serial.println("Motion Detected");
            myservo.write(openPos); // Open the lid
            delay(500); // Wait for 500 ms to ensure servo moves
            myservo.write(closedPos); // Close the lid
            delay(500); // Wait before next iteration
}
