#ifndef GYRO
#define GYRO
#include <Arduino.h>
#include <Wire.h>
#include <L3G.h>

class Gyro {
	public: 
		Gyro ();
		void initialize();
		float getXGyro();
		float getYGyro();
		float getZGyro();
		void updateGyro();
		void setGyroOffset();
		void setGyroDrift();
	private:
		long prevTime;   //general purpose timer
		float G_gain=.00875; // gyros gain factor for 250deg/sec
		float gyro_x, gyro_y, gyro_z, gyro_xcumulative, gyro_ycumulative, gyro_zcumulative, gerrx, gerry, gerrz, gdriftx, gdrifty, gdriftz, Dt;
		L3G gyro;
};
#endif