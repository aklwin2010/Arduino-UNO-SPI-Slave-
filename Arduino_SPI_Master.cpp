#include <SPI.h>

// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;

void setup ()
{
  Serial.begin(115200);
  Serial.print(F(__TIME__ "\t" __DATE__ "\n\r" __FILE__));  delay(1);
  // set the slaveSelectPin as an output:
  pinMode(slaveSelectPin, OUTPUT);
  SPI.begin(); //default speed: 4 MHz
  SPI.setClockDivider(SPI_CLOCK_DIV8);  // SPI_CLOCK_DIV128 [bit rate = 16 MHz/128 = 125 kbit/sec]
  digitalWrite(slaveSelectPin, HIGH);  delay(10);
}


void loop()
{
  digitalWrite(slaveSelectPin, LOW); //delayMicroseconds(10);//Slave is selected
  SPI.transfer(0x12); delay(10);
  SPI.transfer(0x34); delay(10);
  digitalWrite(slaveSelectPin, HIGH); //delay(500);//Slave is selected
  delay(500);
}


