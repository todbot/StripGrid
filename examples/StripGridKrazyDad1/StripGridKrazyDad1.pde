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

const int bandSize = 7;
color_t band[ bandSize ];
int ctrs[rows*cols];

void setup()
{
  Serial.begin(19200);
  Serial.println("StripGridDemo5");

  band[0] = black;
  band[1] = red;
  band[2] = magenta;
  band[3] = white;
  band[4] = yellow;
  band[5] = cyan;
  band[6] = blue;
  
  grid.begin();
  for (int i = rows*cols-1; i >= 0; --i) {
    ctrs[i] = 0;
  }
}

int ctr = 0;
void loop()
{
  int n = 0;
  for( int j=0; j<cols; j++ ) {
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,j, band[ctrs[n] % bandSize] );
      if (ctr % n == 0)
        ctrs[n]++;
      n++;
    }
  }
  grid.update();
  delayMicroseconds(100);
  ctr++;
}

