#include <Wire.h>
#include <ArduinoJson.h>

#define I2C_ADDRESS 0x08

#define START_TRIGGER_PIN 2
#define SP_L1 5
#define SP_R1 6
#define SP_L2 10
#define SP_R2 9

unsigned long onset = 0;
unsigned long offset = 0;
int channel;
int activePin = -1;
bool stimulusReady = false;
bool trialRunning = false;
unsigned long trialStartTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_ADDRESS);
  Wire.onReceive(receiveEvent);

  pinMode(START_TRIGGER_PIN, INPUT);
  pinMode(SP_L1, OUTPUT);
  pinMode(SP_R1, OUTPUT);
  pinMode(SP_L2, OUTPUT);
  pinMode(SP_R2, OUTPUT);

  digitalWrite(SP_L1, LOW);
  digitalWrite(SP_R1, LOW);
  digitalWrite(SP_L2, LOW);
  digitalWrite(SP_R2, LOW);

  Serial.println("Arduino I2C Audio Slave pronto");
}

void loop() {
  if (!trialRunning && digitalRead(START_TRIGGER_PIN) == HIGH && stimulusReady) {
    trialRunning = true;
    trialStartTime = micros();
    Serial.println("Trigger ricevuto: inizio cronometro");
  }

  if (trialRunning) {
    unsigned long elapsed = micros() - trialStartTime;

    if (elapsed >= onset * 1000 && elapsed < offset * 1000) {
      int pwmValue = (rand() % 2);
      digitalWrite(activePin, pwmValue);
    } else if (elapsed >= offset * 1000) {
      digitalWrite(activePin, LOW);
      trialRunning = false;
      stimulusReady = false;
      Serial.println("Stimolo terminato");
    }
  }
}

void receiveEvent(int howMany) {
  String json = "";
  while (Wire.available()) {
    char c = Wire.read();
    json += c;
  }

  if (Serial) {
    Serial.print("Raw I2C JSON: ");
    Serial.println(json);
  }

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) {
    Serial.print("Errore JSON: ");
    Serial.println(error.c_str());
    return;
  }

  onset = doc["ON"] | 0;
  offset = doc["OFF"] | 0;
  channel = doc["C"] | 0;

  switch(channel) {
    case 6:
      activePin = SP_L1; break;
    case 26:
      activePin = SP_R1; break;
    case 7:
      activePin = SP_R2; break;
    case 25:
      activePin = SP_L2; break;
    default: activePin = -1;
    
  }

  if (activePin != -1) {
    stimulusReady = true;
    Serial.print("→ Stimolo ricevuto: Speaker=");
    Serial.print(channel);
    Serial.print(" | ON=");
    Serial.print(onset);
    Serial.print(" | OFF=");
    Serial.println(offset);
  } else {
    Serial.println("Errore: speaker non riconosciuto");
  }
}
