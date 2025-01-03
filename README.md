
![alt text][image1]

---

## BIT SERIAL DEVICE (BSD) INTERFACE
BSD is a pulse-width modulated signal with three possible states: sync, 0, and 1. These are detailed, along with their associated tolerances. The frame length is 19 bits, and communication occurs at 1200 bps ± 3%.

**BSD Protocol Description**

| Pause        | DIR | Slave Address|Register Address| P1| Data| P2| ACK|
| ----------- | ----------- | ----------- |----------- |----------- |----------- |----------- |----------- |
| 3 bits    | 1 bit       | 3 bits |  4 bits| 1 bit|  8 bits| 1 bit| 1 bit|

[Integrated Precision Battery Sensor for Automotive ADuC7036](datasheet/ADuC7036.pdf)

[//]: # (Image References)
[image1]: ./images/IBS.png "IBS"
[image2]: ./images/TEK00000.png "14.4V RX High Byte"
[image3]: ./images/TEK00001.PNG "14.4V TX Low Byte"
[image4]: ./images/TEK00002.PNG "12V RX High Byte"
[image5]: ./images/TEK00003.PNG "12V RX Low Byte"
[image6]: ./images/logic-level-shifting-basics.png "Logic Level Shifting"
[image7]: ./images/PICO_PIO_IBS_BSD_SETUP.png "Logic Level Shifting"


## Logic Level Shifting 
Logic level shifting is necessary when devices operating at different voltage levels need to communicate. In this project, the Raspberry Pi Pico's GPIO is used to simulate the BSD protocol. The GPIO operates at 3.3V, while the IBS (Intelligent Battery Sensor) BSD wire communicates at a 12V level. To ensure compatibility and reliable bidirectional communication, a bidirectional logic level shifter is used.

The level shifter in this setup uses a Diodes N-channel MOSFET (2N7002W) and 6.8kΩ pull-up resistors. This configuration allows the Pico's GPIO to drive the 12V BSD line without exceeding its voltage limits, and vice versa. The MOSFET handles the bidirectional nature of the communication, enabling proper signal transmission in both directions.
![alt text][image6]

[LOGIC LEVEL CONVERTER BOARD - 333029](https://www.digikey.com/en/products/detail/soldered-electronics/333029/21720444)  
[LOGIC LEVEL CONVERTER BOARD - 2595](https://www.digikey.com/en/products/detail/pololu-corporation/2595/10450598)

## Setup
![alt text][image7]
This circuit consists of four main components:
PICO MCU Controller, Logic Level Conversion Module, Intelligent Battery Sensor (IBS), 12V Battery or Power Supply.

## Mapping IBS Data Registers: Current, Voltage, and Temperature
By testing all bus addresses and registers, it was discovered that the IBS responds to read/write operations at address 0. Based on the analysis:

* Address 0, Register 0 likely represents current (16 bits).
* Address 0, Register 1 likely represents voltage (16 bits).
* Address 0, Register 3 likely represents temperature (8 bits).

![alt text][image2]
![alt text][image3]
![alt text][image4]
![alt text][image5]
The images above show readings of 14.48V and 12V, with the IBS providing the high 8 bits and low 8 bits of data for each voltage.
The minimum operating voltage for the BSD protocol is 7V.