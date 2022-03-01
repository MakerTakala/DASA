#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#define MAX_BIT 257

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
void sub (int8_t a[], int8_t b[]) {
    for (int i = MAX_BIT - 1; i >= 0; i--) {
        a[i] -= b[i];
        if (a[i] < 0) {
            a[i - 1]--;
            a[i] += 10;
        }
    }
}
void compare (int8_t **a, int8_t **b) {
    for (int i = 0; i < MAX_BIT; i++) {
        if ((*a)[i] > (*b)[i]){
            return;
        }
        if ((*a)[i] < (*b)[i]) {
            int8_t *tmp = *a;
            *a = *b;
            *b = tmp;
            return;
        }
    }
}

bool iszero (int8_t *num) {
    for (int i = 0; i < MAX_BIT; i++) {
        if (num[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {

    char char_m[MAX_BIT] = {0}, char_n[MAX_BIT] = {0};
    int8_t m[MAX_BIT] = {0}, n[MAX_BIT] = {0};
    scanf("%s %s", char_m, char_n);
    preprocess(char_m, m);
    preprocess(char_n, n);
    int8_t *pMAX = m, *pMIN = n;
    compare(&pMAX, &pMIN);
    
    int8_t binary[MAX_BIT] = {0};
    binary[MAX_BIT - 1] = 1;

    while (!iszero(pMAX) && !iszero(pMIN)) {
        if ( !(pMAX[MAX_BIT - 1] & 1) && !(pMIN[MAX_BIT - 1] & 1) ) {
            mul_two(binary);
            div_two(pMAX);
            div_two(pMIN);
        }
        else if (!(pMAX[MAX_BIT - 1] & 1)) {
            div_two(pMAX);
        }
        else if (!(pMIN[MAX_BIT - 1] & 1)) {
            div_two(pMIN);
        }
        compare(&pMAX, &pMIN);
        sub(pMAX, pMIN);
    }
    while (!iszero(binary)) {
        div_two(binary);
        mul_two(pMIN);
    }
    div_two(pMIN);

    int i = 0;
    while (pMIN[i] == 0) {
        i++;
    } 
    while (i < MAX_BIT) {
        printf("%d", pMIN[i++]);
    }

    return 0;
}