#include <stdio.h>
#include <stdint.h>

void preprocess (char num[]) {
    for(int i = 0 ; i < 128; i++){
        char tmp = num[i];
        num[i] = num[255 - i];
        num[255 - i] = tmp;
    }
}

void mul_two (char num[]) {

}

void div_two (char num[]) {

}
void sub (char dividend[], char divisor[]) {
    
}

int main() {

    char m[256] = {0}, n[256] = {0};
    scanf("%s %s", m, n);
    preprocess(m);
    preprocess(n);


    for(int i = 0; i < 256; i++){
        printf("%c", m[i]);
    }
    printf(" ");
    for(int i = 0; i < 256; i++){
        printf("%c", n[i]);
    }
    return 0;
}