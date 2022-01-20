#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "list.h"
#include "tree.h"
#include "dyntable.h"
#include "heap.h"
#include "town.h"
#define NBNODE 6
#define NBTAB 8
#define NBLIST 6


void viewHNodeT(const void *node) {
	HNode* hnode =(HNode*)node;
	struct town* town =(struct town * )hnode->data;
	printf("(%d, %s) %d\n", hnode->value, getTownName(town),(int)hnode->ptr);
}

void printIntDict(const void * data){
	int * ptr = data;
	printf(" >%d\n", (int)ptr);

}

void printIntHNode(const void * data){
	int * i = (int*) ((HNode*)data)->data;
	printf("\tprio : %d ", ((HNode*)data)->value);
	printf("\tdata :%d\n", *i);
}

void printInt(const void * data){
	int * i = (int*) data;
	printf("%d", *i);
}
void printPrioData(Heap * H){
	printf("\n");
	LNode * iterator = ((List*)H->heap)->head;
	while(iterator){
		printf("prio : %d  ", ((HNode*)iterator->data)->value);
		printf("data : ");
		printInt(((HNode*)iterator->data)->data);
		printf("\n");
		iterator = iterator->suc;
	}
}

void test_list() {
	
	int i = 0;
	int * ptInt;
	int nbNodeTree = NBNODE;
	int nbTabElem = NBTAB;
	int nbListElem = NBLIST;
	int * valNode[nbNodeTree];
	int * valTab[nbTabElem];
		printf("la\n");
	int * valList[nbListElem];
	

	for(i = 0; i < nbNodeTree; i++){
		ptInt = malloc(sizeof(int));
		*ptInt = i+1;
		valNode[i] = ptInt;
	}

	for(i = 0; i < nbTabElem; i++){
		ptInt = malloc(sizeof(int));
		*ptInt = i+1;
		valTab[i] = ptInt;
	}

	for(i = 0; i < nbListElem; i++){
		ptInt = malloc(sizeof(int));
		*ptInt = i+1;
		valList[i] = ptInt;
	}

	printf("\n\t\t****Test fonction list****\n\n");

	List * L = newList();

	for(i = 0; i < nbListElem; i++){
		listInsertLast(L, valList[i]);
	}


	if(nbListElem > 2){
		printf("\n\t>test Swap\n\n");
		viewList(L, &printInt);
		
		listSwap(L, L->head, L->head->suc);
		viewList(L, &printInt);
		
		listSwap(L, L->head, L->head->suc);
	}

	printf("\n\t>test remove\n\n");
	viewList(L, &printInt);
	LNode * valSup = listRemoveNode(L, L->head->suc);
	viewList(L, &printInt);
	
	printf("valSup = ");
	printInt(valSup->data);
	printf("\n");
	
	printf("\n\n\t\t****Test fonction tree****\n\n");
	
	
	printf("\nTest CBTreeInsert\n");
	CBTree * tree = newCBTree();
	for(i = 0; i < nbNodeTree; i++){
		CBTreeInsert(tree, (void *) valNode[i]);		
	}	
	viewCBTree(tree, &printInt, 0);	

	printf("\nTest CBTreeRemove\n");
	TNode * node = CBTreeRemove(tree);
	viewCBTree(tree,&printInt, 0);
	printf("node remove = ");
	printInt(node->data);
	printf("\n");
	printf("\nTest Swap\n");
	CBTreeSwap(tree, tree->root->left, tree->root->left->right);
	viewCBTree(tree,&printInt, 0);

	printf("\ntest swap root-last\n");
	printf("root :");
	printInt(tree->root->data);
	printf(" last :");
	printInt(tree->last->data);
	CBTreeSwapRootLast(tree);
	printf("\n");
	viewCBTree(tree,&printInt,0);
	printf("\ntest swap root-last\n");
	printf("root :");
	printInt(tree->root->data);
	printf(" last :");
	printInt(tree->last->data);
	printf("\n");
	CBTreeSwapRootLast(tree);
	viewCBTree(tree,&printInt,0);




	printf("\n\n\t\t****Test fonction dyntable****\n\n");


	DTable * dtab = newDTable();
	testStaticSUDyntable(dtab);
	
	for(i = 0; i < nbTabElem; i++){
		DTableInsert(dtab, valTab[i]); 
	}

	viewDTable(dtab, &printInt);
	DTableRemove(dtab);
	viewDTable(dtab, &printInt);
	
	DTableSwap(dtab, 0, 4);
	viewDTable(dtab, &printInt);
	



	printf("\n\n\t\t****Test tas minimier LO****\n\n");

	Heap * H = newHeap(2);
		
	for(i = 0; i < nbListElem; i++){
		H->HeapInsert(H, i+1, valList[i]); 
	}
	
	
	viewOLHeap(H, &printInt);
	
	printf("hNode retire :\n");
	HNode * hNode = OLHeapExtractMin(H);
	printIntHNode(hNode);
	printf("\n\nafter remove\n\n");
	viewOLHeap(H, &printInt);
	printf("prio removed data : %d\n", hNode->value);	
	
	printf("\n\nTest IncreasePriorite\n\n");
	OLHeapIncreasePriority(H, ((List*)H->heap)->head, 1);

	viewOLHeap(H, &printInt);
		
	
	
	printf("\n\n\t\t****Test tas minimier CBT****\n\n");
	

	H = newHeap(1);

	for(i = 0; i < nbNodeTree; i++){
		H->HeapInsert(H, i+10, valNode[i]);
	}
	
	printf("Insert :\n");
	viewCBTHeap(H, &printIntHNode);
	

	printf("ExtractMin :\n");
	CBTHeapExtractMin(H);
	
	viewCBTHeap(H, &printIntHNode);
	
	printf("Increase :\n");
	CBTHeapIncreasePriority(H,((CBTree*)H->heap)->last, 11);
	
	H->viewHeap(H, &printIntHNode);



	printf("\n\n\t\t****Test tas minimier DT****\n\n");


	H = newHeap(0);
	
	for(i = 0; i < nbTabElem; i++){
		H->HeapInsert(H, i+10, valTab[nbTabElem - i - 1]);
	}
	
	printf("Insert :\n");
	H->viewHeap(H, &printIntHNode);
	
	printf("ExtractMin :\n");
	DTHeapExtractMin(H);	
	
	H->viewHeap(H, &printIntHNode);
	
	int num = 3;
	
	printf("Increase :\n");
	DTHeapIncreasePriority(H, (void*) &num, 2);
	
	H->viewHeap(H, &printIntHNode);
}
