#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SPI.h>
#include <LoRa.h>

const int analogPin = A7; // De analoge pin waar de spanningsdeler is aangesloten
const float Vcc = 5.0; // Referentiespanning van de Arduino (5V)
const float R1 = 10000.0; // Weerstand R1 in ohm (10kΩ)
const float R2 = 22000.0; // Weerstand R2 in ohm (22kΩ)

// Initialiseer het LCD-scherm met het I2C-adres 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Lora gedeelte
#define ss 10   // RFM95 NSS
#define rst 9   // RFM95 RFM_RST
#define dio0 2  // RFM95 DIO5
#define knop 4 //switch

void setup() {
  // Start de seriële communicatie
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  LoRa.setPins(ss, rst, dio0);
    while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  pinMode(knop, INPUT_PULLUP);
  
  // Initialiseer het LCD-scherm
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("LoRa verbonden");
  lcd.setCursor(0, 1);
  lcd.print("");
  delay(500);  
}

void SpanningMeter(){  
  // Lees de analoge waarde van de spanningsdeler
  int analogValue = analogRead(analogPin);
  // Bereken de spanning op de analoge pin (0-5V)
  float voltage = analogValue * (Vcc / 1023.0);
  // Bereken de oorspronkelijke spanning (voor de spanningsdeler)
  float actualVoltage = voltage * ((R1 + R2) / R1);
    // Print de gemeten spanning naar het LCD-scherm
  lcd.setCursor(0, 1);
  lcd.print("Voltage: ");
  lcd.print(actualVoltage);
  lcd.print(" V ");

  
}

void loop() {

    if (digitalRead(knop) == 1){
    Serial.println("stopt jong");
    LoRa.beginPacket();
    LoRa.print("stop");
    LoRa.endPacket();
    lcd.setCursor(0, 0);
    lcd.print("stand: stop");
    SpanningMeter();
    
  }
  else {
    Serial.println("goat jong");
    LoRa.beginPacket();
    LoRa.print("go");
    LoRa.endPacket();
    lcd.setCursor(0, 0);
    lcd.print("stand: go       ");
    SpanningMeter();
  }
  delay(500);
  
  
}
