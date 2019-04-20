void PID_balance (){
  /////////////////////////////I M U/////////////////////////////////////
    timePrev = time;  // the previous time is stored before the actual time read
    time = millis();  // actual time read
    elapsedTime = (time - timePrev) / 1000; 
 
     Wire.beginTransmission(0x68);
     Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
     Wire.endTransmission(false);
     Wire.requestFrom(0x68,6,true); 

     Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
     Acc_rawY=Wire.read()<<8|Wire.read();
     Acc_rawZ=Wire.read()<<8|Wire.read();

     /*---X---*/
     Acceleration_angle[0] = atan((Acc_rawY/16384.0)/sqrt(pow((Acc_rawX/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
     /*---Y---*/
     Acceleration_angle[1] = atan(-1*(Acc_rawX/16384.0)/sqrt(pow((Acc_rawY/16384.0),2) + pow((Acc_rawZ/16384.0),2)))*rad_to_deg;
 

   Wire.beginTransmission(0x68);
   Wire.write(0x43); //Gyro data first adress
   Wire.endTransmission(false);
   Wire.requestFrom(0x68,4,true); //Just 4 registers
   
   Gyr_rawX=Wire.read()<<8|Wire.read(); //Once again we shif and sum
   Gyr_rawY=Wire.read()<<8|Wire.read();
 


   /*---X---*/
   Gyro_angle[0] = Gyr_rawX/131.0; 
   /*---Y---*/
   Gyro_angle[1] = Gyr_rawY/131.0;

   /*---X axis angle---*/
   Total_angle[0] = 0.98 *(Total_angle[0] + Gyro_angle[0]*elapsedTime) + 0.02*Acceleration_angle[0];
   /*---Y axis angle---*/
   Total_angle[1] = 0.98 *(Total_angle[1] + Gyro_angle[1]*elapsedTime) + 0.02*Acceleration_angle[1];
   
   /*Now we have our angles in degree and values from -10º0 to 100º aprox*/
    Serial.println(channel[1]);

   
  
/*///////////////////////////P I D///////////////////////////////////*/

  
  error = Total_angle[1] - desired_angle;

  pid_p = kp*error;


  if(-3 <error <3)
  {
    pid_i = pid_i+(ki*error);  
  }


  pid_d = kd*((error - previous_error)/elapsedTime);


  PID = pid_p + pid_i + pid_d;


  if(PID < -1000)
  {
    PID=-1000;
  }
  if(PID > 1000)
  {
    PID=1000;
  }
  
  pwmLeft = channel[0] + PID;
  pwmRight = channel[0] - PID;
  
  

  //Right
  if(pwmRight < 1000)
  {
    pwmRight= 1000;
  }
  if(pwmRight > 2000)
  {
    pwmRight=2000;
  }
  //Left
  if(pwmLeft < 1000)
  {
    pwmLeft= 1000;
  }
  if(pwmLeft > 2000)
  {
    pwmLeft=2000;
  }
  

  left_motor.writeMicroseconds(pwmLeft);
  right_motor.writeMicroseconds(pwmRight);
  previous_error = error; 
   
}
