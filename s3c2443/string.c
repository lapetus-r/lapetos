#include <include.h>

// ���� : ��ҹ��ڸ� ���� ������ ����� ���ڿ� ��
int strnicmp(const char *s1, const char *s2, size_t len)
{
	unsigned char c1, c2;

	c1 = 0;	c2 = 0;
	if (len) {
		do {
			c1 = *s1; c2 = *s2;
			s1++; s2++;
			if (!c1)
				break;
			if (!c2)
				break;
			if (c1 == c2)
				continue;
			c1 = tolower(c1);
			c2 = tolower(c2);
			if (c1 != c2)
				break;
		} while (--len);
	}
	return (int)c1 - (int)c2;
}

char * ___strtok;

// ���� : ���ڿ� ����
char * strcpy(char * dest,const char *src)
{
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;
}

// ���� : ���ڿ� ����
char * strncpy(char * dest,const char *src,size_t count)
{
	char *tmp = dest;

	while (count-- && (*dest++ = *src++) != '\0')
		/* nothing */;

	return tmp;
}

// ���� : ���ڿ� �߰�
char * strcat(char * dest, const char * src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0')
		;

	return tmp;
}

// ���� : ���ڿ� �߰�
char * strncat(char *dest, const char *src, size_t count)
{
	char *tmp = dest;

	if (count) {
		while (*dest)
			dest++;
		while ((*dest++ = *src++)) {
			if (--count == 0) {
				*dest = '\0';
				break;
			}
		}
	}

	return tmp;
}

// ���� : ���ڿ� ��
int strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}

// ���� : ���ڿ� ��
int strncmp(const char * cs,const char * ct,size_t count)
{
	register signed char __res = 0;

	while (count) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
		count--;
	}

	return __res;
}

// ���� : ���ڿ��ӿ��� ���ڸ� �߰��Ѵ�.
char * strchr(const char * s, int c)
{
	for(; *s != (char) c; ++s)
		if (*s == '\0')
			return NULL;
	return (char *) s;
}

