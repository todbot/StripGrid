//
// StripGrid.cpp -- 
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
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

#include <avr/pgmspace.h>

//
StripGrid::StripGrid( uint8_t r, uint8_t c, HL1606strip* s)
{
    rows = r;
    cols = c;

    brightness = 255;

    strip = s;
}

void StripGrid::begin()
{
    clear();
    update();
}

//
void StripGrid::update() 
{
  strip->writeStrip();

  /*
  if( brightness < 255 ) { 
      for( int i=0; i<brightness/2; i++ ) {
          strip->sPulse();
          //delayMicroseconds(10);
          delay(1);
      }
  }
  */
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
    boolean otherLEDLayout = true; // FIXME
    if( otherLEDLayout ) { 
        if( color.r > 127 )  hl1606color |= RED ;
        if( color.g > 127 )  hl1606color |= BLUE;
        if( color.b > 127 )  hl1606color |= GREEN;
    } else { 
        if( color.r > 127 )  hl1606color |= RED ;
        if( color.g > 127 )  hl1606color |= GREEN;
        if( color.b > 127 )  hl1606color |= BLUE;
    }
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

void StripGrid::setBrightness(uint8_t b)
{
    brightness = b;
}

//
void StripGrid::setFrame( color_t* buf2d )
{
    for( int i=0; i< rows; i++ ) {
        for( int j=0; j<cols; j++ ) {
            setLED( i,j, buf2d[i*cols+j] );
        }
    }
}

//
void StripGrid::setFrame_P( const color_t* buf2d )
{
    color_t colr;
    for( int i=0; i< rows; i++ ) {
        for( int j=0; j<cols; j++ ) {
            memcpy_P( &colr, &buf2d[i*cols+j], sizeof(color_t) );
            setLED( i,j, colr );
        }
    }
}


//
void StripGrid::clear() 
{
    color_t black = {0,0,0};
    fill(black);
}

// turn off strip without affecting underlying buffer
void StripGrid::blankStrip()
{
    for (uint8_t i=0; i< rows*cols; i++) {
        strip->pushCmd( 0x80 ); // latch
    }
    strip->latch();
}


void StripGrid::saveFrame( color_t* savebuf )
{
    // oh if only we got access to underlying leds array
    //memcpy( savebuf, buf2d, sizeof(color_t)*rows*cols );
    for( int i=0; i<rows; i++ ) { 
        for( int j=0; j<cols; j++ ) {
            getLED( i,j, &savebuf[i*cols+j] );
        }
    }
}


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
