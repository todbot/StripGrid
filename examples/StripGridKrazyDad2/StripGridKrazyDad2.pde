//
// StripGridKrazydad1 -- 
//
//
// 2011, Jim Bumgardner
//

#include "StripGrid.h"

const int stripDPin = 11;
const int stripCPin = 13;
const int stripLPin = 10;
const int stripSPin = 12; // optional


const int rows = 10;
const int cols = 16;

StripGrid grid = StripGrid( rows,cols,
                            stripDPin, stripCPin, stripLPin, stripSPin, 
                            StripTypeHL1606 );


color_t white  = {255,255,255};
color_t red    = {255,0,0};
color_t green  = {0,255,0};
color_t blue   = {0,0,255};
color_t cyan   = {0,255,255};
color_t yellow = {255,255,0};
color_t magenta = {255,0,255};
color_t off    = {0,0,0};
color_t black  = {0,0,0};

const int bandSize = 8;
color_t band[ bandSize ];
int cells[rows*cols];
int ocells[cols];
int rules[8];

void setup()
{
  Serial.begin(19200);
  Serial.println("StripGridDemo5");

  band[0] = black;
  band[1] = blue;
  band[2] = green;
  band[3] = cyan;
  band[4] = red;
  band[5] = magenta;
  band[6] = yellow;
  band[7] = white;
  
  grid.begin();
  for (int i = rows*cols-1; i >= cols; --i) {
    cells[i] = 0;
  }

  for (int i = 0; i < 8; ++i)
    rules[i] = (int) random(2);
  for (int i = 0; i < cols; ++i) {
    cells[i] = (int) random(8);
  }

}

void loop()
{
  int y,x,i;

  if (random(10) < 1) {
    if (random(2) < 1) {
      rules[(int) random(8)] = (int) random(2);
    } else {
      cells[(int) random(cols)] = (int) random(8);
    }
  }
  for (i = rows*cols-1; i >= cols; --i) {
    cells[i] = cells[i-cols];
  }

  for (x = 0; x < cols; ++x) {
    ocells[x] = cells[x];
  }

  for (x = 0; x < cols; ++x) {
    cells[x] = (rules[ocells[(x+cols-1) % cols]] << 2) | (rules[ocells[x]] << 1) | rules[ocells[(x+1)%cols]];
  }

  i = 0;
  for( int y=0; y<rows; y++ ) {
    for( int x=0; x<cols; x++ ) {
      grid.setLED( y,x, band[cells[i] % bandSize] );
      i++;
    }
  }
  grid.update();
  //delayMicroseconds(33);
  delay(10);
}

