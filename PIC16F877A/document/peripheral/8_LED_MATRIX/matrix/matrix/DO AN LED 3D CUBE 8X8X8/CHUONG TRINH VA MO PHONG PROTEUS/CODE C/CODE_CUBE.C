#include <REGX52.H>
 /////////////////
#define dk P3	  //dieu_khien
#define ms P2	  //quet
#define dl P1		//du lieu
///////////////////////////////////////////////
#define ab 3		 //thoi gian 1 led sang
#define bc 2
//#define bc 3
///////////////////////////////////////////////////////
void delay(int t)							//delay
{int i;
unsigned char b;
for (i=0;i<t;i++){for(b=0;b<125;b++)
{;}}
}
/////////////////

void linh_tinh()
{ unsigned char so[31]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,
                      0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00,
					  0xf8,0xf1,0xe3,0xc7,0x8f,0x1f,
					  0xf0,0xe1,0xc3,0x87,0x0f,
					  0xe0,0xc1,0x83,0x07};	
unsigned char i,j;
for (i=0;i<8;i++)	                             // sang quet tat
 { dk=~so[i]; dl=0xff; ms= 0xff;  delay(200);}
for (i=0;i<8;i++)
 { dl=~so[i]; dk=~0xff; ms= 0xff;  delay(200);}
for (i=0;i<8;i++)
 { ms=~so[i]; dk=~0xff; dl= 0xff; delay(200);}
 /////////////////// 
dk=~0X00; dl=0X00; ms= 0x00;  delay(500);      //chop tat 
dk=~0XFF; dl=0xff; ms= 0xff;  delay(400); 
dk=~0X00; dl=0X00; ms= 0x00;  delay(400);
dk=~0XFF; dl=0xff; ms= 0xff;  delay(400);
///////////////////
for (i=8;i<16;i++)			                     //sang het giam dan  
  { dk=so[i]; delay(500) ; }
//////////////////
for(j=0;j<2;j++)										   //chay hinh hop
{for(i=15;i<10;i++)
 { dk=~so[i];ms=so[i];dl =so[i]; delay(300);}
 }
 for(j=0;j<3;j++)
{for(i=21;i<27;i++)
 { dk=~so[i];ms=so[i];dl =so[i]; delay(300);}

 }
