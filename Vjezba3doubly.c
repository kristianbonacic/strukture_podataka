#define _CRT_SECURE_NO_WARNINGS
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

Student* findBySurname(Student* head, char surname[]) {
    Student* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->surname, surname) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

Student* deleteNode(Student** head, Student* target) {
    if (!target) return *head;
    if (target->prev) target->prev->next = target->next;
    else *head = target->next;
    if (target->next) target->next->prev = target->prev;
    free(target);
    return *head;
}

Student* printList(Student* head) {
    Student* temp = head;
    while (temp) {
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
            case 3: {
                printf("Enter surname to delete: ");
                scanf("%s", surname);
                Student* target = findBySurname(head, surname);
                head = deleteNode(&head, target);
                break;
            }
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
