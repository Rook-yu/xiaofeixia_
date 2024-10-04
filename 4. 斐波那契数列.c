# include<stdio.h>

void    feibo(int  t)
{
    int n;
    int a1=1;
    int a2=1;
    int a3;
    if (t==1|t==2)
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
    int  a[m-1];
    for (i=0;i<=m-1;i++ )
        {
        scanf ("%d",&a[i]);
        }
    i=0;
    for (i=0;i<=m-1;i++ )
        {
            feibo(a[i]);


        }








}