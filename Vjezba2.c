
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
        return 0;
    }

    strcpy(newPerson->name, name);
    strcpy(newPerson->surname, surname);
    newPerson->birthYear = year;
    newPerson->next = NULL;
    return newPerson;
}

int Beginning(struct Person** head, char name[], char surname[], int year) {
    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == 0)
        return 0;
    newPerson->next = *head;
    *head = newPerson;
    return 0;
}

int End(struct Person** head, char name[], char surname[], int year) {
    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == 0)
        return 0;
    if (*head == NULL) {
        *head = newPerson;
        return 0;
    }
    struct Person* current = *head;
    while (current->next != NULL)
        current = current->next;
    current->next = newPerson;
    return 0;
}

int printList(struct Person* head) {
    if (head == NULL) {
        printf("\nLista je prazna.\n");
        return 0;
    }
    printf("\nPopis osoba:\n");
    struct Person* current = head;
    while (current != NULL) {
        printf("%s %s (%d)\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }
    return 0;
}

struct Person* findBySurname(struct Person* head, char surname[]) {
    struct Person* current = head;
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0)
            return current;
        current = current->next;
    }
    return 0;
}

int saveToFile(struct Person* head, char filename[]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 0;
    }
    struct Person* current = head;
    while (current != NULL) {
        fprintf(file, "%s %s %d\n", current->name, current->surname, current->birthYear);
        current = current->next;
    }
    fclose(file);
    printf("Podaci su spremljeni u datoteku '%s'.\n", filename);
    return 0;
}

int loadFromFile(struct Person** head, char filename[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Datoteka '%s' ne postoji. Stvorit ce se nova.\n", filename);
        return 0;
    }
    char name[50], surname[50];
    int year;
    while (fscanf(file, "%s %s %d", name, surname, &year) == 3)
        End(head, name, surname, year);
    fclose(file);
    printf("Podaci su ucitani iz datoteke '%s'.\n", filename);
    return 0;
}

int main() {
    struct Person* head = NULL;
    char filename[] = "studenti.txt";
    loadFromFile(&head, filename);

    int choice;
    char name[50], surname[50];
    int year;

    while (1) {
        printf("\n--- IZBORNIK ---\n");
        printf("1 - Dodaj osobu na pocetak\n");
        printf("2 - Dodaj osobu na kraj\n");
        printf("3 - Ispisi sve osobe\n");
        printf("4 - Pronadi po prezimenu\n");
        printf("5 - Spremi u datoteku\n");
        printf("0 - Izlaz\n");
        printf("Odaberi opciju: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Unesi ime, prezime i godinu rodenja: ");
            scanf("%s %s %d", name, surname, &year);
            Beginning(&head, name, surname, year);
        }
        else if (choice == 2) {
            printf("Unesi ime, prezime i godinu rodenja: ");
            scanf("%s %s %d", name, surname, &year);
            End(&head, name, surname, year);
        }
        else if (choice == 3) {
            printList(head);
        }
        else if (choice == 4) {
            printf("Unesi prezime koje zelis pronaci: ");
            scanf("%s", surname);
            struct Person* found = findBySurname(head, surname);
            if (found != NULL)
                printf("Pronadeno: %s %s (%d)\n", found->name, found->surname, found->birthYear);
            else
                printf("Osoba s prezimenom '%s' nije pronadena.\n", surname);
        }
        else if (choice == 5) {
            saveToFile(head, filename);
        }
        else if (choice == 0) {
            printf("Kraj programa.\n");
            break;
        }
        else {
            printf("Nepostojeca opcija! Pokusaj ponovo.\n");
        }
    }
    return 0;
}
