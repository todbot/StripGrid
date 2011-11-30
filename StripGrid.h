//
// StripGrid - Abstraction of 2 dimentional pixels on LED strips
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//


#ifndef StripGrid_h
#define StripGrid_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


#include "HL1606strip.h";

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

class StripGrid {
    
 public:
    StripGrid( uint8_t rows, uint8_t cols, HL1606strip* strip );
    HL1606strip* strip;
    uint8_t rows;
    uint8_t cols;
    uint8_t brightness;

    void begin();
    void update();

    void clear();
    void fill(color_t color);
    void writeGrid();
    void setLED(uint8_t row, uint8_t col, color_t color);
    void setLED(uint8_t row, uint8_t col,uint8_t r,uint8_t g,uint8_t b);
    void getLED(uint8_t row, uint8_t col, color_t* color);
    void setBrightness(uint8_t b);

    void setFrame( color_t* buf2d );
    void setFrame_P( const color_t* buf2d );

    uint16_t ledpos(uint8_t row, uint8_t col);

    void saveFrame( color_t* savebuf );
    void blankStrip();
};

#endif
