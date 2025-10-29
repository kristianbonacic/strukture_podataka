#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    char surname[50];
    int age;
    struct Student* next;
    struct Student* prev;
} Student;

Student* createStudent(char name[], char surname[], int age) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) return NULL;
    strcpy(newStudent->name, name);
    strcpy(newStudent->surname, surname);
    newStudent->age = age;
    newStudent->next = NULL;
    newStudent->prev = NULL;
    return newStudent;
}

Student* addBeginning(Student* head, Student* newStudent) {
    if (!head) return newStudent;
    newStudent->next = head;
    head->prev = newStudent;
    return newStudent;
}

Student* addEnd(Student* head, Student* newStudent) {
    if (!head) return newStudent;
    Student* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newStudent;
    newStudent->prev = temp;
    return head;
}

Student* addAfter(Student* target, Student* newStudent) {
    newStudent->next = target->next;
    newStudent->prev = target;
    if (target->next != NULL) target->next->prev = newStudent;
    target->next = newStudent;
    return newStudent;
}

Student* addBefore(Student** head, Student* target, Student* newStudent) {
    newStudent->next = target;
    newStudent->prev = target->prev;
    if (target->prev != NULL) target->prev->next = newStudent;
    else *head = newStudent;
    target->prev = newStudent;
    return newStudent;
}

Student* printList(Student* head) {
    Student* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->age);
        temp = temp->next;
    }
    return head;
}

Student* deleteNode(Student** head, Student* target) {
    if (!target) return *head;
    if (target->prev != NULL) target->prev->next = target->next;
    else *head = target->next;
    if (target->next != NULL) target->next->prev = target->prev;
    free(target);
    return *head;
}
