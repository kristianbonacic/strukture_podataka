#ifndef ALATI_LISTA_H
#define ALATI_LISTA_H
#include "tipovi.h"

Item* createItem(char* name, int quantity, float price);
int insertItemSorted(Item** head, Item* newItem);

Receipt* createReceipt(char* date);
int insertReceiptSorted(Receipt** head, Receipt* newReceipt);

int freeMemory(Receipt* head);


#endif