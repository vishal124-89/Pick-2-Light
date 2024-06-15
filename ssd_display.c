/*
 * File:   ssd_display.c
 * Author: Vishal
 *
 * Created on 17 April, 2024, 2:36 PM
 */

#include <xc.h>
#include "ssd_display.h"

void init_ssd_control(void)
{
	/* Setting PORTD as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
}

/* Better if implemented in timer handler */
void display(unsigned char data[])
{
	unsigned int wait;
	unsigned char data_bit;
	unsigned char digit;

	for (digit = 0; digit < MAX_SSD_CNT; digit++)
	{
		SSD_DATA_PORT = data[digit];
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0x01 << digit);

		for (wait = 1000; wait--; );
        
	}
}