for(j=0;j<4;j++)
{for(i=26;i<31;i++)
 { dk=~so[i];ms=so[i];dl =so[i]; delay(300);}
}
}
//////////////////////
void quet_qua_lai ()
{ dk= ~0xff,dl =0xff;
   ms =0x01;delay(250);ms =0x03;delay(250);ms =0x06;delay(250);ms =0x0c;delay(250);	 //len
   ms =0x18;delay(250);ms =0x30;delay(250);ms =0x60;delay(250);ms =0xc0;delay(250);ms =0x80;delay(250);

   ms =0xc0;delay(250);ms =0x60;delay(250);ms =0x30;delay(250);ms =0x18;delay(250);	//xuong
   ms =0x0c;delay(250);ms =0x06;delay(250);ms =0x03;delay(250);ms =0x01;delay(250);
  ms= 0xff;dl =0xff;
   dk =~0x01;delay(250);dk =~0x03;delay(250);dk =~0x06;delay(250);dk =~0x0c;delay(250);	 //tientoi
   dk =~0x18;delay(250);dk =~0x30;delay(250);dk =~0x60;delay(250);dk =~0xc0;delay(250);dk =~0x80;delay(250);

   dk =~0xc0;delay(250);dk =~0x60;delay(250);dk =~0x30;delay(250);dk =~0x18;delay(250);	//tien lui
   dk =~0x0c;delay(250);dk =~0x06;delay(250);dk =~0x03;delay(250);dk =~0x01;delay(250);
  ms=0xff; dk =~0xff;
   dl =0xc0;delay(250);dl =0x60;delay(250);dl =0x30;delay(250);dl =0x18;delay(250);	//qua phai
   dl =0x0c;delay(250);dl =0x06;delay(250);dl =0x03;delay(250);dl =0x01;delay(250);

   dl =0x03;delay(250);dl =0x06;delay(250);dl =0x0c;delay(250);	                    //qua trai
   dl =0x18;delay(250);dl =0x30;delay(250);dl =0x60;delay(250);dl =0xc0;delay(250);
}
/////////////////
void hinh_vuong()
{unsigned char hv[32] ={0xff,0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,
  					    0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff,
 					    0xff,0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,
 					    0x80,0xc0,0xe0,0xf0,0xf8,0xfc,0xfe,0xff,};
 unsigned char i;  
    for(i=0;i<8;i++)
	  {ms= hv[i]; dk=~hv[i];dl=hv[i];delay(200);}			 //xuong qua phai
	 ms=0x00;dl=0x00;dk=0x00;  
	for(i=8;i<16;i++)
	  {ms= hv[i]; dk=~hv[i];dl=hv[i];delay(200);}

	for(i=16;i<24;i++)										//len qua trai
	  {ms= hv[i]; dk=~hv[i];dl=hv[i];delay(200);}
	for(i=24;i<32;i++)
	  {ms= hv[i]; dk=~hv[i];dl=hv[i];delay(200);}
                ///////////////////

	for(i=0;i<8;i++)
	  {ms= hv[i+16]; dk=~hv[i];dl=hv[i];delay(200);} 		 //len qua phai
	for(i=8;i<16;i++)
	  {ms= hv[i+16]; dk=~hv[i];dl=hv[i];delay(200);} 


	for(i=0;i<8;i++)
	  {ms= hv[i]; dk=~hv[i+16];dl=hv[i+16];delay(200);} 		 //xuong qua trai
	for(i=8;i<16;i++)
	  {ms= hv[i]; dk=~hv[i+16];dl=hv[i+16];delay(300);}  

                    /////////////////////
	for(i=0;i<8;i++)
	  {ms= hv[i]; dk=~hv[i+16];dl=hv[i];delay(200);} 		 //xuong toi truoc
	for(i=8;i<16;i++)
	  {ms= hv[i]; dk=~hv[i+16];dl=hv[i];delay(200);}  

	for(i=0;i<8;i++)
	  {ms= hv[i+16]; dk=~hv[i];dl=hv[i+16];delay(200);} 		 //len ra sau
	for(i=8;i<16;i++)
	  {ms= hv[i+16]; dk=~hv[i];dl=hv[i+16];delay(200);}  
                   ////////////////////
	for(i=0;i<8;i++)
	  {ms= hv[i+16]; dk=~hv[i+16];dl=hv[i];delay(200);} 		 //len toi truoc
	for(i=8;i<16;i++)
	  {ms= hv[i+16]; dk=~hv[i+16];dl=hv[i];delay(200);} 

   	for(i=0;i<8;i++)
	  {ms= hv[i]; dk=~hv[i];dl=hv[i+16];delay(200);} 		 //xuong ra sau
	for(i=0;i<8;i++)
	  {ms= hv[i+8]; dk=~hv[i+8];dl=hv[i+24];delay(200);} 
				  ///////////////////
	ms=0x7e;dl=0x7e,dk=~0x7e;delay(500);						 //thu nho lai
	ms=0x3c;dl=0x3c;dk=~0x3c;delay(500);
	ms=0x18;dl=0x18;dk=~0x18;delay(500);
	ms=0x00;dl=0x00;dk=~0x00;delay(500);

}
/////////////////
void quet_mang()
{unsigned char i,j;
unsigned char mg4[29] ={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,
                        0xbf,0xdf,0xef,0xf7,0xfb,0xfd,
					    0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe,
						0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

 dl=0xff;dk=~0xff;
  ms=0x01;delay(300);
  ms=0x03;delay(300);
  ms=0x07;delay(300);
  ms=0x0f;delay(300);
  ms=0x1f;delay(300);
  ms=0x3f;delay(300);
  ms=0x7f;delay(300);
  ms=0xff;delay(300);
 for(i=0;i<5;i++)
   {for(j=0;j<14;j++)
     {ms=mg4[j];dl=mg4[j];dk=~mg4[j+14];delay(300);
	 }
   }
}
//////////////////

   void mang1() {dl=0x01;}				 
   void mang2() {dl=0x02;}				 
   void mang3() {dl=0x04;}				 
   void mang4() {dl=0x08;}				
   void mang5() {dl=0x10;}				
   void mang6() {dl=0x20;}				
   void mang7() {dl=0x40;}				
   void mang8() {dl=0x80;}				

void mang_len_xuong()
{unsigned char i,j,k;
////////////////////////
 unsigned char mg[21]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,			   //xuong
                       0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
					   0x02,0x04,0x08,0x10,0x20,0x40					   //len
					   };
 unsigned char mg2[16]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,		  //xep len
                        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80};	
									
 unsigned char mg3[21]={0x80,0x80,0x80,0x80,
	                       0x40,0x20,0x10,0x08,0x04,0x02,0x01,				//xuong
						   0x01,0x01,0x01,
						   0x02,0x04,0x08,0x10,0x20,0x40,0x80			   //len
                          };						
							   												   
 for(i=0;i<15;i++)
   {for(j=7;j<21;j++)
     {for(k=0;k<10;k++)
	   {dk=~0xff;
	    ms=mg[j];   mang1();delay(2);					 ///mang quet len xuong
	    ms=mg[j-1]; mang2();delay(2);
		ms=mg[j-2]; mang3();delay(2);
		ms=mg[j-3]; mang4();delay(2);
		ms=mg[j-4]; mang5();delay(2);
		ms=mg[j-5]; mang6();delay(2);
		ms=mg[j-6]; mang7();delay(2);
		ms=mg[j-7]; mang8();delay(2);
	   }
	 }
   };
