#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1050  

void add_big(int a[], int b[], int *len) {
    int carry = 0;
    for (int i = 0; i < *len; i++) {
        int sum = a[i] + b[i] + carry;
        a[i] = sum % 10;  // 保留当前位
        carry = sum / 10; // 计算进位
    }
    // 处理最高位的进位
    while (carry > 0) {
        a[*len] = carry % 10;
        carry /= 10;
        (*len)++;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    // 基础情况：n=1或n=2直接输出
    if (n == 1) {
        printf("1\n");
        return 0;
    } else if (n == 2) {
        printf("2\n");
        return 0;
    }

    // 初始化：用数组逆序存储大整数（个位在index=0）
    int a[MAX_DIGITS] = {1};  // f(1) = 1
    int b[MAX_DIGITS] = {2};  // f(2) = 2
    int length = 1;           // 当前数字的有效位数（初始为1位）

    // 迭代计算到第n阶：f(i) = f(i-1) + f(i-2)
    for (int i = 3; i <= n; i++) {
        int temp[MAX_DIGITS];
        memcpy(temp, b, sizeof(temp));  // 临时保存f(i-1)
        add_big(b, a, &length);         // b = b + a（即f(i) = f(i-1) + f(i-2)）
        memcpy(a, temp, sizeof(a));     // a更新为f(i-1)
    }
    
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", b[i]);
    }
    printf("\n");

    return 0;
}
