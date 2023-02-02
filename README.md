# IFX9021_Driver
A simple spi interface for the IFX9021 motor driver chip by infenion

## Datasheet
https://octopart.com/datasheet/ifx9201sgauma1-infineon-57372547

## Setup

Connect the spi pins on the IFX9021 to the ESP32. The default pins are as follows:

| ESP32 | Common Name | IFX9021 Name | IFX9021 Pin # |
| ----- | ----------- | ------------ | ------------- |
| 3.3V  | VCC         | VSO          | 2             |
| GND   | GND         | GND          | 6             |
| 14    | SCK         | SCK          | 10            |
| 13    | MOSI        | SI           | 8             |
| 12    | MISO        | SO           | 3             |
| 15    | CS          | CSN          | 9             |

!!Remember to also connect the ship to its supply voltage to pin 4, 12V in this case.

The ESP32 pins can be changed. Multiple chips can be used, each gets its own CS pin.


## Usage
Put the data to send into a byte variable and call the spiCommand function. The function takes the spi handle (fancy name for the network name), the data to send, and the CS pin as arguments:

byte data = 0x12;
    spiCommand(hspi, data, HSPI_CS);

the return of spiCommand is the data received in response from the chip.

The IFX9021 can be daisy chained, such the CS pin can be used to select which chip to send data to. 

The chip transmits MSB first
