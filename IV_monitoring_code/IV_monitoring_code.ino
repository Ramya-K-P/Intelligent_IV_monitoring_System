#include "HX711.h"

#define DT  3
#define SCK 2
#define BUZZER_PIN 7

HX711 scale;

float thresholdWeight = 50.0;  // Threshold weight in grams

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);
  scale.set_scale(170.91);    // Use calibration factor here if available
  scale.tare();         // Set current weight as 0

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("System Initializing... Waiting for 30 seconds...");
  delay(30000);  // Wait for 30 seconds before starting monitoring
  Serial.println("Monitoring started...");
}

void loop() {
  float weight = scale.get_units();

  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");

  if (weight < thresholdWeight) {
    digitalWrite(BUZZER_PIN, HIGH);  // Turn ON buzzer
    Serial.println("Alert: IV fluid low!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);   // Turn OFF buzzer
  }

  delay(1000);  // Check every 1 second
}
