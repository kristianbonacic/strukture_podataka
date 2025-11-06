#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Poly {
    int coef;
    int exp;
    struct Poly* next;
} Poly;

Poly* newEl(int c, int e) {
    Poly* el = (Poly*)malloc(sizeof(Poly));
    el->coef = c;
    el->exp = e;
    el->next = NULL;
    return el;
}

Poly* insertSorted(Poly* head, int c, int e) {
    if (c == 0) return head;
    Poly* newP = newEl(c, e);
    if (head == NULL || e < head->exp) {
        newP->next = head;
        return newP;
    }
    Poly* prev = head;
    Poly* p = head->next;
    while (p != NULL && p->exp < e) {
        prev = p;
        p = p->next;
    }
    if (p != NULL && p->exp == e) {
        p->coef += c;
        free(newP);
        if (p->coef == 0) {
            prev->next = p->next;
            free(p);
        }
        return head;
    }
    newP->next = prev->next;
    prev->next = newP;
    return head;
}

Poly* readPoly(char* name) {
    FILE* f = fopen(name, "r");
    if (!f) return NULL;
    Poly* head = NULL;
    int c, e;
    while (fscanf(f, "%d %d", &c, &e) == 2)
        head = insertSorted(head, c, e);
    fclose(f);
    return head;
}

Poly* printPoly(Poly* head) {
    if (!head) {
        printf("0\n");
        return head;
    }
    Poly* p = head;
    while (p != NULL) {
        printf("%dx^%d", p->coef, p->exp);
        if (p->next != NULL) printf(" + ");
        p = p->next;
    }
    printf("\n");
    return head;
}

Poly* add(Poly* p1, Poly* p2) {
    Poly* res = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            res = insertSorted(res, p1->coef + p2->coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp < p2->exp) {
            res = insertSorted(res, p1->coef, p1->exp);
            p1 = p1->next;
        }
        else {
            res = insertSorted(res, p2->coef, p2->exp);
            p2 = p2->next;
        }
    }
    while (p1 != NULL) {
        res = insertSorted(res, p1->coef, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        res = insertSorted(res, p2->coef, p2->exp);
        p2 = p2->next;
    }
    return res;
}

// oduzimanje san doda za provježbat malo samostalno

Poly* subtract(Poly* p1, Poly* p2) {
    Poly* res = NULL;
    while (p1 != NULL && p2 != NULL) {
        if (p1->exp == p2->exp) {
            res = insertSorted(res, p1->coef - p2->coef, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exp < p2->exp) {
            res = insertSorted(res, p1->coef, p1->exp);
            p1 = p1->next;
        }
        else {
            res = insertSorted(res, -p2->coef, p2->exp);
            p2 = p2->next;
        }
    }
    while (p1 != NULL) {
        res = insertSorted(res, p1->coef, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        res = insertSorted(res, -p2->coef, p2->exp);
        p2 = p2->next;
    }
    return res;
}

Poly* freePoly(Poly* head) {
    while (head != NULL) {
        Poly* temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}

int main() {
    Poly* P1 = readPoly("poly1.txt");
    Poly* P2 = readPoly("poly2.txt");

    printf("P1(x) = ");
    printPoly(P1);

    printf("P2(x) = ");
    printPoly(P2);

    Poly* Sum = add(P1, P2);
    printf("\nSum: ");
    printPoly(Sum);

    Poly* Diff = subtract(P1, P2);
    printf("Difference: ");
    printPoly(Diff);

    P1 = freePoly(P1);
    P2 = freePoly(P2);
    Sum = freePoly(Sum);
    Diff = freePoly(Diff);
    return 0;
}
