//
// Random colored sparklies on a StripGrid
//
//

// assumes the following globals exist
// rows, cols == rows & col dimenions of grid
// grid -- StripGrid object
//



// call regularly in loop()
void sparkles_update()
{
  color_t colr;
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

  grid.update();

}
