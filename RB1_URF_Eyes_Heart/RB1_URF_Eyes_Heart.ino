// Redboard #1
// Ultrasonic Range Finder, LED Eyes, LED Heart
// by Kelcie Feeney, Rosanna Lui and Ruthanne Featherston

// Based on Arduino Example Sketch
// for Ultrasonic ranging module, HC-SR04
// See https://github.com/CytronTechnologies/Arduno_UltrasonicRangingModule

#include "Ultrasonic.h"

// The robot panics when objects are within 50 cm
// Sensor value is already in cm units (no conversion needed)
#define URF_DISTANCE_CM_PANIC   50

// The robot has digital I/O with URF, Eyes and Heart
// These values correspond to pin numbers on the Redboard
#define COMMAND_PIN_RB23_PANIC  2
#define HEART_PIN               8
#define EYES_PIN_RED            9
#define EYES_PIN_GREEN          10
#define EYES_PIN_BLUE           11
#define SENSOR_PIN_TRIG         12
#define SENSOR_PIN_ECHO         13

Ultrasonic ultrasonic(SENSOR_PIN_TRIG, SENSOR_PIN_ECHO);

void setup() {

  // Prepare for serial output
  // This can be observed from the serial monitor
  Serial.begin(9600);
  Serial.println("HC-SR4 testing...");

  // Prepare for digital I/O
  pinMode(COMMAND_PIN_RB23_PANIC, OUTPUT);
  pinMode(HEART_PIN, OUTPUT);
  pinMode(EYES_PIN_RED, OUTPUT);
  pinMode(EYES_PIN_GREEN, OUTPUT);
  pinMode(EYES_PIN_BLUE, OUTPUT);

  // Set digital output for commands to LOW (no panic)
  // Note Arduinos RB2 and RB3 will receive this data
  digitalWrite(COMMAND_PIN_RB23_PANIC, LOW);

  // Set digital output for LEDs to HIGH (off)
  // Note LEDs will light up when digital I/O is LOW
  // because they are common anode and use pull down resistors
  digitalWrite(HEART_PIN, HIGH);
  digitalWrite(EYES_PIN_RED, HIGH);
  digitalWrite(EYES_PIN_GREEN, HIGH);
  digitalWrite(EYES_PIN_BLUE, HIGH);

}

void loop() {

  int urfDistanceCm = ultrasonic.Ranging(CM);

  Serial.print(urfDistanceCm);
  Serial.println(" cm");

  if (urfDistanceCm < URF_DISTANCE_CM_PANIC) {
    PanicEyes();
    PanicHeart();
    PanicOtherArduinos();
  } else {
    RelaxEyes();
    RelaxHeart();
    RelaxOtherArduinos();
  }

  delay(100);

}

void PanicEyes() {

  // To panic, the eyes turn red
  digitalWrite(EYES_PIN_RED, LOW);
  digitalWrite(EYES_PIN_GREEN, HIGH);
  digitalWrite(EYES_PIN_BLUE, HIGH);

}

void PanicHeart() {

  // To panic, the heart stops (turns off)
  digitalWrite(HEART_PIN, HIGH);

}

void PanicOtherArduinos() {

  // To panic, the other arduinos take some actions
  digitalWrite(COMMAND_PIN_RB23_PANIC, HIGH);

}

void RelaxEyes() {

  // To relax, the eyes turn blue
  digitalWrite(EYES_PIN_RED, HIGH);
  digitalWrite(EYES_PIN_GREEN, HIGH);
  digitalWrite(EYES_PIN_BLUE, LOW);

}

void RelaxHeart() {

  // To relax, the heart starts again (turns on)
  digitalWrite(HEART_PIN, LOW);

}

void RelaxOtherArduinos() {

  // To relax, the other arduinos stop taking those actions
  digitalWrite(COMMAND_PIN_RB23_PANIC, LOW);

}

