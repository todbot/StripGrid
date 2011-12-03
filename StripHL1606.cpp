//
// Lightly edited by todbot to make work in Arduino 1.0
//
// A basic HL1606 LED strip library, a little simpler to use than the core LEDStrip lib
// this library is a slow, & synchronous
/*
 * LEDStrip - Arduino driver for HL1606-based LED strips
 * Thanks to: John M Cohn
 * Copyright (c) 2009, Synoptic Labs
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the <organization> nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SYNOPTIC LABS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL SYNOPTIC LABS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "StripHL1606.h"


#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif



StripHL1606::StripHL1606(uint8_t dPin, uint8_t cPin, uint8_t lPin, uint16_t nLEDs)
{
  datPin = dPin;
  clkPin = cPin;
  latchPin = lPin;
  syncPin = 255;
  numLEDs = nLEDs;

  _faderEnabled = 0;

  leds = (uint8_t *)malloc(numLEDs);

  for (uint8_t i=0; i<numLEDs; i++) {
    setLEDcolor(i, (color_t){0,0,0});
  }

  digitalWrite(datPin, LOW);
  pinMode(datPin, OUTPUT);
  digitalWrite(syncPin, LOW);
  pinMode(syncPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  pinMode(latchPin, OUTPUT);
  digitalWrite(clkPin, LOW);
  pinMode(clkPin, OUTPUT);
}


StripHL1606::StripHL1606(uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t sPin, uint16_t nLEDs)
{
  datPin = dPin;
  clkPin = cPin;
  latchPin = lPin;
  syncPin = sPin;
  numLEDs = nLEDs;

  leds = (uint8_t *)malloc(numLEDs);

  for (uint8_t i=0; i<numLEDs; i++) {
    setLEDcolor(i, (color_t){0,0,0});  // FIXME: black
  }

  digitalWrite(datPin, LOW);
  pinMode(datPin, OUTPUT);
  digitalWrite(syncPin, LOW);
  pinMode(syncPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  pinMode(latchPin, OUTPUT);
  digitalWrite(clkPin, LOW);
  pinMode(clkPin, OUTPUT);
}


void StripHL1606::sleep()
{
  digitalWrite(datPin, LOW);
  pinMode(datPin, INPUT);
  digitalWrite(syncPin, LOW);
  pinMode(syncPin, INPUT);
  digitalWrite(latchPin, LOW);
  pinMode(latchPin, INPUT);
  digitalWrite(clkPin, LOW);
  pinMode(clkPin, INPUT);
}


void StripHL1606::wakeup()
{
  digitalWrite(datPin, LOW);
  pinMode(datPin, OUTPUT);
  digitalWrite(syncPin, LOW);
  pinMode(syncPin, OUTPUT);
  digitalWrite(latchPin, LOW);
  pinMode(latchPin, OUTPUT);
  digitalWrite(clkPin, LOW);
  pinMode(clkPin, OUTPUT);
}

void StripHL1606::faderCrank()
{
  unsigned long mymillis;
 
  if (!_faderEnabled) return;

  mymillis = millis();

  // Give us 250ms slop in case we don't exactly catch our edge.
  if (mymillis >= _faderPulseNextEdge && mymillis < _faderPulseNextEdge + 250) {
    if (digitalRead(syncPin) == HIGH) {
      digitalWrite(syncPin, LOW);
    } else {
      // only load new value of _faderPulseHalfWidth on rising edge
      digitalWrite(syncPin, HIGH);
      _faderPulseHalfWidth = _faderPulseNewHalfWidth;
    }

    _faderPulseNextEdge = mymillis + _faderPulseHalfWidth;
  }
}

unsigned int StripHL1606::faderSpeedGet()
{
  return _faderPulseHalfWidth;
}

void StripHL1606::faderSpeedSet(unsigned int halfWidthms)
{
  if (halfWidthms == 0) {
    _faderEnabled = 0;
    _faderPulseHalfWidth = 0;
    _faderPulseNewHalfWidth = 0;
    digitalWrite(syncPin, LOW);
    return;  
  }

  _faderPulseNewHalfWidth = halfWidthms;
 
  // if we're already running, don't re-init _faderPulseNextEdge
  if (_faderEnabled != 1) {  // starting from non-running state,
    _faderEnabled = 1;

    digitalWrite(syncPin, HIGH);
    _faderPulseHalfWidth = halfWidthms;
    _faderPulseNextEdge = millis() + _faderPulseHalfWidth;
  }
}

/* The HL1606 drives 2 RGB LED's.  Each 3-color LED is controlled with a command
 * word consisting of 8 bits.  Command word is clocked out MSB first (i.e. D8
 * is first bit sent)
 *
 * Format of command word (using conventions in datasheet):
 *   ________________________________________________________________________
 *  |   D1   |   D2   |   D3   |   D4   |   D5   |   D6   |   D7   |    D8   |
 *   ------------------------------------------------------------------------
 *   ________________________________________________________________________
 *  |     LED1 CMD    |    LED2 CMD     |    LED3 CMD     |   2X   | LatchOK |
 *   ------------------------------------------------------------------------
 *
 *   LED{1,2,3} CMD -
 *       00 - LED off
 *       01 - LED on (max bright)
 *       10 - LED fade up   (start at min bright)
 *       11 - LED fade down (start at max bright)
 *
 *   2X - Double fade speed
 *       0 - 1X fade speed, each pulse on SI line steps brightness by 1/128th.
 *       1 - 2X fade speed, each pulse on SI line steps brightness by 1/64th.    
 *
 *   LatchOK - Enable latch.  Set to 0 to insert 'white space' in the serial
 *             chain.  If set to 0, the entire CMD is ignored.
 *       0 - Do not latch this CMD when Latch is thrown.
 *       1 - Latch CMD as normal when Latch is thrown.
 *
*/

