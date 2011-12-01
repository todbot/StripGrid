//
// GifToLogoCode --Generate Arduino code from GIF images
// 
// 2011, Tod E. Kurt, http://todbot.com/blog/
// 
// Note: the gif files must be in the "data" folder of the sketch
//

// for animated gif support  http://www.extrapixel.ch/processing/gifAnimation/
import gifAnimation.*;

// for pop-up text box
import javax.swing.*;
import java.awt.*;


int rows = 10;
int cols = 16;

int scale = 20;       // scale magnification for viewing
int viewMillis = 100; // how long to wait between images when viewing

String[] imgPaths;
ArrayList<String> imgNames = new ArrayList();
ArrayList<PImage> imgs = new ArrayList();
String textstr=""; 

Gif myGif;

//
void setup() 
{
  size(cols*scale, rows*scale);

  getImagePaths();

  getImages(); // all images are now loaded

  generateCode();

}

int i=0;
int lastMillis;
boolean done = false;
//
void draw() 
{
  if( !done && (millis() - lastMillis) > viewMillis ) { 
    lastMillis = millis();
    PImage img = imgs.get(i);
    image( img, 0,0, cols*scale, rows*scale );  
    i++;
    if( i == imgs.size() ) { // done!
      done = true;
      showText();
    }
  }
}


// generate code text from images
void generateCode()
{
  textstr += "//\n";
  textstr += "// Logos.h -- place this file in your StripGrid Arduino sketch folder\n";
  textstr += "//\n";
  textstr += "// Generated on "+year()+"/"+month()+"/"+day()+"@"+hour()+":"+minute()+"\n\n";
  textstr += "const int rows="+rows+";\n";
  textstr += "const int cols="+cols+";\n";

  for( int i=0; i< imgs.size(); i++ ) {
    PImage img = imgs.get(i);
    String name = imgNames.get(i);
    textstr += imageToFrameCode( img, name ); 
  }

  textstr += "\n// list of all the logos\n";
  textstr += "const int logoListCount = "+imgs.size()+";\n";
  textstr += "const int logoListDurations[] = {\n";
  for( int i=0; i<imgNames.size(); i++ ) { 
    String name = imgNames.get(i);
    int duration = 1000;
    textstr += "  "+duration+", // "+name+"\n";
  }
  textstr += "};\n";
  textstr += "const PROGMEM color_t* logoList[] = {\n";
  for( int i=0; i<imgNames.size(); i++ ) { 
    textstr += "  "+ imgNames.get(i)+",\n";
  }
  textstr += "};\n";
  textstr += "// end of file\n";
  
}
//
String imageToFrameCode( PImage img, String name )
{
  String thistext = "\nconst PROGMEM color_t "+name+"[rows*cols] = {\n";
  
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

  return thistext;
}

// get PImages for all gifs, explodes animated gifs too
void getImages()
{
  for( int i=0; i< imgPaths.length; i++ ) { 
    String imgpath = imgPaths[i];
    String name = nameFromImagePath( imgpath );
    PImage[] anim = Gif.getPImages(this, imgpath );
    for( int j=0; j<anim.length; j++ ) { 
      imgNames.add( name+j ); // makes name0, name1, name2, etc.
      imgs.add( anim[j] );    // but may only be one frame
    }
  }
}

//
String nameFromImagePath( String imgpath ) 
{
  String name = imgpath.replaceAll("\\.gif","");
  name = name.replaceAll("\\-","");
  return name;
}

//
void getImagePaths() 
{
  // http://exampledepot.com/egs/java.io/GetFiles.html
  println("sketchPath: "+sketchPath);
  String imgPath = sketchPath + File.separator + "data";
  File dir = new File(imgPath);
  imgPaths = dir.list();
  if( imgPaths == null ) {
    // dir doesn't exist or not a directory
  } 
  else {
    for( int i=0; i<imgPaths.length; i++) {
      String filename = imgPaths[i];
      println("imgPaths["+i+"]: "+filename);
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
  dialog.setLocationRelativeTo(frame); // center it 
  dialog.pack();
  dialog.setVisible(true);
  
}
