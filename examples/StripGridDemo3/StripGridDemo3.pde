//
// StripGridDemo3 --
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//
//

#include "StripGrid.h"


#include <avr/pgmspace.h>


const int statusLedPin = 13;

const int stripDPin = 11;
const int stripCPin = 13;
const int stripLPin = 10;
const int stripSPin = 12;


// 10x16 == 160 pixels == one 5m roll
const int rows = 10;
const int cols = 16;

StripGrid grid = StripGrid( rows,cols,
                            stripDPin, stripCPin, stripLPin, stripSPin, 
                            StripTypeHL1606 );


#include "Logos.h"



// temp var for holding a color value
color_t colr = {0,0,0};

color_t savebuf[rows*cols];

//
void setup()
{
  pinMode( statusLedPin, OUTPUT);
  digitalWrite( statusLedPin, HIGH);

  Serial.begin(19200);
  Serial.println("StripGridDemo3");

  grid.clear();
  grid.update();

}

unsigned long lastMillis, otherLastMillis;

//
void loop()
{

  if( millis() - lastMillis > 10 ) { 
    lastMillis = millis();
    int c = random(cols);
    int r = random(rows);
    colr.r = random(255); 
    colr.g = random(255);
    colr.b = random(255);
    grid.setLED( r,c, colr );

    if( millis() > 5000 ) { 
      c = random(cols);
      r = random(rows);
      colr.r = 0; colr.g = 0; colr.b = 0;
      grid.setLED( r,c, colr );
    }
  }

  if( (millis() - otherLastMillis) > 5000 ) {  
    otherLastMillis = millis();
    grid.saveFrame( savebuf );
    grid.setFrame_P( logo0 );
    grid.update();
    delay(200);
    grid.setFrame( savebuf );
    
  }

  grid.update();

}



