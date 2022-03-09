#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_LENGTH 1000000

typedef struct {
    int32_t top;
    char content[MAX_LENGTH];
}_char_stack;

typedef struct {
    int32_t top;
    int64_t content[MAX_LENGTH];
}_int64_stack;

char char_stack_top( _char_stack *stack );
void char_stack_push( _char_stack *stack, char c );
void char_stack_pop( _char_stack *stack );
bool char_stack_empty( _char_stack *stack );
int64_t int64_stack_top( _int64_stack *stack );
void int64_stack_push( _int64_stack *stack, int64_t num );
void int64_stack_pop( _int64_stack *stack );
bool int64_stack_empty( _int64_stack *stack );
uint8_t operator_priority( char c );
int64_t calculate( _char_stack *operator_stack, _int64_stack *number_stack );

int main() {
    char input[MAX_LENGTH] = {0};
    scanf("%s", input);
    _char_stack operator_stack = {.top = -1};
    _int64_stack number_stack = {.top = -1};
    for(char *cur = input; *cur != 0; cur++ ) {
        if( *cur == '=' ) {
            while( !char_stack_empty( &operator_stack ) ) {
                int64_stack_push( &number_stack, calculate( &operator_stack, &number_stack ) );
            }
            printf("Print: %ld\n", int64_stack_top( &number_stack ) );
        }
        else if( isdigit(*cur) ) {
            int64_t num = *cur - '0';
            while( isdigit( *(cur + 1) ) ){
                cur++;
                num = num * 10 + (*cur - '0');
            }
            int64_stack_push( &number_stack, num );
        }
        else {
            if( operator_priority( char_stack_top( &operator_stack ) ) < operator_priority( *cur ) ) {
                char_stack_push( &operator_stack, *cur );
            }
            else {
                while( !char_stack_empty( &operator_stack ) && operator_priority( char_stack_top( &operator_stack ) ) >= operator_priority( *cur ) && char_stack_top( &operator_stack ) != '(' ) {
                    int64_stack_push( &number_stack, calculate( &operator_stack, &number_stack ) );
                }
                if( *cur != ')' ) {
                    char_stack_push( &operator_stack, *cur );
                }
                if( *cur == ')' && char_stack_top( &operator_stack ) == '(' ){
                    char_stack_pop( &operator_stack );
                }
            }
        }
    }
    return 0;
}

uint8_t operator_priority( char c ) {
    if( c == ')' ) {
        return 1;
    }
    if( c == '+' || c == '-' ) {
        return 2;
    }
    if( c == '*' || c == '/' || c == '%' ) {
        return 3;
    }
    if(c == '(') {
        return 4;
    }
    return 0;
}

int64_t calculate( _char_stack *operator_stack, _int64_stack *number_stack ) {
    char oper = char_stack_top( operator_stack );
    char_stack_pop( operator_stack );
    int64_t num2 = int64_stack_top( number_stack );
    int64_stack_pop( number_stack );
    int64_t num1 = int64_stack_top( number_stack );
    int64_stack_pop( number_stack );
    if(oper == '+') return num1 + num2;
    if(oper == '-') return num1 - num2;
    if(oper == '*') return num1 * num2;
    if(oper == '/') return num1 / num2;
    if(oper == '%') return num1 % num2;
}

char char_stack_top( _char_stack *stack ) {
    return stack -> content[stack -> top];
}

void char_stack_push( _char_stack *stack, char c ) {
    (stack -> top)++;
    stack -> content[stack -> top] = c;
    return;
}

void char_stack_pop( _char_stack *stack ) {
    (stack -> top)--;
    return;
}

bool char_stack_empty( _char_stack *stack ) {
    return stack -> top == -1;
}

int64_t int64_stack_top( _int64_stack *stack ) {
    return stack -> content[stack -> top];
}

void int64_stack_push( _int64_stack *stack, int64_t num ) {
    (stack -> top)++;
    stack -> content[stack -> top] = num;
    return;
}

void int64_stack_pop( _int64_stack *stack ) {
    (stack -> top)--;
    return;
}