/*
 * main.cpp
 *
 *  Created on: Jan 15, 2021
 *      Author: Korneliusz Osmenda
 */

#include <sched/bezbios_sched_api.h>
#include <display/bezbios_display_api.h>
#include <uart/monitor.hpp>
#include <interrupts.h>
#include <uart/tlay2.hpp>

static BEZBIOS_INIT_PIT delay_implementation;

static void beep()
 {
	char leters[]="beep\n";
	while(1)
	{
		bezbios_delay_ms(1000);
		tlay2_uart.dbgout(leters);
	}

 }

static BEZBIOS_CREATE_PROCESS<beep,1024> beep_thread;

static void mainf()
{
	init_display();
	unsigned char line[640];
	for(int y=0;y<480;y++)
	{
		for(int x=0;x<640;x++)
			line[x]=(x%4)+4*(y%4);
		put_next_pixels(0,y,640,line);
	}
	int i = 0;
	while(1)
	{
		unsigned char palette[3*16];
		i++;
		if (i==3*4)
			i=0;

		for(int p=0;p<3*16;p++)
			palette[p]=0;
		palette[i+3*4*0] = 255;
		palette[i+3*4*1] = 255;
		palette[i+3*4*2] = 255;
		palette[i+3*4*3] = 255;

		put_palette(0,16,palette);
		bezbios_delay_ms(1000);
	}
}

static BEZBIOS_CREATE_PROCESS<mainf,1024> main_thread;

struct Tlay2Payloads tlay2_payloads[] = {
		{0,nullptr} // terminator
};
