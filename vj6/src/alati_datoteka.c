#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "alati_datoteka.h"
#include "alati_lista.h"
#include "tipovi.h"

int initializeData(char* masterFile, Receipt** receiptList) {
	FILE* fp = fopen(masterFile, "r");

	if (!fp) {
		fprintf(stderr, "GRESKA: Nismo uspjeli otvoriti master datoteku %s.\n", masterFile);
		return EXIT_FAILURE;
	}
	char fileName[256];
	while (fscanf(fp, "%s", fileName) == 1) {
		FILE* individualFile = fopen(fileName, "r");
		if (individualFile) {
			char dateBuffer[11];
			if (fscanf(individualFile, "%s", dateBuffer) == 1) {
				Receipt* receipt = createReceipt(dateBuffer);
				char nameBuffer[100];
				int quantity;
				float price;

				while (fscanf(individualFile, " %[^,], %d, %f", nameBuffer, &quantity, &price) == 3) {
					Item* item = createItem(nameBuffer, quantity, price);
					insertItemSorted(&(receipt->itemsHead), item);
				}

				insertReceiptSorted(receiptList, receipt);
			}
			fclose(individualFile);
		}
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
