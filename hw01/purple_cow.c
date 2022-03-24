#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Student {
    uint32_t id;
    uint32_t group;
    bool flag;
    struct Student *next;
    struct Student *prev;
}Student;

void pop_first_student( Student **bathroom_head );
void pop_last_student( Student **bathroom_tail );
void travel( Student *bathroom_head );


int main() {
    uint32_t bathroom_size = 0, situation = 0, group_size = 0;
    scanf("%u %u %u\n", &bathroom_size, &situation, &group_size);

    char command[10] = {0};

    Student *bathroom_head[bathroom_size];
    Student *bathroom_tail[bathroom_size];

    for( int i = 0; i < bathroom_size; i++) {
        bathroom_tail[i] = bathroom_head[i];
    }





    for( int i = 0; i < situation; i++ ) {
        scanf( "%s", command );
        uint32_t p_group = 0, id = 0, bathroom_id = 0;
        if( strcmp( command, "enter" ) ) {
            scanf( "%u %u %u\n", &p_group, &id, &bathroom_id );

        }
        else if( strcmp( command, "leave" ) ) {
            scanf( "%u\n", &bathroom_id );
            pop_last_student( &bathroom_tail[bathroom_id] );
        }
        else if( strcmp( command, "go" ) ) {
            scanf( "%u\n", &bathroom_id );
            pop_first_student( &bathroom_tail[bathroom_id] );
        }
        else {
            scanf( "%u", &bathroom_id );

        }
    }

    for( int i = 0; i < bathroom_size; i++ ) {
        travel( bathroom_head[i] );
    }

    return 0;
}

void travel( Student *bathroom_head ) {
    while( bathroom_head != NULL ) {
        printf("%u ", bathroom_head->id);
        bathroom_head = bathroom_head->next;
    }
    printf("\n");
    return;
}

void pop_first_student( Student **bathroom_head ) {
    Student *first = *bathroom_head;
    *bathroom_head = (*bathroom_head)->next;
    (*bathroom_head)->prev = NULL;
    free(first);
    return;
}

void pop_last_student( Student **bathroom_tail ) {
    Student *last = *bathroom_tail;
    *bathroom_tail = (*bathroom_tail)->prev;
    (*bathroom_tail)->next = NULL;
    free(last);
    return;
}