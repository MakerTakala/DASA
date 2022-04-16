#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct _Node{
    uint32_t child;
    struct _Node *next;
}Node;

uint32_t city, query, s_city, r_city;
Node **graph;
uint32_t *stack;
bool *visited;
bool *path;
uint32_t *ans;

void add_edge( uint32_t parent, uint32_t data);
void find_path( uint32_t cur_city, uint32_t depth );
void get_ans( uint32_t cur_city, uint32_t pre_ans );

int main() {
    scanf( "%u %u %u %u", &city, &query, &s_city, &r_city );
    graph = calloc( city + 1, sizeof( Node* ) );
    stack = calloc( city + 1, sizeof( uint32_t ) );
    visited = calloc( city + 1, sizeof( bool ) );
    path = calloc( city + 1, sizeof( bool ) );
    ans = calloc( city + 1, sizeof( uint32_t ) );
    
    for( int i = 0, a = 0, b = 0; i < city - 1; i++ ) {
        scanf( "%u %u", &a, &b );
        add_edge( a, b );
        add_edge( b, a );
    }

    visited[s_city] = true;
    find_path( s_city, 0 );
    free( stack );
    memset( visited, false, city + 1 );
    get_ans( s_city, 0 );

    for( int i = 1; i <= city; i++ ) {
        printf( "%u ", path[i] );
    }
    printf("\n");

    for( int i = 1; i <= city; i++ ) {
        printf( "%u ", ans[i] );
    }

    for( int i = 0, x; i < query; i++ ) {
        scanf( "%d", &x );
        printf( "%u\n", ans[x] );
    }

    
    return 0;
}

void add_edge( uint32_t parent, uint32_t child ) {
    Node *newNode = calloc( 1, sizeof( Node ) );
    newNode->child = child;
    newNode->next = graph[parent];
    graph[parent] = newNode;
    return;
}

void find_path( uint32_t cur_city, uint32_t depth ) {
    if( cur_city == r_city ) {
        stack[depth] = r_city;
        for( int i = 0; i <= depth; i++ ) {
            printf("%u " ,stack[i]);
            path[ stack[i] ] = true;
        }
        printf("\n");
        return;
    }
    stack[depth] = cur_city;
    Node *t = graph[cur_city];
    while( t ) {
        if( visited[t->child] == false ) {
            visited[t->child] = true;
            find_path( t->child, depth  + 1 );
            visited[t->child] = false;
        }
        t = t->next;
    }
    return;
}

void get_ans( uint32_t cur_city, uint32_t pre_ans ) {
    if( path[cur_city] ) {
        ans[cur_city] = cur_city;
        pre_ans = cur_city;
    }
    else {
        ans[cur_city] = pre_ans;
    }

    Node *t = graph[cur_city];
    while( t ) {
        if( visited[t->child] == false ) {
            visited[t->child] = true;
            get_ans( t->child, pre_ans );
            visited[t->child] = false;
        }
        t = t->next;
    }
    return;
}