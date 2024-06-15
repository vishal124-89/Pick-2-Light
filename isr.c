#include <xc.h>

extern unsigned char ch;
    
void __interrupt() isr(void)
{
    if (RCIF == 1)
    {
        if (OERR == 1)    //frame overrun abit
            OERR = 0;
        
        ch = RCREG;
        
        RCIF = 0;
    }
}



