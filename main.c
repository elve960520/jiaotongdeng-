#include < reg52.h >
#include <intrins.h>

typedef unsigned char uchar;  
typedef unsigned int uint;

#define NUM P0

int mode;//定义模式


unsigned int set_ns_time = 20;
unsigned int set_we_time = 12;
unsigned int time;
unsigned int temp_time = 0;

sbit num_ns_L = P1^1;
sbit num_ns_R = P1^2;
sbit num_we_L = P1^3;
sbit num_we_R = P1^4;

sbit led = P1^0;

sbit ns_RED = P2^5;
sbit ns_YELLOW = P2^4;
sbit ns_GREEN = P2^3;
sbit we_RED = P2^2;
sbit we_YELLOW = P2^1;
sbit we_GREEN = P2^0;

sbit reset_key = P3^3;
sbit night_key = P3^4;
sbit urgent_key = P3^5;
sbit ns_key = P3^6;
sbit we_key = P3^7;
sbit confirm_key = P3^2;
sbit add_key = P1^7;
sbit sub_key = P1^6;
sbit change_key = P1^5;

char  Show_Num[] = {
	0xED,			//数字0
	0x81,			//数字1
	0x6B,			//数字2
	0xAB,			//数字3
	0x87,			//数字4
	0xAE,			//数字5
	0xEE,			//数字6
	0x89,			//数字7
	0xEF,			//数字8
	0xAF			//数字9
};
void Delay10ms()		//@12.000MHz  改为20 s
{
	unsigned char i, j;

	i = 40;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}

//定时器初始化
void system_Init()
{
	TMOD=0x01; 
	TH0=(65535 - 50000) / 256; 
	TL0=(65535 - 50000) % 256;
	TR0=1; 
	ET0=1; 
	EA=1; 
}
//按键初始化
void key_init()
{
	reset_key = 1;
	night_key = 1;
	urgent_key = 1;
	ns_key = 1;
	we_key = 1;
	confirm_key = 1;
	add_key = 1;
	sub_key = 1;
	change_key = 1;
}

