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
StripGrid::StripGrid( uint8_t r, uint8_t c, 
                      uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t sPin,  
                      StripType type )
{
    int pixel_count = r*c;
    if( type == StripTypeHL1606 ) { 
        strip = new StripHL1606( dPin, cPin, lPin, sPin, pixel_count);
    }
    else { 
        // what?
    }

    rows = r;
    cols = c;

}

void StripGrid::begin()
{
    clear();
    update();
}

//
void StripGrid::update() 
{
  strip->update();

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
    strip->setLEDcolor( ledpos(row,col), color );
}

//
void StripGrid::getLED(uint8_t row, uint8_t col, color_t* color) 
{
    strip->getLEDcolor( ledpos(row,col), color ); 
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




// bresenham's algorithm - thx wikpedia
void StripGrid::drawLine(int8_t x0, int8_t y0, int8_t x1, int8_t y1, 
                         color_t color ) {
  uint16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0, color);
    } else {
      drawPixel(x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

// draw a rectangle
void StripGrid::drawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
                         color_t color) {
  drawLine(x, y, x+w-1, y, color);
  drawLine(x, y+h-1, x+w-1, y+h-1, color);

  drawLine(x, y, x, y+h-1, color);
  drawLine(x+w-1, y, x+w-1, y+h-1, color);
}

// fill a rectangle
void StripGrid::fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, 
                         color_t color) {
  for (uint8_t i=x; i<x+w; i++) {
    for (uint8_t j=y; j<y+h; j++) {
        drawPixel(j,i, color);
    }
  }
}





// turn off strip without affecting underlying buffer
void StripGrid::blankStrip()
{
    strip->blank();
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
