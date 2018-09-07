#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void simple(void)
{
	if( isascii('a') )
	{
		printf("%s isascii [PASS]\n",__func__);
	}
	else
	{
		printf("%s isascii [FAIL]\n",__func__);
	}

	if( isalpha('a') )
	{
		printf("%s isalpha [PASS]\n",__func__);
	}
	else
	{
		printf("%s isalpha [FAIL]\n",__func__);
	}

	if( islower('a') )
	{
		printf("%s islower [PASS]\n",__func__);
	}
	else
	{
		printf("%s islower [FAIL]\n",__func__);
	}

	if( isupper('A') )
	{
		printf("%s isupper [PASS]\n",__func__);
	}
	else
	{
		printf("%s isupper [FAIL]\n",__func__);
	}

	if( isdigit('5') )
	{
		printf("%s isdigit [PASS]\n",__func__);
	}
	else
	{
		printf("%s isdigit [FAIL]\n",__func__);
	}

	if( isxdigit('A') )
	{
		printf("%s isxdigit [PASS]\n",__func__);
	}
	else
	{
		printf("%s isxdigit [FAIL]\n",__func__);
	}

	if( isspace(' ') )
	{
		printf("%s isspace [PASS]\n",__func__);
	}
	else
	{
		printf("%s isspace [FAIL]\n",__func__);
	}

	if( ispunct('!') )
	{
		printf("%s ispunct [PASS]\n",__func__);
	}
	else
	{
		printf("%s ispunct [FAIL]\n",__func__);
	}

	if( iscntrl(0) )
	{
		printf("%s iscntrl [PASS]\n",__func__);
	}
	else
	{
		printf("%s iscntrl [FAIL]\n",__func__);
	}

}

void exhaustive( void )
{
	int a;

	for( a=0; a<0x80; a++ )
	{
		if( !isascii(a) )
		{
			printf("%s isascii+ [FAIL: %d]\n",__func__, a );
			break;
		}
	}

	for( a=0x80; a<0x100; a++ )
	{
		if( isascii(a) )
		{
			printf("%s isascii- [FAIL]: %d\n",__func__, a );
			break;
		}
	}
}

int main()
{
	simple();
	exhaustive();
	return 0;
}

