#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char ime[50];
    char prezime[50];
    int godine;
    struct Student* next;
    struct Student* prev;
} Student;


Student* createStudent(char ime[], char prezime[], int godine) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (!newStudent) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    strcpy(newStudent->ime, ime);
    strcpy(newStudent->prezime, prezime);
    newStudent->godine = godine;
    newStudent->next = NULL;
    newStudent->prev = NULL;
    return newStudent;
}

void addBeginning(Student** head, char ime[], char prezime[], int godine) {
    Student* newStudent = createStudent(ime, prezime, godine);
    if (*head == NULL) {
        *head = newStudent;
        return;
    }
    newStudent->next = *head;
    (*head)->prev = newStudent;
    *head = newStudent;
}


void addEnd(Student** head, char ime[], char prezime[], int godine) {
    Student* newStudent = createStudent(ime, prezime, godine);
    if (*head == NULL) {
        *head = newStudent;
        return;
    }
    Student* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newStudent;
    newStudent->prev = temp;
}


void addAfter(Student** head, char targetSurname[], char ime[], char prezime[], int godine) {
    Student* temp = *head;
    while (temp != NULL && strcmp(temp->prezime, targetSurname) != 0)
        temp = temp->next;
    if (temp == NULL) {
        printf("Prezime nije pronadjeno!\n");
        return;
    }
    Student* newStudent = createStudent(ime, prezime, godine);
    newStudent->next = temp->next;
    newStudent->prev = temp;
    if (temp->next != NULL)
        temp->next->prev = newStudent;
    temp->next = newStudent;
}

void addBefore(Student** head, char targetSurname[], char ime[], char prezime[], int godine) {
    Student* temp = *head;
    while (temp != NULL && strcmp(temp->prezime, targetSurname) != 0)
        temp = temp->next;
    if (temp == NULL) {
        printf("Prezime nije pronadjeno!\n");
        return;
    }
    Student* newStudent = createStudent(ime, prezime, godine);
    newStudent->next = temp;
    newStudent->prev = temp->prev;
    if (temp->prev != NULL)
        temp->prev->next = newStudent;
    else
        *head = newStudent;
    temp->prev = newStudent;
}

void printList(Student* head) {
    Student* temp = head;
    printf("\nPopis studenata:\n");
    while (temp != NULL) {
        printf("%s %s (%d)\n", temp->ime, temp->prezime, temp->godine);
        temp = temp->next;
    }
}


void sortList(Student* head) {
    if (head == NULL) return;
    int swapped;
    Student* ptr;
    Student* lptr = NULL;

    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != lptr) {
            if (strcmp(ptr->prezime, ptr->next->prezime) > 0) {
                char tmpIme[50], tmpPrezime[50];
                int tmpGodine;

                strcpy(tmpIme, ptr->ime);
                strcpy(tmpPrezime, ptr->prezime);
                tmpGodine = ptr->godine;

                strcpy(ptr->ime, ptr->next->ime);
                strcpy(ptr->prezime, ptr->next->prezime);
                ptr->godine = ptr->next->godine;

                strcpy(ptr->next->ime, tmpIme);
                strcpy(ptr->next->prezime, tmpPrezime);
                ptr->next->godine = tmpGodine;

                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}


void saveToFile(Student* head, char filename[]) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Greska pri otvaranju datoteke!\n");
        return;
    }
    Student* temp = head;
    while (temp != NULL) {
        fprintf(f, "%s %s %d\n", temp->ime, temp->prezime, temp->godine);
        temp = temp->next;
    }
    fclose(f);
}


void loadFromFile(Student** head, char filename[]) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Datoteka ne postoji.\n");
        return;
    }
    char ime[50], prezime[50];
    int godine;
    while (fscanf(f, "%s %s %d", ime, prezime, &godine) == 3)
        addEnd(head, ime, prezime, godine);
    fclose(f);
}


int main() {
    Student* head = NULL;
    char filename[] = "studenti.txt";
    loadFromFile(&head, filename);

    int choice;
    char ime[50], prezime[50], target[50];
    int godine;

    while (1) {
        printf("\n--- IZBORNIK ---\n");
        printf("1 - Dodaj studenta na pocetak\n");
        printf("2 - Dodaj studenta na kraj\n");
        printf("3 - Ispisi sve studente\n");
        printf("4 - Dodaj iza prezimena\n");
        printf("5 - Dodaj ispred prezimena\n");
        printf("6 - Sortiraj po prezimenima\n");
        printf("7 - Spremi u datoteku\n");
        printf("0 - Izlaz\n");
        printf("Odaberi opciju: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Unesi ime, prezime i godine: ");
            scanf("%s %s %d", ime, prezime, &godine);
            addBeginning(&head, ime, prezime, godine);
            break;
        case 2:
            printf("Unesi ime, prezime i godine: ");
            scanf("%s %s %d", ime, prezime, &godine);
            addEnd(&head, ime, prezime, godine);
            break;
        case 3:
            printList(head);
            break;
        case 4:
            printf("Unesi prezime iza kojeg dodajes: ");
            scanf("%s", target);
            printf("Unesi ime, prezime i godine: ");
            scanf("%s %s %d", ime, prezime, &godine);
            addAfter(&head, target, ime, prezime, godine);
            break;
        case 5:
            printf("Unesi prezime ispred kojeg dodajes: ");
            scanf("%s", target);
            printf("Unesi ime, prezime i godine: ");
            scanf("%s %s %d", ime, prezime, &godine);
            addBefore(&head, target, ime, prezime, godine);
            break;
        case 6:
            sortList(head);
            printf("Lista sortirana po prezimenima.\n");
            break;
        case 7:
            saveToFile(head, filename);
            printf("Lista spremljena u datoteku.\n");
            break;
        case 0:
            printf("Kraj programa.\n");
            return 0;
        default:
            printf("Nepostojeca opcija! Pokusaj ponovo.\n");
        }
    }

    return 0;
}