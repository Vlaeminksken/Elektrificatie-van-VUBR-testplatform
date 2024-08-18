#include <SPI.h>
#include <LoRa.h>

// Define the pins used by the transceiver module
#define ss 10   // RFM95 NSS
#define rst 9   // RFM95 RFM_RST
#define dio0 2  // RFM95 DIO5
#define controlPin 3 // Define the control pin

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Receiver");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  
  // Change sync word (0xF3) to match the transmitter
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  // Set control pin as output
  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW); // Ensure it's initially low
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: ");
    
    // Buffer to hold the incoming message
    String receivedText = "";

    // Read packet
    while (LoRa.available()) {
      receivedText += (char)LoRa.read();
    }

    // Print the received message
    Serial.println(receivedText);

    // Check the received message
    if (receivedText == "go") {
      digitalWrite(controlPin, HIGH);
      Serial.println("Pin D3 set to HIGH");
    } else if (receivedText == "stop") {
      digitalWrite(controlPin, LOW);
      Serial.println("Pin D3 set to LOW");
    }
  }
}
