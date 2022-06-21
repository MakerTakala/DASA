#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) (a > b ? a : b)

long long int id = 1;

typedef struct _Node{
    long long int id;
    long long int time;
    long long int sum;
    long long int size;
    long long int pir;
    struct _Node *r ;
    struct _Node *l ;
    bool reverse;
    long long int reboot;
    long long int first;
    long long int second;
    long long int cnt;
}Node;

Node* init_Node( long long int time ) {
    Node *init = calloc( sizeof( Node ), 1 );
    init->id = id++;
    init->time = time;
    init->sum = time;
    init->size = 1;
    init->pir = rand() % __LONG_LONG_MAX__;
    init->r = NULL;
    init->l = NULL;
    init->reverse = false;
    init->reboot = 0;
    init->first = time;
    init->second = 0;
    init->cnt = 1;
    return init;
}

long long int size( Node *node ){
    if( !node ) return 0;
    return node->size;
}

long long int sum( Node *node ) {
    if( !node ) return 0;
    return node->sum;
}

long long int first( Node *node ) {
    if( !node ) return 0;
    return node->first;
}

long long int second( Node *node ) {
    if( !node ) return 0;
    return node->second;
}

long long cnt( Node* node ) {
    if( !node ) return 0;
    return node->cnt;
}

void push_reverse( Node **node ) {
    if( !*node ) return;
    if( (*node)->reverse ) {
        Node *tmp = (*node)->l;
        (*node)->l = (*node)->r;
        (*node)->r = tmp;
        (*node)->reverse = false;
        if( (*node)->l ) (*node)->l->reverse ^= true;
        if( (*node)->r ) (*node)->r->reverse ^= true;
    }
}

void push_reboot( Node **node ) {
    if( !*node ) return;
    if( (*node)->reboot != 0 ) {
        if( (*node)->time > (*node)->reboot ) {
            (*node)->time = (*node)->reboot;
        }
        if( (*node)->first <= (*node)->reboot ) {
            (*node)->reboot = 0;
        }
        else if( (*node)->second <= (*node)->reboot ) {
            (*node)->sum -= ( ( (*node)->first - (*node)->reboot ) * (*node)->cnt );
            if( (*node)->l ) (*node)->l->reboot = (*node)->reboot;
            if( (*node)->r ) (*node)->r->reboot = (*node)->reboot;
            (*node)->reboot = 0;
        }
        else {
            if( (*node)->l ) (*node)->l->reboot = (*node)->reboot;
            if( (*node)->r ) (*node)->r->reboot = (*node)->reboot;
            push_reboot( &(*node)->l );
            push_reboot( &(*node)->r );
            (*node)->reboot = 0;
        }
    }
}

void pull( Node **node ){
    if( !*node ) return;
    (*node)->size = 1 + size( (*node)->l ) + size( (*node)->r);
    push_reboot( node );
    push_reboot( &(*node)->l );
    push_reboot( &(*node)->r );
    pull( &(*node)->l );
    pull( &(*node)->r );
    (*node)->sum = (*node)->time + sum( (*node)->l ) + sum( (*node)->r);
    long long int compare[5] = {0};
    compare[0] = (*node)->time;
    compare[1] = first( (*node)->l );
    compare[2] = first( (*node)->r );
    compare[3] = second( (*node)->l );
    compare[4] = second( (*node)->r );
    (*node)->first = MAX( MAX( compare[0], compare[1] ) , compare[2] );
    long long int second = 0;
    for( int i = 0; i < 5; i++ ) {
        if( compare[i] < (*node)->first ) {
            second = MAX( second,  compare[i] );
        }
    }
    (*node)->second = second;
    (*node)->cnt = 0;
    if( (*node)->time == (*node)->first )
        (*node)->cnt += 1;
    if( (*node)->first == first( (*node)->l ) ) 
        (*node)->cnt += cnt((*node)->l);
    if( (*node)->first == first( (*node)->r ) ) 
        (*node)->cnt += cnt((*node)->r);
}

Node* merge( Node **a, Node **b ){
    if( !*a ) return *b;
    if( !*b ) return *a;
    push_reverse( a );
    push_reverse( b );
    push_reboot( a );
    push_reboot( b );
    if( (*a)->pir > (*b)->pir ) {
        (*a)->r = merge( &(*a)->r, b );
        pull( a );
        return *a;
    }
    else {
        (*b)->l = merge( a, &(*b)->l );
        pull( b );
        return *b;
    }
}

void split( Node **s, long long int k, Node **a, Node **b ) {
    if( !*s ) {
        *a = NULL;
        *b = NULL;
        return;
    }
    push_reverse( s );
    push_reboot( s );
    if( size((*s)->l) >= k ) {
        *b = *s;
        split( &(*s)->l, k, a, &(*b)->l );
        push_reverse( b );
        push_reboot( b );
        pull( b );
    }
    else {
        *a = *s;
        split( &(*s)->r, k - size((*s)->l) - 1, &(*a)->r, b );
        push_reverse( a );
        push_reboot( a );
        pull( a );
    }
}

