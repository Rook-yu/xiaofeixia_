#include <stdio.h>

int zhi(int m)                  //构造判断质数函数，t=0为质数
{
     int t=0;
    int q=2;
while  (q<m)
    if  (m%q==0&q!=2|m==4)     //考虑2和4（只有2为因数）的特殊情况
    {  t=t+1;
      q=m;
      }
    else 
        q = q+1;
return t;



}

int  main ()
{
    int  x=1;
  
    while  ((x<4|x>10000) |( x%2!=0) )        //确保输入数在4到10000范围内且为偶数
    {
        printf("输入4到10000的偶数\n");
          scanf( "%d",&x);
    }
    int a=4;
     while (a<=x)   //限制范围
    {
         int b,c;
         b=2;
        c=a-b;
         while  (b<=a/2)        //寻找质数，内部递增循环

             if (zhi(b)==0&zhi (c)==0)       //判断是否为质数
             {
                 printf("%d=%d+%d\n",a,b,c);
                 break;
               }

                else
                {
                    b=b+1;    //内部递增
                     c=a-b;
                     if(b>a/2)
                        printf("歌德巴赫的猜想不成立。");             //完善题干验证猜想的要求
                }
    a=a+2;  //外部递增
    
    }
return 0;
}