# Automatic Gate Demo Kit

Arduino-based gate control system using HC-SR04 ultrasonic sensor and servo motor.

## Features

- Distance measurement using ultrasonic sensor
- Gate opens (servo to 103°) when object detected within 20cm
- Gate closes automatically after 5 seconds
- Red LED indicates closed state
- Blue LED indicates open state
- Buzzer beeps while gate is open

## Components

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Red & Blue LEDs
- Buzzer
- Jumper wires

## Setup

1. Connect components as per [code pin definitions](./automatic_gate.ino)
2. Upload provided code to Arduino
3. Power with 5V supply

## Operation

- Object detection triggers gate opening sequence
- Blue LED and buzzer activate during open state
- System returns to standby after timeout
- Red LED shows secure/closed status

```arduino
// Core Functionality:
void loop() {
  if (getDistance() < 20) {
    openGate(); // Activates servo, blue LED, buzzer
    lastDetection = millis();
  }
  else if (gateOpen && millis() - lastDetection > 5000) {
    closeGate(); // Returns to red LED state
  }
}
```