void insert( Node **root, long long int pos, long long int time ) {
    Node *new = init_Node( time );
    Node *lt = NULL, *rt = NULL;
    split( root, pos, &lt, &rt );
    Node *tmp = merge( &lt, &new );
    *root = merge( &tmp, &rt );
}//operaiton 1

void delete( Node **root, long long int key ) {
    Node *lt = NULL, *rt = NULL;
    split( root, key - 1, &lt, root );
    split( root, 1, root, &rt );
    *root = merge( &lt, &rt );
}//operation 2

void reverse( Node **root, int l, int r ) {
    Node *lt = NULL, *mt = NULL, *rt = NULL;
    split( root, l - 1, &lt, &mt );
    split( &mt, r - l + 1, &mt, &rt );
    mt->reverse = true;
    mt = merge( &mt, &rt );
    *root = merge( &lt, &mt );
}//operation 3

void swap( Node **root, long long int l, long long int r, long long int x, long long int y ) {
    if( !*root ) return;
    Node *t1 = NULL, *t2 = NULL, *t3 = NULL, *t4 = NULL, *t5 = NULL;
    if( l < x ) {
        split( root, l - 1, &t1, &t2 );
        split( &t2, r - l + 1, &t2, &t3 );
        split( &t3, x - r - 1, &t3, &t4 );
        split( &t4, y - x + 1, &t4, &t5 );
    }
    else {
        split( root, x - 1, &t1, &t2 );
        split( &t2, y - x + 1, &t2, &t3 );
        split( &t3, l - y - 1, &t3, &t4 );
        split( &t4, r - l + 1, &t4, &t5 );
    }
    *root = merge( &t1, &t4 );
    *root = merge( root, &t3 );
    *root = merge( root, &t2 );
    *root = merge( root, &t5 );
}//operation 4

void reboot( Node **root, long long int l, long long int r, long long k ){
    Node *lt = NULL, *mt = NULL, *rt = NULL;
    split( root, l - 1, &lt, &mt );
    split( &mt, r - l + 1, &mt, &rt );
    mt->reboot = k;
    mt = merge( &mt, &rt );
    *root = merge( &lt, &mt );
}//opertaion 5

void query( Node **root, long long int l, long long int r ) {
    travel( *root );
    printf( "query:" );
    if( !*root ){
        printf( "0\n" );
        return;
    }
    Node *lt = NULL, *mt = NULL, *rt = NULL;
    split( root, l - 1, &lt, &mt );
    split( &mt, r - l + 1, &mt, &rt );
    printf( "%lld\n", mt->sum );
    mt = merge( &mt, &rt );
    *root = merge( &lt, &mt );
}//operation 6

void travel( Node* node ) {
    if( !node ) return;
    travel( node->l );
    printf( "id:%2lld size:%2lld time:%2lld sum:%3lld first:%2lld second:%2lld cnt:%2lld reboot%2lld ",node->id, node->size, node->time, node->sum, node->first, node->second, node->cnt, node->reboot );
    if( node->l )
        printf( "l:%lld ", node->l->id );
    if( node->r )
        printf( "r:%lld", node->r->id );
    printf( "\n" );
    travel( node->r );
}

int main() {
    long long int N, Q;
    scanf( "%lld %lld", &N, &Q );
    Node *root = NULL;
    for( long long int i = 1, x; i <= N; i++ ) {
        scanf( "%lld", &x );
        insert( &root, i, x );
    }
    travel( root );
    for( long long int i = 0; i < Q; i++ ) {
        long long int O;
        scanf( "%lld", &O );
        if( O == 1 ) {
            long long int p, k;
            scanf( "%lld %lld", &p, &k );
            insert( &root, p, k );
        }
        else if( O == 2 ) {
            long long int p;
            scanf( "%lld", &p );
            delete( &root, p );
        }
        else if( O == 3 ) {
            long long int l, r;
            scanf( "%lld %lld", &l, &r );
            reverse( &root, l, r );
        }
        else if( O == 4 ) {
            long long int l, r, x, y;
            scanf( "%lld %lld %lld %lld", &l, &r, &x, &y );
            swap( &root, l, r, x, y );
        }
        else if( O == 5 ) {
            long long int l, r, k;
            scanf( "%lld %lld %lld", &l, &r, &k );
            reboot( &root, l, r, k );
        }
        else if( O == 6 ) {
            long long int l, r;
            scanf( "%lld %lld", &l, &r );
            query( &root, l, r );
        }
        travel( root );
    }

    return 0;
}