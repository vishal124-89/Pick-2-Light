/*
 * File:   n_id.c
 * Author: Vishal
 *
 * Created on 5 June, 2024, 4:49 PM
 */


#include <xc.h>
#include "main.h"
#include "external_interrupt.h"
#include "digital_keypad.h"
#include "ssd_display.h"
#include "eeprom.h"

extern unsigned int key_detected;
static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

void n_id(char key) {
    static char field = 1,flag=1;
    static int i, j, k, l = 0;
    
    if(flag)
    {
        flag=0;
    i = (read_internal_eeprom(0x00)-48);
    j = (read_internal_eeprom(0x01)-48);
    k = (read_internal_eeprom(0x02)-48);
    l = (read_internal_eeprom(0x03)-48);
    }
  
    
    if (field < 5) {
        if (key == SWITCH2) {
            field++;
        }
    } 
    else if (field > 4)
        field = 1;

    if (field == 1) 
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
    
    else if (field == 2) 
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
    else if (field == 3) 
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
    else if (field == 4) 
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
        write_internal_eeprom(0x00, i+48);
        write_internal_eeprom(0x01, j+48);
        write_internal_eeprom(0x02, k+48);
        write_internal_eeprom(0x03, l+48);
        key_detected=!key_detected; //OFF ALL SSD         
    }

    display(ssd);
}

