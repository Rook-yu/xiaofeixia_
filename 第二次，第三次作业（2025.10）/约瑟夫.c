#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    
    if (k == 0) {
        printf("1\n");
        return 0;
    }
    
    int m = k + 1;  // 从k+1开始尝试
    while (1) {
        int current = 0;  // 当前位置，从0开始（第一个好人）
        int valid = 1;
        
        // 模拟k次处决
        for (int i = 0; i < k; i++) {
            // 计算第i次处决的位置
            current = (current + m - 1) % (2 * k - i);
            
            // 检查是否在坏人区域（位置k到2k-1，数组下标从0开始）
            if (current < k) {
                valid = 0;
                break;
            }
            
            // 移除被处决的人后，调整位置
            if (current < 2 * k - i - 1) {
                // 被处决的人不是最后一个，后面的人位置前移
                // 当前位置不需要调整，已经计算了下一次的位置
            }
        }
        
        if (valid) {
            printf("%d\n", m);
            break;
        }
        m++;
    }
    
    return 0;
}
