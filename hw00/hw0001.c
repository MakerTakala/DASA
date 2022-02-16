#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define MAX_BIT 256

void preprocess (char char_num[], int8_t num[]) {
    int len = strlen(char_num);
    for (int i = 0 ; i < len; i++) {
        num[i + (MAX_BIT - len)] = char_num[i] -'0';
    }
}

void mul_two (int8_t num[]) {
    int8_t carry = 0;
    for (int i = MAX_BIT - 1; i >= 0; i--) {
        num[i] = num[i] * 2 + carry;
        carry = num[i] / 10;
        num[i] %= 10;
    }
}

void div_two (int8_t num[]) {
    int carry = 0;
    for (int i = 0; i < MAX_BIT; i++) {
        int tmp  = num[i] & 1;
        num[i] = (carry * 10 + num[i]) >> 1;
        carry = tmp;
    }
}
void sub (int8_t dividend[], int8_t divisor[]) {

}

int main() {

    char char_m[MAX_BIT] = {0}, char_n[MAX_BIT] = {0};
    int8_t m[MAX_BIT] = {0}, n[MAX_BIT] = {0};
    scanf("%s %s", char_m, char_n);
    preprocess(char_m, m);
    preprocess(char_n, n);
    mul_two(m);
    div_two(n);

    for(int i = 0; i < 256; i++){
        printf("%d", m[i]);
    }
    printf("\n\n");
    for(int i = 0; i < 256; i++){
        printf("%d", n[i]);
    }
    return 0;
}