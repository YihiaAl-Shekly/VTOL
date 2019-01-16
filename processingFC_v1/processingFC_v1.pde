// import processing serial library and declaring some variables
import processing.serial.*;
String val;
Serial myPort;
PShape euroFighter;

// setup
void setup()
{
  size(640, 360, P3D);
  frameRate(100);
  String portName = Serial.list()[0];
  myPort = new Serial (this, portName, 115200);
  euroFighter = loadShape("Eurofighter.obj");
  delay(3000);
}
// loop
void draw()
{
  background(255, 204, 0);
  // serial communication
  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
    println(val);
    if (val!=null) {                             //ignore null's
      if (!val.contains("null")) {
        String[] valArr = val.split(",");             // split the string 
        float[] valAng = new float [valArr.length];     //convert the sting to float arry
        //println(val); //print it out in the console
        for (int i = 0; i < valArr.length; i ++) {
          try {
            valAng[i]= Float.parseFloat(valArr[i]);
          }
          catch(NumberFormatException e) {
            println("error");
          }
        }
        // assigning the array to individual floats
        float tempValx = valAng[0];
        float tempValy = valAng[1];
        float tempValz = valAng[2];
        
        // maping the vals to 180 
        tempValx = map(tempValx, -180, 180, height, 0);
        tempValy = map(tempValy, -180, 180, height, 0);
        tempValz = map(tempValz, -180, 180, height, 0);
        
        
        // insirting the 3d model and rotating the 3d model based on the values 
        lights();
        translate(300,150, -80);
        scale(15);
        rotateX(radians(tempValx));
        rotateY(radians(tempValy));
        rotateZ(radians(tempValz));
        shape(euroFighter);
        

        
        println(val);
      }
    }
  }
}
