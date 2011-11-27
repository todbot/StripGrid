


#include "HL1606strip.h"
#include "StripGrid.h"


#include <avr/pgmspace.h>


const int statusLedPin = 13;

const int STRIP_D  = 11;
const int STRIP_L  = 10;
const int STRIP_C  = 13;
const int STRIP_S  = 12;


const int rows = 5;
const int cols = 6;
const int pixel_count = rows * cols;


#include "Logos.h"

HL1606strip strip = HL1606strip( STRIP_D, STRIP_L, STRIP_C, pixel_count);
StripGrid grid = StripGrid( rows,cols, &strip );


// temp var for holding a color value
color_t colr = {0,0,0};

int i=0,j=0;


//
void setLogo_P(const color_t* logo)
{
  for( int i=0; i< rows; i++ ) {
    for( int j=0; j<cols; j++ ) {
      memcpy_P( &colr, &logo[i*cols+j], sizeof(color_t) );
      grid.setLED( i,j, colr );
    }
  }
  grid.update();
}


//
void setup()
{
  pinMode( statusLedPin, OUTPUT);
  digitalWrite( statusLedPin, HIGH);

  Serial.begin(19200);
  Serial.println("StripGridDemo2");

  grid.clear();
  grid.update();

  setLogo_P( logo0 );  // takes 4ms on 5x6, 35ms on 30x40

}

boolean toggle = false;
//
void loop()
{
  Serial.println("loop");

  //grid.update();
  
  /*
  digitalWrite(statusLedPin, HIGH);
  delay(100);
  digitalWrite(statusLedPin, LOW);
  delay(100);
  */

  // reallly lame brightness control
  if( millis() > 5000 ) {
    setLogo_P( (toggle) ? logo1:logo0 ) ;
    toggle = !toggle;
  }

}

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


