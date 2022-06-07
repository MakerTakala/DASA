#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_N 1000006

typedef struct{
    bool query;
    int boom;
    int merge[2];
    int loser;
    int previous_day;
}DAY;

typedef struct _CHILD{
    int day;
    struct _CHILD *next;
}CHILD;

CHILD dummy_child_head[MAX_N];
CHILD *tail[MAX_N] = {NULL};

void add_child(int p, int c) {
    CHILD *tmp = calloc( sizeof(CHILD), 1 );
    tmp->day = c;
    tail[p]->next = tmp;
    tail[p] = tail[p]->next;
    return ;
}

int ans = 0, shop_parent[MAX_N] = {0}, size[MAX_N] = {0}, query_ans[MAX_N] = {0};
DAY day[MAX_N] = {0};

int find( int a ) {
    if( shop_parent[a] == a ) 
        return a;
    return find( shop_parent[a] );
}

int merge( int a, int b ) {
    printf( "\n" );
    printf( "merge %d %d\n", a, b );
    a = find(a);
    b = find(b);
    int loser;
    if( a == b ) 
        return 0;
    if( size[a] < size[b] ) {
        shop_parent[a] = b;
        loser = a;
    }
    else {
        shop_parent[b] = a;
        if( size[a] == size[b] )
            size[a]++;
        loser = b;
    }
    ans--;
    return loser;
}

void DFS( int cur ) {
    int loser = 0;
    if( day[cur].query == true ) {
        printf( "DAY %d query\n", cur );
        query_ans[cur] = ans;
        printf( "   query %d\n", ans );
    }
    else if( day[cur].merge[0] != 0 ) {
        printf( "DAY %d merge\n", cur );
        loser = merge( day[cur].merge[0], day[cur].merge[1] );
        printf( "   query %d\n", ans );
    }
    else {
        printf( "DAY %d Nothing\n", cur );
    }
    CHILD *tmp = dummy_child_head[cur].next;
    while( tmp ) {
        DFS(tmp->day);
        tmp = tmp->next;
    }
    if( day[cur].merge[0] != 0 && loser != 0 ) {
        printf( "loser %d\n", loser );
        shop_parent[loser] = loser;
        ans++;
    }
    return ;
}

int main() {
    int n, m ;
    scanf( "%d %d", &n, &m );
    ans = n;
    memset( day, 0, sizeof(DAY) * m );
    for( int i = 1; i <= n; i++ ) {
        shop_parent[i] = i;
    }
    for( int i = 0; i <= m; i++ ) {
        tail[i] = &dummy_child_head[i];
    }
    for( int i = 1, previous_day = 0; i <= m; i++ ) {
        char str[10] = {0};
        scanf( "%s", str );
        if( !strcmp( str, "merge" ) ){
            int a, b;
            scanf( "%d %d", &a, &b );
            day[i].merge[0] = a;
            day[i].merge[1] = b;
            add_child( previous_day, i );
            day[i].previous_day = previous_day;
            previous_day = i;
        }
        else if( !strcmp( str, "query" ) ) {
            day[i].query = true;
            add_child( previous_day, i );
            day[i].previous_day = previous_day;
            previous_day = i;
        }
        else {
            int x;
            scanf( "%d", &x );
            day[i].boom = x;
            previous_day = x;
            add_child( previous_day, i );
            day[i].previous_day = previous_day;
        }
    }
    
    printf( "\nDFS: \n" );
    DFS(0);

    for( int i = 1; i <= m; i++ ) {
        if( query_ans[i] != 0 ) {
            printf( "%d\n", query_ans[i] );
        }
    }
    return 0;
}