// Push a color value down the strip, setting the latch-enable flag.
uint8_t StripHL1606::rgbPush(uint8_t redcmd, uint8_t greencmd, uint8_t bluecmd)
{
  uint8_t cmd = 0;
  uint8_t flags = LatchOk;

  if (redcmd >= NONCMD || bluecmd >= NONCMD || greencmd >= NONCMD) return 0;

  cmd |= (greencmd << 4) & (_BV(5) | _BV(4));
  cmd |= (redcmd << 2) & (_BV(3) | _BV(2));
  cmd |= (bluecmd) & (_BV(1) | _BV(0));
  cmd |= flags & (_BV(6) | _BV(7));

  pushCmd(cmd);

  return cmd;
}

uint8_t StripHL1606::rgbPush2X(uint8_t redcmd, uint8_t greencmd, uint8_t bluecmd)
{
  uint8_t cmd = 0;
  uint8_t flags = LatchOk | Fade2x;

  if (redcmd >= NONCMD || bluecmd >= NONCMD || greencmd >= NONCMD) return 0;

  cmd |= (greencmd << 4) & (_BV(5) | _BV(4));
  cmd |= (redcmd << 2) & (_BV(3) | _BV(2));
  cmd |= (bluecmd) & (_BV(1) | _BV(0));
  cmd |= flags & (_BV(6) | _BV(7));

  pushCmd(cmd);

  return cmd;
}

void StripHL1606::sPulse()
{
  if (digitalRead(syncPin) == HIGH) {
    //delay(1);
    digitalWrite(syncPin, LOW);
    delayMicroseconds(1000);
    digitalWrite(syncPin, HIGH);
    delayMicroseconds(1000);
  } else {
    //delay(1);
    digitalWrite(syncPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(syncPin, LOW);
    delayMicroseconds(1000);
  }

}

//
void StripHL1606::blank()
{
  for (uint8_t i=0; i< numLEDs; i++) {
    pushCmd( 0x80 ); // latch
  }
  latch();
}

// Push a blank value down the strip, not setting latch-enable flag.  
// Does not affect the status of a particular LED when latched.  It's
// like using whitespace.
void StripHL1606::blankPush()
{
  pushCmd(0);
}

//
void StripHL1606::pushCmd(uint8_t cmd)
{
  //shiftOut(datPin, clkPin, MSBFIRST, cmd);     // doesnt work on teensy?
  for (uint8_t i=0; i<8; i++) {
    if (cmd & _BV(7-i)) {
      digitalWrite(datPin, HIGH);
    } else {
      digitalWrite(datPin, LOW);
    }      
    digitalWrite(clkPin, HIGH);

    digitalWrite(clkPin, LOW);

  }
}

void StripHL1606::latch()
{
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(1);  // spec sheet specifies minimum latch pulse of 1us
  digitalWrite(latchPin, LOW);
}


/* high level commands */

// this takes about 20ms for a 160 LED strip
//void StripHL1606::writeStrip(void)
void StripHL1606::update()
{
  for (uint16_t i=0; i<numLEDs; i++) {
    pushCmd(leds[numLEDs-1-i]);
  }
  latch();
}

// FIXME
//uint8_t StripHL1606::getLEDcolor(uint8_t n) {
void StripHL1606::getLEDcolor(uint16_t n, color_t* color)
{
  uint8_t x;

  if (n > numLEDs) return;
  
  x = leds[n];
  
  x &= 0x7F; // get rid of latch
  
  uint8_t r, g, b;
  r = g = b = 0;
  if (x & 0x3) { b = 1; }
  if (x & 0xC) { r = 1; } 
  if (x & 0x30) { g = 1; }
  
  x =  (g << 1) | (r << 2) | b;
  /*
  // FIXME:
  color->r = (v & _BV(2) ) ? 255 : 0;
  color->g = (v & _BV(1) ) ? 255 : 0;
  color->b = (v & _BV(0) ) ? 255 : 0;
  */
}



void StripHL1606::setLEDcolor(uint16_t n, color_t colr) 
{
  /*
  uint8_t color = 0b000; // 1-bit per color channel
  boolean otherLEDLayout = true; // FIXME
  if( otherLEDLayout ) { 
    if( colort.r > 127 )  color |= RED ;
    if( colort.g > 127 )  color |= BLUE;
    if( colort.b > 127 )  color |= GREEN;
  } else {
    if( colort.r > 127 )  color |= RED ;
    if( colort.g > 127 )  color |= GREEN;
    if( colort.b > 127 )  color |= BLUE;
  }
  */
  if (n > numLEDs) return;

  uint8_t x = LatchOk;
  
  if( colr.r > 127 ) 
    x |= RedOn;
  if (colr.g > 127 )
    x |= GreenOn;
  if (colr.b > 127 )
    x |= BlueOn;
  
  leds[n] = x;
}

