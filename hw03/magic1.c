#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int64_t failure( char *str, int64_t n ) {
    int64_t prefix[n];
    prefix[0] = -1;
    for( int64_t i = 1, len = -1 ; i < n; i++ ) {
        while( ~len && str[len + 1] != str[i] )
            len = prefix[len];
        if( str[len + 1] == str[i] )
            len++;
        prefix[i] = len;
    }
    return prefix[n - 1] + 1;
}

int main() {
    char *str = calloc( 10000005, sizeof( char ) );
    scanf( "%s", str );
    int64_t n = strlen( str );

    char *reverse_str = calloc( n + 1, sizeof( char ) );
    char *reverse_front_str = calloc( 2 * n + 2, sizeof( char ) );
    char *reverse_back_str = calloc( 2 * n + 2, sizeof( char ) );
    for( int i = 0 ; i < n; i++ ) {
        reverse_str[n - i - 1] = str[i];
    }
    strcpy( reverse_front_str, str );
    strcat( reverse_front_str, " " );
    strcat( reverse_front_str, reverse_str );

    strcpy( reverse_back_str, reverse_str );
    strcat( reverse_back_str, " " );
    strcat( reverse_back_str, str );

    int64_t r1 = n - failure( reverse_front_str, n * 2 + 1 ), r2 = n - failure( reverse_back_str, n * 2 + 1 );

    if( r1 < r2 ) {
        printf( "%ld\n", r1 );
        for( int64_t i = 0; i < r1; i++ )
            printf( "%c", reverse_str[i] );
        printf( "%s\n", str );
    }
    else if( r1 > r2 ) {
        printf( "%ld\n", r2 );
        for( int64_t i = 0; i < r2; i++ )
            printf( "%c", str[i] );
        printf( "%s\n", reverse_str );
    }
    else {
        printf( "%ld\n", r1 );
        if( r1 == 0 )
            printf( "%s\n", str );
        else {
            for( int64_t i = 0; i < r1; i++ ) 
                printf( "%c", reverse_str[i] );
            printf( "%s\n", str );
            for( int64_t i = 0; i < r2; i++ )
                printf( "%c", str[i] );
            printf( "%s\n", reverse_str );
        }
    }
    return 0;
}