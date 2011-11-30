//
// StripGridDemo1 -- 
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//

#include "HL1606strip.h"
#include "StripGrid.h"

const int stripDPin = 11;
const int stripLPin = 10;
const int stripCPin = 13;
const int stripSPin = 12; // optional


const int rows = 10;
const int cols = 16;
const int pixel_count = rows * cols;

//HL1606strip strip = HL1606strip(STRIP_D,STRIP_S,STRIP_L,STRIP_C,pixel_count);
HL1606strip strip = HL1606strip( stripDPin, stripSPin, stripLPin, stripCPin, pixel_count);
//HL1606strip strip = HL1606strip( stripDPin,stripLPin,stripCPin, pixel_count);
StripGrid grid = StripGrid( rows,cols, &strip );

color_t white  = {255,255,255};
color_t red    = {255,0,0};
color_t green  = {0,255,0};
color_t blue   = {0,0,255};
color_t cyan   = {0,255,255};
color_t yellow = {255,255,0};
color_t off    = {0,0,0};

void setup()
{
  Serial.begin(19200);
  Serial.println("StripGridDemo1");

  grid.begin();

}

void loop()
{
  // wipe from left to right
  for( int j=0; j<cols; j++ ) {
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,j, green );
    }
    grid.update();
    delay(100);
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,j, blue );
    }
  }

  // wipe from right to left
  for( int j=0; j<cols; j++ ) {
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,cols-1-j, cyan );
    }
    grid.update();
    delay(100);
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,cols-1-j, yellow );
    }
  }

  // wipe top to bottom
  for( int i=0; i< rows; i++ ) {
    for( int j=0; j< cols; j++ ) {
      grid.setLED( i,j, red );
    }
    grid.update();
    delay(100);
  }
  // wipe top to bottom
  for( int i=0; i< rows; i++ ) {
    for( int j=0; j< cols; j++ ) {
      grid.setLED( rows-1-i,j, blue );
    }
    grid.update();
    delay(100);
  }


  // march through from top to bottom, left to right
  for( int i=0; i< rows; i++ ) { 
    for( int j=0; j<cols; j++ ) {
      int p = grid.ledpos(i,j);
      Serial.print("turning on: ");
      Serial.print(i); Serial.print(','); Serial.print(j); 
      Serial.print(" p:"); Serial.println(p);
      grid.setLED( i,j, green );
      grid.update();
      delay(1);
      grid.setLED( i,j, off );
    }
  }

    
}
