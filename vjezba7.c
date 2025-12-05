#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_NAME 32

typedef struct Directory* Pos;
typedef struct Directory {
  char name[MAX_NAME];
  Pos subdirectory;
  Pos siblings;
} Directory;

typedef struct StackNode* StackPos;
typedef struct StackNode {
 Pos directory;
 StackPos next;
} StackNode;

typedef struct StackHead {
  StackPos next;
} StackHead;

int Menu(Pos* currentDirectory, StackPos stackHead);
Pos CreateNewDirectory(char* name);
int AddDirectory(Pos parent, Pos newDirectory);
int PrintDirectoryContent(Pos directory);
int ChangeDirectory(Pos* currentDirectory, char* name, StackPos stackHead);
int GoBack(StackPos stackHead, Pos* currentDirectory);
Pos FindDirectory(Pos parent, char* name);
int Push(StackPos stackHead, Pos directory);
Pos Pop(StackPos stackHead);
Pos InitializeRoot(char* name);
int DelTree(Pos root);
int DelStack(StackPos stackHead);

int main() {
 Pos root = InitializeRoot("C:");
 Pos currentDirectory = root;
 StackHead stack = { NULL };
 int status = 0;

  if (root == NULL) {
  return EXIT_FAILURE;
 }

    while (status != 5) {
      status = Menu(&currentDirectory, stack.next);
      if (status == 3 && currentDirectory != root) {
      GoBack(stack.next, &currentDirectory);
    }
  }

    DelTree(root);
    DelStack(stack.next);

    return EXIT_SUCCESS;
}

Pos InitializeRoot(char* name) {
    Pos root = (Pos)malloc(sizeof(Directory));
    if (root == NULL) {
        return NULL;
 }
    strncpy(root->name, name, MAX_NAME - 1);
    root->name[MAX_NAME - 1] = '\0';
    root->subdirectory = NULL;
    root->siblings = NULL;
    return root;
}

int Menu(Pos* currentDirectory, StackPos stackHead) {
  int choice = 0;
  char name[MAX_NAME] = { 0 };
  Pos newDirectory = NULL;

  printf("\nTrenutni direktorij: %s\n", (*currentDirectory)->name);
  printf("Odaberite opciju:\n");
  printf("1 - md (Kreiraj novi direktorij)\n");
  printf("2 - cd dir (Uði u poddirektorij)\n");
  printf("3 - cd.. (Vrati se u nadreðeni direktorij)\n");
  printf("4 - dir (Ispiši sadržaj direktorija)\n");
  printf("5 - Izlaz\n");
  printf("Izbor: ");

    if (scanf("%d", &choice) != 1) {
     while (getchar() != '\n');
     printf("Neispravan unos.\n");
     return 0;
}

    switch (choice) {
     case 1:
      printf("Unesite naziv novog direktorija: ");
       if (scanf("%31s", name) == 1) {
        newDirectory = CreateNewDirectory(name);
         if (newDirectory != NULL) {
          AddDirectory(*currentDirectory, newDirectory);
 }
  else {
   printf("Greška pri alokaciji novog direktorija.\n");
 }
  }
   break;
    case 2:
        printf("Unesite naziv poddirektorija: ");
        if (scanf("%31s", name) == 1) {
            ChangeDirectory(currentDirectory, name, stackHead);
        }
  break;
    case 3:
        if (strcmp((*currentDirectory)->name, "C:") == 0) {
            printf("Veæ ste u korijenskom direktoriju.\n");
            return 0;
        }
        return 3;
    case 4:
        PrintDirectoryContent(*currentDirectory);
        break;
    case 5:
        printf("Izlaz iz programa.\n");
        return 5;
    default:
        printf("Neispravan izbor.\n");
        break;
    }
    return choice;
}

Pos CreateNewDirectory(char* name) {
  Pos newDirectory = (Pos)malloc(sizeof(Directory));
  if (newDirectory == NULL) {
   return NULL;
    }
   strncpy(newDirectory->name, name, MAX_NAME - 1);
   newDirectory->name[MAX_NAME - 1] = '\0';
   newDirectory->subdirectory = NULL;
   newDirectory->siblings = NULL;
   return newDirectory;
}

