/*
 * File:   u_st.c
 * Author: Vishal
 *
 * Created on 5 June, 2024, 4:48 PM
 */


#include <xc.h>
#include "main.h"
#include "external_interrupt.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "eeprom.h"
#include "can.h"
#include "uart.h"

extern unsigned int key_detected;
static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
char buffer[8];

void u_st(char key) {
    static char u_field = 1,flag=1;
    static int i, j, k, l = 0;
    
    if(flag)
    {
        flag=0;
    i = (read_internal_eeprom(0x04)-48);
    j = (read_internal_eeprom(0x05)-48);
    k = (read_internal_eeprom(0x06)-48);
    l = (read_internal_eeprom(0x07)-48);
    }
    
    if (u_field < 5) {
        if (key == SWITCH2) {
            u_field++;
        }
    } 
    else if (u_field > 4)
        u_field = 1;

    if (u_field == 1) 
    {
        if (key == SWITCH1) 
        {
            i++;
            if (i > 9) {
                i = 0;
            }
        }
        ssd[0] = digit[i] | DOT;
        ssd[1] = digit[j];
        ssd[2] = digit[k];
        ssd[3] = digit[l];
    } 
    
    else if (u_field == 2) 
    {
        if (key == SWITCH1) 
        {
            j++;
            if (j > 9) {
                j = 0;
            }
        }
        ssd[0] = digit[i];
        ssd[1] = digit[j]| DOT;
        ssd[2] = digit[k];
        ssd[3] = digit[l];
    } 
    else if (u_field == 3) 
    {
        if (key == SWITCH1) 
        {
            k++;
            if (k > 9) {
                k = 0;
            }
        }
        ssd[0] = digit[i];
        ssd[1] = digit[j];
        ssd[2] = digit[k] | DOT;
        ssd[3] = digit[l];
    } 
    else if (u_field == 4) 
    {
        if (key == SWITCH1) 
        {
            l++;
            if (l > 9) {
                l = 0;
            }
        }
        ssd[0] = digit[i];
        ssd[1] = digit[j];
        ssd[2] = digit[k];
        ssd[3] = digit[l] | DOT;
    } 
    
    if (key == SWITCH3) 
    {
        
        write_internal_eeprom(0x04, i+48);
        write_internal_eeprom(0x05, j+48);
        write_internal_eeprom(0x06, k+48);
        write_internal_eeprom(0x07, l+48);
        
        for(int i=0; i<8; i++)
            buffer[i] = read_internal_eeprom(i);
        
        can_transmit();

        key_detected=!key_detected;         //OFF All LED
    }

    display(ssd);
}