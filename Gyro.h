#ifndef GYRO
#define GYRO
#include <Arduino.h>
#include <Wire.h>
#include <L3G.h>

class Gyro {
	public: 
		Gyro ();
		void initialize();
		float getGyro();
		void updateGyro();
		void setGyroOffset();
		void setGyroDrift();
	private:
		long prevTime;   //general purpose timer
		float G_gain=.00875; // gyros gain factor for 250deg/sec
		float gyro_x, gyro_xcumulative, gerrx, gdriftx, Dt;
		L3G gyro;
};
#endif