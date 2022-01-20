#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "dyntable.h"
#include "heap.h"

List * newList() {
	List * L = calloc(1, sizeof(List));
	return L;
}

void deleteList(List * L, void (*ptrF)()) {
	LNode * iterator = L->head;

	if (ptrF == NULL) {
		while (iterator) {
			LNode * current = iterator;

			iterator = iterator->suc;
			free(current);
		}
	} else {
		while (iterator) {
			LNode * current = iterator;

			(*ptrF)(&current->data);
			free(current);
		}
	}
	L->head = NULL;
	L->tail = NULL;
	L->numelm = 0;
}

void viewList(const List * L, void (*ptrF)()) {
	if(!L->head){
		printf("la liste est vide\n");
	}else{
		printf("nb of nodes = %d\n", L->numelm);
		for(LNode * iterator = L->head; iterator; iterator = iterator->suc) {
			(*ptrF)(iterator->data);
			printf(" ");
		}
		printf("\n");
	}
}

void listInsertFirst(List * L, void * data) {
	LNode * E = calloc(1, sizeof(LNode));

	E->data = data;
	E->suc = L->head;

	if(L->head == NULL){
		L->tail = E;
	}else{
		L->head->pred = E;
	}
	L->head = E;
	L->numelm += 1;
}

void listInsertLast(List * L, void * data) {
	LNode * E = calloc(1, sizeof(LNode));

	E->data = data;
	E->pred = L->tail;

	if(L->tail == NULL){
		L->head = E;
	}else{
		L->tail->suc = E;
	}
	L->tail = E;
	L->numelm += 1;
}

void listInsertAfter(List * L, void * data, LNode * ptrelm) {
	LNode * E = calloc(1, sizeof(LNode));

	E->data = data;
	E->pred = ptrelm;

	if(ptrelm == L->tail)
		L->tail = E;
	else
		ptrelm->suc->pred = E;
	E->suc = ptrelm->suc;
	ptrelm->suc = E;
	L->numelm += 1;
}

/*Arthur
* remove la tete de la liste 
*/
LNode* listRemoveFirst(List * L) { 
	assert(L->head);
	LNode * CopieTete = L->head;
	
	if( L->numelm == 1){
		L->head = NULL;
		L->tail = NULL;
	}else if(L->numelm == 2){
		L->head = L->tail;
		L->tail->pred = NULL;
		CopieTete->suc=NULL;
	}else{
		L->head = L->head->suc;
		L->head->pred=NULL;
		CopieTete->suc = NULL;
	}
	L->numelm = L->numelm - 1;
	return CopieTete;
}

/*Fonction faite par Justine SOMMERLATT 
 *Retire la queue de la liste sans supprimer la donnée 
 *@CopieQueue : correspond à la queue initiale de la liste dénuée du prédécesseur
 */
LNode* listRemoveLast(List * L) {
	assert(L->head);// pour s'assurer que la liste n'est pas vide
	LNode * CopieQueue = L->tail;
	
	if( L->numelm == 1){
		L->head = NULL;
		L->tail = NULL;
	}else if(L->numelm == 2){
		L->tail = L->head;
		L->head->suc = NULL;
		CopieQueue->pred=NULL;
	}else{
		L->tail = L->tail->pred;
		L->tail->suc=NULL;
		CopieQueue->pred = NULL;
	}	
	L->numelm = L->numelm - 1;
	return CopieQueue;
}

/**
 * Gaetan
 * Retire un element dans la liste et le renvoie
 */
LNode* listRemoveNode(List * L, LNode * node) {
	LNode * iterator = L->head;
	do{
		if(iterator == node){
			break;
		}
		else{
			iterator = iterator->suc;
		}
	}while(iterator);
	


	if(iterator == L->head)
	{
		listRemoveFirst(L);
	}
	else if(iterator == L->tail)
	{
		listRemoveLast(L);
	}
	else
	{
		iterator->suc->pred = iterator->pred;
		iterator->pred->suc = iterator->suc;
		iterator->suc = NULL;
		iterator->pred = NULL;
		L->numelm -= 1;
	}
	return iterator;
}

/**
 * Echange de place deux elements d'une liste qui sont respectivement cote a cote
 * ne retourne rien
 * */
void listSwap(List * L, LNode * left, LNode *right) {
	assert(left->suc == right && left == right->pred);
	if(left->pred){
		left->pred->suc = right;
	}else{
		L->head = right;
	}
	if(right->suc){
		right->suc->pred = left;
	}else{
		L->tail = left;
	}
	left->suc = right->suc;
	right->pred = left->pred;
	left->pred = right;
	right->suc = left;
}

