// Pin Definitions
const int PIR = 2;    // PIR sensor pin
const int LED = 7;    // LED pin

// Timing Constants
const unsigned long STABILIZATION_TIME = 30000; // 30 seconds

// State Variables
unsigned long startTime;
bool motionState = false;  // Current motion state
bool previousMotionState = false; // Previous motion state

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing Setup...");
    pinMode(PIR, INPUT);
    pinMode(LED, OUTPUT);

    startTime = millis(); // Start stabilization timer
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

    // Read PIR Sensor
    motionState = digitalRead(PIR);

    // Handle Motion Detection with State Change
    if (motionState != previousMotionState) { // Detect state change
        if (motionState) {
            Serial.println("Motion Detected");
            digitalWrite(LED, HIGH); // Turn on LED
            delay(3000); //Simulate actuator duration
        } else {
            Serial.println("No Motion");
            digitalWrite(LED, LOW); // Turn off LED
        }
        previousMotionState = motionState; // Update previous state
    }
}
