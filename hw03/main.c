#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define BASE 94
#define MOD 98120979115476319

typedef struct{
    int64_t index;
    int64_t hash;
}magic;

int64_t K = 0, L = 0, flag = 0, count = 0;
int64_t *str_hash;
magic *sort_str_hash;

int64_t hashing( char *str ) {
    int64_t hash = 0;
    for( int i = 0; i < L; i++ ) {
        hash = ( ( hash * BASE ) % MOD + ( str[i] - '!' ) ) % MOD;
    }
    return hash;
}

int compare( const void *a, const void *b ) {
    return ((magic*)a)->hash > ((magic*)b)->hash;
}

int main() {
    
    scanf( "%lu %lu %lu", &K, &L, &flag );
    char **str = calloc( sizeof( char* ), K );
    str_hash = calloc( sizeof( int64_t ), K );
    sort_str_hash = calloc( sizeof( magic ), K );
    for( int i = 0; i < K; i++ ) {
        str[i] = calloc( sizeof( char ), L );
        scanf( "%s", str[i] );
        str_hash[i] = hashing( str[i] );
    }
    
    for( int i = 0; i < K; i++ ) {
        sort_str_hash[i].hash = str_hash[i];
    }
    int64_t ci = 1, repeat = 0;;
    qsort( sort_str_hash, K, sizeof( magic ), compare );
    for( int i = 1; i < K; i++ ) {
        if( sort_str_hash[i - 1].hash == sort_str_hash[i].hash ) {
            repeat += ci;
                ci++;
        }
        else {
            ci = 1;
        }
    }

    int64_t pow = 1, pair1 = 0, pair2 = 0;
    for( int i = L - 1; i >= 0; i-- ) {
        for( int j = 0; j < K; j++ ) {
            sort_str_hash[j].hash = ( ( str_hash[j] - ( ( str[j][i] - '!' ) * pow ) ) % MOD + MOD ) % MOD;
            sort_str_hash[j].index = j;
        }
        qsort( sort_str_hash, K, sizeof( magic ), compare );
        
        int64_t conti = 1;
        for( int j = 1; j < K; j++ ) {
            if( sort_str_hash[j - 1].hash == sort_str_hash[j].hash ) {
                pair1 = sort_str_hash[j - 1].index;
                pair2 = sort_str_hash[j].index;
                count += conti;
                conti++;
            }
            else {
                conti = 1;
            }
        }
        pow = ( pow * BASE ) % MOD;
    }
    if( count == 0 ) {
        printf( "No\n" );
    }
    else {
        printf( "Yes\n" );
        if( flag == 0 ) {
            printf( "%ld %ld\n", pair1, pair2 );
        }
        else {
            printf( "%ld\n", count - repeat * ( L - 1 ) );
        }
        
    }
    

    return 0;
}