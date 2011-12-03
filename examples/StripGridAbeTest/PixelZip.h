

byte pzi,pzj;

color_t off = {0,0,0};
// march through from top to bottom, left to right
void pixelzip_update()
{
  colr.r = 0; 
  colr.g = 0;
  colr.b = 255;

  if( millis() - lastMillis > 10 ) { 
    lastMillis = millis();
    grid.setLED( pzi, pzj, colr );
    delay(1);
    grid.setLED( pzi,pzj, off );
    pzj++;
    if( pzj==cols ) { 
      pzj = 0;
      pzi++;
      if( pzi == rows ) {
        pzi = 0;
        colr.r = random(255);
        colr.g = random(255);
        colr.b = random(255);
      }
    }
    grid.update();
  }
}
