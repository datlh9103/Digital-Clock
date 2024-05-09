#include <REGX52.H>
int so[12] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8, 0X80, 0X90, 0X88, 0XC7};
int gio = 0;
int h = -1;
int phut = 0;
int m = 0;
int giay = 0;
int temp = &phut;
int min = 0;
int hour = 0;
unsigned int count = 0;
int mode = 0;
int timer = 0;
int a = 0;
void delay(unsigned int i)
{
	while (i>0)
	{
		i--;
	}
}
void Interrupt_Timer0()
{
	TMOD = 0X01;
	TH0 = 0XFC;
	TL0 = 0X18;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}
void clock() interrupt 1
{
	if (ET0 == 1)
	{
		count++;
		if (977 == count)
		{
			P1_0 = ~P1_0;
			giay++;
			if(giay > 59)
			{
				phut++;
				temp = phut;
				giay = 0;
				if (phut > 59)
				{
					gio++;
					phut = 0;
					temp = 0;
					if (gio > 23)
					{
						gio = 0;
					}
				}
			}
			count = 0;
		}
		TH0 = 0XFC;
		TL0 = 0X18;
	}
}
void hienthi(unsigned int i)
{
	int digit;
	if (i == 0)
	{
		digit = gio/10;
		P0 = so[digit];
		P2_0 = 1;
		delay(100);
		P2_0 = 0;
		digit = gio%10;
		P0 = so[digit];
		P0_7 =0;
		P2_1 = 1;
		delay(100);
		P2_1 = 0;
		P0_7 = 1;
		
		digit = phut/10;
		P0 = so[digit];
		P2_2 = 1;
		delay(100);
		P2_2 = 0;
		digit = phut%10;
		P0 = so[digit];
		P0_7 = 0;
		P2_3 = 1;
		delay(100);
		P2_3 = 0;
		P0_7 = 1;
		
		digit = giay/10;
		P0 = so[digit];
		P2_4 = 1;
		delay(100);
		P2_4 = 0;
		digit = giay%10;
		P0 = so[digit];
		P2_5 = 1;
		delay(100);
		P2_5 = 0;
	}
	if (i == 1)
	{
		digit = gio/10;
		P0 = so[digit];
		P2_0 = 1;
		delay(100);
		P2_0 = 0;
		digit = gio%10;
		P0 = so[digit];
		P0_7 =0;
		P2_1 = 1;
		delay(100);
		P2_1 = 0;
		P0_7 = 1;
		
	}
	else if (i == 2)
	{
		digit = phut/10;
		P0 = so[digit];
		P2_2 = 1;
		delay(100);
		P2_2 = 0;
		digit = phut%10;
		P0 = so[digit];
		P0_7 = 0;
		P2_3 = 1;
		delay(100);
		P2_3 = 0;
		P0_7 = 1;
		
	}
	else if (i == 3)
	{
		digit = h/10;
		P0 = so[digit];
		P2_0 = 1;
		delay(100);
		P2_0 = 0;
		digit = h%10;
		P0 = so[digit];
		P0_7 =0;
		P2_1 = 1;
		delay(100);
		P2_1 = 0;
		P0_7 = 1;
		
		P0 = so[10];
		P2_4 = 1;
		delay(100);
		P2_4 = 0;
		P0 = so[11];
		P2_5 = 1;
		delay(100);
		P2_5 = 0;
	}
	else if (i==4)
	{
		digit = m/10;
		P0 = so[digit];
		P2_2 = 1;
		delay(100);
		P2_2 = 0;
		digit = m%10;
		P0 = so[digit];
		P0_7 = 0;
		P2_3 = 1;
		delay(100);
		P2_3 = 0;
		P0_7 = 1;
		
		P0 = so[10];
		P2_4 = 1;
		delay(100);
		P2_4 = 0;
		P0 = so[11];
		P2_5 = 1;
		delay(100);
		P2_5 = 0;
	}
}
void setuptime()
{
	if(P3_3 == 0)
	{
		delay(100000);
		while(P3_3 ==0);
		timer++;
	}
	if (timer == 0)
	{
		hienthi(1);
		if(P3_4 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			gio++;
			if (gio > 23)	gio = 0;
		}
		if(P3_5 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			gio--;
			if (gio < 0)	gio = 23;
		}
	}
	else if (timer == 1)
	{
		hienthi(2);
		if(P3_4 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			phut++;
			if (phut > 59)	phut = 0;
		}
		if(P3_5 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			phut--;
			if (phut < 0)	phut = 59;
		}
	}
	else 
	{
		timer = 0;
	}
}
void alarm()
{
	if(P3_3 == 0)
	{
		delay(100000);
		while(P3_3 ==0);
		a++;
	}
	if (a == 0)
	{
		hienthi(3);
		if(P3_4 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			h++;
			if (h > 23)	h = 0;
		}
		if(P3_5 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			h--;
			if (h < 0)	h = 23;
		}
	}
	else if (a == 1)
	{
		hienthi(4);
		if(P3_4 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			m++;
			if (m > 59)	m = 0;
		}
		if(P3_5 == 0)
		{
			delay(120000);
			while(P1_0 ==0);
			m--;
			if (m < 0)	m = 59;
		}
	}
	else a = 0;
}
void main()
{
	Interrupt_Timer0();
	while(1)
	{
		if(P3_2 == 0)
		{
			delay(100000);
			while(P3_2 ==0);
			mode++;
		}
		if (mode == 0)
		{
			hienthi(0);
		}
		else if (mode == 1)
		{
			setuptime();
		}
		else if (mode == 2)
		{
			alarm();
		}
		else
		{
			mode = 0;
			min = m;
			hour = h;
			timer = 0;
			a = 0;
		}
		if ((hour == gio) && (min == temp))	P3_7 = 0;
		else P3_7 = 1;
		if(P3_6 == 0)
		{
			delay(100000);
			while(P3_6 == 0);
			temp = -1;
		}
	}
}