# Projet LoRa + ESP32 avec DHT11 et Firebase

Ce projet Arduino/ESP32 utilise un module LoRa pour recevoir des données de température et déclencher un buzzer en cas de dépassement de seuil.

L'ESP32 transmet aussi des données du capteur DHT11 vers Firebase Realtime Database et commande des LEDs selon les seuils.

## Matériel utilisé
- Module LoRa 433 MHz
- ESP32
- Capteur DHT11
- Buzzer
- LEDs

## Fonctionnalités
- Réception LoRa et déclenchement buzzer
- Envoi WiFi des données vers Firebase
- Contrôle des LEDs selon seuils température et humidité

## Installation
- Configurer le WiFi dans `WIFI_SSID` et `WIFI_PASSWORD`
- Configurer Firebase dans `FIREBASE_HOST` et `FIREBASE_AUTH`
- Télécharger les bibliothèques nécessaires dans Arduino IDE

## Auteurs
- Mohammed Zribi

