//
// StripGridAbeTest --
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//
//

#include <avr/pgmspace.h>

#include "HL1606strip.h"
#include "StripGrid.h"

#include "Logos.h"

// note: more #includes below

enum { 
    MODE_OFF,
    MODE_PLASMA,
    MODE_LOGOS,
    MODE_SPARKLES,
    MODE_NONE,
};
      
int mode = MODE_PLASMA;
    

// how long to view each logo
unsigned long durationMillis;

const int statusLedPin = 13;

const int stripDPin = 11;
const int stripLPin = 10;
const int stripCPin = 13;
const int stripSPin = 12;

const int buttonPin = 8;


HL1606strip strip = HL1606strip( stripDPin, stripSPin, stripLPin, stripCPin, rows*cols);
StripGrid grid = StripGrid( rows,cols, &strip );

unsigned long lastMillis;
int imgi=0;


#include "Plasma.h"
#include "Sparkles.h"

//
void setup()
{
  pinMode( statusLedPin, OUTPUT);
  digitalWrite( statusLedPin, HIGH);

  pinMode( buttonPin, INPUT);
  digitalWrite( buttonPin, HIGH); // turn on internal pullup

  Serial.begin(19200);
  Serial.println("StripGridAbeTest");

  grid.clear();
  grid.update();

  durationMillis = 0;

  plasma_begin();
}

//
void loop()
{
  // begin mode switch code 
  if( digitalRead( buttonPin ) == LOW ) { 
    delay( 100 );
    if( digitalRead( buttonPin ) == LOW ) { // make sure (simple debounce)
      mode++;
      if( mode == MODE_NONE ) {
        mode = MODE_OFF;
      }
      imgi=0;
    }
    while( digitalRead(buttonPin) == LOW ); // wait it out
    Serial.print("mode="); Serial.println(mode);
  }
  // end mode switch code 


  if( mode == MODE_PLASMA ) {
    plasma_morph();
  }
  else if( mode == MODE_LOGOS ) {
    logo_update();

  }
  else if( mode == MODE_SPARKLES ) { 
    sparkles_update();
  }
  else if( mode == MODE_OFF ) { 
    grid.clear();
    grid.update();
  }

}

void logo_update() 
{
  if( millis() - lastMillis > durationMillis ) {  // time up?
    lastMillis = millis();
    showNextLogo();
  }
}

//
void showNextLogo()
{
  // this is confusing, just roll with it
  color_t* logo = (color_t*) pgm_read_word( &(logoList[imgi]) );
  durationMillis = logoListDurations[imgi];
  Serial.println(durationMillis);
  grid.setFrame_P( logo );
  imgi++;
  if( imgi == logoListCount ) imgi = 0;
  grid.update();
}