//////////////////////
																				   
   for(j=7;j<16;j++)
     {for(k=0;k<15;k++)
	   {dk=~0xff;
	    ms=mg2[j];   mang1();delay(3);		    	//	mang tap trung len tren
	    ms=mg2[j-1]; mang2();delay(3);
		ms=mg2[j-2]; mang3();delay(3);
		ms=mg2[j-3]; mang4();delay(3);
		ms=mg2[j-4]; mang5();delay(3);
		ms=mg2[j-5]; mang6();delay(3);
		ms=mg2[j-6]; mang7();delay(3);
		ms=mg2[j-7]; mang8();delay(3);
	   }
	 };
/////////////////

 for(i=0;i<10;i++)
   {for(j=4;j<21;j++)
     {for(k=0;k<15;k++)
	   {dk=~0xff;
	    ms=mg3[j];   mang4();delay(2);mang5();delay(2);			  //canh chim bay
	    ms=mg3[j-1]; mang3();delay(2);mang6();delay(2);
		ms=mg3[j-2]; mang2();delay(2);mang7();delay(2);
		ms=mg3[j-3]; mang1();delay(2);mang8();delay(2);
	   }
	 }
   };
ms=0x00;dl=0x00;dk=~0x00;delay(500);
}
/////////////////
void so1()  {dk =~0x81;dl =0x81;delay(ab),dk =~0x81;dl =0x81;delay(bc);}
void so2() {dk =~0x42;dl =0x81;delay(ab),dk =~0x81;dl =0x42;delay(bc);}			//du lieu
void so3a() {dk =~0x24;dl =0x81;delay(ab),dk =~0x81;dl =0x24;delay(bc);}
void so3b()  {dk =~0x42;dl =0x42;delay(ab),dk =~0x42;dl =0x42;delay(bc);}
void so4a()  {dk =~0x18;dl =0x81;delay(ab),dk =~0x81;dl =0x18;delay(bc);}
void so4b()  {dk =~0x24;dl =0x42;delay(ab),dk =~0x42;dl =0x24;delay(bc);}
void so5a()  {dk =~0x18;dl =0x42;delay(ab),dk =~0x42;dl =0x18;delay(bc);}
void so5b()  {dk =~0x24;dl =0x24;delay(ab),dk =~0x24;dl =0x24;delay(bc);}
void so6()   {dk =~0x18;dl =0x24;delay(ab),dk =~0x24;dl =0x18;delay(bc);}
void so7()   {dk =~0x18;dl =0x18;delay(ab),dk =~0x18;dl =0x18;delay(bc);}
/////////////////
			
