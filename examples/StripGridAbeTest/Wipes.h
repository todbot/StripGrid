


void wipes_update()
{
  
  color_t colr1;
  color_t colr2;

  colr1.r = random(255);
  colr1.g = random(255);
  colr1.b = random(255);
  colr2.r = random(255);
  colr2.g = random(255);
  colr2.b = random(255);


  // wipe from left to right
  for( int j=0; j<cols; j++ ) {
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,j, colr1 );
    }
    grid.update();
    delay(100);
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,j, colr2 );
    }
  }

  colr1.r = random(255);
  colr1.g = random(255);
  colr1.b = random(255);
  colr2.r = random(255);
  colr2.g = random(255);
  colr2.b = random(255);

  // wipe from right to left
  for( int j=0; j<cols; j++ ) {
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,cols-1-j, colr1 );
    }
    grid.update();
    delay(100);
    for( int i=0; i<rows; i++ ) {
      grid.setLED( i,cols-1-j, colr2 );
    }
  }



}