#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int parent[1 << 24];
bool set[1 << 24];

int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

inline void static init(int i) {
    if (!set[i]) {
        parent[i] = i;
        set[i] = 1;
    }
}

int find_set(int i) {
    init(i);
    return parent[i] = ( parent[i] == i ? i : find_set(parent[i]) );
}

void group(int ra, int rb) {
    int a = find_set(ra), b = find_set(rb);
    parent[b] = parent[a];
}

bool same_set( int a, int b) {
    return find_set(a) == find_set(b);
}

int main() {
    int n = 0;;
    scanf( "%d", &n );

    for( int i = 0; i < n; i++ ) {
        char type[10] = {0}, A[15] = {0}, B[15] = {0};
        scanf( "%s %s %s", type, A, B );
        if( !strcmp( type, "group" ) ) {
            group( hash(A), hash(B) );
        }
        else {
            printf( "%s\n", same_set( hash(A), hash(B) ) ? "Positive" : "Negative" );
        }
    }
    return 0;
}