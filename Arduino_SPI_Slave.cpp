#include <SPI.h>

volatile uint8_t i = 0;
volatile byte txData[] = {0x12, 0x34, 0x56};

const int slaveSelectPin = 10;

void setup ()
{
  Serial.begin(115200);
  Serial.print(F(__TIME__ "\t" __DATE__ "\n\r" __FILE__));  delay(1);
  // set the slaveSelectPin as an output:
  //  pinMode(slaveSelectPin, INPUT_PULLUP);
  pinMode(slaveSelectPin, INPUT); // ensure SS stays high for now
  pinMode(MISO, OUTPUT); //must do
  pinMode(MOSI, INPUT); //always do
  pinMode(SCK, INPUT); //always do
  bitSet(SPCR, SPE); //SPI Port is enabled
  bitClear(SPCR, MSTR); //Arduino is Slave
  SPI.attachInterrupt(); //interrupt logic is enabled
}

ISR(SPI_STC_vect)
{
	rxData[i] = SPDR;
	i++;
}

void sPrint()
{	
  Serial.println(F("\n\rreceived Data...")); delay(1);
  for(uint8_t x=0; x<i; x++) {
    Serial.print(rxData[x], HEX); Serial.print(' '); delay(1);
  }
  i = 0; //array pointer is reset
}

void loop()
{
  if (i >= 2)	{
    sPrint();
  }
}


