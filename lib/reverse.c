#include <string.h>

__norts__ asm
char *reverse(char *str)
{
	asm {
_strlen EXTERN

 pshs  u
*   register char *hd = s;
 ldu   4,s
 pshs  u
*   char *tl = hd + strlen(hd) - 1;
 pshs  u
 lbsr  _strlen
 leas  2,s
 addd  ,s++
 tfr   d,x
* while (hd < tl)
* {
 bra   @check
@loop ldb   ,u
*      temp = *hd;
*      *hd++ = *tl;
*      *tl-- = temp;
 lda   ,-x
 sta   ,u+
 stb   ,x
@check pshs  x
 cmpu  ,s++
 bcs   @loop
* }
 ldd   4,s
 puls  u,pc
 	}
}
