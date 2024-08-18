#include <ODriveUART.h>
#include <ODriveCAN.h>

#include <VescUart.h>

/** Initiate VescUart class */
VescUart UART1;


void setup() {
  // Setup Serial port to display data
  Serial.begin(9600);
  while(!Serial); // wait for Serial to connect

  // Setup UART port for Raspberry Pi Pico W
  // Voor de Pico, Serial1 gebruikt standaard UART0 op pinnen 0 (RX) en 1 (TX) 
  // of een andere vooraf gedefinieerde set afhankelijk van je borddefinities.
  // Controleer de documentatie voor de specifieke pinout.
  Serial1.begin(9600); // Je kunt hier alleen de baudrate specificeren.
  
  Serial.println("Connecting to VESC with UART1");
  while (!Serial1) {;}
  Serial.println("Connected to VESC on UART1");

  // Define which ports to use as UART
  UART1.setSerialPort(&Serial1);
}

void loop() {
  // Call the function getVescValues() to acquire data from VESC
  if (UART1.getVescValues()) {
    Serial.print("RPM:\t\t");
    Serial.println(UART1.data.rpm);
    Serial.print("Vin:\t\t");
    Serial.println(UART1.data.inpVoltage);
    Serial.print("A:\t\t");
    Serial.println(UART1.data.ampHours);
    Serial.print("Tachometer:\t");
    Serial.println(UART1.data.tachometerAbs);
    Serial.println();
  }

  
  UART1.setDuty(0.2);
  //UART1.setCurrent(3.0);
  //UART1.setRPM(100.0);

  delay(50);

  


}
