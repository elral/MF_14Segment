#include <Arduino.h>
#include "14Segment.h"
#include "allocateMem.h"
#include "commandmessenger.h"

/* **********************************************************************************
    This is just the basic code to set up your custom device.
    Change/add your code as needed.
********************************************************************************** */

//Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();


Segment14::Segment14()
{
    _initialised = false;
}

void Segment14::begin()
{
}

void Segment14::attach(uint8_t addrI2C)
{
    _addrI2C = addrI2C;
    Wire.begin();
    Wire.setClock(400000);
    if (!FitInMemory(sizeof(AlphaNum4))) {
        // Error Message to Connector
        cmdMessenger.sendCmd(kStatus, F("Custom Device does not fit in Memory"));
        return;
    }
    alpha4 = new (allocateMemory(sizeof(AlphaNum4))) AlphaNum4();
    alpha4->begin(_addrI2C);
    _initialised = true;
}

void Segment14::detach()
{
    if (!_initialised)
        return;
    _initialised = false;
}


void Segment14::test()
{
    alpha4->writeDigitRaw(3, 0x0);
    alpha4->writeDigitRaw(0, 0xFFFF);
    alpha4->writeDisplay();
    delay(200);
    alpha4->writeDigitRaw(0, 0x0);
    alpha4->writeDigitRaw(1, 0xFFFF);
    alpha4->writeDisplay();
    delay(200);
    alpha4->writeDigitRaw(1, 0x0);
    alpha4->writeDigitRaw(2, 0xFFFF);
    alpha4->writeDisplay();
    delay(200);
    alpha4->writeDigitRaw(2, 0x0);
    alpha4->writeDigitRaw(3, 0xFFFF);
    alpha4->writeDisplay();
    delay(200);
    
    alpha4->clear();
    alpha4->writeDisplay();

    // display every character, 
    for (uint8_t i='!'; i<='z'; i++) {
        alpha4->writeDigitAscii(0, i);
        alpha4->writeDigitAscii(1, i+1);
        alpha4->writeDigitAscii(2, i+2);
        alpha4->writeDigitAscii(3, i+3);
        alpha4->writeDisplay();
        
        delay(300);
    }

    alpha4->clear();
    alpha4->writeDisplay();
}

void Segment14::set(int16_t messageID, char *setPoint)
{
    /* **********************************************************************************
        Each messageID has it's own value
        check for the messageID and define what to do.
        Important Remark!
        MessageID == -1 will be send from the connector when Mobiflight is closed
        Put in your code to shut down your custom device (e.g. clear a display)
        MessageID == -2 will be send from the connector when PowerSavingMode is entered
        Put in your code to enter this mode (e.g. clear a display)

    ********************************************************************************** */
    int32_t  data = atoi(setPoint);

    // do something according your messageID
    switch (messageID) {
    case -1:
        // tbd., get's called when Mobiflight shuts down
        break;
    case -2:
        // tbd., get's called when PowerSavingMode is entered
        break;
    case 0:
        test();
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    default:
        break;
    }
}

void Segment14::update()
{
    // Do something which is required regulary
}
