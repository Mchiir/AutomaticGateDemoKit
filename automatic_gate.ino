#include <Servo.h>


const int TRIG_PIN = 2;   
const int ECHO_PIN = 3;    
const int RED_LED = 4;   
const int BLUE_LED = 5;   
const int SERVO_PIN = 6;  
const int GND_PIN1 = 7;   
const int GND_PIN2 = 8;  
const int BUZZER_PIN = 12; 

// Constants
const int openAngle = 103;      
const int closeAngle = 7;      
const int distanceThreshold = 20; 
const int indicatorDuration = 5000;
const int buzzerInterval = 250;   

// Variables
Servo gateServo;              
unsigned long lastDetectionTime; 
unsigned long gateOpenTime;    
bool gateOpen = false;        
bool indicatorsActive = false; 

void setup() {
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GND_PIN1, OUTPUT); digitalWrite(GND_PIN1, LOW); 
  pinMode(GND_PIN2, OUTPUT); digitalWrite(GND_PIN2, LOW);
  
  // Attach servo and set initial position
  gateServo.attach(SERVO_PIN);
  smoothServoMove(closeAngle); 
  digitalWrite(RED_LED, HIGH); 
  digitalWrite(BLUE_LED, LOW); 
  digitalWrite(BUZZER_PIN, LOW); 
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Setup complete: Gate closed, Red LED ON, Blue LED OFF");
}

void loop() {
  // Measure distance
  long distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  // Check if object is within threshold
  if (distance < distanceThreshold && distance > 0) {
    // Object detected, open gate
    if (!gateOpen) {
      smoothServoMove(openAngle); // Open gate smoothly
      gateOpen = true;
      gateOpenTime = millis();   // Record gate open time
      indicatorsActive = true;   // Activate LED/buzzer
      digitalWrite(RED_LED, LOW);  // Red LED OFF
      digitalWrite(BLUE_LED, HIGH); // Blue LED ON
      Serial.println("Gate opened: Red LED OFF, Blue LED ON");
    }
    lastDetectionTime = millis(); // Update detection time
  } else {
    
    if (gateOpen && millis() - lastDetectionTime > indicatorDuration) {
      smoothServoMove(closeAngle); 
      gateOpen = false;
      indicatorsActive = false;
      digitalWrite(RED_LED, HIGH);   // Red LED ON
      digitalWrite(BLUE_LED, LOW);   // Blue LED OFF
      digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF
      Serial.println("Gate closed: Red LED ON, Blue LED OFF");
    }
  }

  // Handle intermittent buzzer when gate is open
  if (indicatorsActive && millis() - gateOpenTime < indicatorDuration) {
    // Buzzer beeps for 5 seconds
    if ((millis() - gateOpenTime) % (buzzerInterval * 2) < buzzerInterval) {
      digitalWrite(BUZZER_PIN, HIGH); // Buzzer ON
    } else {
      digitalWrite(BUZZER_PIN, LOW);  // Buzzer OFF
    }
  } else if (indicatorsActive) {
    // After 5 seconds, turn off blue LED and buzzer
    digitalWrite(BLUE_LED, LOW);   // Blue LED OFF
    digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF
    indicatorsActive = false;
    Serial.println("Indicators off: Blue LED OFF, Buzzer OFF");
  }

  delay(50); // Small delay for stability
}

// Function to measure distance using ultrasonic sensor
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // 30ms timeout
  if (duration == 0) return -1; // Invalid reading
  return duration * 0.0343 / 2; // Distance in cm (kit formula)
}

// Function to move servo smoothly to avoid shaking
void smoothServoMove(int targetAngle) {
  int currentAngle = gateServo.read();
  int step = (targetAngle > currentAngle) ? 1 : -1;
  
  for (int angle = currentAngle; angle != targetAngle; angle += step) {
    gateServo.write(angle);
    delay(15); // Smooth movement
  }
  gateServo.write(targetAngle);
}
