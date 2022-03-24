#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

int8_t n, m;

bool board[30][30] = {{false}};
int8_t quiz_y[15][15] = {{0}}, quiz_x[15][15] = {{0}};

void print_board() {
    for(int i = 0; i < n; i++) {
        for(int j = 0;j < m; j++) {
            printf("%c", board[i][j] ? 'o' : '_');
        }
        printf("\n");
    }
    printf("\n");
}

bool success(void) {
    print_board();
    for(int i = 0; i < n; i++) {
        int8_t cur_quiz = 0;
        for(int j = 0; j < m; j++) {
            if( board[i][j] == true ) {
                int conti = 0;
                while( board [i][j] == true && j < m ) {
                    conti++;
                    j++;
                }
                if( conti != quiz_y[i][cur_quiz++] ) {
                    return false;
                }
                if( board[i][j] != false ) {
                    return false;
                }
                j++;
            }
        }
        if( quiz_y[i][cur_quiz] != 0 ) {
            return false;
        }
    }
    printf("quiz_y success\n");
    for(int i = 0; i < m; i++) {
        int8_t cur_quiz = 0;
        for(int j = 0; j < n; j++) {
            if( board[j][i] == true ) {
                int conti = 0;
                while( board[j][i] == true && j < n ) {
                    conti++;
                    j++;
                }
                if( conti != quiz_x[i][cur_quiz++] ) {
                    return false;
                }
                if( board[j][i] != false ) {
                    return false;
                }
                j++;
            }
        }
        if( quiz_x[i][cur_quiz] != 0 ) {
            return false;
        }
    }
    printf("quiz_x success\n\n");
    return true;
}

void recur( int8_t cur_cell ) {
    if( cur_cell == n * m ) {
        if( success() ) {
            print_board();
        }
        return;
    }
    board[cur_cell / m][cur_cell % m] = false;
    recur(cur_cell + 1);
    board[cur_cell / m][cur_cell % m] = true;
    recur(cur_cell + 1);
    return;
}

int main(){
    scanf("%hhd %hhd\n", &n, &m);
    for(int i = 0, len; i < n; i++) {
        scanf("%d", &len);
        for(int j = 0; j < len; j++) {
            scanf("%hhd", &quiz_y[i][j]);
        }
    }
    for(int i = 0, len; i < m; i++) {
        scanf("%d", &len);
        for(int j = 0; j < len; j++) {
            scanf("%hhd", &quiz_x[i][j]);
        }
    }
    recur(0);

    return 0;
}