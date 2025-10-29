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
    if (!newStudent) {
        printf("Memory allocation error!\n");
        return NULL;
    }
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

// Add after a specific surname
Student* addAfter(Student* head, char targetSurname[], Student* newStudent) {
    Student* target = findBySurname(head, targetSurname);
    if (!target) {
        printf("Surname not found!\n");
        return head;
    }
    newStudent->next = target->next;
    target->next = newStudent;
    return head;
}

// Add before a specific surname
Student* addBefore(Student* head, char targetSurname[], Student* newStudent) {
    if (!head) return head;
    if (strcmp(head->surname, targetSurname) == 0) {
        return addBeginning(head, newStudent);
    }
    Student* temp = head;
    while (temp->next != NULL && strcmp(temp->next->surname, targetSurname) != 0)
        temp = temp->next;
    if (temp->next == NULL) {
        printf("Surname not found!\n");
        return head;
    }
    newStudent->next = temp->next;
    temp->next = newStudent;
    return head;
}

Student* deleteNode(Student* head, char surname[]) {
    if (!head) return NULL;
    Student* temp = head;
    Student* prev = NULL;

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Surname not found!\n");
        return head;
    }
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

Student* sortBySurname(Student* head) {
    if (!head) return head;
    Student* i;
    Student* j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->surname, j->surname) > 0) {
                char tempName[50], tempSurname[50];
                int tempAge;
                strcpy(tempName, i->name);
                strcpy(tempSurname, i->surname);
                tempAge = i->age;
                strcpy(i->name, j->name);
                strcpy(i->surname, j->surname);
                i->age = j->age;
                strcpy(j->name, tempName);
                strcpy(j->surname, tempSurname);
                j->age = tempAge;
            }
        }
    }
    return head;
}

Student* saveToFile(Student* head, char filename[]) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file!\n");
        return head;
    }
    Student* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s %s %d\n", temp->name, temp->surname, temp->age);
        temp = temp->next;
    }
    fclose(file);
    return head;
}

Student* loadFromFile(Student* head, char filename[]) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("File does not exist. New file will be created.\n");
        return head;
    }
    char name[50], surname[50];
    int age;
    while (fscanf(file, "%s %s %d", name, surname, &age) == 3) {
        head = addEnd(head, createStudent(name, surname, age));
    }
    fclose(file);
    return head;
}

int main() {
    Student* head = NULL;
    char filename[] = "students.txt";
    head = loadFromFile(head, filename);
    int choice;
    char name[50], surname[50];
    int age;

    while (1) {
        printf("\n--- MENU ---\n");
        printf("1 - Add at beginning\n2 - Add at end\n3 - Add after surname\n4 - Add before surname\n");
        printf("5 - Delete by surname\n6 - Print list\n7 - Sort by surname\n8 - Save to file\n0 - Exit\n");
        printf("Enter choice: ");
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
                printf("Enter surname to add after: ");
                scanf("%s", surname);
                printf("Enter name, surname, age: ");
                scanf("%s %s %d", name, surname, &age);
                head = addAfter(head, surname, createStudent(name, surname, age));
                break;
            case 4:
                printf("Enter surname to add before: ");
                scanf("%s", surname);
                printf("Enter name, surname, age: ");
                scanf("%s %s %d", name, surname, &age);
                head = addBefore(head, surname, createStudent(name, surname, age));
                break;
            case 5:
                printf("Enter surname to delete: ");
                scanf("%s", surname);
                head = deleteNode(head, surname);
                break;
            case 6:
                head = printList(head);
                break;
            case 7:
                head = sortBySurname(head);
                break;
            case 8:
                head = saveToFile(head, filename);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