// ���� : ���ڿ��� ���̸� ��ȯ�Ѵ�.
size_t strlen(const char * s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

// ���� : ���ڿ��ӿ��� ���ڸ� �߰��Ѵ�.
char * strrchr(const char * s, int c)
{
       const char *p = s + strlen(s);
       do {
           if (*p == (char)c)
               return (char *)p;
       } while (--p >= s);
       return NULL;
}

// ���� : ���ڿ��� ���̸� ��ȯ�Ѵ�.
size_t strnlen(const char * s, size_t count)
{
	const char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

// ���� : ���ڿ��� ���� ������ �� �Ѵ�.
size_t strspn(const char *s, const char *accept)
{
	const char *p;
	const char *a;
	size_t count = 0;

	for (p = s; *p != '\0'; ++p) {
		for (a = accept; *a != '\0'; ++a) {
			if (*p == *a)
				break;
		}
		if (*a == '\0')
			return count;
		++count;
	}

	return count;
}

// ���� : ���� ���ڸ� �˻��Ѵ�.
char * strpbrk(const char * cs,const char * ct)
{
	const char *sc1,*sc2;

	for( sc1 = cs; *sc1 != '\0'; ++sc1) {
		for( sc2 = ct; *sc2 != '\0'; ++sc2) {
			if (*sc1 == *sc2)
				return (char *) sc1;
		}
	}
	return NULL;
}

// ���� : ��ū ���ڸ� �����Ѵ�.
char * strtok(char * s,const char * ct)
{
	char *sbegin, *send;

	sbegin  = s ? s : ___strtok;
	if (!sbegin) {
		return NULL;
	}
	sbegin += strspn(sbegin,ct);
	if (*sbegin == '\0') {
		___strtok = NULL;
		return( NULL );
	}
	send = strpbrk( sbegin, ct);
	if (send && *send != '\0')
		*send++ = '\0';
	___strtok = send;
	return (sbegin);
}

// ���� : ���ڿ����� ��ū�� �����Ѵ�.
char * strsep(char **s, const char *ct)
{
	char *sbegin = *s, *end;

	if (sbegin == NULL)
		return NULL;

	end = strpbrk(sbegin, ct);
	if (end)
		*end++ = '\0';
	*s = end;

	return sbegin;
}

// ���� : �޸� ������ Ư�� ���� ä���.
void * memset(void * s,int c,size_t count)
{
	char *xs = (char *) s;

	while (count--)
		*xs++ = c;

	return s;
}

// ���� : �޸� ������ �����Ѵ�.
char * bcopy(const char * src, char * dest, int count)
{
	char *tmp = dest;

	while (count--)
		*tmp++ = *src++;

	return dest;
}

// ���� : �޸� ������ �����Ѵ�.
void * memcpy(void * dest,const void *src,size_t count)
{
	char *tmp = (char *) dest, *s = (char *) src;

	while (count--)
		*tmp++ = *s++;

	return dest;
}

// ���� : �޸� ������ �����Ѵ�.
void * memmove(void * dest,const void *src,size_t count)
{
	char *tmp, *s;

	if (dest <= src) {
		tmp = (char *) dest;
		s = (char *) src;
		while (count--)
			*tmp++ = *s++;
		}
	else {
		tmp = (char *) dest + count;
		s = (char *) src + count;
		while (count--)
			*--tmp = *--s;
		}

	return dest;
}

// ���� : �޸� ������ ���Ѵ�.
int memcmp(const void * cs,const void * ct,size_t count)
{
	const unsigned char *su1, *su2;
	signed char res = 0;

	for( su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}

// ���� : �޸� �������� ���� Ž���Ѵ�
void * memscan(void * addr, int c, size_t size)
{
	unsigned char * p = (unsigned char *) addr;

	while (size) {
		if (*p == c)
			return (void *) p;
		p++;
		size--;
	}
  	return (void *) p;
}

// ���� : ���ڿ����� �ٸ� ���ڿ��� Ž���Ѵ�.
char * strstr(const char * s1,const char * s2)
{
	int l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *) s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1,s2,l2))
			return (char *) s1;
		s1++;
	}
	return NULL;
}

// ���� : �޸𸮿��� 1 ����Ʈ�� Ž���Ѵ�.
void *memchr(const void *s, int c, size_t n)
{
	const unsigned char *p = s;
	while (n-- != 0) {
        	if ((unsigned char)c == *p++) {
			return (void *)(p-1);
		}
	}
	return NULL;
}

// ���� : �빮�� ���ڿ��� �ٲ۴�.
void UpperStr( char *Str )
{
   while( *Str ){ *Str = toupper( *Str ); Str++; }
}

// ���� : �ҹ��� ���ڿ��� �ٲ۴�.
void LowerStr( char *Str )
{
   while( *Str ){ *Str = tolower( *Str ); Str++; }
}

// ���� : ��ġ�� ���ڿ��� ���������� �ٲ۴�.
unsigned long strtoul(const char *p, char **out_p, int base)
{
	unsigned long v = 0;

	while (isspace(*p))
		p++;
	if (((base == 16) || (base == 0)) &&
	    ((*p == '0') && ((p[1] == 'x') || (p[1] == 'X'))))
	{
		p += 2;
		base = 16;
	}
	if (base == 0)
	{
		if (*p == '0')
			base = 8;
		else
			base = 10;
	}
	while (1)
	{
		char c = *p;
		if ((c >= '0') && (c <= '9') && (c - '0' < base))
			v = (v * base) + (c - '0');
		else if ((c >= 'a') && (c <= 'z') && (c - 'a' + 10 < base))
			v = (v * base) + (c - 'a' + 10);
		else if ((c >= 'A') && (c <= 'Z') && (c - 'A' + 10 < base))
			v = (v * base) + (c - 'A' + 10);
		else
			break;
		p++;
	}

	if (out_p) *out_p = (char*)p;
	return v;
}