//按键扫描
int key_scan()
{
	if(reset_key == 0) 
	{
		Delay10ms();
		if(reset_key == 0)
		{
			while(!reset_key);
			return 1;
		}
	}
	else if(night_key == 0) 
	{
		Delay10ms();
		if(night_key == 0)
		{
			while(!night_key);
			return 2;
		}			
	}
	else if(urgent_key == 0) 
	{
		Delay10ms();
		if(urgent_key == 0)
		{
			while(!urgent_key);
			return 3;
		}
//		else 
//			return 0;
	}
	else if(ns_key == 0)
	{
		Delay10ms();
		if(ns_key == 0)
		{
			while(!ns_key);
			return 4;
		}
//		else 
//			return 0;
	}		
	else if(we_key == 0)
	{
		Delay10ms();
		if(we_key == 0)
		{
			while(!we_key);
			return 5;
		}
//		else 
//			return 0;
	}		
	else if(confirm_key == 0)
	{
		Delay10ms();
		if(confirm_key == 0)
		{
			while(!confirm_key);
			return 6;
		}
//		else 
//			return 0;
	}	
	else if(add_key == 0) 
	{
		Delay10ms();
		if(add_key == 0)
		{
			while(!add_key);
			return 7;
		}
	}
	else if(sub_key == 0) 
	{
		Delay10ms();
		if(sub_key == 0)
		{
			while(!sub_key);
			return 8;
		}
//		else 
//			return 0;
	}
	else if(change_key == 0) 
	{
		Delay10ms();
		if(change_key == 0)
		{
			while(!change_key);
			return 9;
		}
//		else 
//			return 0;
	}
	else return 0;
}
//显示每一位的数值
void show_num(int num1,int num2,int en1,int en2)
{
	int i,j,k,h;
	i = (int)num1/10;
	j = (int)num1%10;
	k = (int)num2/10;
	h = (int)num2%10;
	if(en1)
	{
		if(i!=0)
		{		
			num_ns_L = 1;
			num_ns_R = 1;
			num_we_L = 1;
			num_we_R = 1;

			NUM = Show_Num[i];
			num_ns_L = 0;
			num_ns_R = 1;
			num_we_L = 1;
			num_we_R = 1;	
		}
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;		
		NUM = Show_Num[j];
		num_ns_L = 1;
		num_ns_R = 0;
		num_we_L = 1;
		num_we_R = 1;	
		
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;
	}
	else 
	{
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;	
	}
	if(en2)
	{
		if(k!=0)
		{
			num_ns_L = 1;
			num_ns_R = 1;
			num_we_L = 1;
			num_we_R = 1;	
			NUM = Show_Num[k];		
			num_ns_L = 1;
			num_ns_R = 1;
			num_we_L = 0;
			num_we_R = 1;		
		}
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;
		NUM = Show_Num[h];		
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 0;		

		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;
	}		
	else 
	{
		num_ns_L = 1;
		num_ns_R = 1;
		num_we_L = 1;
		num_we_R = 1;	
	}
}
//模式一:白天正常
void mode_one()
{
	if(time <= 0) time = set_ns_time + set_we_time;
	if(time <= set_ns_time + set_we_time && time >= set_we_time+4)
	{
		ns_RED = 1;
		ns_YELLOW = 1;
		ns_GREEN = 0;
		we_RED = 0;
		we_YELLOW = 1;
		we_GREEN = 1;
		show_num((time-set_we_time),(time-set_we_time),1,1);
	}
	else if(time <= set_we_time+4 && time >= set_we_time)
	{
		ns_RED = 1;
		if(time%2 == 0)
			ns_YELLOW = 1;
		else if(time%2 == 1)
			ns_YELLOW = 0;
		ns_GREEN = 1;
		we_RED = 0;
		we_YELLOW = 1;
		we_GREEN = 1;
		show_num((time-set_we_time),(time-set_we_time),1,1);

	}
	else if(time <= set_we_time && time >= 4)
	{
		ns_RED = 0;
		ns_YELLOW = 1;
		ns_GREEN = 1;
		we_RED = 1;
		we_YELLOW = 1;
		we_GREEN = 0;
		show_num(time,time,1,1);

	}
	else if(time <= 4 && time >= 0)
	{
		ns_RED = 0;
		ns_YELLOW = 1;
		ns_GREEN = 1;
		we_RED = 1;
		if(time%2 == 0)
			we_YELLOW = 1;
		else if(time%2 == 1)
			we_YELLOW = 0;
		we_GREEN = 1;
		show_num(time,time,1,1);

	}
}
//模式二：夜间模式
void mode_two()
{
	ns_RED = 1;
	ns_GREEN = 1;
	we_RED = 1;	
	we_GREEN = 1;
	if(time%2 == 0)
	{
		we_YELLOW = 1;
		ns_YELLOW = 1;
	}
	else if(time%2 == 1)
	{
		we_YELLOW = 0;
		ns_YELLOW = 0;
	}
	show_num(0,0,0,0);

}
//模式三：紧急模式
void mode_three()
{
	ns_RED = 0;
	ns_YELLOW = 1;
	ns_GREEN = 1;
	we_RED = 0;
	we_YELLOW = 1;
	we_GREEN = 1;
	show_num(0,0,0,0);
}	
//模式四：南北通行
void mode_four()
{
//	flag = 0;
	ns_RED = 1;
	ns_YELLOW = 1;
	ns_GREEN = 0;
	we_RED = 0;
	we_YELLOW = 1;
	we_GREEN = 1;
	show_num(0,0,0,0);
}
//模式五：东西通行
void mode_five()
{
	ns_RED = 0;
	ns_YELLOW = 1;
	ns_GREEN = 1;
	we_RED = 1;
	we_YELLOW = 1;
	we_GREEN = 0;
	show_num(0,0,0,0);
}
//模式六：南北调整时间
void mode_six()
{
	int i;
	ns_RED = 1;
	ns_YELLOW = 1;
	ns_GREEN = 1;
	we_RED = 1;
	we_YELLOW = 1;
	we_GREEN = 1;
	while(1)
	{
		i = key_scan();
		if (i == 6) 
		{
			time = set_ns_time + set_we_time;
			mode = 1;			
			break;
		}
		else if(i == 9) 
		{
			mode = 8;
			break;
		}
		else if(i == 7) 
		{
			set_ns_time++;
		}
		else if(i == 8) 
		{
			set_ns_time--;
		}
		else if(i == 0)
		{
			show_num(set_ns_time,0,1,0);
		}
	}
}
//模式七：东西调整时间
void mode_seven()
{
	int i;
	ns_RED = 1;
	ns_YELLOW = 1;
	ns_GREEN = 1;
	we_RED = 1;
	we_YELLOW = 1;
	we_GREEN = 1;
	while(1)
	{
		i = key_scan();
		if (i == 6) 
		{
			time = set_ns_time + set_we_time;
			mode = 1;			
			break;
		}
		else if(i == 9) 
		{
			mode = 7;
			break;
		}
		else if(i == 7) 
		{
			set_we_time++;
		}
		else if(i == 8) 
		{
			set_we_time--;
		}
		else if(i == 0)
		{
			show_num(0,set_we_time,0,1);
		}
	}

}
void main()
{
	int key;
	int i,j;
  system_Init();
	key_init();
	mode = 1;
	while(1)
	{
		key = key_scan();
		
		
		if(key == 0)
		{
			//mode = 1;
//			mode_one();
		}
		else if(key == 1)
		{
			time = set_ns_time + set_we_time;
			mode = 1;
		}
		else if (key == 2)
		{
			mode = 2;
		}
		else if (key == 3)
		{
			mode =3;
		}
		else if(key == 4)
		{
			mode =4;
		}
		else if(key == 5)
		{
			mode = 5;
		}
		else if(key == 7)
		{
			mode = 7;
		}
		else if(key ==8)
		{
			mode = 8;
		}

		
		
		if(mode == 1)
		{
			mode_one();
		}
		else if(mode == 2)
		{
			mode_two();
		}
		else if(mode == 3)
		{
			mode_three();
		}
		else if(mode == 4)
		{
			mode_four();
		}
		else if(mode == 5)
		{
			mode_five();
		}
		else if(mode ==7)
		{
			mode_six();
		}
		else if(mode == 8)
		{
			mode_seven();
		}
//		mode_one();
	}


//led =0;
}


void timer0() interrupt 1 
{
	TH0=(65535 - 50000) / 256; 
	TL0=(65535 - 50000) % 256;
	temp_time++;			
	led=~led;
	if(temp_time >= 20)
	{
		time--;
		temp_time = 0;		
	}
}