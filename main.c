/*
 * File:   main.c
 * Author: Vishal
 *
 * Created on 12 June, 2024, 11:56 AM
 */


#include <xc.h>
#include "clcd.h"
#include "uart.h"
#include "can.h"

extern char rcv_data[8];
extern char tmt_data[];
char u[5]={},n[5]={};
unsigned char ch;

void init_config() 
{  
    init_clcd();
    init_uart();
    init_can();
    PEIE = 1;
   GIE = 1;
   
}

void main(void) 
{
    init_config();
    static int i = 0,enter=0;
                            puts("Enter the node-id (maximum 4 characters : \n\r");

    while (1)
    {
        if (can_receive())
        {
            clcd_print("  n-id    u-st  ", LINE1(0));
            
            for(int i=0; i<4; i++)
                clcd_putch(rcv_data[i],LINE2(2+i));
            
            for(int i=4; i<8; i++)
                clcd_putch(rcv_data[i], LINE2(6+i));

            puts("Received data.\n\r");
            puts("node-id : ");
            for (int j = 0; j < 4; j++)
                putch(rcv_data[j]);
            puts("\n\r");
            puts("count : ");
                for (int j = 4;j < 8; j++)
            putch(rcv_data[j]);
            
            puts("\n\r");
        }
                
                
            if(ch != '\0')
            {
                if(ch != 13 && enter==0)
                {
                    if(i<4  )
                    {
                    tmt_data[i] = ch;
                    putch(ch);
                    i++;
                    }
                }
                else if(ch != 13 && enter == 1 )
                {
                        
                    if(i>4 )
                    {
                    tmt_data[i] = ch;
                    putch(ch);
                    i++;
                    }
                }
                else
                {
                    
                    char full = i,j=0;
                    while(full<4)
                    {
                        if(enter)
                            u[j] = '0';
                        else
                            n[j] = '0';
                        j++;
                    }
                    char k = 0;
                    for(;j<4;j++)
                    {
                        if(enter)
                            u[j]=tmt_data[k];
                        else
                            n[j] = tmt_data[k];
                        k++;
                    }
                    i=0;
                    
                    enter++;
                    puts("\n\r");
                }
                
                if(enter == 2)
                {
                    //i=0;
                    enter=0;
                    can_transmit();
                    CLEAR_DISP_SCREEN;
                    clcd_print("Transmitted",LINE1(0));
                }
                if(enter)
                        puts("Enter the count (maximum 4 characters : \n\r");
                    else
                        puts("Enter the node-id (maximum 4 characters : \n\r");
                ch ='\0';

            }
    }
}

