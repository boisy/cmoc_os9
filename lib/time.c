#include "time.h"

asm error_code
_os_getime(_os_time *time)
{
    asm
    {
_sysret EXTERN  
* stack:
*	0,s = return address
*	2,s = time packet pointer
        ldx     2,s		get pointer to time packet
        os9     F$Time
        lbra    _sysret
    }
}


asm error_code
_os_setime(_os_time *time)
{
    asm
    {
* stack:
*	0,s = return address
*	2,s = time packet pointer
        ldx     2,s		get pointer to time packet
        os9     F$STime
        lbra    _sysret
    }
}