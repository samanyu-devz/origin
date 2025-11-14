#include <Servo.h>
#include <Ultrasonic.h>

// Define pins for ultrasonic sensor and servo motor
const int trigPin = 2;
const int echoPin = 3;
const int servoPin = 5;

// Define threshold distance for closing the lid
const int thresholdDistance = 15; // Adjust this value as needed (cm)
const int hysteresis = 5;         // Hysteresis range to avoid rapid toggling

Servo myServo;
Ultrasonic ultrasonic(trigPin, echoPin);

bool isLidClosed = false; // Keep track of the lid's state

void setup() {
  // Attach the servo motor to the specified pin
  myServo.attach(servoPin);
  // Initialize the servo motor to an open position
  myServo.write(0); // 0 degrees for open lid
}

void loop() {
  // Take multiple readings and calculate an average for stability
  int distance = getStableDistance();

  // Check the distance and apply hysteresis
  if (!isLidClosed && distance <= thresholdDistance) {
    // Close the lid
    myServo.write(180);
    isLidClosed = true;
  } else if (isLidClosed && distance > (thresholdDistance + hysteresis)) {
    // Open the lid
    myServo.write(0);
    isLidClosed = false;
  }

  delay(100); // Small delay to stabilize readings
}

// Function to get stable distance readings
int getStableDistance() {
  const int numReadings = 5;
  int total = 0;

  for (int i = 0; i < numReadings; i++) {
    total += ultrasonic.read();
    delay(20); // Short delay between readings
  }

  return total / numReadings; // Return the average distance
}
