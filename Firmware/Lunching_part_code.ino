#include <ESP32Servo.h>

const int IN1 = 42;
const int IN2 = 41;
const int buttonPin = 3;
const int enablePin = 9;
const int servoPin15 = 15;
const int servoPin16 = 16;
const int servoPin17 = 17;

Servo servo15;
Servo servo16;
Servo servo17;

// Waits until pin stays HIGH for holdMs consecutively
bool waitForStableHigh(int pin, unsigned long holdMs) {
  unsigned long highStart = 0;

  while (true) {
    if (digitalRead(pin) == HIGH) {
      if (highStart == 0) {
        highStart = millis();
      }

      if (millis() - highStart >= holdMs) {
        return true;
      }
    } else {
      highStart = 0;
    }

    delay(10);
  }
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(enablePin, INPUT);

  servo15.setPeriodHertz(50);
  servo16.setPeriodHertz(50);
  servo17.setPeriodHertz(50);

  servo15.attach(servoPin15, 500, 2400);
  servo16.attach(servoPin16, 500, 2400);
  servo17.attach(servoPin17, 500, 2400);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  servo15.write(90);
  servo16.write(90);
  servo17.write(180);

  delay(1000);

  // Wait for enable pin to stay HIGH for at least 1 second
  waitForStableHigh(enablePin, 1000);

  
  for (int i = 0; i < 3; i++) {
    bool servoMoved = false;

    // arm goes down
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    unsigned long startTime = millis();

    while (millis() - startTime < 3500) {
      // servo15 can move only after 1.9 sec from start of motor down movement
      if ((millis() - startTime >= 3330) && digitalRead(buttonPin) == HIGH && !servoMoved) {
        servo15.write(0);
        servoMoved = true;
      }
    }

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    if (servoMoved) {
      delay(1000);

      // reverse motor for 2 sec
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      delay(1550);

      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);

      servo16.write(0);
      delay(2000);

      servo16.write(90);
      delay(2000);

      servo17.write(0);
      delay(1000);
      servo17.write(90);

      servo15.write(90);
    }

    delay(1000);
  }

  while (1) {
  }
}

void loop() {
}