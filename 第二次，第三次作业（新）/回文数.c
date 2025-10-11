#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 200  // 最大数字长度（100位+反转相加可能翻倍）

// 判断是否为回文数
bool is_palindrome(int *num, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (num[i] != num[len - 1 - i]) {
            return false;
        }
    }
    return true;
}

// 计算反转数
void reverse_num(int *num, int len, int *rev) {
    for (int i = 0; i < len; i++) {
        rev[i] = num[len - 1 - i];
    }
}

// N进制加法：num = num + rev（num和rev长度均为len）
int add_num(int *num, int *rev, int len, int N) {
    int carry = 0;
    for (int i = 0; i < len; i++) {
        int sum = num[i] + rev[i] + carry;
        num[i] = sum % N;
        carry = sum / N;
    }
    // 处理最高位进位
    if (carry != 0) {
        num[len] = carry;
        return len + 1;  // 长度增加1
    }
    return len;  // 长度不变
}

int main() {
    int N;
    char M[101];
    scanf("%d", &N);
    scanf("%s", M);
    int len = strlen(M);
    
    // 将输入的字符串转换为数字数组（低位在前，高位在后）
    int num[MAX_LEN] = {0};
    for (int i = 0; i < len; i++) {
        char c = M[len - 1 - i];  // 反转存储
        if (c >= '0' && c <= '9') {
            num[i] = c - '0';
        } else if (c >= 'A' && c <= 'F') {  // 处理16进制
            num[i] = 10 + c - 'A';
        }
    }
    
    // 检查初始是否为回文数
    if (is_palindrome(num, len)) {
        printf("STEP=0\n");
        return 0;
    }
    
    // 最多尝试30步
    for (int step = 1; step <= 30; step++) {
        int rev[MAX_LEN] = {0};
        reverse_num(num, len, rev);  // 计算反转数
        len = add_num(num, rev, len, N);  // 相加并更新长度
        
        if (is_palindrome(num, len)) {  // 检查是否为回文数
            printf("STEP=%d\n", step);
            return 0;
        }
    }
    
    // 30步内未得到回文数
    printf("Impossible!\n");
    return 0;
}
