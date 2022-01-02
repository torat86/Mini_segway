/*
 * io.h
 *
 *  Created on: Jun 22, 2020
 *      Author: tor
 */

#ifndef IO_H_
#define IO_H_

#include <Arduino.h>
#include <Wire/Wire.h>

extern const int mpu_addr; //Change to static in io.cpp later?

void mpu_init(void);
void mpu_data_print(double* data);
double* mpu_read(void);


#endif /* IO_H_ */
