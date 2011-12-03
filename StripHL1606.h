//
// Lightly edited by todbot to make work in Arduino 1.0
//

/*
 * LEDStrip - Arduino driver for HL1606-based LED strips
 * Thanks to: John M Cohn
 * Copyright (c) 2009, Synoptic Labs
 * All rights reserved.
 
    Some higher level commands added by ladyada

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

#ifndef StripHL1606_h
#define StripHL1606_h


#include "Strip.h"




#define LatchOk  0b10000000  // 0x80
#define Fade2x   0b01000000  // 0x40

#define BlueOn   0b00010000
#define RedOn    0b00000100
#define GreenOn  0b00000001

//#define SPEED2X (_BV(6))

// colors, each bit one LED
#define BLACK  0b000
#define WHITE  0b111
#define RED    0b100
#define YELLOW 0b110
#define GREEN  0b010
#define TEAL   0b011
#define BLUE   0b001
#define VIOLET 0b101


class StripHL1606 : public Strip
{
 public: 

    enum {
        OFF,  // 0b00
        ON,   // 0b01
        UP,   // 0b10
        DOWN, // 0b11
        NONCMD 
    };

  private:
    
    uint8_t datPin;
    uint8_t clkPin;
    uint8_t latchPin;
    uint8_t syncPin;

    uint8_t _faderEnabled;
    unsigned int _faderPulseHalfWidth;
    unsigned int _faderPulseNewHalfWidth;
    unsigned long _faderPulseNextEdge;

    uint8_t* leds;

  public:

    StripHL1606(uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t sPin, 
                uint16_t nLEDs);

    StripHL1606(uint8_t dPin, uint8_t cPin, uint8_t lPin,
                uint16_t nLEDs);
    
    virtual void setLEDcolor(uint16_t n, color_t color);
    virtual void getLEDcolor(uint16_t n, color_t* color);

    virtual void update();

    virtual void blank();

    virtual void sleep();
    virtual void wakeup();

    // HL1606 specific features
    uint8_t rgbPush(uint8_t, uint8_t, uint8_t);
    uint8_t rgbPush2X(uint8_t, uint8_t, uint8_t);

    void pushCmd(uint8_t);
    void blankPush();
    void latch();

    void faderSpeedSet(unsigned int);
    unsigned int faderSpeedGet();
    void faderCrank();
    void sPulse();
};

#endif
