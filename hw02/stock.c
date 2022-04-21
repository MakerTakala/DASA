#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "price.h"

#define MAX_HEAP_SIZE 1024 * 1024 + 5
#define MAX_K_SIZE 1000000

typedef struct {
    int64_t belonging;
    int64_t data;
    int64_t day;
}Price;

Price heap[MAX_HEAP_SIZE];
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
            break;;
        }
    }
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

    uint64_t min_price_data[MAX_K_SIZE] = {0}, data_size = 0;
    while( heap_tail != 0 && data_size < MAX_HEAP_SIZE ) {
        min_price_data[data_size++] = heap[0].data;
        if( heap[0].day + increasing_day <= 1000000000 ) {
            Price p;
            p.belonging = heap[0].belonging;
            p.data = price( heap[0].belonging, heap[0].day + increasing_day );
            p.day = heap[0].day + increasing_day;
            pop();
            push( p );
        }
    }
    for( int i = 0; i < data_size; i++ ) {
        printf( "%ld ", min_price_data[i] );
    }
    return 0;
}