#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 128

typedef struct City {
    char name[MAX];
    int population;
    struct City *next;
} City;

typedef struct CountryList {
    char name[MAX];
    City *cities;
    struct CountryList *next;
} CountryList;

typedef struct CountryTree {
    char name[MAX];
    City *cities;
    struct CountryTree *left;
    struct CountryTree *right;
} CountryTree;

City* insertCityList(City *head, char *name, int pop) {
    City *n = malloc(sizeof(City));
    strcpy(n->name, name);
    n->population = pop;
    n->next = NULL;

    if (!head || pop > head->population || (pop == head->population && strcmp(name, head->name) < 0)) {
        n->next = head;
        return n;
    }

    City *cur = head;
    while (cur->next && (cur->next->population > pop ||
          (cur->next->population == pop && strcmp(name, cur->next->name) > 0)))
        cur = cur->next;

    n->next = cur->next;
    cur->next = n;
    return head;
}

CountryList* insertCountryList(CountryList *head, char *name, City *cities) {
    CountryList *n = malloc(sizeof(CountryList));
    strcpy(n->name, name);
    n->cities = cities;
    n->next = NULL;

    if (!head || strcmp(name, head->name) < 0) {
        n->next = head;
        return n;
    }

    CountryList *cur = head;
    while (cur->next && strcmp(name, cur->next->name) > 0)
        cur = cur->next;

    n->next = cur->next;
    cur->next = n;
    return head;
}

CountryTree* insertCountryTree(CountryTree *root, char *name, City *cities) {
    if (!root) {
        CountryTree *n = malloc(sizeof(CountryTree));
        strcpy(n->name, name);
        n->cities = cities;
        n->left = n->right = NULL;
        return n;
    }

    if (strcmp(name, root->name) < 0)
        root->left = insertCountryTree(root->left, name, cities);
    else
        root->right = insertCountryTree(root->right, name, cities);

    return root;
}

City* readCities(char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;

    City *head = NULL;
    char name[MAX];
    int pop;

    while (fscanf(f, " %[^,],%d", name, &pop) == 2)
        head = insertCityList(head, name, pop);

    fclose(f);
    return head;
}

void printCities(City *c) {
    while (c) {
        printf("    %s %d\n", c->name, c->population);
        c = c->next;
    }
}

void printCountryList(CountryList *c) {
    while (c) {
        printf("%s\n", c->name);
        printCities(c->cities);
        c = c->next;
    }
}

void printCountryTree(CountryTree *r) {
    if (!r) return;
    printCountryTree(r->left);
    printf("%s\n", r->name);
    printCities(r->cities);
    printCountryTree(r->right);
}

City* findCitiesList(CountryList *c, char *name) {
    while (c) {
        if (!strcmp(c->name, name))
            return c->cities;
        c = c->next;
    }
    return NULL;
}

City* findCitiesTree(CountryTree *r, char *name) {
    if (!r) return NULL;
    int cmp = strcmp(name, r->name);
    if (cmp == 0) return r->cities;
    if (cmp < 0) return findCitiesTree(r->left, name);

    return findCitiesTree(r->right, name);
}

void searchCities(City *c, int minPop) {
    while (c) {
        if (c->population > minPop)
            printf("    %s %d\n", c->name, c->population);
        c = c->next;
    }
}

int main() {
    FILE *f = fopen("drzave.txt", "r");
    if (!f) 
return 1;

    CountryList *list = NULL;
    CountryTree *tree = NULL;
    char country[MAX], file[MAX];

    while (fscanf(f, "%s %s", country, file) == 2) {
        City *cities = readCities(file);
        list = insertCountryList(list, country, cities);
        tree = insertCountryTree(tree, country, cities);
    }

    fclose(f);

    printf("VEZANA LISTA:\n");
    printCountryList(list);

    printf("\nSTABLO:\n");
    printCountryTree(tree);

    char searchCountry[MAX];
    int minPop;

    printf("\nUnesi drzavu: ");
    scanf("%s", searchCountry);
    printf("Unesi minimalan broj stanovnika: ");
    scanf("%d", &minPop);

    City *c = findCitiesTree(tree, searchCountry);
    if (c)
        searchCities(c, minPop);
    else
        printf("Drzava ne postoji\n");

    return 0;
}
