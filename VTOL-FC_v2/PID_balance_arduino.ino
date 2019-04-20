//BIG NOTE: the gear channel is three position

#include <Wire.h>
#include <Servo.h>


Servo right_motor;
Servo left_motor;

Servo right_servo;
Servo left_servo;

// mpu vars
int16_t Acc_rawX, Acc_rawY, Acc_rawZ,Gyr_rawX, Gyr_rawY, Gyr_rawZ;
float Acceleration_angle[2];
float Gyro_angle[2];
float Total_angle[2];
float elapsedTime, time, timePrev;
int i;
float rad_to_deg = 180/3.141592654;

// pid 
float PID, pwmLeft, pwmRight, error, previous_error;
float pid_p=0;
float pid_i=0;
float pid_d=0;
/////////////////PID CONSTANTS/////////////////
double kp=3.55;//3.55
double ki=0.005;//0.003
double kd=2.05;//2.05
///////////////////////////////////////////////

/////////// Chanels ///////////////////
double channel[4];


float desired_angle = 0; //This is the angle in which we whant the yaw


void setup() {
  Wire.begin(); //begin the wire comunication
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(250000);
  
  right_servo.attach(3); 
  left_servo.attach(5);
  
  right_motor.attach(6); //attatch the right motor to pin 6
  left_motor.attach(9);  //attatch the left motor to pin 9

  time = millis(); //Start counting time in milliseconds
  /*In order to start up the ESCs we have to send a min value
   * of PWM to them before connecting the battery. Otherwise
   * the ESCs won't start up or enter in the configure mode.
   * The min value is 1000us and max is 2000us, REMEMBER!*/
  left_motor.writeMicroseconds(1000); 
  right_motor.writeMicroseconds(1000);

  //seting pin mods
  // RX pins
  pinMode(2,INPUT);
  pinMode(4,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(12,INPUT);
  
  
  delay(1000); /*Give some delay, 7s, to have time to connect
                *the propellers and let everything start up*/ 
}//end of setup void

void loop() {
 // reading from the RX
  channel[0] = pulseIn(2,HIGH);   // throutel
  channel[1] = pulseIn(4,HIGH);   // right alivon
  channel[2] = pulseIn(7,HIGH);   // left alivon 
  channel[3] = pulseIn(8,HIGH);   // rudder
  channel[4] = pulseIn(12,HIGH);  // aux 1
  
  desired_angle = map(channel[3],1000,2000,45,-45);
  
  if (channel[4] > 1250){
    
    PID_balance();
  
  }else if (channel[4] < 1250){
    // manual mood
     left_motor.writeMicroseconds(channel[0] + desired_angle);
     right_motor.writeMicroseconds(channel[0] - desired_angle);
     left_servo.writeMicroseconds(channel[1]);
     right_servo.writeMicroseconds(channel[2]);
  
   }
   
}//end of loop void
