#define _CRT_SECURE_NO_WARNINGS
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

Student* deleteNode(Student* head, char surname[]) {
    if (!head) return NULL;
    Student* temp = head;
    Student* prev = NULL;

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) return head;

    if (prev) prev->next = temp->next;
    else head = temp->next;

    free(temp);
    return head;
}

Student* printList(Student* head) {
    Student* temp = head;
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->name, temp->surname, temp->age);
        temp = temp->next;
    }
    return head;
}

int main() {
    Student* head = NULL;
    int choice, age;
    char name[50], surname[50];

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1 - Add at beginning\n2 - Add at end\n3 - Delete by surname\n4 - Print\n0 - Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter name, surname, age: ");
                scanf("%s %s %d", name, surname, &age);
                head = addBeginning(head, createStudent(name, surname, age));
                break;
            case 2:
                printf("Enter name, surname, age: ");
                scanf("%s %s %d", name, surname, &age);
                head = addEnd(head, createStudent(name, surname, age));
                break;
            case 3:
                printf("Enter surname to delete: ");
                scanf("%s", surname);
                head = deleteNode(head, surname);
                break;
            case 4:
                head = printList(head);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
