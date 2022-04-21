#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "price.h"

#define MAX_HEAP_SIZE 1024 * 1024 + 5
#define MAX_K_SIZE 1000005

typedef struct {
    uint64_t belonging;
    uint64_t data;
    uint64_t day;
}Price;

Price heap[MAX_HEAP_SIZE] = {0};
uint64_t min_price_data[MAX_K_SIZE] = {0};
uint64_t heap_tail = 0;

void swap( Price *a, Price *b ) {
    Price tmp = *a;
    *a = *b;
    *b = tmp;
}

void push( Price price ) {
    heap[heap_tail] = price;
    uint64_t cur_index = heap_tail;
    while( heap[cur_index].data < heap[(cur_index - 1) / 2].data ) {
        swap( &heap[cur_index], &heap[(cur_index - 1) / 2] );
        cur_index = (cur_index - 1) / 2;
    }
    heap_tail++;
    return;
}
void pop() {
    heap_tail--;
    swap( &heap[0], &heap[heap_tail] );
    uint64_t cur_index = 0;
    while( 1  ) {
        uint64_t min = cur_index, l = cur_index * 2 + 1, r = cur_index * 2 + 2;
        if( l < heap_tail && heap[l].data < heap[min].data ) {
            min = l;
        }
        if( r < heap_tail && heap[r].data < heap[min].data ) {
            min = r;
        }
        if( cur_index != min ) {
            swap( &heap[cur_index], &heap[min] );
            cur_index = min;
        }
        else {
            break;
        }
    }
    return;
}

int cmp ( const void *a , const void *b ) { 
    return *(int *)a > *(int *)b; 
}

uint64_t get_median( uint64_t data[] ) {
    
}


void median_of_medians( uint64_t data[], uint64_t size ) {
    uint64_t l = 0, r = size;
    uint32_t pivot = get_median( data, 0, size );
}

void lower_bound( uint64_t stock, uint64_t k, uint32_t N ) {
    uint64_t l = 0, r = k;

    while( l <= r ) {
        int m = ( l + r ) / 2;

        if( min_price_data[m] == price( stock, k - m ) ) {
            printf( "%lu", min_price_data[m] );
            return;
        }
        else if( min_price_data[m] > price( stock, k - m + N ) ) {
            r = m - 1;
        }
        else if( min_price_data[m] < price( stock, k - m - N ) ) {
            l = m + 1;
        }
        else {
            uint64_t extra_data[2 * N + 1];
            uint64_t size = 0;
            for( int i = k - m - N <= 0 ? 1 : k - m - N; i < k - m + N; i++ ) {
                extra_data[size] = min_price_data[i];
            }
            median_of_medians( extra_data, size );
        }
    }
    printf( "%lu", min_price_data[l] );
    return;
}

int main() {
    uint32_t stock_size = 0, question = 0, increasing_day = 0;
    scanf( "%u %u %u", &stock_size, &question, &increasing_day );
    uint64_t stocks[stock_size];
    for( int i = 0; i < stock_size; i++ ) {
        scanf( "%lu", &stocks[i] );
        for( int j = 1; j <= increasing_day; j++ ) {
            Price p;
            p.belonging = stocks[i];
            p.data = price( stocks[i], j );
            p.day = j;
            push( p );
        }
    }

    uint64_t data_size = 0;
    while( heap_tail != 0 && data_size <= MAX_K_SIZE  ) {
        min_price_data[data_size++] = heap[0].data;
        if( heap[0].day + increasing_day <= 1000000000 ) {
            Price p;
            p.belonging = heap[0].belonging;
            p.data = price( heap[0].belonging, heap[0].day + increasing_day );
            p.day = heap[0].day + increasing_day;
            push( p );
        }
        pop();
    }
    
    for( int i = 0; i < question; i++ ) {
        uint64_t extra_stock = 0, k = 0;
        scanf( "%lu %lu", &extra_stock, &k );
        if( extra_stock == 0 ) {
            printf( "%lu\n", min_price_data[k] );
        }
        else {
            lower_bound( extra_stock, k, increasing_day );
        }
    }
    return 0;
}