int AddDirectory(Pos parent, Pos newDirectory) {
    Pos current = parent->subdirectory;

    if (current == NULL) {
        parent->subdirectory = newDirectory;
        return EXIT_SUCCESS;
 }

    if (strcmp(newDirectory->name, current->name) < 0) {
        newDirectory->siblings = current;
        parent->subdirectory = newDirectory;
        return EXIT_SUCCESS;
 }

    while (current->siblings != NULL && strcmp(newDirectory->name, current->siblings->name) > 0) {
        current = current->siblings;
 }

    if (current->siblings != NULL && strcmp(newDirectory->name, current->siblings->name) == 0) {
        printf("Direktorij '%s' veæ postoji.\n", newDirectory->name);
        free(newDirectory);
        return EXIT_FAILURE;
 }

    if (strcmp(newDirectory->name, current->name) == 0) {
        printf("Direktorij '%s' veæ postoji.\n", newDirectory->name);
        free(newDirectory);
        return EXIT_FAILURE;
 }

    newDirectory->siblings = current->siblings;
    current->siblings = newDirectory;
    return EXIT_SUCCESS;
}

int PrintDirectoryContent(Pos directory) {
    Pos current = directory->subdirectory;

    printf("Sadržaj direktorija '%s':\n", directory->name);
    if (current == NULL) {
        printf("  <PRAZNO>\n");
        return EXIT_SUCCESS;
}

    while (current != NULL) {
        printf("  <DIR> %s\n", current->name);
        current = current->siblings;
 }
    return EXIT_SUCCESS;
}

int ChangeDirectory(Pos* currentDirectory, char* name, StackPos stackHead) {
    Pos target = FindDirectory(*currentDirectory, name);

  if (target != NULL) {
     if (Push(stackHead, *currentDirectory) == EXIT_SUCCESS) {
      *currentDirectory = target;
       printf("Uspješno promijenjen direktorij u '%s'.\n", (*currentDirectory)->name);
       return EXIT_SUCCESS;
}
     else {
    printf("Greška pri spremanju nadreðenog direktorija u stog.\n");
    return EXIT_FAILURE;
 }
}
else {
    printf("Direktorij '%s' nije pronaðen.\n", name);
     return EXIT_FAILURE;
 }
}

Pos FindDirectory(Pos parent, char* name) {
  Pos current = parent->subdirectory;
  while (current != NULL && strcmp(current->name, name) != 0) {
   current = current->siblings;
 }
    return current;
}

int Push(StackPos stackHead, Pos directory) {
    StackPos newNode = (StackPos)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        return EXIT_FAILURE;
}
  newNode->directory = directory;
  newNode->next = stackHead->next;
  stackHead->next = newNode;
  return EXIT_SUCCESS;
}

Pos Pop(StackPos stackHead) {
  StackPos temp = NULL;
  Pos directory = NULL;

  if (stackHead->next == NULL) {
   return NULL;
}

 temp = stackHead->next;
 stackHead->next = temp->next;
 directory = temp->directory;
 free(temp);

 return directory;
}

int GoBack(StackPos stackHead, Pos* currentDirectory) {
 Pos parent = Pop(stackHead);

 if (parent != NULL) {
     *currentDirectory = parent;
     printf("Vraæeno u nadreðeni direktorij '%s'.\n", (*currentDirectory)->name);
     return EXIT_SUCCESS;
 }
 else {
  printf("Nema nadreðenog direktorija (veæ ste u rootu).\n");
  return EXIT_FAILURE;
 }
}

int DelTree(Pos root) {
  if (root == NULL) {
  return EXIT_SUCCESS; 
  }

    DelTree(root->subdirectory);
    DelTree(root->siblings);
    free(root);

 return EXIT_SUCCESS;
}

int DelStack(StackPos stackHead) {
  while (Pop(stackHead) != NULL);
  return EXIT_SUCCESS;
}