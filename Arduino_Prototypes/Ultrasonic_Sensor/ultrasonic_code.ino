#include <Servo.h>

// Pin assignments
#define servoPin 8
#define trigPin 9
#define echoPin 10

// Global objects/vars
Servo myservo;  // Create Servo object to control a servo
float duration, distance;
const int closedPos = 90; // Lid closed position
const int openPos = 180; // Lid opened position
const int opDist = 35; // Operation distance (cm)

void setup() {
  myservo.attach(servoPin);
  myservo.write(closedPos); // Start with the lid closed
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Ultrasonic operating logic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Time to distance conversion
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;  // Convert to distance in cm

  // Compare distance and control servo
  if (distance <= opDist) {
    myservo.write(openPos); // Open the lid
    delay(500); // Wait for 500 ms to ensure servo moves
    myservo.write(closedPos); // Close the lid
    delay(500); // Wait before next iteration
  }
}
