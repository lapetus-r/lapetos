#ifndef _STDARG_HEADER_
#define _STDARG_HEADER_

typedef char *va_list;

#  define va_start(ap, p)	(ap = (char *) (&(p)+1))
#  define va_arg(ap, type)	((type *) (ap += sizeof(type)))[-1]
#  define va_end(ap)		((void)0)

#endif // _STDARG_HEADER_
