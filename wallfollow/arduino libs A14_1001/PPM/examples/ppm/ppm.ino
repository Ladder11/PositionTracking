#include <PPM.h>

PPM ppm(2);

void setup(){
  Serial.begin(115200);

}

void loop(){
  /*to recalibrate channels print out the raw data for the channel and using the setLow and setHigh
  command set the high and low values for the given channel*/
  //ppm.setLow(1,900); //set new low value for mapping output
  //ppm.setHigh(1, 1830); //set new high value for mapping output
  Serial.print(ppm.getChannel(1));
  Serial.print(',');
  Serial.print(ppm.getRawChannel(1));
  Serial.print(',');
  Serial.print(ppm.getChannel(2));
  Serial.print(',');
  Serial.print(ppm.getRawChannel(2));
  Serial.print(',');
  Serial.print(ppm.getChannel(3));
  Serial.print(',');
  Serial.print(ppm.getRawChannel(3));
  Serial.print(',');
  Serial.print(ppm.getChannel(4));
  Serial.print(',');
  Serial.print(ppm.getRawChannel(4));
  Serial.print(',');
  Serial.print(ppm.getChannel(5));
  Serial.print(',');
  Serial.print(ppm.getRawChannel(5));
  Serial.print(',');
  Serial.print(ppm.getChannel(6));
  Serial.print(',');
  Serial.println(ppm.getRawChannel(6));
}


