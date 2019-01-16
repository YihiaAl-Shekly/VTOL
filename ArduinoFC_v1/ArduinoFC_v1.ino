#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
//yaw
unsigned long timer = 0;
float timeStep = 0.01;
int yaw;

void setup() 
{
  Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    //Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  //establishContact();  // send a byte to establish contact until receiver responds
}

void loop()
{ 
  //if (Serial.available() > 0) {
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();
  // yaw
  Vector norm = mpu.readNormalizeGyro();
  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;
  //yaw
  timer = millis();
  yaw = yaw + norm.ZAxis * timeStep;
  // Output
  //Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(",");
  Serial.print(roll);
  //yaw
  Serial.print(",");
  Serial.print(yaw);

 
  
  delay((timeStep*1000) - (millis() - timer));
  Serial.println();
  //delay(10); 
   //println(" Pitch = " +pitch + " Roll = "+roll+" Yaw = "+yaw);

  //}
}
