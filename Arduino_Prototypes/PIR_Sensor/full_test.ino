#include <Servo.h>
#include "ArduinoLowPower.h"

// Pin assignments
#define PIR 2 // PIR interrupt
#define servoPin 8

// Global objects/vars
Servo myservo;
const int closedPos = 90; // Servo position for the lid closed
const int openPos = 180;  // Servo position for the lid open
unsigned long startTime;  // Time to track stabilization period
#define STABILIZATION_TIME 30000 // Stabilization time in milliseconds (30 seconds)
volatile bool motionDetected = false; // Flag for motion detection

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Setup...");
  
  // PIR setup
  pinMode(PIR, INPUT); // Set PIR pin as input
  attachInterrupt(digitalPinToInterrupt(PIR), OpenLid, RISING); // Interrupt on rising edge
  startTime = millis(); // Record the start time

  // Servo setup
  myservo.attach(servoPin); // Attach servo to specified pin
  myservo.write(closedPos); // Start with the lid closed
  
  Serial.println("Setup Complete. Stabilizing PIR...");
}

void loop() {
  // Stabilization period
  if (millis() - startTime < STABILIZATION_TIME) {
    if (millis() % 1000 < 50) { // Inform user once every second
      Serial.println("Stabilizing PIR...");
    }
    return; // Exit loop until stabilization is complete
  }

  // Check if motion was detected
  if (motionDetected) {
    Serial.println("Motion Detected");
    myservo.write(openPos); // Open the lid
    delay(500); // Wait for servo to fully open
    myservo.write(closedPos); // Close the lid
    delay(500); // Wait before next operation
    motionDetected = false; // Reset flag
  }
}

void OpenLid() {
  motionDetected = true; // Set flag when motion is detected
}
