//
// StripGrid - Abstraction of 2 dimentional pixels on LED strips
//
//
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
    enum StripTypes {
        NONE,
        HL1606,
        LPD8806,
    };
    
 public:
    StripGrid( uint8_t rows, uint8_t cols, HL1606strip* strip );
    HL1606strip* strip;
    uint8_t rows;
    uint8_t cols;

    void update();

    void clear();
    void fill(color_t color);
    void writeGrid();
    void setLED(uint8_t row, uint8_t col, color_t color);
    void setLED(uint8_t row, uint8_t col,uint8_t r,uint8_t g,uint8_t b);
    void getLED(uint8_t row, uint8_t col, color_t* color);

    uint16_t ledpos(uint8_t row, uint8_t col);
};

#endif
