#include <s3c2440.h>
#include <time.h>
#include <gpio.h>
#include <serial.h>
#include <stdio.h>
#include <string.h>

#define HIS_MAX               8

char HisBuff[HIS_MAX][32] = { {0,}, };
int  HisCount               = 0;
int  HisIndex               = 0;

// ���� : �ѹ��ڸ� ����Ѵ�. 

int putc(char c)
{
	SerialOutChar_CheckCR( c );
	return 1;
}

// ���� : �ѹ��ڸ� ����Ѵ�. 

int putx(char c)
{
	SerialOutChar( c );
	return 1;
}

// ���� : ������ ���ڿ��� ����Ѵ�. 

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

// ���� : �ѹ����� �Է��� ��´�. 

int getc(void)
{
	unsigned int lp = 0;

	// �ѹ��� ��� 
	while( !SerialIsReadyChar() ) 
    {
		lp++;
    }
	return SerialIsGetChar() & 0xFF;
}

// ���� : ���ڿ� �Է��� �޴´�. ( CR�� �Էµɶ����� )

int gets(char *s)
{
     int cnt = 0;
     char  c;

     while((c = getc()) != CR)
     {
          if(c != BS) 
          {  
               cnt++;
               *s++ = c;
               printf("%c",c );
          }
          else 
          {
               if(cnt > 0) 
               { cnt--; *s-- = ' '; 
                 printf("\b \b");  
               } 
               
          }
     }
     *s = 0;
   
     return(cnt);
}

// ���� : �����丮�� �߰� �Ѵ�. 

int his_append(char *s)
{
    int loop;

    // �̹� ���� ���ڿ��� ������ �����Ѵ�. 
    for( loop = 0; loop < HIS_MAX; loop++ )
    {
      if( strcmp( s, HisBuff[loop] ) == 0 ) 
      {
          HisIndex = 0;
          if( HisCount ) HisIndex = HisCount-1;
          return HisCount;
      } 
    } 

    // ���ο� ������ �����丮 ���ۿ� �߰� �Ѵ�. 
    if( HisCount < HIS_MAX )
    {
        strcpy( HisBuff[HisCount], s );
        HisCount++;
    }
    else
    {   
        for( loop = 1; loop < HIS_MAX ; loop++ )
        {
            strcpy( HisBuff[loop-1], HisBuff[loop] );
        }
        strcpy( HisBuff[HIS_MAX-1], s );
        HisIndex = HisCount-1;
    }

    HisIndex = 0; 
    if( HisCount ) HisIndex = HisCount-1;

    return HisCount;
}

// ���� : �����丮�� ���� ���ۿ� �����Ѵ�. 

int his_set(char *s, int index )
{
    int loop;
    int len;

    len = strlen( s );

    // ���� ���� ���ڿ��� �����. 
    for( loop = 0; loop < len; loop++ )
    {
      printf("\b \b");
    }
     
    // ���� ������ �����Ѵ�. 
    strcpy( s, HisBuff[index] ); 
    printf( "%s", s );

    return index;
}

// ���� : ���ڿ� �Է��� �޴´�. ( CR�� �Էµɶ����� )

int gets_his(char *s)
{
     int cnt = 0;
     char  *fp;
     char  c;

     fp = s;
     
     while( 1 )
     {
          c = getc();

          if( c == CR )
          {
              *s = 0;
              if( strlen( fp ) ) his_append( fp );
              break;
          } 

          switch( c )
          {
          case 0x1a  : // ^Z
                       if( HisIndex >= 0 )
                       { 
                           his_set( fp, HisIndex );
                           if( HisIndex ) HisIndex--;
                           if( HisIndex >= HisCount ) HisIndex = HisCount -1;
                           cnt = strlen( fp );
                           s = fp + cnt; 
                       } 
                       break;
          case 0x18  : // ^X
                       if( HisIndex < HisCount )
                       { 
                           his_set( fp, HisIndex );
                           HisIndex++;
                           cnt = strlen( fp );
                           s = fp + cnt; 
                       }  
                       break;
      
          case BS    : if( cnt > 0 )
                       { 
                         cnt--; *s-- = ' '; 
                         printf("\b \b");  
                       } 
                       break;
          default    : cnt++;
                       *s++ = c;
                       printf("%c",c );
                       break;
          }
     }
   
     return(cnt);

}

// ���� : �ѹ����� �Է��� ��´�. 

int     getc_timed( char cmpKey, int mTimeOver )
{
		char    key;
		unsigned char	Dtime;
		
    	Dtime = mTimeOver/500;

		if(Dtime == 0) Dtime =1;
    	
    	FreeTimer(0);
		ReloadTimer(0, 500);

        // Ÿ�̸�0 �����÷ο��Ʈ�� ������ ���� ���
		while( Dtime > 0 )
		{
			while( 0 == TimeOverflow(0) )
			{
				if ( SerialIsReadyChar() )
				{
					key = SerialIsGetChar()&0xFF;
					if ( cmpKey     == key ) return 0;
					if ( (char)0x0d == key ) return -1;
				}
			}
       		FreeTimer(0);
       		ReloadTimer(0, 500);
       		printf( "." );
       		Dtime--;
		}
        
        return -1;
}
