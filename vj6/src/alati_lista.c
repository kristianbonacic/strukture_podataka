#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "alati_lista.h"
#include "tipovi.h"

Item* createItem(char* name, int quantity, float price) {
	Item* newItem = (Item*)malloc(sizeof(Item));
	if (!newItem)
		return NULL;


	strcpy(newItem->name, name);
	newItem->quantity = quantity;
	newItem->price = price;
	newItem->next = NULL;
	return newItem;

}

int insertItemSorted(Item** head, Item* newItem) {
	if (!newItem)
		return EXIT_FAILURE;


if (*head == NULL || strcmp(newItem->name, (*head)->name) < 0) {
	newItem->next = *head;
	*head = newItem;
}
else {
	Item* current = *head;
	while (current->next && strcmp(current->next->name, newItem->name) < 0)
		current = current->next;
		newItem->next = current->next;
		current->next = newItem;
	}
	return EXIT_SUCCESS;
}
Receipt* createReceipt(char* date) {
	Receipt* newReceipt = (Receipt*)malloc(sizeof(Receipt));
	if (!newReceipt)
		return NULL;

	strcpy(newReceipt->date, date);
	newReceipt->itemsHead = NULL;
	newReceipt->next = NULL;
	return newReceipt;
}

int insertReceiptSorted(Receipt** head, Receipt* newReceipt) {
	if (!newReceipt)
		return EXIT_FAILURE;

	if (*head == NULL || strcmp(newReceipt->date, (*head)->date) < 0) {
		newReceipt->next = *head;
		*head = newReceipt;
	}
	else {
		Receipt* current = *head;
		while (current->next && strcmp(current->next->date, newReceipt->date) < 0)
			current = current->next;
		newReceipt->next = current->next;
		current->next = newReceipt;
	}
	return EXIT_SUCCESS;
}

int freeMemory(Receipt* head) {
	while (head) {
		Receipt* tempReceipt = head;
		head = head->next;

		Item* item = tempReceipt->itemsHead;
		while (item) {
			Item* tempItem = item;
			item = item->next;
			free(tempItem);

		}
		free(tempReceipt);
	}

	return EXIT_SUCCESS;
}
