#include <SPI.h>
#include <LoRa.h>

// Define the pins used by the transceiver module
#define ss 10   // RFM95 NSS
#define rst 9   // RFM95 RFM_RST
#define dio0 2  // RFM95 DIO5

int counter = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  // Replace the LoRa.begin(---E-) argument with your location's frequency 
  // 433E6 for Asia
  // 866E6 for Europe
  // 915E6 for North America
  // 865E6 -867E6 For India
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(500);
}
