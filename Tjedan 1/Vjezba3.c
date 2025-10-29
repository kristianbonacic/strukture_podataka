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
    if (!newPerson) return 0;
    newPerson->next = *head;
    *head = newPerson;
    return 1;
}


int addToEnd(struct Person** head, char name[], char surname[], int year) {
    struct Person* newPerson = createPerson(name, surname, year);
    if (!newPerson) return 0;

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
    while (head != NULL) {
        printf("%s %s (%d)\n", head->name, head->surname, head->birthYear);
        head = head->next;
    }
}


struct Person* findBySurname(struct Person* head, char surname[]) {
    while (head != NULL) {
        if (strcmp(head->surname, surname) == 0)
            return head;
        head = head->next;
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

// 🔹 A. Dodavanje iza određenog elementa
int insertAfter(struct Person* head, char targetSurname[], char name[], char surname[], int year) {
    struct Person* target = findBySurname(head, targetSurname);
    if (target == NULL) return 0;

    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == NULL) return 0;

    newPerson->next = target->next;
    target->next = newPerson;
    return 1;
}

// 🔹 B. Dodavanje ispred određenog elementa
int insertBefore(struct Person** head, char targetSurname[], char name[], char surname[], int year) {
    if (*head == NULL) return 0;

   
    if (strcmp((*head)->surname, targetSurname) == 0)
        return addToBeginning(head, name, surname, year);

    struct Person* current = *head;
    while (current->next != NULL && strcmp(current->next->surname, targetSurname) != 0)
        current = current->next;

    if (current->next == NULL) return 0;

    struct Person* newPerson = createPerson(name, surname, year);
    if (newPerson == NULL) return 0;

    newPerson->next = current->next;
    current->next = newPerson;
    return 1;
}

// 🔹 C. Sortiranje liste po prezimenu
void sortList(struct Person** head) {
    if (*head == NULL || (*head)->next == NULL) return;

    int swapped;
    struct Person* ptr1;
    struct Person* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->surname, ptr1->next->surname) > 0) {
              
                char tmpName[50], tmpSurname[50];
                int tmpYear;

                strcpy(tmpName, ptr1->name);
                strcpy(tmpSurname, ptr1->surname);
                tmpYear = ptr1->birthYear;

                strcpy(ptr1->name, ptr1->next->name);
                strcpy(ptr1->surname, ptr1->next->surname);
                ptr1->birthYear = ptr1->next->birthYear;

                strcpy(ptr1->next->name, tmpName);
                strcpy(ptr1->next->surname, tmpSurname);
                ptr1->next->birthYear = tmpYear;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// 🔹 D. Spremanje u datoteku
int saveToFile(struct Person* head, char filename[]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return 0;

    while (head != NULL) {
        fprintf(file, "%s %s %d\n", head->name, head->surname, head->birthYear);
        head = head->next;
    }

    fclose(file);
    return 1;
}

// 🔹 E. Učitavanje iz datoteke
int loadFromFile(struct Person** head, char filename[]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return 0;

    char name[50], surname[50];
    int year;

    while (fscanf(file, "%s %s %d", name, surname, &year) == 3)
        addToEnd(head, name, surname, year);

    fclose(file);
    return 1;
}


int main() {
    struct Person* head = NULL;
    char filename[] = "osobe.txt";
    loadFromFile(&head, filename);

    int choice;
    char name[50], surname[50], target[50];
    int year;

    while (1) {
        printf("\n--- IZBORNIK ---\n");
        printf("1 - Dodaj na pocetak\n");
        printf("2 - Dodaj na kraj\n");
        printf("3 - Ispisi listu\n");
        printf("4 - Dodaj iza osobe\n");
        printf("5 - Dodaj ispred osobe\n");
        printf("6 - Sortiraj po prezimenu\n");
        printf("7 - Obrisi po prezimenu\n");
        printf("8 - Spremi u datoteku\n");
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
            printf("Iza koje osobe (prezime)? ");
            scanf("%s", target);
            printf("Nova osoba (ime, prezime, godina): ");
            scanf("%s %s %d", name, surname, &year);
            if (!insertAfter(head, target, name, surname, year))
                printf("Osoba nije pronadena.\n");
        }
        else if (choice == 5) {
            printf("Ispred koje osobe (prezime)? ");
            scanf("%s", target);
            printf("Nova osoba (ime, prezime, godina): ");
            scanf("%s %s %d", name, surname, &year);
            if (!insertBefore(&head, target, name, surname, year))
                printf("Osoba nije pronadena.\n");
        }
        else if (choice == 6) {
            sortList(&head);
            printf("Lista sortirana.\n");
        }
        else if (choice == 7) {
            printf("Prezime za brisanje: ");
            scanf("%s", surname);
            if (deleteBySurname(&head, surname))
                printf("Osoba obrisana.\n");
            else
                printf("Osoba nije pronadena.\n");
        }
        else if (choice == 8) {
            saveToFile(head, filename);
            printf("Podaci spremljeni u '%s'.\n", filename);
        }
        else if (choice == 0) {
            printf("Kraj programa.\n");
            saveToFile(head, filename);
            break;
        }
        else {
            printf("Nepostojeca opcija.\n");
        }
    }

    return 0;