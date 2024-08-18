#include <SPI.h>
#include <LoRa.h>

// Define the pins used by the transceiver module
#define ss 10   // RFM95 NSS
#define rst 9   // RFM95 RFM_RST
#define dio0 2  // RFM95 DIO5

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

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
  
  // Change sync word (0xF3) to match the transmitter
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
     // Read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.println();

    
  }
}
