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
#define READ_CONTROL 0b01100000
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

void readDiag()
{

    byte response = spiCommand(hspi, READ_DIA, HSPI_CS);
    Serial.print("spi sent: ");
    Serial.println(READ_DIA, BIN);

    int responseArray[8] = {0}; // Array to store each bit of the binary number
    int index = 0;        // Index to keep track of the position in the array

    for (int i = 7; i >= 0; i--)
    {
        if ((response >> i) & 1)
        {
            responseArray[index++] = 1;
        }
        else
        {
            responseArray[index++] = 0;
        }
    }

    Serial.print("EN: " + String(responseArray[0]));
    Serial.print(" OT: " + String(responseArray[1]));
    Serial.print(" TV: " + String(responseArray[2]));
    Serial.print(" CL: " + String(responseArray[3]));
    Serial.print(" DIA4: " + String(responseArray[4]));
    Serial.print(" DIA3: " + String(responseArray[5]));
    Serial.print(" DIA2: " + String(responseArray[6]));
    Serial.print(" DIA1: " + String(responseArray[7]));

    Serial.println();
}

void readConfig()
{
    byte response = spiCommand(hspi, READ_CONTROL, HSPI_CS);
    Serial.print("spi sent: ");
    Serial.println(READ_CONTROL, BIN);

    int responseArray[8] = {0}; // Array to store each bit of the binary number
    int index = 0;        // Index to keep track of the position in the array

    for (int i = 7; i >= 0; i--)
    {
        if ((response >> i) & 1)
        {
            responseArray[index++] = 1;
        }
        else
        {
            responseArray[index++] = 0;
        }
    }

    Serial.print("CMD: " + String(responseArray[0]) + String(responseArray[1]) + String(responseArray[2]));
    Serial.print(" OLDIS: " + String(responseArray[3]));
    Serial.print(" SIN: " + String(responseArray[4]));
    Serial.print(" SEN: " + String(responseArray[5]));
    Serial.print(" SDIR: " + String(responseArray[6]));
    Serial.print(" SPWM: " + String(responseArray[7]));
    Serial.println();
}

void readRevision()
{
    byte response = spiCommand(hspi, READ_REV, HSPI_CS);
    Serial.print("spi sent: ");
    Serial.println(READ_REV, BIN);

    int responseArray[8] = {0}; // Array to store each bit of the binary number
    int index = 0;        // Index to keep track of the position in the array

    for (int i = 7; i >= 0; i--)
    {
        if ((response >> i) & 1)
        {
            responseArray[index++] = 1;
        }
        else
        {
            responseArray[index++] = 0;
        }
    }

    Serial.print("ZERO: " + String(responseArray[0]));
    Serial.print(" ZERO: " + String(responseArray[1]));
    Serial.print(" ONE: " + String(responseArray[2]));
    Serial.print(" ZERO: " + String(responseArray[3]));
    Serial.print(" REV: " + String(responseArray[4]) + String(responseArray[5]) + String(responseArray[6]) + String(responseArray[7]));
    Serial.println();
}

void serialRX()
{
    if (Serial.available())
    {
        String str = Serial.readStringUntil('\n');

        if (str.startsWith("READDIA"))
        {
            readDiag();
           // readConfig();
           // readRevision();
        }
    }
}

void setup()
{
    Serial.begin(115200);
    hspi.begin(HSPI_SCK, HSPI_MISO, HSPI_MOSI, HSPI_CS);
    // hspi.begin();
    pinMode(HSPI_CS, OUTPUT);
}

void loop()
{
    serialRX();
    delay(100);
}