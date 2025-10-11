#include  <stdio.h>
#include <math.h>
 
int zhi(int m)                  //构造判断质数函数，t=0为质数
{
    int t = 0;
    int q= 2;
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
    int L;
    int x = 0;
    int n = 0;
    int k =0;
    scanf ("%d",&L);
    for (int i = 2;n  < L ;i++){
        if(zhi(i) == 0){
            n+=i;
            if(n<=L){
                printf("%d\n",i);
                k=k+1;
            }
        } 
        
    }
    printf("%d\n",k);
}
 
    
  


    