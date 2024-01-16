
## Buy the components

To build the watch, you should buy components:
1. [NodeMcu v3 CH340](https://www.aliexpress.com/item/33053690164.html) controller type-c or micro USB
2. [TFT Display 1.8 inch IPS ST7735](https://www.aliexpress.com/item/1005003797803015.html)
3. [Dupont Line Female to Female Jumper 10CM](https://www.aliexpress.com/item/32823004985.html)

## Connection

To connect the controller to the display use this pins:
| Display | Controller |
|--|--|
| LED | 3v |
| SCK | d5 |
| SDA | d7 |
| A0 | d2 |
| Res | d4 |
| CS | d3 |
| GND | G |
| VCC | 3v |

## Upload the firmware

1. Download and install [arduino-cli](https://arduino.github.io/arduino-cli/0.35/installation/). 
2. Download the **bin** file from the [latest release](https://github.com/rublin/russian-losses-watch/releases/latest)
3. Connect your controller to the PC
4. Upload the bin file

    arduino-cli upload -b esp8266:esp8266:nodemcuv2 -i .\Downloads\rlw-r-v0.0.30.bin -p COM5

5. Print the [case](https://github.com/rublin/russian-losses-watch/blob/main/3d_printing/case_for_lolin_with_display_1.8.stl)
6. Assemble everything in the case

Pay attention that **.\Downloads\rlw-r-v0.0.30.bin** should be the valid path to your bin file and **COM5** is a valid COM PORT.
