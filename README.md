# Serial communication

In this situation, a team decided to use a family of microcontroller (ATSAMD) for a new design.

Due to the lack of space in the board, a header with 5 pins will be used for both SPI and I2C. This has to be done to so the new design also supports legacy architecture.

I am making the assumption that the ATSAMD21E (QFN32) will be used, because it is small and space is a constraint.


![Alt-text](https://github.com/entiredrop/atsamdsercom/blob/master/mcu_pins.jpeg?raw=true)


The microcontroller is very versatile, providing several SERCOMs that can be multiplexed with any function desired. This will help with the space constraint because we can use the same ports to work with both I2C and SPI.

After reading the datasheet, it is clear that we can use pins 11 (PA08), 12 (PA09) and 14 (PA11) for both I2C and SPI.

The reason behind this choice is that:

- Pin 11 can work as both MISO for SPI and SDA for I2C
- Pin 12 can work as both SCK for SPI and SCL for I2C, having the clock of both functionallities on the same pin
- Pin 14 can work as MOSI for SPI - Not used for I2C

Beucase we have only 5 pins in the connector, it is not possible to use Pin 13 as Chip Select, since we already have the 5 pins alocated to VCC, GND, MOSI, MISO and CLK for SPI. Thus, it is made the assumption that the chip connected will always be selected on the slave side.

On the hardware side, it is also needed to add pull up resistors to pins 11 and 12, since I2C does not have a push-pull setup. This will not affect SPI, since it has push-pull setup on the pins.

But, in order to accomplish the desired architecture, the firmware must be compliant, being smart enough to switch between protocols and adapt to the device plugged.

A simple setup would be:

##### For SPI:
- CTRLA.MODE = 0x3 (SPI host - page #462)
- CTRLA.DIPO = 0x0 (Pad[0] "Pin 11" as data in - page #462)
- CTRLA.DOPO = 0x2 (Pad[1] "Pin 12" as Clock, Pad[3] "Pin 14" as data out - page #462)

##### For I2C:
- CTRLA.MODE = 0x5 (I2C host)
- CTRLA.PINOUT = 0x0 (4 wire operation *disabled*)
- By default, the SDA is Pad[0] and Pad[1] is SCL - page #476 item 28.4

##### Both interfaces speeds must be set according to the application in question.

For both interfaces:
- CTRLA.ENABLE = 0x1 (enables interface - page #463 and #511)

## Protocol Diagram

A pseudo-code simulating some interaction between SPI and I2C is available in this repository.

Below it is possible to understand in a diagram how the communication could happen.

![Alt-text](https://github.com/entiredrop/atsamdsercom/blob/master/ProtocoDiagram.png?raw=true)

