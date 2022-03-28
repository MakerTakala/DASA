#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct Student {
    uint64_t id;
    uint64_t group;
    bool flag;
    struct Student *next;
    struct Student *prev;
}Student;

void enter( uint64_t group_id, uint64_t id, uint64_t bathroom_id );
void leave( uint64_t bathroom_id );
void go( uint64_t bathroom_id );
void close( uint64_t bathroom_id );
void travel();


Student *dummy_bathroom_head;
Student **bathroom_tail;
Student ***bathroom_group_tail;
Student ***bathroom_group_head;
bool *close_bathroom;
uint64_t bathroom_size = 0, situation = 0, group_size = 0;

int main() {

    scanf("%lu %lu %lu", &bathroom_size, &situation, &group_size);

    dummy_bathroom_head = calloc( sizeof(Student), bathroom_size );
    bathroom_tail = calloc( sizeof(Student*), bathroom_size );
    bathroom_group_tail = calloc( sizeof(Student**), bathroom_size );
    bathroom_group_head = calloc( sizeof(Student**), bathroom_size );
    close_bathroom = calloc( sizeof(bool), bathroom_size );

    for( int i = 0; i < bathroom_size; i++ ) {
        *(bathroom_tail + i) = (dummy_bathroom_head + i);
        *(bathroom_group_tail + i) = calloc( sizeof(Student*), group_size );
        *(bathroom_group_head + i) = calloc( sizeof(Student*), group_size );
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
                printf("%p ", bathroom_group_head[i][j]);
            }
            printf("\n");
        }
        printf("\nTAIL:\n");
        for( int i = 0; i < bathroom_size; i++ ) {
            for( int j = 0; j < group_size; j++ ) {
                printf("%p ", bathroom_group_tail[i][j]);
            }
            printf("\n");
        }
        travel();
    }
    printf("-------------\n");
    travel();

    return 0;
}

void travel() {
    for( int i = 0; i < bathroom_size; i++ ) {
        bool reverse = false;
        Student *head = (dummy_bathroom_head + i)->next ;
        while( head != NULL ) {
            printf( "%lu(%ld) ", head->id, head->group );
            reverse ^= head->flag;
            if(reverse) {
                head = head->prev;
            }
            else {
                head = head->next;
            }
        }
        printf( "\n" );
    }
    
    return;
}

void enter( uint64_t group_id, uint64_t id, uint64_t bathroom_id ) {
    Student *new_student = calloc( 1, sizeof(Student) );
    new_student->group = group_id;
    new_student->id = id;
    new_student->flag = false;

    Student **group_tail = *(bathroom_group_tail + bathroom_id) + group_id ;
    Student **group_head = *(bathroom_group_head + bathroom_id) + group_id ;
    Student **last_Student = bathroom_tail + bathroom_id;

    if( (*group_tail) == NULL || (*group_tail)->next == NULL ) {
        (*last_Student)->next = new_student;
        new_student->prev = (*last_Student);
        (*last_Student) = (*last_Student)->next;
        if( (*group_tail) == NULL ) {
            (*group_head) = new_student;
        }
        (*group_tail) = new_student;
    }
    else {
        Student *next = (*group_tail)->next;
        (*group_tail)->next = new_student;
        new_student->prev = (*group_tail);
        next->prev = new_student;
        new_student->next = next;
        (*group_tail) = new_student;
    }
    return;
}


void leave( uint64_t bathroom_id ) {
    
    Student *last_student = *(bathroom_tail + bathroom_id);
    Student **group_tail = *(bathroom_group_tail + bathroom_id) + (*(bathroom_tail + bathroom_id))->group;
    Student **group_head = *(bathroom_group_head + bathroom_id) + (*(bathroom_tail + bathroom_id))->group;
    
    *(bathroom_tail + bathroom_id) = (*(bathroom_tail + bathroom_id))->prev;

    (*(bathroom_tail + bathroom_id))->next = NULL;
    if( *(bathroom_tail + bathroom_id) == (dummy_bathroom_head + bathroom_id) || last_student->group != (*bathroom_tail + bathroom_id)->group ) {
        (*group_tail) = NULL;
        (*group_head) = NULL;
    }
    else {
        (*group_tail) = *(bathroom_tail + bathroom_id);
    }
    
    free(last_student);

    return;
}

void go( uint64_t bathroom_id ) {
    Student *first_student = (dummy_bathroom_head + bathroom_id)->next;
    Student **group_tail = *(bathroom_group_tail + bathroom_id) + (dummy_bathroom_head + bathroom_id)->next->group;
    Student **group_head = *(bathroom_group_head + bathroom_id) + (dummy_bathroom_head + bathroom_id)->next->group;
    
    (dummy_bathroom_head + bathroom_id)->next = (dummy_bathroom_head + bathroom_id)->next->next;
    if( (dummy_bathroom_head + bathroom_id)->next != NULL ) {
        (dummy_bathroom_head + bathroom_id)->next->prev = (dummy_bathroom_head + bathroom_id);
        if( first_student->group != (dummy_bathroom_head + bathroom_id)->next->group ) {
            (*group_tail) = NULL;
            (*group_head) = NULL;
        }
        else{
            (*group_head) = (dummy_bathroom_head + bathroom_id)->next;
        }
    }
    else {
        (*group_tail) = NULL;
        (*group_head) = NULL;
        *(bathroom_tail + bathroom_id) = (dummy_bathroom_head + bathroom_id);
    }
    free(first_student);
    return;
}

void close( uint64_t bathroom_id ) {
    *(close_bathroom + bathroom_id) = true; 
    uint64_t next_bathroom = bathroom_id;
    while( *(close_bathroom + next_bathroom) == true ) {
        next_bathroom--;
        next_bathroom = (next_bathroom + bathroom_size) % bathroom_size;
    }

    Student *leaveing_bathroom_head = dummy_bathroom_head + bathroom_id;
    Student *entering_bathroom_head = dummy_bathroom_head + next_bathroom;

    while( leaveing_bathroom_head->next != NULL ) {
        Student **leaveing_group_head = *(bathroom_group_head + bathroom_id) + leaveing_bathroom_head->next->group;
        Student **leaveing_group_tail = *(bathroom_group_tail + bathroom_id) + leaveing_bathroom_head->next->group;
        Student **entering_group_tail = *(bathroom_group_tail + next_bathroom) + entering_bathroom_head->next->group;

        if( *entering_group_tail != NULL ) {
            (*entering_group_tail)->next = *leaveing_group_tail;
            (*leaveing_group_tail)->next = *entering_group_tail;
            (*leaveing_group_tail)->flag = true;
        }
        else {
            (*(bathroom_tail + bathroom_id))->next = *leaveing_group_tail;
            (*leaveing_group_tail)->next = *(bathroom_tail + bathroom_id);
        }

        if( *entering_group_tail != NULL && (*entering_group_tail)->next != NULL ) {
            (*leaveing_group_head)->prev = (*entering_group_tail)->next;
            ((*entering_group_tail)->next)->prev = *leaveing_group_head;
        }
        else {
            (*leaveing_group_head)->prev = NULL;
        }
        
    }
}