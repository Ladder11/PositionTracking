//Written by Joe St. Germain 8/1/15
// Simply keeps track of the gyro reading from an minimu9
// I reccommend going one step further with a 
//complimentary filter with the accelerometer for greater accuracy over longer periods of time. 
#include "Gyro.h"

Gyro::Gyro() {

}

void Gyro::initialize() {
  Wire.begin(); // i2c begin
  gyro.enableDefault(); // gyro init. default 250/deg/s
  delay(1000);// allow time for gyro to settle
  
  setGyroOffset();
  setGyroDrift();
  prevTime = millis();
}

float Gyro::getXGyro() {
  return gyro_xcumulative;
}

float Gyro::getYGyro() {
  return gyro_ycumulative;
}

float Gyro::getZGyro() {
  return gyro_zcumulative;
}

void Gyro::updateGyro() {
  Dt = (float)(millis()-prevTime)/1000.0;
  gyro.read(); // read gyro

  gyro_x=(float)(gyro.g.x-gerrx)*G_gain; // offset by error then multiply by gyro gain factor 
  gyro_y=(float)(gyro.g.y-gerry)*G_gain;
  gyro_z=(float)(gyro.g.z-gerrz)*G_gain;

  gyro_x = (gyro_x-gdriftx)*Dt; // Multiply the angular rate by the time interval
  gyro_y = (gyro_y-gdrifty)*Dt; 
  gyro_z = (gyro_z-gdriftz)*Dt;

  gyro_xcumulative += gyro_x; // add the displacment(rotation) to the cumulative displacment
  gyro_ycumulative += gyro_y;
  gyro_zcumulative += gyro_z;

  prevTime=millis(); //reset prevTime
}

void Gyro::setGyroOffset() {
  for(int i =0;i<100;i++){  // takes 100 samples of the gyro
    gyro.read();
    gerrx+=gyro.g.x;
    gerry+=gyro.g.y;
    gerrz+=gyro.g.z;
    delay(25);
  }

  gerrx = gerrx/100; // average reading to obtain an error/offset
  gerry = gerry/100;
  gerrz = gerrz/100;

  Serial.println(gerrx); // print error vals
  Serial.println(gerry);  
  Serial.println(gerrz);
}

void Gyro::setGyroDrift() {
// Get drift rate
  long stime = millis();
  for(int i =0;i<100;i++){  // takes 100 samples of the gyro
    gyro.read();
    gyro_x=(float)(gyro.g.x-gerrx)*G_gain; // offset by error then multiply by gyro gain factor 
    gyro_y=(float)(gyro.g.y-gerry)*G_gain;
    gyro_z=(float)(gyro.g.z-gerrz)*G_gain;

    gyro_x = gyro_x*0.025; // Multiply the angular rate by the time interval
    gyro_y = gyro_y*0.025; 
    gyro_z = gyro_z*0.025;

    gdriftx += gyro_x; // add the displacment(rotation) to the cumulative displacment
    gdrifty += gyro_y;
    gdriftz += gyro_z;
    delay(25);
  }
  long etime = millis();
  gdriftx = gdriftx/(etime-stime)*1000; // Accumulated rate over the sample time to obtain drift rate
  gdrifty = gdrifty/(etime-stime)*1000;
  gdriftz = gdriftz/(etime-stime)*1000;

  Serial.println(gdriftx, 5); // print error vals
  Serial.println(gdrifty, 5);  
  Serial.println(gdriftz, 5);
}
