#include "gpt.h"

void gpt_init_freerun(uint8_t clk_src)
{

	GPT1_CR &= ~GPT_CR_EN;
	GPT1_IR &= 0x0000;
	GPT1_CR &= ~(GPT_CR_OM3(0) | GPT_CR_OM2(0) | GPT_CR_OM1(0));
	GPT1_CR &= ~(GPT_CR_IM2(0) | GPT_CR_IM1(0));
	GPT1_CR |= GPT_CR_CLKSRC(clk_src);
	GPT1_CR |= GPT_CR_SWR;
	GPT1_SR &= 0x0000;
	GPT1_CR |= GPT_CR_ENMOD;
	GPT1_IR |= 0x003F;
	GPT1_CR |= GPT_CR_FRR;
}

void gpt_init_restart(uint8_t clk_src)
{

	GPT1_CR &= ~GPT_CR_EN;
	GPT1_IR &= 0x0000;
	GPT1_CR &= ~(GPT_CR_OM3(0) | GPT_CR_OM2(0) | GPT_CR_OM1(0));
	GPT1_CR &= ~(GPT_CR_IM2(0) | GPT_CR_IM1(0));
	GPT1_CR |= GPT_CR_CLKSRC(clk_src);
	GPT1_CR |= GPT_CR_SWR;
	GPT1_SR &= 0x0000;
	GPT1_CR |= GPT_CR_ENMOD;
	GPT1_IR |= 0x003F;
	GPT1_CR &= ~GPT_CR_FRR;
}


void gpt_start() {GPT1_CR |= GPT_CR_EN;}
void gpt_stop() {GPT1_CR &= ~GPT_CR_EN;}
uint32_t gpt_read() {return GPT1_CNT;}