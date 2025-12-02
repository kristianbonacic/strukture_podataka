#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logika_aplikacije.h"
#include "tipovi.h"

int runUserQuery(Receipt* head) {
	if (!head) {
		printf("Nema podataka.\n");
		return EXIT_FAILURE;
	}
	char targetItem[100], dateFrom[11], dateTo[11];
	int totalQuantity = 0;
	float totalSpent = 0.0f;

	printf("\n--- UPIT KORISNIKA ---\n");
	printf("Unesite naziv artikla: ");
	scanf(" %[^\n]", targetItem);
	printf("Unesite pocetni datum (YYYY-MM-DD): "); 
	scanf("%s", dateFrom);
	printf("Unesite zavrsni datum (YYYY-MM-DD): "); 
	scanf("%s", dateTo);

	Receipt* currentReceipt = head;
	while (currentReceipt) {
 if (strcmp(currentReceipt->date, dateFrom) >= 0 && strcmp(currentReceipt->date, dateTo) <= 0) {
	 
	 Item* currentItem = currentReceipt->itemsHead;
	 while (currentItem) {
		 if (strcmp(currentItem->name, targetItem) == 0) {
			 totalQuantity += currentItem->quantity;
			 totalSpent += (currentItem->quantity * currentItem->price);
		 }
		 currentItem = currentItem->next;
	 }
 }
 currentReceipt = currentReceipt->next;
	}
	printf("\n--- REZULTAT ZA ARTIKL '%s' (%s do %s) ---\n", targetItem, dateFrom, dateTo);
	if (totalQuantity > 0) {
		printf(">> Ukupna  kolicina: %d komada\n", totalQuantity);
		printf(">> Ukupno potroseno novaca: %.2f EUR\n", totalSpent);
	}
	else {
		printf(">> Taj artikl nije pronaden u zadanom vremenskom periodu.\n");
	}

	return EXIT_SUCCESS;
}