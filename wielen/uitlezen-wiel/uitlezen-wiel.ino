#include <VescUart.h>
#include <SoftwareSerial.h>

const int RX_PIN = 2; // Verbind deze pin met TX van de VESC
const int TX_PIN = 3; // Verbind deze pin met RX van de VESC

SoftwareSerial mySerial (RX_PIN, TX_PIN);

/** Initiate VescUart class */
VescUart UART1;


void setup() {
  // Setup Serial port to display data
  Serial.begin(9600);

  // Setup UART port for Raspberry Pi Pico W
  // Voor de Pico, Serial1 gebruikt standaard UART0 op pinnen 0 (RX) en 1 (TX) 
  // of een andere vooraf gedefinieerde set afhankelijk van je borddefinities.
  // Controleer de documentatie voor de specifieke pinout.
  mySerial.begin(115200); // Je kunt hier alleen de baudrate specificeren.
  
  while (!mySerial) {;}

  // Define which ports to use as UART
  UART1.setSerialPort(&mySerial);
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

  
  //UART1.setDuty(0.2);
  //UART1.setCurrent(3.0);
  //UART1.setRPM(100.0);

  delay(50);

  

}
