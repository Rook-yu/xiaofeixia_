#include <stdio.h> 

int jiecheng (int n){
    int   t  = 1;
    if (n == 0 || n == 1){
        return t  ;
    }
    else{
        t =  n * jiecheng (n - 1);
        return t;
    }
}

int main (){
    int n;
    scanf("%d", &n);
    printf("%d\n", jiecheng (n));
    return 0;
}