/////////////////
void pheu_len_xuong()
{ unsigned char so[33]={0x10,0x08,0x04,0x02,0x01,0x01,0x01,0x01,0x01,
                      0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,				 //len
                      0x80,0x80,0x80,0x80,
					  0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,				 //xuong
					  0x01,0x01,0x01,0x01};
unsigned char a,c,b;
for(c=0;c<10;c++)
 {for(a=10;a<33;a++)
  {for(b=0;b<4;b++)
    {ms= so[a]; so1();	 
     ms= so[a-1]; so2();
	 ms= so[a-2]; so3a();
	 ms= so[a-3]; so3b();
  	 ms= so[a-4]; so4a();
	 ms= so[a-5]; so4b();
	 ms= so[a-6]; so5a();
	 ms= so[a-7]; so5b();
	 ms= so[a-8]; so6();
	 ms= so[a-9]; so7();
	 ms= so[a-10]; so7();
    }
  }
 }
}
//////////////////////////
void mua_roi()
{unsigned char so[22] ={0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                        0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
						0x00,0x00,0x00,0x00};
 unsigned char i,j,k ;
 for(k=0;k<10;k++)
   {for(i=16;i<22;i++)

	  {for(j=0;j<3;j++) 
	    {ms =so[i];
	      dl=0x88;dk=~0x21;delay(10);
		 ms =so[i-1]; 
		  dl=0x12;dk=~0x11;delay(10);
		 ms =so[i-2];
	      dl=0x42;dk=~0xc4;delay(10);
	   	 ms =so[i-4];
	      dl=0x14;dk=~0x54;delay(10);
		 ms =so[i-6];
	      dl=0x21;dk=~0x22;delay(10);
		 ms =so[i-8];
		  dl=0x12;dk =~0x22;delay(10);
		 ms =so[i-10];
		  dl=0x82;dk =~0x14;delay(10);
		}
	  }
	}
}
////////////////////////
void ban_phao_hoa(unsigned char lap)
{ unsigned int b;
  unsigned char a,c;
  unsigned char maso2[14]={0x80,0xc0,0x20,0x10,0x08,0x04,0x02,
                           0x01,0x00,0x00,0x00,0x00,0x00,0x00};
   for(a=0;a<lap;a++)
    {
	dk=~0x10;dl=0x10;
	 ms =0x03;delay(200);									//chay len
	 ms =0x06;delay(200);
	 ms =0x0c;delay(200);
	 ms =0x18;delay(200);
	 ms =0x30;delay(200);
	 ms =0x60;delay(200);
	dk=~0x30;dl=0x30;									  //no23
	 ms =0xe0;delay(150);
	dk=~0x38;dl=0x38;
	 ms =0xe0;delay(150);
	  for(b=0;b<13;b++)								  //chuki 1
	   {ms =0x80;
	     dk =~0x68;dl=0x40;delay(ab);
	     dk =~0x0c;dl=0x20;delay(ab);
		 dk =~0x54;dl=0x10;delay(ab);
		 dk =~0x50;dl=0x08;delay(ab);
		 dk =~0x2c;dl=0x04;delay(ab);
		ms =0x40;
		 dk =~0x38;dl=0x40;delay(ab);
	     dk =~0x2a;dl=0x20;delay(ab);
		 dk =~0x4a;dl=0x10;delay(ab);
		 dk =~0x34;dl=0x08;delay(ab);
		 dk =~0x14;dl=0x04;delay(ab);
		ms =0x08;
	     dk =~0x30;dl=0x20;delay(ab);
	     dk =~0x28;dl=0x10;delay(ab);
		 dk =~0x10;dl=0x08;delay(ab);
		}


	  for(b=0;b<13;b++)							   //chuki2
	   {ms =0x80;
		 dk =~0x24;dl=0x80;delay(ab);
	     dk =~0x66;dl=0x40;delay(ab);
	     dk =~0x14;dl=0x20;delay(ab);
		 dk =~0x72;dl=0x10;delay(ab);
		 dk =~0x96;dl=0x04;delay(ab);
		 dk =~0xd8;dl=0x02;delay(ab);
		ms =0x40;
	     dk =~0x66;dl=0x40;delay(ab);
	     dk =~0xe4;dl=0x20;delay(ab);
		 dk =~0x38;dl=0x10;delay(ab);
		 dk =~0x5a;dl=0x08;delay(ab);
		 dk =~0xd8;dl=0x02;delay(ab);
		ms =0x20;
	     dk =~0x68;dl=0x40;delay(ab);
		 dk =~0xe4;dl=0x10;delay(ab);
		 dk =~0x5a;dl=0x08;delay(ab);
		 dk =~0x26;dl=0x04;delay(ab);
		ms =0x08;
		 dk =~0x84;dl=0x20;delay(ab);
		 dk =~0x72;dl=0x10;delay(ab);
		 dk =~0x5a;dl=0x08;delay(ab);
		  }


		  for(c=5;c<14;c++)									//no roi xuong
		    {
				   for(b=0;b<6;b++)
	        {ms =maso2[c]; 
	           dk =~0x66;dl=0x40;delay(3);
	           dk =~0x84;dl=0x20;delay(3);		       
		       dk =~0x5a;dl=0x08;delay(3);
		       dk =~0x16;dl=0x04;delay(3);
			ms =maso2[c-2];
			   dk =~0x81;dl=0x80;delay(3);
	           dk =~0x24;dl=0x40;delay(3);	           
	           dk =~0x51;dl=0x08;delay(3);
		       dk =~0x88;dl=0x02;delay(3);
		   ms =maso2[c-3];
		       dk =~0x44;dl=0x10;delay(3);
			   dk =~0x44;dl=0x20;delay(3);
			} 
		    }
		 }
   }
