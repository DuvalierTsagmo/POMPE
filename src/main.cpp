

/*
  Titre      : Titre du programme
  Auteur     : Duvalier Tsagmo
  Date       : 16/03/2022
  Description: Une description du programme
  Version    : 0.0.1
*/

#include <Arduino.h>
#include "WIFIConnector_MKR1010.h"
#include "MQTTConnector.h"

void EtatDeLaPompe();

const int RELAI = 1;
const int PinSensor = 5;

unsigned long Delai = 10000; // On envoie les données toutes les 10s
unsigned long TempsEnCours = 0;
int ValeurSensor = 0;
bool Pompe = false;

void setup()
{
    Serial.begin(9600);
    // Initialisation du wifi.
    wifiConnect(); // Branchement au réseau WIFI
    MQTTConnect(); // Branchement au broker MQTT
    pinMode(RELAI, OUTPUT);
    pinMode(PinSensor, INPUT);
    attachInterrupt(digitalPinToInterrupt(PinSensor), EtatDeLaPompe, CHANGE);
}

void loop()
{
    if (Pompe)
    {
        digitalWrite(RELAI, HIGH);
        Pompe = true;
    }
    else
    {
        digitalWrite(RELAI, LOW);
        Pompe = false;
    }

    if (millis() - TempsEnCours > Delai)
    {
        appendPayload("Pompe", Pompe);
        appendPayload("ValeurSensor", ValeurSensor);
        sendPayload();
        TempsEnCours = millis();
    }
}

void EtatDeLaPompe()
{
    Pompe = !Pompe;
}