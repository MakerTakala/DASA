#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct Student {
    uint32_t id;
    uint32_t group;
    bool flag;
    struct Student *next;
    struct Student *prev;
}Student;

void enter( uint32_t group_id, uint32_t id, Student **bathroom_tail, Student **find );
void leave( Student *bathroom_head, Student **bathroom_tail, Student **find );
void go( Student *bathroom_head, Student **bathroom_tail, Student **find );
void travel( Student *bathroom_head );



int main() {
    uint32_t bathroom_size = 0, situation = 0, group_size = 0;
    scanf("%u %u %u", &bathroom_size, &situation, &group_size);
    Student dummy_bathroom_head[MAX_SIZE];
    Student *bathroom_tail[MAX_SIZE];
    Student *bathroom_group_tail[MAX_SIZE][MAX_SIZE] = {{NULL}};
    for( int i = 0; i < bathroom_size; i++ ) {
        bathroom_tail[i] = &dummy_bathroom_head[i];
    }

    char command[20] = {0};
    for( int i = 0; i < situation; i++ ) {
        scanf( "%s", command );
        uint32_t group_id = 0, id = 0, bathroom_id = 0;
        if( !strcmp( command, "enter" ) ) {
            scanf( "%u %u %u", &group_id, &id, &bathroom_id );
            enter( group_id, id, &bathroom_tail[bathroom_id], &bathroom_group_tail[bathroom_id][group_id] );
        }
        else if( !strcmp( command, "leave" ) ) {
            scanf( "%u", &bathroom_id );
            leave( &dummy_bathroom_head[bathroom_id], &bathroom_tail[bathroom_id], &bathroom_group_tail[bathroom_id][ bathroom_tail[bathroom_id]->group ] );
        }
        else if( !strcmp( command, "go" ) ) {
            scanf( "%u", &bathroom_id );
            go( &dummy_bathroom_head[bathroom_id], &bathroom_tail[bathroom_id], &bathroom_group_tail[bathroom_id][ dummy_bathroom_head[bathroom_id].next->group ] );
        }
        else {
            scanf( "%u", &bathroom_id );

        }
        for( int i = 0; i < bathroom_size; i++ ) {
            for( int j = 0; j < group_size; j++ ) {
                printf("%p ", bathroom_group_tail[i][j]);
            }
            printf("\n");
        }
        for( int i = 0; i < bathroom_size; i++ ) {
            travel( &dummy_bathroom_head[i] );
        }
    }
    printf("-------------\n");
    for( int i = 0; i < bathroom_size; i++ ) {
        travel( &dummy_bathroom_head[i] );
    }

    return 0;
}

void travel( Student *bathroom_head ) {
    bathroom_head = bathroom_head->next;
    while( bathroom_head != NULL ) {
        printf("%u ", bathroom_head->id);
        bathroom_head = bathroom_head->next;
    }
    printf("\n");
    return;
}

void enter( uint32_t group_id, uint32_t id, Student **bathroom_tail, Student **find ) {
    Student *new_student = calloc( 1, sizeof(Student) );
    new_student->group = group_id;
    new_student->id = id;
    new_student->flag = false;
    if( (*find) == NULL || (*find)->next == NULL ) {
        (*bathroom_tail)->next = new_student;
        new_student->prev = (*bathroom_tail);
        (*bathroom_tail) = (*bathroom_tail)->next;
        (*find) = new_student;
    }
    else {
        Student *next = (*find)->next;
        (*find)->next = new_student;
        new_student->prev = (*find);
        next->prev = new_student;
        new_student->next = next;
        (*find) = new_student;
    }
    return;
}


void leave( Student *bathroom_head, Student **bathroom_tail, Student **find ) {
    Student *last = *bathroom_tail;
    *bathroom_tail = (*bathroom_tail)->prev;
    (*bathroom_tail)->next = NULL;
    if( (*bathroom_tail) == bathroom_head || last->group != (*bathroom_tail)->group ) {
        (*find) = NULL;
    }
    else {
        (*find) = *bathroom_tail;
    }
    free(last);
    return;
}

void go( Student *bathroom_head, Student **bathroom_tail, Student **find ) {
    Student *first = bathroom_head->next;
    bathroom_head->next = bathroom_head->next->next;
    if( bathroom_head->next != NULL ) {
        bathroom_head->next->prev = bathroom_head;
        if( first->group != bathroom_head->next->group ) {
            (*find) = NULL;
        }
    }
    else {
        (*find) = NULL;
        (*bathroom_tail) = bathroom_head;
    }
    free(first);
    return;
}

void close() {
    
}