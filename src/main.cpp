

/*
  Titre      : Titre du programme
  Auteur     : Duvalier Tsagmo
  Date       : 16/03/2022
  Description: Une description du programme
  Version    : 0.0.1
*/

#include <wifi101.h>
#include "MQTTConnector.h"
#include <Arduino.h>

#define pinDuRelai 6
#define pinDePompe 5

const int delai = 1500;

bool StatutCapteur = 0;
bool StatutpinDePompe = 0;

void ecoute()
{

    digitalWrite(pinDuRelai, HIGH);

    StatutpinDePompe = digitalRead(pinDePompe);
    StatutCapteur = digitalRead(pinDuRelai);

    appendPayload("Capteur", StatutCapteur);
    appendPayload("Pompe", StatutpinDePompe);
    sendPayload();

    delay(delai);
}

void setup()
{
    Serial.begin(9600);

    wifiConnect(); // Branchement au réseau WIFI
    MQTTConnect(); // Branchement au broker MQTT

    pinMode(pinDePompe, INPUT);
    pinMode(pinDuRelai, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(pinDePompe), ecoute, HIGH);
}

void loop()
{

    digitalWrite(pinDuRelai, LOW);

    StatutpinDePompe = digitalRead(pinDePompe);

    StatutCapteur = digitalRead(pinDuRelai);

    appendPayload("Capteur", StatutCapteur);
    appendPayload("Pompe", StatutpinDePompe);

    sendPayload();
    delay(delai);
}