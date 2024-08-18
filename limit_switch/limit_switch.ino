const int limitSwitchPin = 6; // Pin waar de limit switch is aangesloten
const int ledPin = 13;        // Interne LED pin voor indicatie

void setup() {
  // Zet de limit switch pin als input met een interne pull-up weerstand
  pinMode(limitSwitchPin, INPUT_PULLUP);
  
  // Zet de LED pin als output
  pinMode(ledPin, OUTPUT);
  
  // Start de seriële communicatie
  Serial.begin(9600);
}

void loop() {
  // Lees de status van de limit switch
  int switchState = digitalRead(limitSwitchPin);
  
  // Check de status van de limit switch
  if (switchState == LOW) { // Limit switch is ingedrukt (gesloten)
    Serial.println("SW1 is INGEDRUKT");
    digitalWrite(ledPin, HIGH); // Zet de LED aan
  } else { // Limit switch is niet ingedrukt (open)
    Serial.println("SW1 is NIET INGEDRUKT");
    digitalWrite(ledPin, LOW); // Zet de LED uit
  }
  
  // Kleine vertraging om het overstromen van de seriële monitor te voorkomen
  delay(200);
}
