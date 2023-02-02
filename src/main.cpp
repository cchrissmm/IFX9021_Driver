#include <SPI.h>
#include <Arduino.h>

const int spiClk = 1000000; // SPI clock speed in Hz

SPIClass hspi;
SPIClass vspi;

#define HSPI_CS 15
#define HSPI_MOSI 13
#define HSPI_MISO 12
#define HSPI_SCK 14

byte spiCommand(SPIClass &spi, byte data, int CS)
{
    spi.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(SS, LOW); // assume SS pin is connected to digital pin 10
    byte spiResponse = spi.transfer(data);
    digitalWrite(SS, HIGH);
    spi.endTransaction();
    return spiResponse;
}

void setup()
{
    Serial.begin(115200);
    hspi.begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, HSPI_CS);
    //hspi.begin();
    pinMode(HSPI_CS, OUTPUT);
}

void loop()
{
    byte data = 0x12;
    byte response = spiCommand(hspi, data, HSPI_CS);
    Serial.print("spi response: ");
    Serial.println(response, BIN);
    delay(100);
}