#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define HASH_SIZE 11

typedef struct _city {
    char name[MAX_NAME];
    int population;
    struct _city *left;
    struct _city *right;
} City;

typedef struct _country {
    char name[MAX_NAME];
    City* cityRoot;
    struct _country* next;
} Country;

typedef struct {
    Country* buckets[HASH_SIZE];
} HashTable;

City* createCity(char* name, int pop) {
    City* newCity = (City*)malloc(sizeof(City));
    strcpy(newCity->name, name);
    newCity->population = pop;
    newCity->left = newCity->right = NULL;
    return newCity;
}

City* insertCity(City* root, char* name, int pop) {
    if (root == NULL) return createCity(name, pop);
    if (pop < root->population) {
        root->left = insertCity(root->left, name, pop);
    } else if (pop > root->population) {
        root->right = insertCity(root->right, name, pop);
    } else {
        if (strcmp(name, root->name) < 0)
            root->left = insertCity(root->left, name, pop);
        else
            root->right = insertCity(root->right, name, pop);
    }
    return root;
}

void printCities(City* root, int minPop) {
    if (root == NULL) return;
    printCities(root->left, minPop);
    if (root->population >= minPop) {
        printf("\t%s (%d)\n", root->name, root->population);
    }
    printCities(root->right, minPop);
}

int calculateHash(char* name) {
    int sum = 0;
    for (int i = 0; i < 5 && name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % HASH_SIZE;
}

City* readCitiesFromFile(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) return NULL;
    City* root = NULL;
    char name[MAX_NAME];
    int pop;
    while (fscanf(fp, " %[^,], %d", name, &pop) == 2) {
        root = insertCity(root, name, pop);
    }
    fclose(fp);
    return root;
}

void insertCountrySorted(HashTable* ht, char* countryName, char* fileName) {
    int index = calculateHash(countryName);
    Country* newCountry = (Country*)malloc(sizeof(Country));
    strcpy(newCountry->name, countryName);
    newCountry->cityRoot = readCitiesFromFile(fileName);
    newCountry->next = NULL;
    Country** current = &(ht->buckets[index]);
    while (*current != NULL && strcmp((*current)->name, countryName) < 0) {
        current = &((*current)->next);
    }
    newCountry->next = *current;
    *current = newCountry;
}

void search(HashTable* ht) {
    char target[MAX_NAME];
    int minPop;
    printf("\nUnesite ime drzave: ");
    scanf("%s", target);
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &minPop);
    int index = calculateHash(target);
    Country* curr = ht->buckets[index];
    while (curr != NULL) {
        if (strcmp(curr->name, target) == 0) {
            printf("Rezultati za %s:\n", target);
            printCities(curr->cityRoot, minPop);
            return;
        }
        curr = curr->next;
    }
    printf("Drzava nije pronadjena.\n");
}

int main() {
    HashTable ht;
    for (int i = 0; i < HASH_SIZE; i++) ht.buckets[i] = NULL;
    FILE* fp = fopen("drzave.txt", "r");
    if (!fp) return 1;
    char countryName[MAX_NAME], fileName[MAX_NAME];
    while (fscanf(fp, "%s %s", countryName, fileName) == 2) {
        insertCountrySorted(&ht, countryName, fileName);
    }
    fclose(fp);
    for (int i = 0; i < HASH_SIZE; i++) {
        Country* curr = ht.buckets[i];
        while (curr) {
            printf("\n%s:", curr->name);
            printCities(curr->cityRoot, 0);
            curr = curr->next;
        }
    }
    search(&ht);
    return 0;
}