#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "price.h"

#define MAX_HEAP_SIZE 1024 * 1024 + 5
#define MAX_K_SIZE 1000005
#define MIN(a, b) ( a < b ? a : b )

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

void swap_( uint64_t *a, uint64_t *b ) {
    uint64_t tmp = *a;
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
    return *(uint64_t *)a > *(uint64_t *)b; 
}

uint64_t partition( uint64_t data[], uint64_t size, uint64_t pivot ) {
    for( int i = 0; i < size; i++ ) {
        if( data[i] == pivot ) {
            swap_( &data[i], &data[size - 1] );
        }
    }
    
    uint64_t len = 0;
    for( int i = 0; i < size - 1; i++ ) {
        if( data[i] <= pivot ) {
            swap_( &data[len], &data[i] );
            len++;
        }
    }
    swap_( &data[size - 1], &data[len] );

    return len;
}

uint64_t median_of_medians( uint64_t data[], uint64_t size, uint64_t kth ) {
    if( size == 1 ) {
        return data[0];
    }

    uint64_t next_size = 0;
    for( int i = 0; i < size; i+= 5 ) {
        int len = MIN( 5, size - i );
        qsort( data + i, len, sizeof(uint64_t), cmp );
        swap_( &data[i / 5], &data[i + len / 2] );
        next_size++;
    }

    uint64_t median = 0;
    if( next_size > 1 ) {
        median = median_of_medians( data, next_size, next_size / 2 );
    }
    else {
        median = data[0];
    }
    
    uint64_t part = partition( data, size, median );

    if( part == kth ) {
        return median;
    }
    else if( part > kth ) {
        return median_of_medians( data, part, kth );
    } 
    else {
        return median_of_medians( data + part, size - part, kth - part );
    }
}


void lower_bound( uint64_t stock, uint64_t k, uint32_t N ) {
    uint64_t l = 1, r = k;
    uint64_t extra_data[2 * N - 1];
    uint64_t m;
    \*
    for( int i = 1 ; i <= 10; i++ ) {
        printf("%llu ", price(stock, i) );
    }
    *\
    while( l <= r ) {
        m = ( l + r ) / 2;
        printf("[DEBUG]l r: %lu %lu", l, r);

        if( min_price_data[m] >= price( stock, k - m + N ) ) {
            printf("[DEBUG]r move \n");
            r = m - 1;
        }
        else if( min_price_data[m] <= ( k <= m + N ? 0 :price( stock, k - m - N ) ) ) {
            printf("[DEBUG]l move \n");
            l = m + 1;
        }
        else {

            memset( extra_data, 0, (2 * N - 1) * sizeof( uint64_t ) );
            int64_t start = (int64_t)k - (int64_t)m - (int64_t)N + 1;
            int64_t end = (int64_t)k - (int64_t)m + (int64_t)N - 1;
            printf("[DEBUG]start end:%ld %ld\n", start, end);
            for( int i = 0, j = start; j <= end ; i++, j++ ) {
                if( j >= 1 ) {
                    extra_data[i] = price( stock, j );
                }
            }
            

            //uint64_t p = median_of_medians( extra_data, 2 * N - 1, N - 1 );
            qsort( extra_data, 2 * N - 1, sizeof(uint64_t), cmp );

            uint64_t p = extra_data[N - 1];
            printf("[DEBUG]p:%lu\n", p);
            if( min_price_data[m] == p ) {
                printf( "%lu\n", min_price_data[m] );
                return;
            }
            else if( min_price_data[m] > p) {
                r = m - 1;
            }
            else if( min_price_data[m] < p ) {
                l = m + 1;
            }
        }
    }

    uint64_t p1 = min_price_data[l], p2 = extra_data[(k - r) - (k - m - N ) - 1];//median_of_medians( extra_data, 2 * N - 1, (k - r) - (k - m - N) - 1 );
    uint64_t p3 = min_price_data[r], p4 = median_of_medians( extra_data, 2 * N - 1, (k - l) - (k - m - N) - 1 );
    printf("[DEBUG]p:%lu %lu %lu %lu\n", p1, p2, p3, p4);
    printf("[DEBUG]l r:%lu %lu\n", l, r);
    printf( "%lu\n", MIN(p1, p2) );
    return;
}



int main() {
    uint64_t stock_size = 0, question = 0, increasing_day = 0;
    scanf( "%lu %lu %lu", &stock_size, &question, &increasing_day );
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

    uint64_t data_size = 1;
    while( heap_tail != 0 && data_size <= 1000000  ) {
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
