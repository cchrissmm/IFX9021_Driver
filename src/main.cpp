#include <SPI.h>
#include <Arduino.h>

const int spiClk = 1000000; // SPI clock speed in Hz

SPIClass hspi;
SPIClass vspi;

#define HSPI_CS 15
#define HSPI_MOSI 13
#define HSPI_MISO 12
#define HSPI_SCK 14

#define READ_DIA 0b00000000
#define READ_REV 0b00100000

byte spiCommand(SPIClass &spi, byte data, int CS)
{
    spi.beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW); 
    byte spiResponse = spi.transfer(data);
    digitalWrite(CS, HIGH);
    spi.endTransaction();
    return spiResponse;
}

void serialRX()
{
    if (Serial.available())
    {
        String str = Serial.readStringUntil('\n');

        if (str.startsWith("READDIA"))
        {
            byte response = spiCommand(hspi, READ_DIA, HSPI_CS);
            Serial.print("spi response: ");
            Serial.println(response, BIN);
        }
        if (str.startsWith("READREV"))
        {
            byte response = spiCommand(hspi, READ_REV, HSPI_CS);
            Serial.print("spi response: ");
            Serial.println(response, BIN);
        }
    }
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
    serialRX();
    byte response = spiCommand(hspi, READ_DIA, HSPI_CS);
    Serial.print("spi response: ");
    Serial.println(response, BIN);
    delay(100);
}