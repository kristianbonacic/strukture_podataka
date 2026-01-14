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

City* createCity(char* name, int pop);
City* insertCity(City* root, char* name, int pop);
void printCities(City* root, int minPop);
void freeCities(City* root);

int calculateHash(char* name);
City* readCitiesFromFile(char* filename);
void insertCountrySorted(HashTable* ht, char* countryName, char* fileName);
void freeHashTable(HashTable* ht);

void search(HashTable* ht);

int main() {
    HashTable ht;
    int i = 0;
    FILE* fp = NULL;
    char countryName[MAX_NAME], fileName[MAX_NAME];

    for (i = 0; i < HASH_SIZE; i++) {
        ht.buckets[i] = NULL;
    }

    fp = fopen("drzave.txt", "r");
    if (!fp) {
        printf("Greska: Nije moguce otvoriti datoteku drzave.txt\n");
        return 1;
    }

    while (fscanf(fp, "%s %s", countryName, fileName) == 2) {
        insertCountrySorted(&ht, countryName, fileName);
    }
    fclose(fp);

    printf("--- ISPIS SVIH DRZAVA I GRADOVA ---\n");
    for (i = 0; i < HASH_SIZE; i++) {
        Country* curr = ht.buckets[i];
        while (curr) {
            printf("\nDRZAVA: %s (Index: %d)", curr->name, i);
            printCities(curr->cityRoot, 0);
            curr = curr->next;
        }
    }

    search(&ht);
    freeHashTable(&ht);

    return 0;
}

City* createCity(char* name, int pop) {
    City* newCity = (City*)malloc(sizeof(City));
    if (!newCity) 
        return NULL;
    strcpy(newCity->name, name);
    newCity->population = pop;
    newCity->left = NULL;
    newCity->right = NULL;
    return newCity;
}

City* insertCity(City* root, char* name, int pop) {
    if (root == NULL) {
        return createCity(name, pop);
    }

    if (pop < root->population) {
        root->left = insertCity(root->left, name, pop);
    } else if (pop > root->population) {
        root->right = insertCity(root->right, name, pop);
    } else {
        if (strcmp(name, root->name) < 0) {
            root->left = insertCity(root->left, name, pop);
        } else {
            root->right = insertCity(root->right, name, pop);
        }
    }
    return root;
}

void printCities(City* root, int minPop) {
    if (root == NULL) 
        return;
    printCities(root->left, minPop);
    if (root->population >= minPop) {
        printf("\n  - %-15s | Populacija: %d", root->name, root->population);
    }
    printCities(root->right, minPop);
}

void freeCities(City* root) {
    if (root == NULL) 
        return;
    freeCities(root->left);
    freeCities(root->right);
    free(root);
}

int calculateHash(char* name) {
    int sum = 0;
    int i = 0;
    for (i = 0; i < 5 && name[i] != '\0'; i++) {
        sum += name[i];
    }
    return sum % HASH_SIZE;
}

City* readCitiesFromFile(char* filename) {
    FILE* fp = fopen(filename, "r");
    City* root = NULL;
    char name[MAX_NAME];
    int pop = 0;

    if (!fp)
        return NULL;

    while (fscanf(fp, " %[^,], %d", name, &pop) == 2) {
        root = insertCity(root, name, pop);
    }
    fclose(fp);
    return root;
}

void insertCountrySorted(HashTable* ht, char* countryName, char* fileName) {
    int index = calculateHash(countryName);
    Country* newCountry = (Country*)malloc(sizeof(Country));
    Country** current = &(ht->buckets[index]);

    if (!newCountry) 
        return;

    strcpy(newCountry->name, countryName);
    newCountry->cityRoot = readCitiesFromFile(fileName);
    newCountry->next = NULL;

    while (*current != NULL && strcmp((*current)->name, countryName) < 0) {
        current = &((*current)->next);
    }
    newCountry->next = *current;
    *current = newCountry;
}

void search(HashTable* ht) {
    char target[MAX_NAME];
    int minPop = 0;
    int index = 0;
    Country* curr = NULL;

    printf("\n\n--- PRETRAGA ---");
    printf("\nUnesite ime drzave: ");
    scanf("%s", target);
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &minPop);

    index = calculateHash(target);
    curr = ht->buckets[index];

    while (curr != NULL) {
        if (strcmp(curr->name, target) == 0) {
            printf("\nGradovi u %s s populacijom vecom od %d:", target, minPop);
            printCities(curr->cityRoot, minPop);
            return;
        }
        curr = curr->next;
    }
    printf("\nDrzava '%s' nije pronadjena.", target);
}

void freeHashTable(HashTable* ht) {
    int i = 0;
    for (i = 0; i < HASH_SIZE; i++) {
        Country* curr = ht->buckets[i];
        while (curr != NULL) {
            Country* temp = curr;
            curr = curr->next;
            freeCities(temp->cityRoot);
            free(temp);
        }
        ht->buckets[i] = NULL;
    }
}
