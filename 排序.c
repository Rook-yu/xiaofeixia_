# include<stdio.h>
int main()
{
    int i,j,n,t;
    scanf("%d",&n);
    int  a[n-1];                   //建数组存数据
    for (i=0;i<n;i++)
        scanf("%d",&a[i]);
    for(i=0;i<n-1;i++)                    //循环比大小排序
    for (j=0;j<n-1-i;j++)
        if(a[j]>a[j+1])                         //交换
        {
            t=a[j];
            a[j]=a[j+1];
            a[j+1]=t;
        }
    for(i=0;i<n;i++)       //输出
        printf("%d    ",a[i]);
    return 0;
}