////////////////

void hieu_ung_lop_mang(unsigned char time,unsigned char lap)
{
	unsigned char a;
	unsigned char x,y;

	unsigned char code ma[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	unsigned char code dieu_khien[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 

	/////////////////////// trai phai
	dk=0xff;
	ms=dl=0x00;
for(y=0;y<lap;y++)
{
   for(a=0;a<4;a++)
  {
	for(x=0;x<8;x++)
	{
		
		dk=0x00;
		dl=ma[x];
		ms=0xff;			
		delay(time);
		ms=dl=0x00;
		
		
		
	}
	for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=ma[7-x];
		ms=0xff;			
		delay(time);
		ms=dl=0x00;

		
		
	}
  } 
	///lop len xuong
  for(a=0;a<4;a++)
  {
	for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=0xff;
		ms=ma[x];
		delay(time);
		
		
	}
	for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=0xff;
		ms=ma[7-x];
		delay(time);
		
		
	}
  }
  //////////////  mang truoc sau
   for(a=0;a<4;a++)
  {
	for(x=0;x<8;x++)
	{		
		dl=0xff;
		dk=dieu_khien[x];
		ms=0xff;
		delay(time);
		
		
	}
	for(x=0;x<8;x++)
	{
		dl=0xff;
		dk=dieu_khien[7-x];
		ms=0xff;
		delay(time);
		
		
	}
  }
 }
 }

////////////////////////////

void lop_mang_xen_ke(unsigned char time,unsigned char lap)
{
	unsigned char a;
	unsigned char x;

	unsigned char code ma[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	unsigned char code dieu_khien[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 
for(a=0;a<lap;a++)
{
	for(x=0;x<8;x++)
	{		
		dl=0xff;
		dk=dieu_khien[x];  //truoc  
		ms=0xff;
		delay(time);
							 		
		
	}
	//////////
	for(x=0;x<8;x++)
	{
		
		dk=0x00;
		dl=ma[x];
		ms=0xff;		 //phai	
		delay(time);
		ms=dl=0x00;
		
		
		
	}
	///////////////
	for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=0xff;     //xuong
		ms=ma[7-x];
		delay(time);
		
		
	}
	///////////
	for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=ma[7-x];
		ms=0xff;		//trai	
		delay(time);
		ms=dl=0x00;				
	}
	///////////////
	for(x=0;x<8;x++)
	{
		dl=0xff;
		dk=dieu_khien[7-x]; //sau
		ms=0xff;
		delay(time);
				
	}
		for(x=0;x<8;x++)
	{
		dk=0x00;
		dl=0xff;     //xuong
		ms=ma[7-x];
		delay(time);		
		
	}

}		
}
/////////////////////	
void hienthichucai(unsigned char text,int tocdo)
{ 
			   

	unsigned char code quet[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};	
//	unsigned char code dieu_khien[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 
	unsigned char code machucai[32]={
	0x66,0xFF,0xFF,0xDB,0xDB,0xC3,0xC3,0x00,	 //M
	0x1F,0x33,0x33,0x1F,0x0F,0x1B,0x33,0x00,	  //R
	0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00,	  //T
	0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,	   //U
	};


	 unsigned char a,c;	
	switch(text)
	{
		case 'M':
		{		 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a];
				dk=0xE7;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;
					
				}	
				
             }
			 
	  	   }
		break;

		case 'R':
		{	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+8];
				dk=0xE7;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;
					
				}	
				
             }
			 
	  	   }
		break;
		case 'T':
		{		 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+16];
				dk=0xE7;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;
					
				}	
				
             }
			 
	  	   }
		break;
		case 'U':
		{		 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+24];
				dk=0xE7;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;
					
				}	
				
             }
			 
	  	   }
		break;

	   }
			
       
 }
