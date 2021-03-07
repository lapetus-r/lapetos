#include <include.h>

/* printf */
int printf(const char *fmt, ...)
{
	char buffer[1024];
	va_list ap;
	int len;

	va_start(ap, fmt);
	len = vsprintf(buffer, fmt, ap);
	va_end(ap);
    SerialOutStr_CheckCR(buffer, len);
	return len;
}

/* putchar */
void putchar(unsigned int ch)
{
	while(!(UTRSTAT1 &  0x2));
	UTXH1 = (char)ch;
}
/* getchar */
unsigned int getchar(void)
{
	unsigned int ch;
	
	while(!(UTRSTAT1 & 0x1));
	ch = URXH1;

	return ch;
}
