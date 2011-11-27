//
// StripGridDemo1 -- 
//
//
//

#include "HL1606strip.h"
#include "StripGrid.h"

// use -any- 3 pins!
#define STRIP_D 11
#define STRIP_L 10
#define STRIP_C 13
//#define STRIP_S 5

const int rows = 5;
const int cols = 6;
const int pixel_count = rows * cols;

HL1606strip strip = HL1606strip(STRIP_D, STRIP_L, STRIP_C, pixel_count);
//HL1606strip strip = HL1606strip(STRIP_D,STRIP_S,STRIP_L,STRIP_C, pixel_count);
StripGrid grid = StripGrid( rows,cols, &strip );

color_t green = {0,255,0};
color_t off   = {0,0,0};

void setup()
{
  Serial.begin(19200);
  Serial.println("StripGridDemo1");

  grid.clear();
  grid.update();

}

void loop()
{
  for( int i=0; i< rows; i++ ) { 
    for( int j=0; j<cols; j++ ) {
      int p = grid.ledpos(i,j);
      Serial.print("turning on: ");
      Serial.print(i); Serial.print(','); Serial.print(j); 
      Serial.print(" p:"); Serial.println(p);
      grid.setLED( i,j, green );
      grid.update();
      delay(500);
      grid.setLED( i,j, off );
    }
  }
    
}
