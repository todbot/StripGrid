//
// StripGrid.cpp -- 
//
//
//
// Strips in a grid are arranged like so (for this rows=4,cols=7 grid):
// row/col  0     1     2     3     4     5     6
//   0  >-- 00 -- 01 -- 02 -- 03 -- 04 -- 05 -- 06 --+ 
//   1  +-- 13 -- 12 -- 11 -- 10 -- 09 -- 08 -- 07 --|
//   2  |-- 14 -- 15 -- 16 -- 17 -- 18 -- 19 -- 20 --+
//   3  <-- 27 -- 26 -- 25 -- 24 -- 23 -- 22 -- 21 --|
//
// e.g. for even rows, pixel_pos(row,col) = (row*cols) + col
//                     e.g. pixel_pos(2,3) = (2*7) + 3 = 17
//      for odd rows,  pixel_pos(row,col) = (row*cols) + (cols-col) - 1
//                     e.g. pixel_pos(3,4) = (3*7) + (7-4) - 1 = 21+3-1 = 23 
//

#include "StripGrid.h"

//#define ledpos(row,col) ((col*rows) + row)
//#define ledpos(row,col) ((row%2)==0 ? ((row*cols)+col) : ((row*cols)+(cols-col)-1))

uint16_t StripGrid::ledpos(uint8_t row, uint8_t col)
{
    if( (row % 2) == 0) { // even
        return (row*cols) + col;
    } else {
        return (row*cols) + (cols-col) - 1;
    }
}

//
StripGrid::StripGrid( uint8_t r, uint8_t c, HL1606strip* s)
{
    rows = r;
    cols = c;

    strip = s;
}

//
void StripGrid::update() 
{
  strip->writeStrip();
}

//
void StripGrid::fill(color_t color) 
{
    for (uint8_t i=0; i<rows; i++) {
        for (uint8_t j=0; j<cols; j++) {
            setLED( i,j, color );
        }
    }
}

//
void StripGrid::setLED(uint8_t row, uint8_t col, 
                       uint8_t r, uint8_t g, uint8_t b)
{
    color_t c = {r,g,b};
    setLED( row,col, c );
}

//
void StripGrid::setLED(uint8_t row, uint8_t col, color_t color)
{
    uint8_t hl1606color = 0b000; // 1-bit per color channel
    if( color.r > 127 )  hl1606color |= _BV(2);
    if( color.g > 127 )  hl1606color |= _BV(1);
    if( color.b > 127 )  hl1606color |= _BV(0);

    strip->setLEDcolor( ledpos(row,col), hl1606color );
}

//
void StripGrid::getLED(uint8_t row, uint8_t col, color_t* color) 
{
    int v = strip->getLEDcolor( ledpos(row,col) ); // FIXME
    color->r = (v & _BV(2) ) ? 255 : 0;
    color->g = (v & _BV(1) ) ? 255 : 0;
    color->b = (v & _BV(0) ) ? 255 : 0;
}

//
void StripGrid::clear() 
{
    color_t black = {0,0,0};
    fill(black);
}
