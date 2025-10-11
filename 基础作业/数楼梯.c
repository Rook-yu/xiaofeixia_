#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0) {
        printf("1\n");  // 特殊情况：0阶楼梯只有一种走法
        return 0;
    }
    
    int a = 1, b = 1;  // a表示f(n-2)，b表示f(n-1)
    for (int i = 2; i <= n; i++) {
        int c = a + b;  // 计算f(n) = f(n-1) + f(n-2)
        a = b;          // 更新f(n-2)为f(n-1)
        b = c;          // 更新f(n-1)为f(n)
    }
    
    printf("%d\n", b);  // 输出f(n)
    return 0;
}