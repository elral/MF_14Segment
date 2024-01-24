/*!
 * @file Adafruit_LEDBackpack.cpp
 *
 * @mainpage Adafruit LED Backpack library for Arduino.
 *
 * @section intro_sec Introduction
 *
 * This is an Arduino library for our I2C LED Backpacks:
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
 * @section dependencies Dependencies
 *
 * This library depends on <a
 * href="https://github.com/adafruit/Adafruit-GFX-Library"> Adafruit_GFX</a>
 * being present on your system. Please make sure you have installed the latest
 * version before using this library.
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution
 *
 */

#include "14Segment_driver.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) ///< Bit-value if not defined by Arduino
#endif

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) \
    {                       \
        int16_t t = a;      \
        a         = b;      \
        b         = t;      \
    } ///< 16-bit var swap
#endif

static const PROGMEM uint16_t alphafonttable[] = {

    0b0000000000000001,
    0b0000000000000010,
    0b0000000000000100,
    0b0000000000001000,
    0b0000000000010000,
    0b0000000000100000,
    0b0000000001000000,
    0b0000000010000000,
    0b0000000100000000,
    0b0000001000000000,
    0b0000010000000000,
    0b0000100000000000,
    0b0001000000000000,
    0b0010000000000000,
    0b0100000000000000,
    0b1000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0001001011001001,
    0b0001010111000000,
    0b0001001011111001,
    0b0000000011100011,
    0b0000010100110000,
    0b0001001011001000,
    0b0011101000000000,
    0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0100000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000001001, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,

};

AlphaNum4::AlphaNum4(void) {}

void AlphaNum4::begin(uint8_t addr)
{
    _addrI2C = addr;
    // turn on oscillator
    uint8_t buffer = 0x21;
    Wire.beginTransmission(_addrI2C);
    Wire.write(buffer);
    Wire.endTransmission();
    clear();
    writeDisplay();
    blinkRate(HT16K33_BLINK_OFF);
    setBrightness(15); // max brightness
    return;
}

void AlphaNum4::setDisplayState(bool state)
{
    uint8_t buffer;
    if (state)
        buffer = HT16K33_BLINK_CMD | 1;
    else
        buffer = HT16K33_BLINK_CMD;
    Wire.beginTransmission(_addrI2C);
    Wire.write(buffer);
    Wire.endTransmission();
}

void AlphaNum4::setBrightness(uint8_t b)
{
    if (b > 15)
        b = 15; // limit to max brightness
    uint8_t buffer = HT16K33_CMD_BRIGHTNESS | b;
    Wire.beginTransmission(_addrI2C);
    Wire.write(buffer);
    Wire.endTransmission();
}

void AlphaNum4::blinkRate(uint8_t b)
{
    if (b > 3)
        b = 0; // turn off if not sure
    uint8_t buffer = HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1);
    Wire.beginTransmission(_addrI2C);
    Wire.write(buffer);
    Wire.endTransmission();
}

void AlphaNum4::writeDisplay(void)
{
    uint8_t buffer[17];
    buffer[0] = 0x00; // start at address $00
    for (uint8_t i = 0; i < 8; i++) {
        buffer[1 + 2 * i] = displaybuffer[i] & 0xFF;
        buffer[2 + 2 * i] = displaybuffer[i] >> 8;
    }
    Wire.beginTransmission(_addrI2C);
    Wire.write(buffer, 17);
    Wire.endTransmission();
}

void AlphaNum4::clear(void)
{
    for (uint8_t i = 0; i < 8; i++) {
        displaybuffer[i] = 0;
    }
}

void AlphaNum4::writeDigitRaw(uint8_t n, uint16_t bitmask)
{
    displaybuffer[n] = bitmask;
}

void AlphaNum4::writeDigitAscii(uint8_t n, uint8_t a, bool d)
{
    uint16_t font = pgm_read_word(alphafonttable + a);
    displaybuffer[n] = font;
    if (d)
        displaybuffer[n] |= (1 << 14);
}

void AlphaNum4::writeAscii(char *text, uint8_t dot) {
    for (uint8_t i = 0; i < 4; i++) {
        if (text[i] == 0x00)
            break;
        writeDigitAscii(i, text[i]);
    }
}

void AlphaNum4::setDot(uint8_t digit) {
    if (digit > 3)
        return;
    displaybuffer[digit] |= (1 << 14);
}