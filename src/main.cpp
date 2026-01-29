#include <Arduino.h>
#include <Servo.h>

#define DEBUG 0

namespace {
    constexpr uint8_t kPwmPin = 9;
    constexpr uint8_t kPotPin = A0;
    constexpr uint8_t kModePin = 2;
    constexpr int kMotorOffPulseUs = 1000;
    constexpr int kMinCommandPulseUs = 1000;
    constexpr int kMaxCommandPulseUs = 2000;
} // namespace

Servo pwmServo;

void setup() {
#if DEBUG
    Serial.begin(9600);
#endif
    // Set mode pin to INPUT.
    // The motor/potentiometer mode will be active when the pin is LOW.
    pinMode(kModePin, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pwmServo.attach(kPwmPin, kMinCommandPulseUs, kMaxCommandPulseUs);

    pwmServo.writeMicroseconds(kMotorOffPulseUs);
#if DEBUG
    Serial.println("Motor Driver Initialized");
#endif
}

void loop() {
    const bool use_pot = digitalRead(kModePin) == HIGH;
    digitalWrite(LED_BUILTIN, use_pot ? HIGH : LOW);
    if (use_pot) {
        const int pot_value = analogRead(kPotPin);
        const int pulse_us = map(pot_value, 0, 1023, kMinCommandPulseUs, kMaxCommandPulseUs);
        pwmServo.writeMicroseconds(pulse_us);
#if DEBUG
        Serial.print("Mode: Potentiometer, Pulse: ");
        Serial.print(pulse_us);
        Serial.println(" us");
#endif
    } else {
        pwmServo.writeMicroseconds(kMotorOffPulseUs);
#if DEBUG
        Serial.println("Mode: Fixed (Off)");
#endif
    }

    delay(15);
}
