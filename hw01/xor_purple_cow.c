#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Student {
    uint64_t id;
    uint64_t group;
    struct Student *link;
}Student;

typedef struct Bathroom {
    Student *head;
    Student *tail;
    Student **group_head;
    Student **group_tail;
    Student **next_group;
}Bathroom;


Bathroom *bathroom;
uint64_t bathroom_size = 0, situation = 0, group_size = 0;

Student *XOR( Student *a, Student *b );
void travel();
void enter( uint64_t group_id, uint64_t id, uint64_t bathroom_id );
void leave( uint64_t bathroom_id );
void go( uint64_t bathroom_id );
void close( uint64_t bathroom_id );

int main() {

    scanf("%lu %lu %lu", &bathroom_size, &situation, &group_size);

    bathroom = calloc( sizeof(Bathroom), bathroom_size );
    for( int i = 0; i < bathroom_size; i++ ) {
        (bathroom + i)->group_head = calloc( sizeof(Student*), group_size );
        (bathroom + i)->group_tail = calloc( sizeof(Student*), group_size );
        (bathroom + i)->next_group = calloc( sizeof(Student*), group_size );
    }

    char command[20] = {0};
    for( int i = 0; i < situation; i++ ) {
        scanf( "%s", command );
        uint64_t group_id = 0, id = 0, bathroom_id = 0;
        if( !strcmp( command, "enter" ) ) {
            scanf( "%lu %lu %lu", &group_id, &id, &bathroom_id );
            enter( group_id, id, bathroom_id );
        }
        else if( !strcmp( command, "leave" ) ) {
            scanf( "%lu", &bathroom_id );
            leave( bathroom_id );
        }
        else if( !strcmp( command, "go" ) ) {
            scanf( "%lu", &bathroom_id );
            go( bathroom_id );
        }
        else {
            scanf( "%lu", &bathroom_id );
            close( bathroom_id );
        }
        printf("\nHEAD:\n");
        for( int i = 0; i < bathroom_size; i++ ) {
            for( int j = 0; j < group_size; j++ ) {
                printf("%p", *((bathroom + i)->group_head + j) );
                if( *((bathroom + i)->group_head + j) != NULL) {
                    printf("(%lu)", (*((bathroom + i)->group_head + j))->id);
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\nTAIL:\n");
        for( int i = 0; i < bathroom_size; i++ ) {
            for( int j = 0; j < group_size; j++ ) {
                printf("%p", *((bathroom + i)->group_tail + j) );
                if( *((bathroom + i)->group_tail + j) != NULL) {
                    printf("(%lu)", (*((bathroom + i)->group_tail + j))->id);
                }
                printf(" ");
            }
            printf("\n");
        }
        printf("\nNEXT_GROUP:\n");
        for( int i = 0; i < bathroom_size; i++ ) {
            for( int j = 0; j < group_size; j++ ) {
                printf("%p", *((bathroom + i)->next_group + j));
                if( *((bathroom + i)->next_group + j) != NULL) {
                    printf("(%lu)", (*((bathroom + i)->next_group + j))->group);
                }
                printf(" ");
            }
            printf("\n");
        }
        travel();
        printf("-------------\n");
    }
    printf("-------------\n");
    travel();
    return 0;
}

Student *XOR( Student *a, Student *b ) {
    return (Student*)(((uint64_t)a) ^ ((uint64_t)b));
}

void travel() {
    for( int i = 0; i < bathroom_size; i++ ) {
        Student *prev = NULL;
        Student *Head = (bathroom + i)->head;
        while( Head ) {
            Student *tmp = Head;
            Head = XOR( Head->link, prev );
            prev = tmp;
        }
        printf( "\n" );
    }
    return;
}

void enter( uint64_t group_id, uint64_t id, uint64_t bathroom_id ) {
    Bathroom *cur_bathroom = bathroom + bathroom_id;
    Student **group_head = cur_bathroom->group_head + group_id;
    Student **group_tail = cur_bathroom->group_tail + group_id;
    Student **next_group = cur_bathroom->next_group + group_id;

    Student *new_student = calloc( sizeof(Student), 1 );
    new_student->id = id;
    new_student->group = group_id;


    if( cur_bathroom->tail == NULL ) {
        new_student->link = NULL;
        cur_bathroom->head = new_student;
        cur_bathroom->tail = new_student;
        *group_head = new_student;
        *group_tail = new_student;
    }
    else if( *group_tail == NULL ){
        if( cur_bathroom->tail->group != group_id ) {
            *(cur_bathroom->next_group + cur_bathroom->tail->group) = new_student;
        }
        new_student->link = XOR( cur_bathroom->tail, NULL );
        cur_bathroom->tail->link = XOR( cur_bathroom->tail->link, new_student );
        cur_bathroom->tail = new_student;
        *group_head = new_student;
        *group_tail = new_student;
    }
    else if( *group_tail == cur_bathroom->tail ) {
        if( cur_bathroom->tail->group != group_id ) {
            *(cur_bathroom->next_group + cur_bathroom->tail->group) = new_student;
        }
        new_student->link = XOR( cur_bathroom->tail, NULL );
        cur_bathroom->tail->link = XOR( cur_bathroom->tail->link, new_student );
        cur_bathroom->tail = new_student;
        *group_tail = new_student;
    }
    else {
        (*group_tail)->link = XOR( new_student, XOR( (*group_tail)->link, *next_group ) );
        new_student->link = XOR( *group_tail, *next_group );
        (*next_group)->link = XOR( new_student, XOR( (*next_group)->link, *group_tail ) );
        *group_tail = new_student;
    }
    return;
}
void leave( uint64_t bathroom_id ) {
    Bathroom *cur_bathroom = bathroom + bathroom_id;
    Student *last = cur_bathroom->tail;
    Student *prev = XOR( last->link, NULL );
    Student **group_head = cur_bathroom->group_head + last->group;
    Student **group_tail = cur_bathroom->group_tail + last->group;
    Student **next_group = cur_bathroom->next_group + prev->group;
    
    if( cur_bathroom->head == cur_bathroom->tail ) {
        cur_bathroom->head = NULL;
        cur_bathroom->tail = NULL;
        *next_group = NULL;
    }
    else {
        cur_bathroom->tail = prev;
        prev->link = XOR( prev->link, last );
    }
        
    if( *group_head == *group_tail ) {
        printf("SEPT1\n");
        *group_head = NULL;
        *group_tail = NULL;
        *next_group = NULL;
    }
    else {
        printf("SEPT2\n");
        *group_head = prev;
        
    }
    printf("SEPT3\n");

    return;
}

void go( uint64_t bathroom_id ) {
    Bathroom *cur_bathroom = bathroom + bathroom_id;
    Student *frist = cur_bathroom->head;
    Student *next = XOR( NULL, frist->link );
    Student **group_head = cur_bathroom->group_head + frist->group;
    Student **group_tail = cur_bathroom->group_tail + frist->group;
    Student **next_group = cur_bathroom->next_group + frist->group;
    
    if( cur_bathroom->head == cur_bathroom->tail ) {
        cur_bathroom->head = NULL;
        cur_bathroom->tail = NULL;
        *next_group = NULL;
    }
    else {
        cur_bathroom->head = next;
        next->link = XOR( frist, next->link );
    }

    if( *group_head == *group_tail ) {
        *group_head = NULL;
        *group_tail = NULL;
        *next_group = NULL;
    }
    else {
        *group_head = next;
    }

    return;
}

void close( uint64_t bathroom_id ) {

}