#include <Arduino.h>
#include <Servo.h>

namespace {
constexpr uint8_t kPwmPin = 9;
constexpr uint8_t kPotPin = A0;
constexpr uint8_t kModePin = 2;
constexpr uint16_t kMotorOffPulseUs = 1000;
constexpr uint16_t kMinCommandPulseUs = 1000;
constexpr uint16_t kMaxCommandPulseUs = 2000;
}  // namespace

Servo pwmServo;

void setup() {
  pinMode(kModePin, INPUT);
  pwmServo.attach(kPwmPin);

  pwmServo.writeMicroseconds(kMotorOffPulseUs);
}

void loop() {
  const bool use_pot = (digitalRead(kModePin) == HIGH);
  if (use_pot) {
    const int pot_value = analogRead(kPotPin);
    const uint16_t pulse_us = kMinCommandPulseUs +
                              (static_cast<uint32_t>(pot_value) *
                               (kMaxCommandPulseUs - kMinCommandPulseUs)) /
                                  1023;
    pwmServo.writeMicroseconds(pulse_us);
  } else {
    pwmServo.writeMicroseconds(kMotorOffPulseUs);
  }

  delay(10);
}
