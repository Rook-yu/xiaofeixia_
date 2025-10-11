#include <stdio.h>

void convert(int x, int m) {
    if (x == 0) {
        return; 
    }
    convert(x / m, m);
    int rem = x % m;
    if (rem < 10) {
        printf("%d", rem);
    } else {
        printf("%c", 'A' + rem - 10);
    }
}

int main() {
    int x, m;
    scanf("%d %d", &x, &m);
    // 调用递归函数进行转换
    convert(x, m);
    printf("\n");
    return 0;
}
