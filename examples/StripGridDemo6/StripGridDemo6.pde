//
// StripGridDemo3 --
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//
//

#include "HL1606strip.h"
#include "StripGrid.h"


#include <avr/pgmspace.h>

#include "Logos.h"

// how long to view each logo
unsigned long viewMillis = 3000;

const int statusLedPin = 13;

const int stripDPin = 11;
const int stripLPin = 10;
const int stripCPin = 13;
const int stripSPin = 12;


// 10x16 == 160 pixels == one 5m roll
const int pixel_count = rows * cols;



HL1606strip strip = HL1606strip( stripDPin, stripSPin, stripLPin, stripCPin, pixel_count);
StripGrid grid = StripGrid( rows,cols, &strip );


unsigned long lastMillis;
int imgi=0;


//
void setup()
{
  pinMode( statusLedPin, OUTPUT);
  digitalWrite( statusLedPin, HIGH);

  Serial.begin(19200);
  Serial.println("StripGridDemo6");

  grid.clear();
  grid.update();

}

//
void loop()
{
  if( millis() - lastMillis > viewMillis ) { 
    lastMillis = millis();
    
    color_t* logo = (color_t*) pgm_read_word( &(logoList[imgi]) );
    //pgm_read_word(
    grid.setFrame_P( logo );
    imgi++;
    if( imgi == logoListCount ) imgi = 0;
  }

  grid.update();

}



