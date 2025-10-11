#include <stdio.h>

int main() {
    char c;
    int count = 0;  //括号记录参数

    while ((c = getchar()) != '@') {
        if (c == '(') {
            count++;  
        } else if (c == ')') {
            count--;  
            if (count < 0) {
                printf("NO\n");
                return 0;  
            }
        }
    }

    if (count == 0) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
