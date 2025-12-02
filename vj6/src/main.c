#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#include "tipovi.h"
#include "alati_lista.h"
#include "alati_datoteka.h"
#include "logika_aplikacije.h"

int main() {

	Receipt* receiptList = NULL;

	printf("---Program za pracenje racuna ---\n");

		if (initializeData("racuni.txt", &receiptList) != EXIT_SUCCESS) {
			return EXIT_FAILURE;
	}
	printf("Podaci su uspjesno ucitai i sortirani\n");

	runUserQuery(receiptList);

	freeMemory(receiptList);

   printf("Sva alocirana memorija je oslobodena.\n");

   return EXIT_SUCCESS;

}
