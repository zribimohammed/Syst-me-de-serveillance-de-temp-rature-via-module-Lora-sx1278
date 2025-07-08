#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>

#define LORA_SS_PIN 10       // Broche SS pour le module LoRa
#define LORA_RST_PIN 9       // Broche de réinitialisation pour le module LoRa
#define LORA_DI0_PIN 2       // Broche DIO0 pour le module LoRa
#define BUZZER_PIN 5        // Broche pour contrôler le buzzer

void setup() {
  Serial.begin(9600);

  // Initialisation du module LoRa
  LoRa.setPins(LORA_SS_PIN, LORA_RST_PIN, LORA_DI0_PIN);
  if (!LoRa.begin(433E6)) {
    Serial.println("Erreur d'initialisation du module LoRa !");
    while (1);
  }

  // Configuration de la broche du buzzer en sortie
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  if (LoRa.parsePacket()) {
    // Lecture de la valeur de température reçue via LoRa
    float temperature = LoRa.parseFloat();

    Serial.print("Température reçue : ");
    Serial.print(temperature);
    Serial.println(" °C");

    // Vérification si la température dépasse 35°C
    if (temperature >35.0) {
      // Mettre en marche le buzzer
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.println("Buzzer en marche !");
    } else {
      // Arrêter le buzzer
      digitalWrite(BUZZER_PIN, LOW);
      Serial.println("Buzzer arrêté.");
    }
  }
}
