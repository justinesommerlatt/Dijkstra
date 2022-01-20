#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dyntable.h"
#include "test.h"


DTable * newDTable() {
	DTable * newTab = (DTable *) malloc(sizeof(DTable));
	newTab->T = malloc(sizeof(void **));
	newTab->size = 1;
	newTab->used = 0;
	return newTab;
}

/**
 * @brief
 * Dédoubler la taille du tableau dtab
 */
static void scaleUp(DTable *dtab) {
	dtab->T = realloc(dtab->T, sizeof(void**) * dtab->size * 2);
	dtab->size = dtab->size * 2;
}

/**
 * @brief
 * Diviser par 2 la taille du tableau dtab
 */
static void scaleDown(DTable *dtab) {
	dtab->T = realloc(dtab->T, sizeof(void**) * dtab->size / 2);
	dtab->size = dtab->size / 2;
}



void viewDTable(const DTable *dtab, void (*ptrf)(const void*)) {
	int i;
	printf("size = %d\n", dtab->size);
	printf("used = %d\n", dtab->used);
	for (i = 0; i < dtab->used; i++) {
		ptrf(dtab->T[i]);
		printf(" ");
	}
	printf("\n");
}

void DTableInsert(DTable *dtab, void *data) {
	if( dtab->size == dtab->used ){
		scaleUp(dtab);
	}
	dtab->T[dtab->used] = data;
	dtab->used = dtab->used + 1;	
}


void * DTableRemove(DTable *dtab) {
	assert(dtab->used > 0);
	void * elem = dtab->T[dtab->used-1];
	dtab->T[dtab->used] = NULL;
	dtab->used = dtab->used - 1;
	if( dtab->size > (dtab->used * 4)){
		scaleDown(dtab);
	}

	return elem;
}


void DTableSwap(DTable *dtab, int pos1, int pos2) {


	assert(pos1 < dtab->used);
	assert(pos2 < dtab->used);
	void * elmPos1 = dtab->T[pos1];
	dtab->T[pos1] = dtab->T[pos2];
	dtab->T[pos2] = elmPos1;
}

void testStaticSUDyntable(DTable * dtab){
	printf("\n>dtab->size = %d\n", dtab->size);
	scaleUp(dtab);
	printf(">dtab->size = %d apres multiplication\n", dtab->size);
	scaleUp(dtab);
	printf(">dtab->size = %d apres multiplication\n", dtab->size);
	scaleDown(dtab);
	printf(">dtab->size = %d apres division\n", dtab->size);
	scaleDown(dtab);
	printf(">dtab->size = %d apres division\n\n\n", dtab->size);
}
