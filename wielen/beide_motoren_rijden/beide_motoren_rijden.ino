 
#include <ODriveUART.h>
#include <SoftwareSerial.h>

SoftwareSerial left_odrive_serial(3, 2);
SoftwareSerial right_odrive_serial(5, 4);
int baudrate = 19200; // Must match what you configure on the ODrive (see docs for details)


ODriveUART left_odrive(left_odrive_serial);
ODriveUART right_odrive(right_odrive_serial);

float velocity = 2.0;

void init_odrive(SoftwareSerial* odrive_serial, ODriveUART* odrive, int baudrate) {
  odrive_serial->begin(baudrate);

  // Connecting to ODrive
  while (odrive->getState() == AXIS_STATE_UNDEFINED) {
    delay(100);
  }

  // Enabling closed loop control
  while (odrive->getState() != AXIS_STATE_CLOSED_LOOP_CONTROL) {
    odrive->clearErrors();
    odrive->setState(AXIS_STATE_CLOSED_LOOP_CONTROL);
    delay(10);
  }
}


void setup() {
  Serial.begin(115200); // Serial to PC

  init_odrive(&left_odrive_serial, &left_odrive, baudrate);
  init_odrive(&right_odrive_serial, &right_odrive, baudrate);

}

void loop() {
  
  
  left_odrive.setVelocity(velocity);
  right_odrive.setVelocity(-velocity);

}
