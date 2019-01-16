
import processing.serial.*;
String val;
Serial myPort;
PShape euroFighter;


void setup()
{
  size(640, 360, P3D);
  frameRate(100);
  String portName = Serial.list()[0];
  myPort = new Serial (this, portName, 115200);
  euroFighter = loadShape("Eurofighter.obj");
  delay(3000);
}
void draw()
{
  background(255, 204, 0);

  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
    println(val);
    //if (val.contains("null") || val == null){
    if (val!=null) {
      if (!val.contains("null")) {
        String[] valArr = val.split(",");
        float[] valAng = new float [valArr.length];
        //println(val); //print it out in the console
        for (int i = 0; i < valArr.length; i ++) {
          try {
            valAng[i]= Float.parseFloat(valArr[i]);
          }
          catch(NumberFormatException e) {
            println("error");
          }
        }
        //float tempVal = Float.parseFloat(val);

        float tempValx = valAng[0];
        float tempValy = valAng[1];
        float tempValz = valAng[2];

        tempValx = map(tempValx, -180, 180, height, 0);
        tempValy = map(tempValy, -180, 180, height, 0);
        tempValz = map(tempValz, -180, 180, height, 0);

        lights();
        translate(300,150, -80);
        scale(15);
        rotateX(radians(tempValx));
        rotateY(radians(tempValy));
        shape(euroFighter);
        

        
        println(val);
      }
    }
  }
}
