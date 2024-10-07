#include <stdio.h>



int  main()
{
	int  x;
    x=100;
	
    while ( x<1000 )        //范围
    { 
        int a,b,c;  
        a=x/100;           //百位
        b=(x/10)%10;      //十位
        c=x%10;           //个位
		if  (((a*a*a)+(b*b*b)+(c*c*c))==x)//判断
			{ printf("%d\n",x);}
		x=x+1;              //递增
     }

     return  0;
}