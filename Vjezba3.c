#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char name[50];
    char surname[50];
    int age;
    struct Student* next;
} Student;

Student* createStudent(char name[], char surname[], int age) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) return NULL;
    strcpy(newStudent->name, name);
    strcpy(newStudent->surname, surname);
    newStudent->age = age;
    newStudent->next = NULL;
    return newStudent;
}

Student* addBeginning(Student* head, Student* newStudent) {
    newStudent->next = head;
    return newStudent;
}

Student* addEnd(Student* head, Student* newStudent) {
    if (!head) return newStudent;
    Student* temp = head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newStudent;
    return head;
}

Student* findBySurname(Student* head, char surname[]) {
    Student* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

Student* printList(Student* head) {
    Student* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->age);
        temp = temp->next;
    }
    return head;
}