///////////////////////////////////// dich chu
void dich_chu(unsigned char text,int tocdo)
{ 
			   

	unsigned char code quet[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};	
	unsigned char code dieu_khien[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 
	unsigned char code machucai[80]={
	0x66,0xFF,0xFF,0xDB,0xDB,0xC3,0xC3,0x00,	 //M
	0x1F,0x33,0x33,0x1F,0x0F,0x1B,0x33,0x00,	  //R
	0x7E,0x18,0x18,0x18,0x18,0x18,0x18,0x00,	  //T
	0x66,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,	   //U

	///////////
	0x66,0x66,0x66,0x7E,0x66,0x66,0x66,0x00,// H
	0x3F,0x03,0x03,0x1F,0x03,0x03,0x3F,0x00,//E
	0x03,0x03,0x03,0x03,0x03,0x03,0x3F,0x00,//L
	0x3C,0x66,0x66,0x66,0x66,0x66,0x3C,0x00,//O
	0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00,//I
	0x3C,0x66,0x66,0x66,0x7E,0x66,0x66,0x00,//A
	};


	 unsigned char a,b,c;	
	switch(text)
	{
		case 'M':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

		case 'R':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+8];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'T':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+16];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'U':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+24];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'H':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+32];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'E':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+40];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'L':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+48];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'O':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+56];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;
			case 'I':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+64];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;

			case 'A':
		{	
		for(b=0;b<8;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[a+72];
				dk=dieu_khien[b];;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
		break;
}
}

////////////////////
void pac_man(unsigned char tocdo,unsigned char lap)
{ 
		unsigned char a,b,c,d;	   

	unsigned char code quet[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};	
//	unsigned char code dieu_khien[]={0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F}; 
	unsigned char code machucai[16]={
	0x3C,0x42,0x81,0xF9,0xF9,0x81,0x42,0x3C,
	0x3C,0x42,0xF1,0x09,0x09,0xF1,0x42,0x3C,
	};
	  for(d=0;d<lap;d++)
	  {
		for(b=0;b<2;b++)
		{	 	      
			for(c=0;c<tocdo;c++)
 			 {
		  	    for(a=0;a<8;a++)
				{				 
				dl=machucai[8*b+a];
				dk=0x3F;
			   	ms=quet[a];
				delay(5);
				dl=ms=0x00;		
				}					
             }
		 }
		}
}
//////////////////////////////////				
void main ()
{ 
while(1)
{
hienthichucai('M',50);
ban_phao_hoa(3);   //ok
hienthichucai('R',50);
ban_phao_hoa(3);   //ok
hienthichucai('T',50);
ban_phao_hoa(3);   //ok
hienthichucai('U',50);
ban_phao_hoa(3);   //ok
pac_man(15,5);
dich_chu('H',5); 
dich_chu('E',5); 
dich_chu('L',5); 
dich_chu('L',5); 
dich_chu('O',5); 
ban_phao_hoa(3);   //ok
///////////////////////
dich_chu('I',5); 
dich_chu('A',5); 
dich_chu('M',5); 
//
dich_chu('M',5); 
dich_chu('R',5); 
dich_chu('T',5); 
dich_chu('U',5); 
//
pac_man(15,5);
mua_roi();	  //ok
mang_len_xuong();  //oke
hinh_vuong();
lop_mang_xen_ke(200,3);
//
hieu_ung_lop_mang(100,2);
quet_mang();
pheu_len_xuong();
linh_tinh();
quet_qua_lai();	 //oke
		//oke
}
}			