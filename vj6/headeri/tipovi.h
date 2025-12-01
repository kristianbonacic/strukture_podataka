#indef TIPOVI_H
#define TIPOVI_H

typedef struct Item {
	char name[100];
	int quantity;
	float price;
	struct Item* next;
}Item;

typedef struct Receipt {
	char date[11];
	Item* itemsHead;
	Struct Receipt* next;
}; Receipt;

#endif