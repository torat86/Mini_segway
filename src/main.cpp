/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
//Chaos ensues if header including Arduino.h is included here before header that includes Eigen
//#include "controllers.h"
//#include "io.h"
#include <Arduino.h>


extern "C" int main(void)
{
#ifdef USING_MAKEFILE

	pinMode(13, OUTPUT);
	//mpu_init();
	//Eigen::Vector2d result = Eigen::Vector2d::Zero();

/*	Wire.beginTransmission(mpu_addr);
	Wire.write(0x1A);
	Wire.endTransmission(false);
	Wire.requestFrom(mpu_addr, 1, true);
	int reg_val = Wire.read();
	Wire.endTransmission(true);*/

	//Timer-klokke 150MHz
	//Serial.begin(9600);
	//delay(100);
	while (1)
	{
		//mpu_data_print(mpu_read());
		//result = kalman(mpu_read());
		//Serial.print("Roll: ");
		//Serial.print((double)result[0]);
		//Serial.print("  Pitch: ");
		//Serial.println((double)result[1]);
		//TMR1_CTRL0 = 1;
		digitalWriteFast(13, HIGH);
		delay(5000);
		digitalWriteFast(13, LOW);
		delay(5000);
		//F_CPU_ACTUAL
		//Serial.print(reg_val);
		//LPF reg: 0x1A
	}


#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
#endif
return 0;
}

