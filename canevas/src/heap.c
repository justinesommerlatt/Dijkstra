#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dyntable.h"
#include "test.h"
#include "tree.h"
#include "list.h"
#include "heap.h"
#include "town.h"

HNode * newHNode(int value, void * data) {
	HNode * newNode = (HNode*) malloc(sizeof(HNode));
	newNode->value = value;
	newNode->data = data;
	newNode->ptr = NULL;
	return newNode;
}

// type =
//    0 (DynTableHeap)
//    1 (CompleteBinaryTreeHeap)
//    2 (ListHeap)
Heap * newHeap(int type) {
	assert(type == 0 || type == 1 || type == 2);
	Heap* H = calloc(1, sizeof(Heap));
	H->dict = newDTable();
	switch (type) {
		case 0:
			H->heap = newDTable();
			H->HeapInsert = DTHeapInsert;
			H->HeapExtractMin = DTHeapExtractMin;
			H->HeapIncreasePriority = DTHeapIncreasePriority;
			H->viewHeap = viewDTHeap;
			break;
		case 1:
			H->heap = newCBTree();
			H->HeapInsert = CBTHeapInsert;
			H->HeapExtractMin = CBTHeapExtractMin;
			H->HeapIncreasePriority = CBTHeapIncreasePriority;
			H->viewHeap = viewCBTHeap;
			break;
		case 2:
			H->heap = newList();
			H->HeapInsert = OLHeapInsert;
			H->HeapExtractMin = OLHeapExtractMin;
			H->HeapIncreasePriority = OLHeapIncreasePriority;
			H->viewHeap = viewOLHeap;
			break;
	}
	return H;
}

/**********************************************************************************
 * DYNAMIC TABLE HEAP
 **********************************************************************************/



void* DTHeapInsert(Heap *H, int value, void *data) {
	HNode * hnode = newHNode(value, data);
	hnode->ptr = ((struct town *) data)->ptr;
	DTable * dtab = (DTable*)H->heap;
	DTableInsert(dtab, hnode); // On insert l'element a la fin du tableau
	int i = dtab->used;
	if(dtab->used)i-=1; // On donne l'indice du dernier element
	
	while(i != 0 && value < ((HNode*)dtab->T[(i-1)/2])->value){ // Si l'element a une priorite inferieur a celle de son pere on swap leur position
		DTableSwap(dtab, (i-1)/2, i);
		DTableSwap(H->dict, (int)((HNode*)dtab->T[(i-1)/2])->ptr, (int)((HNode*)dtab->T[i])->ptr);
		i = (i-1)/2;
	}
	return i;
}

HNode * DTHeapExtractMin(Heap* H) {
	DTable * dtab = (DTable*)H->heap;
	HNode * hnode = NULL;


	int indice = 0;	//L\'indice de l'element à replacer

	if(dtab->used > 0 && dtab->used == 1){// Si il n'y a qu'un element on le remove directement 
		hnode = DTableRemove(dtab);
	}else{
		DTableSwap(dtab, 0, dtab->used - 1);	//swap le premier et le dernier
		DTableSwap(H->dict, (int)((HNode*)dtab->T[0])->ptr, (int)((HNode*)dtab->T[dtab->used-1])->ptr);
		hnode = DTableRemove(dtab);		//tant qu'il existe un fils gauche
		while(dtab->used > (2*indice)+1 && (((HNode*)dtab->T[(2*indice)+1])->value <= ((HNode*)dtab->T[indice])->value || ((HNode*)dtab->T[(2*indice)+2])->value < ((HNode*)dtab->T[indice])->value )){
							//Si le fils gauche ou le fils droit
							//a une priorite superieure a celle 
							//du pere
			if((2*indice)+2 < dtab->used){
				
				if( ((HNode*)dtab->T[(2*indice)+1])->value <= ((HNode*)dtab->T[indice])->value || ((HNode*)dtab->T[(2*indice)+2])->value < ((HNode*)dtab->T[indice])->value ){
					
					//Si le fils gauche a une priorite plus haute que celle du fils droit
					if( ((HNode*)dtab->T[(2*indice)+1])->value <= ((HNode*)dtab->T[(2*indice)+2])->value ){
						DTableSwap(dtab, indice, (2*indice)+1);
						DTableSwap(H->dict, (int)((HNode*)dtab->T[indice])->ptr, (int)((HNode*)dtab->T[(2*indice)+1])->ptr);
						indice = (2*indice)+1;
					//sinon le fils droit a une priorite plus haute
					}else{
						DTableSwap(dtab, indice, (2*indice)+2);				
						DTableSwap(H->dict, (int)((HNode*)dtab->T[indice])->ptr, (int)((HNode*)dtab->T[(2*indice)+2])->ptr);	
						indice = (2*indice)+2;
					}
				}
			}else{
				DTableSwap(dtab, indice, (2*indice)+1);
				DTableSwap(H->dict, (int)((HNode*)dtab->T[indice])->ptr, (int)((HNode*)dtab->T[(2*indice)+1])->ptr);
				indice = (2*indice)+1;
			}
		}
	}
	return hnode;
}

