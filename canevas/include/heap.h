#ifndef _HEAP_
#define _HEAP_
/**
 * @brief
 * Tas minimier générique
 */

/**
 * @brief
 * Un élément du tas contient
 * (+) Une donnée (data)
 * (+) Sa valeur (priorité)
 * (+) Sa position au dictionnaire (à utiliser seulement avec DTHeap)
 */
typedef struct HeapNode {
	int value;
	void *data;
	void *ptr;
} HNode;

/**
 * @brief
 * Construire et initialiser un nouveau noeud d'un tas.
 * Renvoie le nouveau noeud créé.
 */
HNode * newHNode(int value, void * data);

/**
 * Le tas est une structure contenant
 * (+) La structure de données heap qui implémente le tas,
 * (+) Le dictionnaire dict qui pointe vers la position actuelle 
 *     de chaque ville à la structure de données DTHeap
 * 	   (à utiliser seulement avec DTHeap),
 * (+) Les pointeurs des 3 fonctions génériques implémentant les primitives du tas:
 *     (-) HeapInsert
 *     (-) HeapExtractMin
 *     (-) HeapIncreasePriority
 * (+) Le pointeur de la fonction générique qui affiche le tas (viewHeap).
 */
typedef struct Heap {
	void *heap;
	DTable *dict;
	void* (*HeapInsert)(struct Heap * H, int value, void * data);
	HNode* (*HeapExtractMin)(struct Heap * H);
	void (*HeapIncreasePriority)(struct Heap * H, void * ptr, int value);
	void (*viewHeap)(const struct Heap * H, void (*ptrf)());
} Heap;

/***
 * @brief
 * Construire un tas vide en choisissant son implémentation (type) :
 * (0) DynTableHeap
 * (1) CompleteBinaryTreeHeap
 * (2) ListHeap
 */
Heap * newHeap(int type);

/***************************************************
 * DYNAMIC TABLE HEAP
 ***************************************************/

/**
 * @brief
 * Ajouter dans le tas H un élément de donnée data et priorité value.
 */
void * DTHeapInsert(Heap * H, int value, void * data);

/**
 * @brief
 * Extraire du tas H le nœud avec la plus grande priorité.
 */
HNode * DTHeapExtractMin(Heap * H);

/**
 * @brief
 * Dans le tas H, incrémenter la priorité du nœud
 * indiqué par le pointeur position à value.
 */
void DTHeapIncreasePriority(Heap * H, void * position, int value);

/**
 * @brief
 * Afficher les éléments du tas H.
 * Chaque élément est affiché grace au pointeur de fonction ptrF.
 */
void viewDTHeap(const Heap * H, void (*ptrf)());

/***************************************************
 * COMPLETE BINARY TREE HEAP
 ***************************************************/

/**
 * @brief
 * Ajouter dans le tas H un élément de donnée data et priorité value.
 */
void * CBTHeapInsert(Heap * H, int value, void * data);

/**
 * @brief
 * Extraire du tas H le nœud avec la plus grande priorité.
 */
HNode * CBTHeapExtractMin(Heap * H);

/**
 * @brief
 * Dans le tas H, incrémenter la priorité du nœud
 * indiqué par le pointeur position à value.
 */
void CBTHeapIncreasePriority(Heap * H, void * tnode, int value);

/**
 * @brief
 * Afficher les éléments du tas H.
 * Chaque élément est affiché grace au pointeur de fonction ptrF.
 */
void viewCBTHeap(const Heap * H, void (*ptrf)());

/***************************************************
 * ORDERED LIST HEAP
 ***************************************************/

/**
 * @brief
 * Ajouter dans le tas H un élément de donnée data et priorité value.
 */
void * OLHeapInsert(Heap * H, int value, void * data);

/**
 * @brief
 * Extraire du tas H le nœud avec la plus grande priorité.
 */
HNode * OLHeapExtractMin(Heap * H);

/**
 * @brief
 * Dans le tas H, incrémenter la priorité du nœud
 * indiqué par le pointeur position à value.
 */
void OLHeapIncreasePriority(Heap * H, void * lnode, int value);

/**
 * @brief
 * Afficher les éléments du tas H.
 * Chaque élément est affiché grace au pointeur de fonction ptrF.
 */
void viewOLHeap(const Heap * H, void (*ptrf)());

#endif // _HEAP_
