#include <include.h>
#include "../../src/include/kernel.h"	/* 대체경로 "/home/lapetus/바탕화면/lapetOS/src/include/kernel.h"*/
#include "font.h"
#define gray		 0x888888
#define black		 0x000000
#define white		 0xffffff
#define red		 0x0000ff
#define orange	 0x33ccff
#define yellow	 0x00ffff
#define green	 0x00ff00
#define blue		 0xff0000

extern void (*Put_Pixel)(unsigned int x, unsigned int y, int color);
extern void (*Put_Pixel_back)(unsigned int x, unsigned int y, int color);
/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ lprintf ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

int lprintf(const char *fmt, ...)
{
	char buffer[1024];
	va_list ap;
	int len;
	va_start(ap, fmt);
	len = vsprintf(buffer, fmt, ap);
	va_end(ap);
	bg_lputs(440, 252,0xff00,0x000000, buffer);
	return len;
}


/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ LCD_Write ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
/*
 LCD 디바이스에 문자열을 보낸다. 
설명 : char형 포인터 배열을 사용하여 매개변수로 넘어오는 char형 배열을 28단위로 잘라 포인터 배열에 순차적으로 넣어주며, 
17번째 줄이 변경되는 순간, 포인터배열의 0번지에는 1번지의 값이 1번지에는 2번지의 값이 넘어가며 마지막 17번째 배열에는 매개변수로 넘어오는 char형 배열의 값이 저장되어 순차적인 스크롤 기능을 구현한 것이다.

각 명령문뒤의 주석은 매개변수의 역할을 설명한것이다.
*/

