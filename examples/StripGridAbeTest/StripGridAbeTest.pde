//
// StripGridAbeTest --
//
//
// 2011, Tod E. Kurt, http://todbot.com/blog/
//
//

#include <avr/pgmspace.h>

#include "StripGrid.h"

#include "Logos.h"

// note: more #includes below

enum { 
    MODE_OFF,
    MODE_PLASMA,
    MODE_LOGOS,
    MODE_SPARKLES,
    MODE_PIXELZIP,
    //MODE_WIPES,
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


StripGrid grid = StripGrid( rows,cols,
                            stripDPin, stripCPin, stripLPin, stripSPin, 
                            StripTypeHL1606 );


color_t colr;  // for temp color uses
unsigned long lastMillis;
int imgi=0;


#include "Plasma.h"
#include "Sparkles.h"
#include "Wipes.h"
#include "PixelZip.h"

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
void modeSwitch(int m)
{
  if( m<0 ) {  // m = -1 means do next mode
    mode++;
  }
  else { 
    mode = m;
  }
  // wrap around
  if( mode >= MODE_NONE ) {
    mode = MODE_OFF;
  }
  // reset any mode variables
  imgi = 0;
  
  Serial.print("mode="); Serial.println(mode);
}

//
void loop()
{
  // begin mode switch code 
  
  if( digitalRead( buttonPin ) == LOW ) { 
    delay( 100 );
    if( digitalRead( buttonPin ) == LOW ) { // make sure (simple debounce)
      modeSwitch(-1);
    }
    while( digitalRead(buttonPin) == LOW ); // wait it out
  }
  if( Serial.available() ) {
    while( Serial.read() != -1 ); // just consume
    modeSwitch(-1);
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
  else if( mode == MODE_PIXELZIP ) { 
    pixelzip_update();
  }
  /*
  else if( mode == MODE_WIPES ) { 
    wipes_update();
  }
  */
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

