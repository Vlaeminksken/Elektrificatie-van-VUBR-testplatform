#include <Stepper.h>

// Defineer de pinnen voor de stappenmotor
#define PUL_PIN_PLUS 9
#define PUL_PIN_MINUS 8
#define DIR_PIN_PLUS 7
#define DIR_PIN_MINUS 6

// Configureer de stappenmotor parameters
const int stepsPerRevolution = 100; // Aantal stappen per omwenteling van de motor
Stepper myStepper(stepsPerRevolution, PUL_PIN_PLUS, PUL_PIN_MINUS, DIR_PIN_PLUS, DIR_PIN_MINUS);

bool isClockwise = true; // Variabele om de draairichting bij te houden

void setup() {
  // Stel de snelheid van de stappenmotor in (in stappen per seconde)
  myStepper.setSpeed(200); // Stel de snelheid in naar wens
  
  // Start de seriële communicatie
  Serial.begin(9600);
}

void loop() {
  // Draai de stappenmotor in de huidige richting
  if (isClockwise) {
    myStepper.step(stepsPerRevolution);
    // Maak een volledige omwenteling in de voorwaartse richting
  } else {
    myStepper.step(stepsPerRevolution); 
    // Maak een volledige omwenteling in de achterwaartse richting
  }

  // Controleer of er iets in de seriële monitor is ingevoerd
  if (Serial.available() > 0) {
    char input = Serial.read(); // Lees de ingevoerde karakter
    
    // Als 's' wordt ingevoerd, verander de draairichting van de motor
    if (input == 's') {
      isClockwise = !isClockwise; // Omkeren van de draairichting
    }
  }
}
