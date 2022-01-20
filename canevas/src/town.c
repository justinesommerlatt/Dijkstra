#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "list.h"
#include "town.h"
#include "road.h"

struct town * createTown(char * name) {
	struct town * T = calloc(1, sizeof(struct town));

	T->name = name;
	T->alist = newList();

	T->dist = INFTY;
	T->pred = NULL;
	T->ptr = NULL;

	return T;
}

void freeTown(struct town * T) {
	deleteList(T->alist, NULL);
	free(T->name);
	free(T);
}

char * getTownName(struct town * T) {
	return T->name;
}

List * getAList(struct town * T) {
	return T->alist;
}

void viewTown (struct town * T) {
	void (*ptrF)(struct road *);

	ptrF = &viewRoad;
	printf("Town : %s\n", T->name);
	if (T->pred != NULL)
		printf("dist = %d, pred = %s\n", T->dist, T->pred->name);
	else
		printf("dist = %d, pred = NULL\n", T->dist);
	viewList(T->alist, ptrF);
}

void printTownName(struct town * T) {
	printf("%s ", T->name);
}
