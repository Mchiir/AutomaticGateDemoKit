# Automatic Gate Demo Kit

This Arduino-based project implements an automatic gate control system using ultrasonic sensors for object detection. The system features LED indicators, a servo motor for gate movement, and a buzzer for audio feedback.

## Hardware Components

- Arduino board
- HC-SR04 Ultrasonic Sensor
- Servo Motor
- 2x LEDs (Red and Blue)
- Buzzer
- Jumper wires
- Power supply

## Pin Configuration

| Component | Pin |
|-----------|-----|
| Ultrasonic Trigger | 2 |
| Ultrasonic Echo | 3 |
| Red LED (Gate Closed) | 4 |
| Blue LED (Gate Open) | 5 |
| Servo Motor | 6 |
| Buzzer | 12 |

## Features

- **Automatic Detection**: Uses ultrasonic sensor to detect objects within 20cm
- **Smooth Gate Operation**: Implements smooth servo movement to prevent jerky motion
- **Status Indicators**:
  - Red LED: Indicates gate is closed
  - Blue LED: Indicates gate is open
  - Buzzer: Provides intermittent beeping when gate is open
- **Safety Timing**: 
  - Gate remains open for 5 seconds after last object detection
  - Buzzer beeps for 5 seconds when gate opens
- **Serial Monitoring**: Outputs status messages for debugging (9600 baud rate)

## Operation

1. When powered on, the gate initializes in the closed position with the red LED on
2. When an object is detected within 20cm:
   - Gate opens smoothly
   - Red LED turns off
   - Blue LED turns on
   - Buzzer beeps intermittently for 5 seconds
3. Gate remains open as long as object is detected
4. After object moves away and 5 seconds elapse:
   - Gate closes smoothly
   - Blue LED turns off
   - Red LED turns on
   - Buzzer stops

## Constants

- Gate Open Angle: 103 degrees
- Gate Closed Angle: 7 degrees
- Detection Distance: 20 cm
- Indicator Duration: 5000 ms (5 seconds)
- Buzzer Interval: 250 ms

## Dependencies

- Servo.h library (standard Arduino library)

## Installation

1. Connect the components according to the pin configuration
2. Install the Arduino IDE
3. Upload the AutomaticGateDemoKit.ino sketch to your Arduino board
4. Power up the system

## Troubleshooting

- If distance readings are inconsistent, check the ultrasonic sensor connections
- If servo movement is jerky, verify the power supply is adequate
- If LEDs don't light up, verify the connections and LED polarity
- Use the Serial Monitor (9600 baud) to debug operation