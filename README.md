# Community Device for 14 Segment Displays with 4 digits using HT16K33 driver

The displays are connected via I2C. If more than 1 display should be used, set each display to another I2C address.
Up to 8 addresses can be choosen.

Define for each display one config on the board and set the I2C address accordingly.

Available messageID's are:

* 0 = Test function, use it carefully, it takes couple of seconds
* 1 = Show data on the display, decimal point is considered automatically
* 2 = Set brigthness, values can be from 0 to 15