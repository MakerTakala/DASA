#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct _Node{
    int time;
    int sum;
    int key;
    int pir;
    struct _Node *r ;
    struct _Node *l ;
    bool reverse;
}Node;

Node* init_Node( int key, int time ) {
    Node *init = calloc( sizeof( Node ), 1 );
    init->time = time;
    init->sum = time;
    init->key = key;
    init->pir = random() % __INT_MAX__;
    init->r = NULL;
    init->l = NULL;
    init->reverse = false;
}

Node* merge( Node **a, Node **b ){
    if( !*a ) return *b;
    if( !*b ) return *a;
    if( (*a)->pir > (*b)->pir ) {
        (*a)->r = merge( &(*a)->r, b );
        return *a;
    }
    (*b)->l = merge( a, &(*b)->l );
    return *b;
}

void split( Node **s, int k, Node **a, Node **b ) {
    if( !*s ) {
        *a = NULL;
        *b = NULL;
    }
    else if( (*s)->key <= k ) {
        *a = *s;
        split( &(*s)->r, k, &(*a)->r, b );
    }
    else {
        *b = *s;
        split( &(*s)->l, k, a, &(*b)->l );
    }
}

void insert( Node **root, int key, int time ) {
    Node *new = init_Node( key, time );
    printf( "\ninsert:\n" );
    printf( "key:%d pri:%d time:%d sum:%d ", new->key, new->pir, new->time, new->sum );
    printf( "\n\n" );
    Node *lt = NULL, *rt = NULL;
    split( root, key, &lt, &rt );
    printf( "%p %p\n", lt, rt );
    Node *tmp = merge( &lt, &new );
    *root = merge( &tmp, &rt );
    printf( "root:%p\n", *root );
}

void delete( Node **root, int key ) {
    Node *lt = NULL, *rt = NULL;
    split( root, key - 1, &lt, root );
    split( root, key, root, &rt );
    *root = merge( &lt, &rt );
}

int oper6( Node* node, int l, int r ) {
    if( node->key < l ) {
        return oper6( node->r, l, r );
    }
    else if( node->key > r ) {
        return oper6( node->l, l, r );
    }
    else {
        return node->time + oper6( node->l, l, r ) + oper6( node->r, l, r );
    }
}

void travel( Node* node ) {
    if( !node ) return;
    travel( node->l );
    printf( "(%p)key:%d pri:%d time:%d sum:%d ",node, node->key, node->pir, node->time, node->sum );
    if( node->l ) printf( "l: %d ", node->l->key );
    else printf( "l:NULL " );
    if( node->r ) printf( "r: %d ", node->r->key );
    else printf( "r:NULL " );
    printf( "\n" );
    travel( node->r );
    return;
}

int main() {
    srandom(time(0));
    int N, Q;
    scanf( "%d %d", &N, &Q );

    Node *root = NULL;
    for( int i = 0; i < Q; i++ ) {
        int O;
        scanf( "%d", &O );
        if( O == 1 ) {
            int p, k;
            scanf( "%d %d", &p, &k );
            insert( &root, p, k );
        }
        else if( O == 2 ) {
            int p;
            scanf( "%d", &p );
        }
        else if( O == 3 ) {
            int l, r;
            scanf( "%d %d", &l, &r );
        }
        else if( O == 4 ) {
            int l, r, x, y;
            scanf( "%d %d %d %d", &l, &r, &x, &y );
        }
        else if( O == 5 ) {
            int l, r, k;
            scanf( "%d %d %d", &l, &r, &k );
        }
        else if( O == 6 ) {
            int l, r;
            scanf( "%d %d", &l, &r );
        }
        travel(root);
    }

    return 0;
}