void DTHeapIncreasePriority(Heap* H, void *position, int value) {

	int pos = H->dict->T[(int)position];		//pos doit etre la position dans le tas

	DTable * dict = H->dict;
	DTable * dtab = (DTable *)H->heap;
	((HNode*)dtab->T[pos])->value = value;

	while(((HNode*)dtab->T[(pos-1)/2])->value > value){
		DTableSwap(dtab, pos, (pos-1)/2);
		DTableSwap(dict, ((HNode*)dtab->T[pos])->ptr, ((HNode*)dtab->T[(pos-1)/2])->ptr);

		pos = dict->T[(int)((HNode*)dtab->T[(pos-1)/2])->ptr];
	}
}


void viewDTHeap(const Heap* H, void (*ptrf)(const void*)){
	viewDTable(H->heap, ptrf);
}

/**********************************************************************************
 * COMPLETE BINARY TREE HEAP
 **********************************************************************************/

void* CBTHeapInsert(Heap *H, int value, void *data) {
	HNode* hnode = newHNode(value, data);
	TNode * iterator;
	CBTree * T = ((CBTree*)H->heap);
	CBTreeInsert(T, hnode); // On insert l'element dans l'arbre
	iterator = T->last;
	while(iterator->parent && ((HNode*)iterator->parent->data)->value > value){ // Tant que sa priorite est inferieur a celle de son pere on swap
		CBTreeSwap(T, iterator->parent, iterator);
	}
	return iterator;
}

HNode * CBTHeapExtractMin(Heap *H) {
	HNode * hnode;
	TNode * iterator;
	CBTree * T = (CBTree*)H->heap;
	CBTreeSwapRootLast(T); // On swap le root avec le last 
	hnode = (HNode*)((TNode*)CBTreeRemove(T))->data; // on retire ensuite le last
	if(T->root != T->last){ // Si il y a plus que 1 element on swap le root jusqu\'a ce qu\'il retrouve sa place dans l'arbre par rapport a sa priorité 
		iterator = T->root;
		while(iterator->left){
			if(iterator->right){	
				if(((HNode*)iterator->right->data)->value >= ((HNode*)iterator->left->data)->value){

					if(((HNode*)iterator->left->data)->value <= ((HNode*)iterator->data)->value){
						CBTreeSwap(T, iterator, iterator->left);
					}
					else{
						break;
					}
				}else{
	
					if(((HNode*)iterator->right->data)->value <= ((HNode*)iterator->data)->value){
						CBTreeSwap(T, iterator, iterator->right);
					}
					else{
						break;
					}
				}
			}else{
				if (  ((HNode*)iterator->left->data)->value >  ((HNode*)iterator->data)->value){
					break;					
				}				
				else{
					CBTreeSwap(T, iterator, iterator->left);
				}
			}
		}
	}
	return hnode;
}

void CBTHeapIncreasePriority(Heap *H, void *tnode, int value) {
	CBTree * T = ((CBTree*)H->heap);
	((HNode*)((TNode*)tnode)->data)->value = value; // On change la priorite de l'element souhaite
		
	while(((TNode*)tnode)->parent && ((HNode*)((TNode*)tnode)->parent->data)->value > ((HNode*)((TNode*)tnode)->data)->value){ // Tant que sa priorite est inferieur a celle de son pere on swap
		CBTreeSwap(T, ((TNode*)tnode)->parent, ((TNode*)tnode));
	}
}

void viewCBTHeap(const Heap *H, void (*ptrf)(const void*)) {
	viewCBTree(((CBTree*)H->heap), ptrf, 0); 
}

/**********************************************************************************
 * ORDERED-LIST HEAP
 **********************************************************************************/

void* OLHeapInsert(Heap *H, int value, void* data) {
	HNode * hnode = newHNode(value, data);
	LNode * iterator = ((List *)H->heap)->head;
	while(iterator){ // On cherche l'element qui se trouvera juste apres l'element insere
		if(((HNode *)iterator->data)->value > value){
			break;
		}else{
			iterator= iterator->suc;
		}
	}
	if(iterator == ((List *)H->heap)->head){// Si cet element est egal a la tete on insert donc notre element en debut de liste 
		listInsertFirst(H->heap, hnode);
		iterator = ((List *)H->heap)->head;
	}else if(iterator == NULL){ // Sinon si l'element que l'on insert a la plus grande priorité de toute la liste on l'insert a la fin
		listInsertLast(H->heap, hnode);
		iterator = ((List *)H->heap)->tail;
       	}else{// Sinon on insert notre element juste apres l'iterator
		listInsertAfter(H->heap, hnode, iterator->pred);
		iterator = iterator->pred;
	}
	return iterator;
}

HNode * OLHeapExtractMin(Heap *H) {
	LNode * first = listRemoveFirst(((List*)H->heap)); 
	return ((HNode*)first->data);
}

void OLHeapIncreasePriority(Heap *H, void* lnode, int value) {

	assert(((List*)H->heap)->head);
	((HNode*)((LNode*)lnode)->data)->value = value;// On change la priorité de l'element souhaite
	// Sinon on parcours notre liste et on swap tant que notre element a une priorite plus petite que son predecesseur
	while( lnode != ((List*)H->heap)->head && value < ((HNode*)((LNode*)lnode)->pred->data)->value ){
		listSwap( (List*)H->heap,((LNode*)lnode)->pred, lnode);
	}

}


void viewOLHeap(const Heap *H, void (*ptrf)()) {
	assert(((List *)H->heap)->head);
	LNode * iterator = ((List * )H->heap)->head;
	while(iterator){
		viewHNode((HNode*)iterator->data, ptrf);
		printf("\n");
		iterator = iterator->suc;
	}	
}

