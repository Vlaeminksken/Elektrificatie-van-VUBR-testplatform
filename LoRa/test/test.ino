#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins used by the transceiver module
#define ss 10   // RFM95 NSS
#define rst 9   // RFM95 RFM_RST
#define dio0 2  // RFM95 DIO5

// Define button pins
#define buttonPin1 7  // Button connected to D7
#define buttonPin2 6  // Button connected to D6

// Initialize the LCD on address 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  // Setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(866E6)) {
    Serial.print(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  // Initialize LCD
  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("LoRa Initializing");
  lcd.setCursor(0, 1);
  lcd.print("Please wait...");

  // Initialize buttons as input with internal pull-up
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  delay(2000);  // Wait a bit before clearing the screen
  lcd.clear();
  lcd.print("Ready to send");
  lcd.setCursor(0, 1);
  lcd.print("Press a button");
}

void loop() {
  // Read the button state
  if (digitalRead(buttonPin1) == LOW) {
    // Display on LCD
    lcd.clear();
    lcd.print("Sending:");
    lcd.setCursor(0, 1);
    lcd.print("red");

    // Send a message via LoRa
    LoRa.beginPacket();
    LoRa.print("rood");
    LoRa.endPacket();

    Serial.println("Message sent: red");
    delay(2000);  // Provide time for reading the message
    lcd.clear();
    lcd.print("Ready to send");
    lcd.setCursor(0, 1);
    lcd.print("Press a button");
  }
  if (digitalRead(buttonPin2) == LOW) {
    // Display on LCD
    lcd.clear();
    lcd.print("Sending:");
    lcd.setCursor(0, 1);
    lcd.print("green");

    // Send a message via LoRa
    LoRa.beginPacket();
    LoRa.print("groen");
    LoRa.endPacket();

    Serial.println("Message sent: green");
    delay(2000);  // Provide time for reading the message
    lcd.clear();
    lcd.print("Ready to send");
    lcd.setCursor(0, 1);
    lcd.print("Press a button");
  }
  delay(10);  // Short delay to stabilize button input
}
