

byte pzi,pzj;

color_t off = {0,0,0};
// march through from top to bottom, left to right
void pixelzip_update()
{
  if( pzj == 0 ) {
    colr.r = random(255);
    colr.g = random(255);
    colr.b = random(255);
    if( colr.r < 128 && colr.g < 128 && colr.b < 128 ) { colr.r = 255; }
  } 
   
  if( millis() - lastMillis > 5 ) { 
    lastMillis = millis();
    grid.setLED( pzi, pzj, colr );
    grid.update();
    delay(10);
    grid.setLED( pzi,pzj, off );
    pzj++;
    if( pzj==cols ) { 
      pzj = 0;
      pzi++;
      if( pzi == rows ) {
        pzi = 0;
      }
    }
    grid.update();
  }
}
