#include <stdio.h>
#include <stdint.h>
#include <string.h>



int main(){
    int8_t n, m;
    scanf("%hhd %hhd\n", &n, &m);
    int8_t quiz_n[n][m], quiz_m[m][n];
    for (int i = 0, len; i < n; i++) {
        memset(quiz_n[i], 0, m);
        scanf("%d", &len);
        for (int j = 0; j < len; j++) {
            scanf("%hhd", &quiz_n[i][j]);
        }
    }
    for (int i = 0, len; i < m; i++) {
        memset(quiz_m[i], 0, m);
        scanf("%d", &len);
        for (int j = 0; j < len; j++) {
            scanf("%hhd", &quiz_m[i][j]);
        }
    }

    printf("\n");

    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < m; j++){
            printf("%hhd ", quiz_n[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < m; i++){
        for(int j = 0 ; j < n; j++){
            printf("%hhd ", quiz_m[i][j]);
        }
        printf("\n");
    }

    return 0;
}