#include <SPI.h>
#include <MFRC522.h>

// Define pins for the laser modules and photodiodes
int photodiodePin1 = A4; // First photodiode pin
int photodiodePin2 = A5; // Second photodiode pin
int relayPin = 8; // Relay module pin for controlling the bulb

int count = 0; // Count of people entered or exited
bool beam1Broken = false; // Status of first beam
bool beam2Broken = false; // Status of second beam
bool peoplePresent = false; // Flag to indicate if people are inside

unsigned long beam1Time = 0; // Time when first beam was broken
unsigned long beam2Time = 0; // Time when second beam was broken
unsigned long peoplePresentStart = 0; // Start time when people are present
unsigned long totalPeoplePresentTime = 0; // Total time in milliseconds the bulb was on
float totalEnergyConsumed = 0.0; // Total energy consumed by the bulb in Watt-hours

// Ensure you have defined a threshold based on your setup
int threshold = 500; // Example threshold, adjust based on your setup and readings

void setup() {
  pinMode(photodiodePin1, INPUT);
  pinMode(photodiodePin2, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Initially, turn off the bulb

  Serial.begin(9600); // Initialize serial communication at 9600 bits per second
}

void loop() {
  int beamStatus1 = analogRead(photodiodePin1);
  int beamStatus2 = analogRead(photodiodePin2);

  if (beamStatus1 < threshold && !beam1Broken) {
    beam1Broken = true;
    beam1Time = millis();
  }

  if (beamStatus2 < threshold && !beam2Broken) {
    beam2Broken = true;
    beam2Time = millis();
  }

  if (beam1Broken && beam2Broken) {
    if (beam1Time < beam2Time) {
      if (count == 0 && !peoplePresent) {
        peoplePresent = true;
        peoplePresentStart = millis(); // Start time when first person enters
      }
      count++;
      Serial.println("Person entered.");
    } else if (beam1Time > beam2Time) {
      if (count > 0) {
        count--;
        Serial.println("Person exited.");
      }
      // Inside the if condition where you determine people have exited and no one is left
      if (count == 0 && peoplePresent) {
          peoplePresent = false;
          unsigned long peoplePresentDuration = millis() - peoplePresentStart;
          totalPeoplePresentTime += peoplePresentDuration;
          float energyConsumed = 6.0 * (peoplePresentDuration / 3600000.0); // Assuming a 6W bulb
          totalEnergyConsumed += energyConsumed;

          Serial.print("Time On: ");
          Serial.print(totalPeoplePresentTime / 1000);
          Serial.print(" s, Energy Consumed: ");
          Serial.println(totalEnergyConsumed);
          peoplePresentStart = 0;
      }

// You can similarly format other Serial.print statements if needed
    }

    digitalWrite(relayPin, (count > 0) ? HIGH : LOW);

    if (count > 0) {
      // Update the energy consumed continuously while the bulb is on
      unsigned long currentTime = millis();
      unsigned long currentSessionDuration = currentTime - peoplePresentStart;
      float currentSessionEnergy = 6.0 * (currentSessionDuration / 3600000.0);
      Serial.print("Current Energy Consumed (Wh): ");
      Serial.println(totalEnergyConsumed + currentSessionEnergy);
    }

    Serial.print("Current Count: ");
    Serial.println(count);

    delay(1000); // Avoid immediate re-triggering
    beam1Broken = false;
    beam2Broken = false;
  }

  if (beamStatus1 >= threshold && beam1Broken) {
    beam1Broken = false;
  }
  if (beamStatus2 >= threshold && beam2Broken) {
    beam2Broken = false;
  }
}

