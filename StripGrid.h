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


#include "StripHL1606.h"


enum StripType {
    StripTypeHL1606,
    StripTypeNONE,
};

#define swap(a, b) { uint16_t t = a; a = b; b = t; }


class StripGrid {

 public:
    //StripGrid( uint8_t rows, uint8_t cols, StripType );
    StripGrid( uint8_t r, uint8_t c, 
               uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t sPin,  
               StripType type );
    Strip* strip;

    uint8_t rows;
    uint8_t cols;

    void begin();
    void update();

    void clear();
    void fill(color_t color);
    void writeGrid();
    void setLED(uint8_t row, uint8_t col, color_t color);
    void setLED(uint8_t row, uint8_t col,uint8_t r,uint8_t g,uint8_t b);
    void getLED(uint8_t row, uint8_t col, color_t* color);

    void setFrame( color_t* buf2d );
    void setFrame_P( const color_t* buf2d );

    void drawPixel(uint8_t x, uint8_t y, color_t color) { setLED(y,x,color); }
    void drawLine(int8_t x0, int8_t y0, int8_t x1, int8_t y1, color_t color);
    void drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, color_t color);
    void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, color_t color);

    uint16_t ledpos(uint8_t row, uint8_t col);

    void saveFrame( color_t* savebuf );
    void blankStrip();
};

#endif
