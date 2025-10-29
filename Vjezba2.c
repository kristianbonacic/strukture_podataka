#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person {
    char name[50];
    char surname[50];
    int birthYear;
    struct Person* next;
};


struct Person* createPerson(char name[], char surname[], int year) {
    struct Person* newPerson = (struct Person*)malloc(sizeof(struct Person));
    if (newPerson == NULL) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = year;
    newPerson->next = NULL;
    return newPerson;
}


int addToBeginning(struct Person** head, char name[], char surname[], int year) {
    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == NULL) return 0;

    newPerson->next = *head; 
    *head = newPerson;       
    return 1;
}


int addToEnd(struct Person** head, char name[], char surname[], int year) {
    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == NULL) return 0;

    if (*head == NULL) { 
        *head = newPerson;
        return 1;
    }

    struct Person* current = *head;
    while (current->next != NULL)
        current = current->next;

    current->next = newPerson;
    return 1;
}


void printList(struct Person* head) {
    if (head == NULL) {
        printf("Lista je prazna.\n");
        return;
    }

    printf("\nPopis osoba:\n");
    struct Person* current = head;
    while (current != NULL) {
        printf("%s %s (%d)\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }
}


struct Person* findBySurname(struct Person* head, char surname[]) {
    struct Person* current = head;
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0)
            return current;
        current = current->next;
    }
    return NULL;
}


int deleteBySurname(struct Person** head, char surname[]) {
    if (*head == NULL) return 0;

    struct Person* temp = *head;
    struct Person* prev = NULL;

    if (strcmp(temp->surname, surname) == 0) {
        *head = temp->next;
        free(temp);
        return 1;
    }

    while (temp != NULL && strcmp(temp->surname, surname) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return 0;

    prev->next = temp->next;
    free(temp);
    return 1;
}


int main() {
    struct Person* head = NULL;
    int choice;
    char name[50], surname[50];
    int year;

    while (1) {
        printf("\n--- IZBORNIK ---\n");
        printf("1 - Dodaj osobu na pocetak\n");
        printf("2 - Dodaj osobu na kraj\n");
        printf("3 - Ispisi listu\n");
        printf("4 - Pronadi po prezimenu\n");
        printf("5 - Obrisi po prezimenu\n");
        printf("0 - Izlaz\n");
        printf("Odaberi opciju: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Unesi ime, prezime i godinu rodenja: ");
            scanf("%s %s %d", name, surname, &year);
            addToBeginning(&head, name, surname, year);
        }
        else if (choice == 2) {
            printf("Unesi ime, prezime i godinu rodenja: ");
            scanf("%s %s %d", name, surname, &year);
            addToEnd(&head, name, surname, year);
        }
        else if (choice == 3) {
            printList(head);
        }
        else if (choice == 4) {
            printf("Unesi prezime: ");
            scanf("%s", surname);
            struct Person* found = findBySurname(head, surname);
            if (found)
                printf("Pronadeno: %s %s (%d)\n", found->name, found->surname, found->birthYear);
            else
                printf("Osoba nije pronadena.\n");
        }
        else if (choice == 5) {
            printf("Unesi prezime za brisanje: ");
            scanf("%s", surname);
            if (deleteBySurname(&head, surname))
                printf("Osoba obrisana.\n");
            else
                printf("Osoba nije pronadena.\n");
        }
        else if (choice == 0) {
            printf("Kraj programa.\n");
            break;
        }
        else {
            printf("Nepostojeca opcija.\n");
        }
    }

    return 0;
}
