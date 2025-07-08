
//#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <FirebaseESP32.h>
#include <Firebase_ESP_Client.h>
//#include <FirebaseESP32HTTPClient.h>
//#include <Firebase_ESP_Loader.h>
#include <WiFi.h>


// Configuration Wi-Fi
#define WIFI_SSID "El FabSpace Lac"
#define WIFI_PASSWORD "Think_Make_Share"

// Configuration Firebase Realtime DB
#define FIREBASE_HOST "https://noeud1-default-rtdb.europe-west1.firebasedatabase.app/"
#define FIREBASE_AUTH "	hixgxpHDhu2FApyuAUEx7kYMC8xcTMqI7qfyrHXj"

// Configuration du capteur DHT11
#define DHT_PIN 14 // Broche de données connectée au DHT11
#define DHT_TYPE DHT11

// Seuils pour la température et l'humidité
#define SEUIL_TEMP 30.0
#define SEUIL_HUMIDITE 50.0

// Broches pour les LEDs
#define LED_TEMP 33 // Broche pour la LED liée à la température
#define LED_HUMIDITE 32 // Broche pour la LED liée à l'humidité

// Création des objets
DHT dht(DHT_PIN, DHT_TYPE);
FirebaseData firebaseData;

// Tâche 1 : Lire les valeurs de température et d'humidité et les envoyer à Firebase
void taskFirebase(void *pvParameters) {
  while (1) {
    float temp = dht.readTemperature();
    float humidite = dht.readHumidity();

    Serial.print("Température: ");
    Serial.println(temp);
    Serial.print("Humidité: ");
    Serial.println(humidite);

    // Envoi des données à Firebase Realtime DB
    Firebase.pushFloat(firebaseData, "/temperature", temp);
    Firebase.pushFloat(firebaseData, "/humidite", humidite);

    delay(5000); // Attente de 5 secondes entre chaque envoi de données
  }
}

// Tâche 2 : Comparer les valeurs avec les seuils et allumer les LEDs en conséquence
void taskLED(void *pvParameters) {
  while (1) {
    float temp = dht.readTemperature();
    float humidite = dht.readHumidity();

    // Comparaison avec les seuils
    if (temp > SEUIL_TEMP) {
      digitalWrite(LED_TEMP, HIGH); // Allumer la LED liée à la température
    } else {
      digitalWrite(LED_TEMP, LOW); // Éteindre la LED liée à la température
    }

    if (humidite > SEUIL_HUMIDITE) {
      digitalWrite(LED_HUMIDITE, HIGH); // Allumer la LED liée à l'humidité
    } else {
      digitalWrite(LED_HUMIDITE, LOW); // Éteindre la LED liée à l'humidité
    }

    delay(1000); // Attente de 1 seconde entre chaque comparaison
  }
}

void setup() {
  Serial.begin(115200);

  // Connexion au réseau Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au Wi-Fi en cours...");
  }
  Serial.println("Connecté au Wi-Fi");

  // Initialisation des broches pour les LEDs
  pinMode(LED_TEMP, OUTPUT);
  pinMode(LED_HUMIDITE, OUTPUT);

  // Initialisation du capteur DHT11
  dht.begin();

  // Tâche 1 : Lire les valeurs de température et d'humidité et les envoyer à Firebase
  xTaskCreatePinnedToCore(taskFirebase, "TaskFirebase", 10000, NULL, 1, NULL, 1);

  // Tâche 2 : Comparer les valeurs avec les seuils et allumer les LEDs en conséquence
  xTaskCreatePinnedToCore(taskLED, "TaskLED", 10000, NULL, 2, NULL, 1);
}

void loop() {
  // La fonction loop() doit rester vide pour permettre l'exécution des tâches
}
