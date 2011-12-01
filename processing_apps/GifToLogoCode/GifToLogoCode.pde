//
//
// 

import javax.swing.*;
import java.awt.*;

// The files must be in the "data" folder of the sketch

int rows = 10;
int cols = 16;

int scale = 20;
int viewMillis = 100;

String[] imgNames;
PImage[] imgs = new PImage[10];
String textstr;

//
void setup() 
{
  size(cols*scale, rows*scale);

  textstr  = "//\n";
  textstr += "// Logos.h -- place this file in your StripGrid Arduino sketch folder\n";
  textstr += "//\n";
  textstr += "// Generated on "+year()+"/"+month()+"/"+day()+"@"+hour()+":"+minute()+"\n\n";
  textstr += "const int rows="+rows+";\n";
  textstr += "const int cols="+cols+";\n";

  getImageNames();
  
}

int i=0;
int lastMillis;
boolean done = false;
//
void draw() 
{
  if( !done && (millis() - lastMillis) > viewMillis ) { 
    lastMillis = millis();
    imgs[i] = imageToFrameCode( imgNames[i] );
    image( imgs[i], 0,0, cols*scale, rows*scale );  
    i++;
    if( i == imgNames.length ) { // done!
      done = true;
      textstr += "\n// list of all the logos\n";
      textstr += "const int logoListCount = "+imgNames.length+";\n";
      textstr += "const PROGMEM color_t* logoList[] = {\n";
      for( int i=0; i<imgNames.length; i++ ) { 
        String name = nameFromImageName( imgNames[i] );
        textstr += "  "+name+",\n";
      }
      textstr += "};\n";
      textstr += "// end of file\n";
      showText();
    }
  }
}

String nameFromImageName( String imgname ) 
{
  String name = imgname.replaceAll("\\.gif","");
  name = name.replaceAll("\\-","");
  return name;
}

//
PImage imageToFrameCode( String imgname ) 
{
  String name = nameFromImageName( imgname );
  String thistext = "\nconst PROGMEM color_t "+name+"[rows*cols] = {\n";
  PImage img = loadImage( imgname ); 
  
  img.loadPixels(); // get the pixels[] array populated
  for( int i=0; i< rows; i++ ) {
    //thistext += "// line "+i+"\n";
    for( int j=0; j<cols; j++ ) { 
      int colr = img.pixels[ i*cols + j];
      String r = str(int(red(colr)));
      String g = str(int(red(colr)));
      String b = str(int(red(colr)));
      thistext += "{"+r+","+g+","+b+"}, ";
    }
    thistext += "\n";
  }
  thistext += "};\n";

  textstr += thistext; // FIXME: don't rely on globals

  return img;
}

//
void getImageNames() 
{
  // http://exampledepot.com/egs/java.io/GetFiles.html
  println("sketchPath: "+sketchPath);
  String imgPath = sketchPath + File.separator + "data";
  File dir = new File(imgPath);
  imgNames = dir.list();
  if( imgNames == null ) {
    // dir doesn't exist or not a directory
  } 
  else {
    for( int i=0; i<imgNames.length; i++) {
      String filename = imgNames[i];
      println("imgNames["+i+"]: "+filename);
    }
  }
}

//
void showText()
{

  Color cBgLightGray = new Color(200, 200, 200);
  Color cBgDarkGray  = new Color(100, 100, 100);
  JDialog dialog = new JDialog(frame, "Arduino Code Output", false);
  
  JPanel panel = new JPanel(new BorderLayout());
  Font font = new Font( "Monospaced", Font.PLAIN, 12);
  JTextArea editArea = new JTextArea(textstr, 48,80);
  editArea.setFont( font );
  JScrollPane scrollPane = new JScrollPane(editArea, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
  panel.add( scrollPane, BorderLayout.CENTER);
  
  dialog.getContentPane().add(panel);
  
  dialog.setPreferredSize( new Dimension(600,450));
  dialog.setResizable(true);
  dialog.setLocationRelativeTo(frame); // center it on the BlinkMSequencer
  dialog.pack();
  dialog.setVisible(true);
  
}