int LCD_Write( char *str, int size )	
{
static char *line[17];									//char형 배열의 주소값을 저장하기위한 char 포인터형 배열
static int i=0;				
int j=0,k,l=0;

	while(j<size){
		if(i<17){
			line[i]=&str[j];
		}else if(i>=17){
			for(k=0;k<=15;k++){
				line[k]=line[k+1];
			}   line[k]=&str[j];
 		}
		i++;
		j+=28;
	}
	for(l=0;l<17;l++){
		bg_lputs(243,l*16+2,0xff00,0x000000,line[l]);			//4번째 매개변수는 글자외의 부분에 백그라운드를 주는 기능으로써 0x0은 검정색을 뜻한다.
	}
	
	return 0;			
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ State ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
int State(int create, int running){
	
	lprintf("%d",ticks);

	switch(create){
		case 1:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Create!\n");
		break;
		case 2:
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Create!\n");
		break;
		case 3:
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Create!\n");
		break;
		case 4:
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Create!\n");
		break;
		case 5:
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Create!\n");
		break;
	}

	switch(running){
		case 1:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Running!\n");
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Suspend!\n");
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Suspend!\n");
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Suspend!\n");
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Suspend!\n");
		break;
		case 2:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Suspend!\n");
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Running!\n");
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Suspend!\n");
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Suspend!\n");
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Suspend!\n");
		break;
		case 3:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Suspend!\n");
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Suspend!\n");
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Running!\n");
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Suspend!\n");
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Suspend!\n");
		break;
		case 4:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Suspend!\n");
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Suspend!\n");
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Suspend!\n");
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Running!\n");
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Suspend!\n");
		break;
		case 5:
			bg_lputs(293, 138,0xff00,0x000000,"Proc_1 is Suspend!\n");
			bg_lputs(293, 154,0xff00,0x000000,"Proc_2 is Suspend!\n");
			bg_lputs(293, 170,0xff00,0x000000,"Proc_3 is Suspend!\n");
			bg_lputs(293, 186,0xff00,0x000000,"Proc_4 is Suspend!\n");
			bg_lputs(293, 202,0xff00,0x000000,"Proc_5 is Running!\n");
		break;
	}

	return running;
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ lputs ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/
void lputs(unsigned int x, unsigned int y, unsigned int color, char *str)
{
	int i,j,k;
	int oneLine;

	for(i=0;i<strlen(str);i++) {
		for(j=0; j<16; j++) {
			if ((str[i]>=0x20)&&(str[i]<0x80))	{
				oneLine=chr_font8X16[str[i]-0x20][j];
			}else{
				oneLine=0;
			}
			for(k=0;k<8;k++) {
				if(oneLine&(1<<k))	{
					Put_Pixel(x+7-k,y+j-1,color);

				}

			}
		}
		x+=8;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ bg_lputs ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void bg_lputs(unsigned int x, unsigned int y, unsigned int color, unsigned int bgcolor, char *str)
{
	int i,j,k;
	int oneLine;

	for(i=0;i<strlen(str);i++) {
		for(j=0; j<16; j++) {
			if ((str[i]>=0x20)&&(str[i]<0x80)){	
				oneLine=chr_font8X16[str[i]-0x20][j];
			}else{
				oneLine=0;
			}

			for(k=0;k<8;k++) {
				if(oneLine&(1<<k)){
					Put_Pixel(x+7-k,y+j,color);
				}else{
					Put_Pixel(x+7-k,y+j,bgcolor);
						if(j==15&&y>=257){				//맨하단줄 사라지는 에러 수정
							LCD_Line(240, 271, 479, 271, 0xff00);
						}
				}
			}
		}
		x+=8;
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ TFT_Box ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/


void TFT_Box(int x1, int y1, int x2, int y2, int color)
{
	int x, y, xx1, yy1, xx2, yy2;
	
	if(x2 > x1) xx1=x1, xx2= x2;
	else		xx1=x2, xx2= x1;

	if(y2 > y1) yy1=y1, yy2= y2;
	else		yy1=y2, yy2= y1;
     
	for(y=yy1;y<=yy2;y++)
		for(x=xx1;x<=xx2;x++)	
			Put_Pixel(x, y, color);		     		
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 											 [ TFT_Box_Select_Color ]												   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

/*
설명 : LCD의 좌측 사각형에 순서와 색상을 선택한다.
i 매개변수는 사각형의 위치를 선택하는 것이며, 
color 는 사각형의 색깔을 선택하는 것 
ex)0번 블랙 1번은 흰색 2번은 빨간색 3번은 주황색 4번은 노란색 5번은 초록색 6번은 파랑색
*/
void TFT_Box_Select_Color(int i, int color)
{
unsigned int Box_color=0;
		switch(color){
			case 0:
				Box_color = black;
			break;
			case 1:
				Box_color = white;
			break;
			case 2:
				Box_color =red;
			break;
			case 3:
				Box_color = orange;
			break;
			case 4:
				Box_color = yellow;
			break;
			case 5:
				Box_color = green;
			break;
			case 6:
				Box_color = blue;
			break;
		}
			switch(i){
				case 1:
					TFT_Box(2,2,119,135,Box_color);//1번째 사각형
				break;
				case 2:
					TFT_Box(121,2,239,135,Box_color);//2번째 사각형
				break;
				case 3:
					TFT_Box(241,2,359,135,Box_color);//3번째 사각형
				break;
				case 4:
					TFT_Box(361,2,479,135,Box_color);//4번째사각형
				break;
				case 5:
					TFT_Box(2,137,119,270,Box_color);//5번째 사각형
				break;

			}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 												 [ LCD_Line ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/


void LCD_Line(int x1, int y1, int x2, int y2, int color)
{
	int dx,dy,e;
	dx=x2-x1; 
	dy=y2-y1;
    
	if(dx>=0) {
		if(dy >= 0) { // dy>=0
			if(dx>=dy) { // 1/8 octant
				e=dy-dx/2;
				while(x1<=x2) {
					Put_Pixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			} else {		// 2/8 octant
				e=dx-dy/2;
				while(y1<=y2) {
					Put_Pixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		} else {		   // dy<0
			dy=-dy;   // dy=abs(dy)
			if(dx>=dy) { // 8/8 octant
				e=dy-dx/2;
				while(x1<=x2) {
					Put_Pixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1+=1;
					e+=dy;
				}
			} else {		// 7/8 octant
				e=dx-dy/2;
				while(y1>=y2) {
					Put_Pixel(x1,y1,color);
					if(e>0){x1+=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	} else { //dx<0
		dx=-dx;		//dx=abs(dx)
		if(dy >= 0) { // dy>=0
			if(dx>=dy) { // 4/8 octant
				e=dy-dx/2;
				while(x1>=x2) {
					Put_Pixel(x1,y1,color);
					if(e>0){y1+=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			} else {		// 3/8 octant
				e=dx-dy/2;
				while(y1<=y2) {
					Put_Pixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1+=1;
					e+=dx;
				}
			}
		} else {		   // dy<0
			dy=-dy;   // dy=abs(dy)
			if(dx>=dy) { // 5/8 octant
				e=dy-dx/2;
				while(x1>=x2) {
					Put_Pixel(x1,y1,color);
					if(e>0){y1-=1;e-=dx;}	
					x1-=1;
					e+=dy;
				}
			} else {		// 6/8 octant
				e=dx-dy/2;
				while(y1>=y2) {
					Put_Pixel(x1,y1,color);
					if(e>0){x1-=1;e-=dy;}	
					y1-=1;
					e+=dx;
				}
			}
		}	
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 												 [ TFT_CLR ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void TFT_CLR(unsigned int k)
{
	int i, j;
	
	if(k) {			// Clear Buffer 1
		for(i=0;i<LCD_XSIZE;i++)
	 		for(j=0;j<LCD_YSIZE;j++)
	 			Put_Pixel_back(i,j,0x0);
	} else {		// Clear Buffer 0
		for(i=0;i<LCD_XSIZE;i++)
	 		for(j=0;j<LCD_YSIZE;j++)
	 			Put_Pixel(i,j,0x000000);
	}
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 												 [ TFT_Intro ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void TFT_Intro(void)
{
	int i,j;
	
	for(j=0;j<LCD_YSIZE;j++) {
		for(i=0;i<LCD_XSIZE;i++) {
			if((i<LCD_XSIZE/2)&&(j<LCD_YSIZE/2)) 			
				Put_Pixel(i,j,0xff0000);
			else if((i>=LCD_XSIZE/2)&&(j<LCD_YSIZE/2)) 		
				Put_Pixel(i,j,0x00ff00);
			else if((i<LCD_XSIZE/2)&&(j>=LCD_YSIZE/2)) 		
				Put_Pixel(i,j,0x0000ff);
			else if((i>=LCD_XSIZE/2)&&(j>=LCD_YSIZE/2)) 	
				Put_Pixel(i,j,0xffffff);
		}
	}
}

/*

╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 													 [ LOGO ]																   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

void LCD_LOGO(void)
{
	lputs(123, 138, 0xff00, "SangMyung University");
	lputs(123, 154, 0xff00, "lapetOS");
	lputs(123, 170, 0xff00, "Made By :");
	lputs(123, 186, 0xff00, "Park Il-Kwon ");
	lputs(123, 202, 0xff00, "Yoo Sang-Gi ");
	lputs(123, 218, 0xff00, "2011-2012");
	lputs(390, 252,0xff00, "Ticks:");
//	lputs(123, 234, 0xff00, "");
//	lputs(123, 250, 0xff00, "");
//	lputs(123, 266, 0xff00, "");
}

/*
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
┃				 											 [ LCD_SQUARE ]															   ┃
╋━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╋
*/

/*아래 함수는 LCD에 아웃라인을 그려주는 함수로써 형광초록색을 나타냅니다.*/
void LCD_SQUARE(void)
{
LCD_Line(1, 1, 1, 272, green); // 상단
LCD_Line(1, 1, 480, 1, green); //좌측
LCD_Line(479, 1, 479, 272, green); //우측
LCD_Line(1, 271, 479, 271, green); //하단

LCD_Line(240,1,240,136,green);//세로줄
LCD_Line(120,1,120,272,green);//세로줄
LCD_Line(360,1,360,136,green);//세로줄
LCD_Line(290,136,290,272,green);//세로줄
LCD_Line(1,136,480,136,green);//가로줄
}

void LCD_TIMER_Select( int n)
{
//int i; //좌표 선택을 위한 변수
int x,y;//좌표 이동을 위한 변수
int f; //for loop를 위한 변수
		switch(n){
				case 1:
					x=0; y=0;
					f=60;
					while(f<121){
					LCD_Line(x+60,y+68,x+f,y+2,green);		//1키기		
					LCD_Line(x+60,y+68,x+f,y+2,green);				//1끄기
					f+=7;
					}
					f=9;
					while(f<137){
					LCD_Line(x+60,y+68,x+119,y+f,green);			
					LCD_Line(x+60,y+68,x+119,y+f,green);			
					f+=8;
					}
					f=68;
					while(f<120){
					LCD_Line(x+60,y+68,x+f,y+135,green);
					LCD_Line(x+60,y+68,x+f,y+135,green);			
					f+=7;						
					}
					f=60;
					while(f>7){
					LCD_Line(x+60,y+68,x+f,y+135,green);					
					LCD_Line(x+60,y+68,x+f,y+135,green);					
					f-=8;
					}
					f=136;
					while(f>6){
					LCD_Line(x+60,y+68,x+2,y+f,green);					
					LCD_Line(x+60,y+68,x+2,y+f,green);					
					f-=8;
					}
					f=1;
					while(f<60){
					LCD_Line(x+60,y+68,x+f+1,y+2,green);			
					LCD_Line(x+60,y+68,x+f+1,y+2,green);			
					f+=7;
					}
				break;

				case 2:
					x=120;y=0;
					f=60;
					while(f<121){
					LCD_Line(x+60,y+68,x+f,y+2,yellow);		//1키기		
					LCD_Line(x+60,y+68,x+f,y+2,yellow);				//1끄기
					f+=7;
					}
					f=9;
					while(f<137){
					LCD_Line(x+60,y+68,x+119,y+f,yellow);			
					LCD_Line(x+60,y+68,x+119,y+f,yellow);			
					f+=8;
					}
					f=68;
					while(f<120){
					LCD_Line(x+60,y+68,x+f,y+135,yellow);
					LCD_Line(x+60,y+68,x+f,y+135,yellow);			
					f+=7;						
					}
					f=60;
					while(f>7){
					LCD_Line(x+60,y+68,x+f,y+135,yellow);					
					LCD_Line(x+60,y+68,x+f,y+135,yellow);					
					f-=8;
					}
					f=136;
					while(f>6){
					LCD_Line(x+60,y+68,x+2,y+f,yellow);					
					LCD_Line(x+60,y+68,x+2,y+f,yellow);					
					f-=8;
					}
					f=1;
					while(f<60){
					LCD_Line(x+60,y+68,x+f,y+2,yellow);			
					LCD_Line(x+60,y+68,x+f,y+2,yellow);			
					f+=7;
					}
				break;
					
				case 3:
					x=240;y=0;
					f=60;
					while(f<121){
					LCD_Line(x+60,y+68,x+f,y+2,red);		//1키기		
					LCD_Line(x+60,y+68,x+f,y+2,red);				//1끄기
					f+=7;
					}
					f=9;
					while(f<137){
					LCD_Line(x+60,y+68,x+119,y+f,red);			
					LCD_Line(x+60,y+68,x+119,y+f,red);			
					f+=8;
					}
					f=68;
					while(f<120){
					LCD_Line(x+60,y+68,x+f,y+135,red);
					LCD_Line(x+60,y+68,x+f,y+135,red);			
					f+=7;						
					}
					f=60;
					while(f>7){
					LCD_Line(x+60,y+68,x+f,y+135,red);					
					LCD_Line(x+60,y+68,x+f,y+135,red);					
					f-=8;
					}
					f=136;
					while(f>6){
					LCD_Line(x+60,y+68,x+2,y+f,red);					
					LCD_Line(x+60,y+68,x+2,y+f,red);					
					f-=8;
					}
					f=1;
					while(f<60){
					LCD_Line(x+60,y+68,x+f,y+2,red);			
					LCD_Line(x+60,y+68,x+f,y+2,red);			
					f+=7;
					}
				break;

				case 4:
					x=360; y=0;
					f=60;
			while(f<121){
					LCD_Line(x+60,y+68,x+f,y+2,yellow);		//1키기		
					LCD_Line(x+60,y+68,x+f,y+2,yellow);				//1끄기
					f+=7;
					}
					f=9;
					while(f<137){
					LCD_Line(x+60,y+68,x+119,y+f,yellow);			
					LCD_Line(x+60,y+68,x+119,y+f,yellow);			
					f+=8;
					}
					f=68;
					while(f<120){
					LCD_Line(x+60,y+68,x+f,y+135,yellow);
					LCD_Line(x+60,y+68,x+f,y+135,yellow);			
					f+=7;						
					}
					f=60;
					while(f>7){
					LCD_Line(x+60,y+68,x+f,y+135,yellow);					
					LCD_Line(x+60,y+68,x+f,y+135,yellow);					
					f-=8;
					}
					f=136;
					while(f>6){
					LCD_Line(x+60,y+68,x+2,y+f,yellow);					
					LCD_Line(x+60,y+68,x+2,y+f,yellow);					
					f-=8;
					}
					f=1;
					while(f<60){
					LCD_Line(x+60,y+68,x+f,y+2,yellow);			
					LCD_Line(x+60,y+68,x+f,y+2,yellow);			
					f+=7;
					}
				break;

				case 5:
					x=0; y=135;
					f=60;
					while(f<121){
					LCD_Line(x+60,y+68,x+f,y+2,green);		//1키기		
					LCD_Line(x+60,y+68,x+f,y+2,green);				//1끄기
					f+=7;
					}
					f=9;
					while(f<137){
					LCD_Line(x+60,y+68,x+119,y+f,green);			
					LCD_Line(x+60,y+68,x+119,y+f,green);			
					f+=8;
					}
					f=68;
					while(f<117){
					LCD_Line(x+60,y+68,x+f,y+135,green);
					LCD_Line(x+60,y+68,x+f,y+135,green);			
					f+=7;						
					}
					f=60;
					while(f>7){
					LCD_Line(x+60,y+68,x+f,y+135,green);					
					LCD_Line(x+60,y+68,x+f,y+135,green);					
					f-=8;
					}
					f=134;
					while(f>7){
					LCD_Line(x+60,y+68,x+2,y+f,green);					
					LCD_Line(x+60,y+68,x+2,y+f,green);					
					f-=8;
					}
					f=1;
					while(f<60){
					LCD_Line(x+60,y+68,x+f+1,y+2,green);			
					LCD_Line(x+60,y+68,x+f+1,y+2,green);			
					f+=7;
					}
				break;
		}
}
