/*!
 * @file Adafruit_LEDBackpack.h
 *
 * Part of Adafruit's Arduino library for our I2C LED Backpacks:
 * ----> http://www.adafruit.com/products/
 * ----> http://www.adafruit.com/products/
 *
 * These displays use I2C to communicate, 2 pins are required to
 * interface. There are multiple selectable I2C addresses. For backpacks
 * with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
 * with 3 Address Select pins: 0x70 thru 0x77
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * MIT license, all text above must be included in any redistribution
 */
#pragma once

#include "Arduino.h"
#include "Wire.h"

#define HT16K33_BLINK_CMD       0x80 ///< I2C register for BLINK setting
#define HT16K33_BLINK_DISPLAYON 0x01 ///< I2C value for steady on
#define HT16K33_BLINK_OFF       0    ///< I2C value for steady off
#define HT16K33_BLINK_2HZ       1    ///< I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ       2    ///< I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ    3    ///< I2C value for 0.5 Hz blink

#define HT16K33_CMD_BRIGHTNESS 0xE0 ///< I2C register for BRIGHTNESS setting

/*
Segment names for 14-segment alphanumeric displays.
See https://learn.adafruit.com/14-segment-alpha-numeric-led-featherwing/usage

    -------A-------
    |\     |     /|
    | \    J    / |
    |   H  |  K   |
    F    \ | /    B
    |     \|/     |
    |--G1--|--G2--|
    |     /|\     |
    E    / | \    C
    |   L  |   N  |
    | /    M    \ |
    |/     |     \|
    -------D-------  DP
*/

/*!
    @brief  Class for the 14 segment driver using HT16K33 controller device.
*/
class AlphaNum4
{
public:
    /*!
      @brief  Constructor for HT16K33 devices.
    */
    AlphaNum4(void);

    /*!
      @brief  Start I2C and initialize display state (blink off, full
              brightness).
      @param  _addr  I2C address.
    */
    void begin(uint8_t _addr = 0x70);

    /*!
      @brief  Turn display on or off
      @param  state  State: true = on, false = off
    */
    void setDisplayState(bool state);

    /*!
      @brief  Set display brightness.
      @param  b  Brightness: 0 (min) to 15 (max).
    */
    void setBrightness(uint8_t b);

    /*!
      @brief  Set display blink rate.
      @param  b  One of:
                 HT16K33_BLINK_DISPLAYON = steady on
                 HT16K33_BLINK_2HZ       = 2 Hz blink
                 HT16K33_BLINK_1HZ       = 1 Hz blink
                 HT16K33_BLINK_HALFHZ    = 0.5 Hz blink
    */
    void blinkRate(uint8_t b);

    /*!
      @brief  Issue buffered data in RAM to display.
    */
    void writeDisplay(void);

    /*!
      @brief  Clear display.
    */
    void clear(void);

    /*!
      @brief  Write single character of alphanumeric display as raw bits
              (not a general print function).
      @param  n        Character index (0-3).
      @param  bitmask  Segment bitmask.
    */
    void writeDigitRaw(uint8_t n, uint16_t bitmask);

    /*!
      @brief  Write single ASCII character to alphanumeric display.
      @param  n      Character index (0-3).
      @param  ascii  ASCII character.
      @param  dot    If true, also light corresponding dot segment.
    */
    void writeDigitAscii(uint8_t n, uint8_t ascii, bool dot = false);

    /*!
      @brief  Write up to 4 ASCII characters to alphanumeric display.
      @param  ascii  ASCII character.
      @param  dot    number of digit, also light corresponding dot segment.
    */
    void writeAscii(char *text, uint8_t dot = 0);

    /*!
      @brief set the dot on alphanumeric display at digit 0...3.
      @param  digit  Digit index (0...3).
    */
    void setDot(uint8_t digit);

private:
    uint8_t  _addrI2C;
    uint16_t displaybuffer[8]; ///< Raw display data
};
