#include <ODriveUART.h>
#include <SoftwareSerial.h>

SoftwareSerial left_odrive_serial(3, 2);
SoftwareSerial right_odrive_serial(5, 4);
int baudrate = 19200; // Moet overeenkomen met de configuratie op de ODrive

ODriveUART left_odrive(left_odrive_serial);
ODriveUART right_odrive(right_odrive_serial);

float velocity = 1.0;
unsigned long last_print = 0;
bool print_left = true;

void init_odrive(SoftwareSerial* odrive_serial, ODriveUART* odrive, int baudrate) {
  odrive_serial->begin(baudrate);
  
  // Verbinding maken met ODrive
  while (odrive->getState() == AXIS_STATE_UNDEFINED) {
    delay(100);
  }

  // Closed loop control inschakelen
  while (odrive->getState() != AXIS_STATE_CLOSED_LOOP_CONTROL) {
    odrive->clearErrors();
    odrive->setState(AXIS_STATE_CLOSED_LOOP_CONTROL);
    delay(10);
  }

  // Reset positie
  odrive->setPosition(0);
}

void setup() {
  Serial.begin(115200); // Seriële communicatie naar PC

  init_odrive(&left_odrive_serial, &left_odrive, baudrate);
  init_odrive(&right_odrive_serial, &right_odrive, baudrate);
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'g') {
      // Zet beide motoren in beweging vooruit
      left_odrive.setVelocity(velocity);
      right_odrive.setVelocity(-velocity); // Vooruit met de juiste oriëntatie
      Serial.println("Vooruit");
    }

    if (command == 's') {
      // Stop beide motoren
      left_odrive.setVelocity(0);
      right_odrive.setVelocity(0);
      left_odrive.setState(AXIS_STATE_IDLE);
      right_odrive.setState(AXIS_STATE_IDLE);
      Serial.println("Stoppen");
    }
  }

  // Print de positie van de motoren om de 500ms
  if (millis() - last_print > 500) {
    if (print_left) {
      Serial.print("Linker motor positie: ");
      Serial.println(left_odrive.getPosition());
    } else {
      Serial.print("Rechter motor positie: ");
      Serial.println(right_odrive.getPosition());
    }
    print_left = !print_left;
    last_print = millis();
  }
}
