#include <Stepper.h>

// Defineer de pinnen voor de stappenmotor
#define PUL_PIN_PLUS 9
#define PUL_PIN_MINUS 8
#define DIR_PIN_PLUS 7
#define DIR_PIN_MINUS 6

// Definieer de pinnen voor de limietschakelaars
#define LIMIT_SWITCH_PIN_10 10
#define LIMIT_SWITCH_PIN_11 11

const int stepsPerRevolution = 100; // Aantal stappen per omwenteling van de motor
Stepper myStepper(stepsPerRevolution, PUL_PIN_PLUS, PUL_PIN_MINUS, DIR_PIN_PLUS, DIR_PIN_MINUS);

int stepCount = 0; // Tel het aantal stappen
int stepsToMiddle = 0; // Aantal stappen naar het midden

void setup() {
  // Stel de pinnen van de limietschakelaars in als input
  pinMode(LIMIT_SWITCH_PIN_10, INPUT_PULLUP);
  pinMode(LIMIT_SWITCH_PIN_11, INPUT_PULLUP);

  // Stel de snelheid van de stappenmotor in (in RPM)
  myStepper.setSpeed(60);

  // Start seriële communicatie
  Serial.begin(9600);
}

void loop() {
  // Draai de motor naar links totdat hij de limietschakelaar op pin 10 raakt
  while (digitalRead(LIMIT_SWITCH_PIN_10) == HIGH) {
    myStepper.step(-1); // Draai naar links
    stepCount++;
    delay(10); // Kleine vertraging voor stabiliteit
  }

  Serial.println("Limit switch 10: TOUCHED");

  // Draai de motor naar rechts totdat hij de limietschakelaar op pin 11 raakt
  while (digitalRead(LIMIT_SWITCH_PIN_11) == HIGH) {
    myStepper.step(1); // Draai naar rechts
    stepCount++;
    delay(10); // Kleine vertraging voor stabiliteit
  }

  Serial.println("Limit switch 11: TOUCHED");

  // Bereken het midden tussen de twee limietschakelaars
  stepsToMiddle = stepCount / 2;

  Serial.print("Steps to middle: ");
  Serial.println(stepsToMiddle);

  // Draai de motor naar het midden
  for (int i = 0; i < stepsToMiddle; i++) {
    myStepper.step(-1); // Draai naar links
    delay(10); // Kleine vertraging voor stabiliteit
  }

  Serial.println("Motor is in the middle. Stopping motor.");

  // Stop de motor
  while (true) {
    // Doe niets, motor blijft in het midden
  }
}
