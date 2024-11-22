
![alt text][image1]

---

## BIT SERIAL DEVICE (BSD) INTERFACE
BSD is a pulse-width modulated signal with three possible states: sync, 0, and 1. These are detailed, along with their associated tolerances. The frame length is 19 bits, and communication occurs at 1200 bps ± 3%.

**BSD Protocol Description**

| Pause        | DIR | Salve Address|Register Address| P1| Data| P2| ACK|
| ----------- | ----------- | ----------- |----------- |----------- |----------- |----------- |----------- |
| 3 bits    | 1 bit       | 3 bits |  4 bits| 1 bit|  8 bits| 1 bit| 1 bit|

[Integrated Precision Battery Sensor for Automotive ADuC7036](datasheet/ADuC7036.pdf)

[//]: # (Image References)
[image1]: ./images/IBS.PNG "IBS"
[image2]: ./images/TEK00000.PNG "14.4V RX High Byte"
[image3]: ./images/TEK00001.PNG "14.4V TX Low Byte"
[image4]: ./images/TEK00002.PNG "12V RX High Byte"
[image5]: ./images/TEK00003.PNG "12V RX Low Byte"


![alt text][image2]
![alt text][image3]
![alt text][image4]
![alt text][image5]