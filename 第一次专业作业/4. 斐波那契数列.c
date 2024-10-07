# include<stdio.h>

void    feibo(int  t)   //计算斐波那契数列并输出
{
    int n;
    int a1=1;
    int a2=1;
    int a3;
    if (t==1|t==2)           //1，2个特殊考虑
        printf("1\n");
    else 
        {
            for(n=1;n<=t-2;n++)
            {
            a3=a1+a2;
            a1=a2;
            a2=a3;
            }
        printf("%d\n",a3);
        }
}


int main()
{
    int m,i;
    scanf ("%d",&m);
    int  a[m-1];                    //建立数组存放数据
    for (i=0;i<=m-1;i++ )
        {
        scanf ("%d",&a[i]);       //数据入数组
        }
    i=0;
    for (i=0;i<=m-1;i++ )       //读取数据并计算输出
        {
            feibo(a[i]);


        }








}