# Community Device for 14 Segment Displays with 4 digits using HT16K33 driver

The displays are connected via I2C. If more than 1 display should be used, set each display to another I2C address.
Up to 8 addresses can be choosen.

Define for each display one config on the board and set the I2C address accordingly.

Available messageID's are:

* 1 = Show data on the display. Decimal point is considered automatically, so must be part of the message
* 2 = Set brigthness, values can be from 0 to 15

All Boards are supported, but the stepper support for the ProMicro is deactivated due to not sufficient Flash memory.

# Installation

Download the zip-file from the ([latest release](https://github.com/elral/MF_14Segment/releases)).

Copy the content to you community folder within you MobiFlight installation folder. It should look like:

```
[MF installation Folder]->Community->Elral_14Segment_Display->boards/
[MF installation Folder]->Community->Elral_14Segment_Display->devices/
[MF installation Folder]->Community->Elral_14Segment_Display->firmware/
```

Connect a new Arduino Mega/Uno/Nano/ProMicro or Raspberry Pi Pico (or reset them), upload the firmware and define for each Display one Device with the I2C address from this display.

Refere in an output reference to the custom device and choose one of the both messageID's.

With version 0.9.1 the foldername for the community folder has changed.
If you update from 0.9.0 please delete the folder `Elral_14Segment_Display` before copying the new one from the zip file.