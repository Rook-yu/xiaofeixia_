#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);  // 读取整数个数

    int arr[N];  
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);  // 读取每个整数
    }

    // 冒泡排序
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换arr[j]和arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // 输出排序后的结果
    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
        if (i < N - 1) {
            printf(" ");  // 数之间用空格分隔
        }
    }
    printf("\n");  

    return 0;
}