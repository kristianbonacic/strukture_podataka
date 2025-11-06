#define _CRT_SECURE_NO_WARNINGS_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    double value;
    struct Node* next;
} Node;

// dodaj na stog
Node* push(Node* top, double value) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->value = value;
    n->next = top;
    return n;
}

// skini sa stoga
Node* pop(Node* top, double* value) {
    *value = top->value;
    Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

// primijeni operator
double op(double a, double b, char c) {
    if (c == '+') return a + b;
    if (c == '-') return a - b;
    if (c == '*') return a * b;
    if (c == '/') return a / b;
    return 0;
}

// izračunaj postfiks izraz
double eval(char* exp) {
    Node* s = NULL;
    char t[50];
    int i = 0;

    while (sscanf(exp + i, "%s", t) == 1) {
        i += strlen(t) + 1;
        if (isdigit(t[0]) || (t[0] == '-' && isdigit(t[1]))) {
            s = push(s, atof(t));
        } else {
            double b, a;
            s = pop(s, &b);
            s = pop(s, &a);
            s = push(s, op(a, b, t[0]));
        }
    }

    double r;
    s = pop(s, &r);
    return r;
}

int main() {
    FILE* f = fopen("expression.txt", "r");
    if (!f) {
        printf("File error!\n");
        return 1;
    }

    char exp[256];
    fgets(exp, sizeof(exp), f);
    fclose(f);

    printf("Result = %.2lf\n", eval(exp));
    return 0;
}
