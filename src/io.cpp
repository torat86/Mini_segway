/*
 * io.cpp
 *
 *  Created on: Jun 22, 2020
 *      Author: tor
 */
#include "io.h"

extern const int mpu_addr = 0x68;	//I2C address of the MPU-6050.


//Initialize MPU 6050
void mpu_init(void)
{
	//Put mpu out of sleep mode
	Wire.begin();
	Wire.beginTransmission(mpu_addr);
	Wire.write(0x6B);	// Power management register address
	Wire.write(0);	// Wakes up the MPU-6050
	Wire.endTransmission(true);
	delay(50);

	//Set mpu_low pass filter cutoff
	Wire.beginTransmission(mpu_addr);
	Wire.write(0x1A);	// dlpf register address
	Wire.write(2);	// 94 Hz for the accel and 98 Hz for the gyro
	Wire.endTransmission(true);
}


//Returns data read from the MPU 6050
double* mpu_read(void)
{
	//int16_t readings[7] = {};	//[Acc_x Acc_y Acc_z Temp Gyr_x Gyr_y Gyr_z]
	double* data = new double [7];

	while(!data[0])
	{
		Wire.beginTransmission(mpu_addr);
		Wire.write(0x3B);  //Starting with Acc_x
		Wire.endTransmission(false);
		Wire.requestFrom(mpu_addr, 14, true);  //Request a total of 14 registers

		for (int i = 0; i < 6; i++)
			data[i] = Wire.read()<<8|Wire.read();

		//Conversion and calibration
		data[0] = (data[0]*(19.62/32768))-0.67;
		data[1] = (data[1]*(19.62/32768))-0.055;
		data[2] = -(data[2]*(19.62/32768)-1.47);
		data[3] = data[3]/340.00+36.53;
		data[4] = 9-(data[4]*250)/32768;
		data[5] = 24 +(data[5]*250)/32768;
		data[6] = (data[6]*250)/32768;
	}

	return data;
}


//Prints to serial over USB
void mpu_data_print(double* data)
{
	//Serial.print("AcX = "); Serial.print(data[0]);
	//Serial.print(" | AcY = "); Serial.print(data[1]);
	//Serial.print(" | AcZ = "); Serial.print(data[2]);
	//Serial.print(" | Tmp = "); Serial.print(data[3]);  //equation for temperature in degrees C from datasheet
	//Serial.print(" | GyX = "); Serial.print(data[4]);
	//Serial.print(" | GyY = "); Serial.print(data[5]);
	//Serial.print(" | GyZ = "); Serial.println(data[6]);
	Serial.print(data[0]); Serial.print("  ");
	Serial.print(data[1]); Serial.print("  ");
	Serial.print(data[2]); Serial.print("  ");
	Serial.print(data[3]); Serial.print("  ");
	Serial.print(data[4]); Serial.print("  ");
	Serial.print(data[5]); Serial.print("  ");
	Serial.println(data[6]);
	delete[] data;
}


