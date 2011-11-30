//
// StripGridDemo2 -- 
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//


#include "HL1606strip.h"
#include "StripGrid.h"


#include <avr/pgmspace.h>


const int statusLedPin = 13;

const int stripDPin = 11;
const int stripLPin = 10;
const int stripCPin = 13;
const int stripSPin = 12; // optional


// 10x16 == 160 pixels == one 5m roll
const int rows = 10;
const int cols = 16;
const int pixel_count = rows * cols;


#include "Logos.h"

//HL1606strip strip = HL1606strip(STRIP_D,STRIP_S,STRIP_L,STRIP_C,pixel_count);
HL1606strip strip = HL1606strip( stripDPin, stripLPin, stripCPin, pixel_count);
StripGrid grid = StripGrid( rows,cols, &strip );



//
void setup()
{
  pinMode( statusLedPin, OUTPUT);
  digitalWrite( statusLedPin, HIGH);

  Serial.begin(19200);
  Serial.println("StripGridDemo2");

  grid.begin();

  grid.setFrame_P( logo0 ) ;
  grid.update();

}

boolean toggle = false;
unsigned long lastMillis;
//
void loop()
{

  if( millis() > 3000 ) { 
    grid.setFrame_P( logo1 );
    grid.update();
  }

  if( 0 ) {
    // reallly lame brightness control
    if( (millis() - lastMillis) > 5000 ) {
      lastMillis = millis();
      toggle = !toggle;
      if( toggle ) { 
        grid.setFrame_P( logo0 ) ;
        grid.update();
      } else { 
        grid.blankStrip();
      }
    }
  }

}

/*
//
void doitslow()
{
  memcpy_P( &colr, &logo0[i*cols+j], sizeof(color_t) );
  grid.setLED( i,j, colr );
  grid.update();

  Serial.print("r,g,b:");
  Serial.print(colr.r, DEC); Serial.print(',');
  Serial.print(colr.g, DEC); Serial.print(',');
  Serial.print(colr.b, DEC); Serial.print('\n');

  j++;
  if( j == cols ) { 
    j=0;
    i++;
    if( i == rows ) {
      i=0;
    }
  }

  digitalWrite(statusLedPin, HIGH);
  delay(300);
  digitalWrite(statusLedPin, LOW);
  delay(300);

}

*/
