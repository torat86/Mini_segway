#ifndef GPT_H_
#define GPT_H_

#include <Arduino.h>

//clk_src clock sources:
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/*
No Clock 												000
Peripheral Clock (ipg_clk)								001
High Frequency Reference Clock (ipg_clk_highfreq)		010
External clock 											011
Low Frequency Reference Clock (ipg_clk_32k)				100
Crystal oscillator as Reference Clock (ipg_clk_24M)		101
*/
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

void gpt_init_freerun(uint8_t clk_src);
void gpt_init_restart(uint8_t clk_src);
void gpt_start();
void gpt_stop();
uint32_t gpt_read();

#endif