#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dyntable.h"
#include "heap.h"
#include "tree.h"
#include "test.h"
#include <math.h> 



TNode * newTNode(void* data) {
	TNode * newNode = (TNode *) malloc(sizeof(TNode));     		  // allocation  de la mémoire pour un nouveau noeud
	if(!newNode){                                          		  // l'allocation mémoire s'est mal effectuée, on sort de la fonction
		printf("erreur lors de l'allocation memoire");
		exit(2);			
	}
	newNode->parent = NULL;					          // on initialise le père et les deux fils du nouveau noeud à NULL car
	newNode->left = NULL;					          // on ne les connait encore pas 
	newNode->right = NULL;					
	newNode->data = data;				 	  	  // on donne au noeud la valeur d'entrée data 
	return newNode;							  // on retourne le noeud que l'on vient de créer 
}


CBTree * newCBTree() {
	CBTree * newTree = (CBTree *) malloc(sizeof(CBTree));		  // allocation de la mémoire pour un nouvel arbre
	if(!newTree){							  // l'allocation mémoire s'est mal effectuée, on sort de la fonction
		printf("erreur lors de l'allocation memoire");
		exit(3);
	}
	newTree->root = NULL;						  // on initialise la racine et le dernier élément de l'arbre à NULL 
	newTree->last = NULL;						  // ainsi que le nombre d'élements à 0, l'arbre est donc vide
	newTree->numelm = 0;
	return newTree;							  // on retourne l'arbre vide que l'on vient de créer
}

static void preorder(TNode *node, void (*ptrF)(const void*)) {		  
	if (node != NULL) {
		ptrF(node->data);
		printf(" ");
		preorder(node->left, ptrF);
		preorder(node->right, ptrF);
	}
}

static void inorder(TNode *node, void (*ptrF)(const void*)) {
	if (node != NULL) {
		inorder(node->left, ptrF);
		ptrF(node->data);
		printf(" ");
		inorder(node->right, ptrF);
	}
}

static void postorder(TNode *node, void (*ptrF)(const void*)) {
	if (node != NULL) {
		postorder(node->left, ptrF);
		postorder(node->right, ptrF);
		ptrF(node->data);
		printf(" ");
	}
}

// order = 0 (preorder), 1 (postorder), 2 (inorder)
void viewCBTree(const CBTree* tree, void (*ptrF)(const void*), int order) {
	assert(order == 0 || order == 1 || order == 2);
	printf("nb of nodes = %d\n", tree->numelm);
	switch (order) {
		case 0:
			preorder(tree->root, ptrF);
			break;
		case 1:
			postorder(tree->root, ptrF);
			break;
		case 2:
			inorder(tree->root, ptrF);
		break;
	}
	printf("\n");
}

/**
 * Gaetan
 * Fonction rajoutee
 * Renvoie true si la node est un fils gauche
 * sinon renvoie false
 * NE PAS UTILISER SUR UN ARBRE A UN ELEMENT
 * OU VIDE
 */
int isLeftChild(TNode * child){
	return child->parent->left == child;
}

/**
 * Gaetan
 * Fonction rajoutee
 * @param numelm Le nombre d'element d'un arbre
 * Renvoie faux si l'arbre est saturee, sinon renvoie
 * le nombre de noeud manquant pour avoir un arbre 
 * sature
 */
int isNotSaturated(int numelm){
	int nbStage = 0;	//nombre d'etage
	int i = 0;		//represente le nombre
				//d'element exacte pour avoir un
				//arbre sature	

	do{
		i = i + pow(2,nbStage);
		nbStage = nbStage + 1;
	}while(i < numelm);
	return i - numelm;
}

/**
 * Gaetan
 * Fonction rajoutee
 * @numelm Le nombre d'element d'un arbre
 * Rôle : 
 * Renvoie le nombre d'etage d'un arbre
 */
int countNbStage(int numelm){
	int nbStage = 0;	//nombre d'etages
	int i = 0;		//represente le nombre
				//d'elements  exact pour avoir un
				//arbre saturé	

	while(i < numelm){
		i = i + pow(2,nbStage);
		nbStage = nbStage + 1;
	}
	return nbStage-1;
}

/**
 * Gaetan
 * Fonction rajoutee
 * @tree un arbre où l'on doit rajouter un feuille
 * mais garder le caractere complet
 * @node la node a ajouter a l'arbre
 * Rôle : 
 * ajoute la node a la fin de l'arbre et conserve son
 * caractere complet
 */
void insertAfterLast(CBTree * tree, TNode * node){
	TNode * iterator = tree->root;
	int nbLastLeaf;	//numero de la derniere feuille du dernier etage
	int nbStage;
	
	nbStage = countNbStage(tree->numelm);	//Je stocke le nombre d'etages de tree
	nbStage = pow(2, nbStage);	//Je transforme le nombre d'etages en nombre
					//de feuilles d'un arbre saturé de taille nbStage
	nbLastLeaf = isNotSaturated(tree->numelm);	//nbLastLeaf = feuille manquante
	nbLastLeaf = nbStage - nbLastLeaf;	//nbLastLeaf = numero de la derniere feuille en trop
	nbLastLeaf = nbLastLeaf + 1;	//nbLastLeaf = numero de la feuille qu'on veut rajouter sur la derniere ligne

	do{
		if(nbLastLeaf > (nbStage/2)){	//nbStage est toujours pair
			nbLastLeaf = nbLastLeaf - (nbStage/2);	//On elimine les feuilles 
								//inateignables qui sont situées 
								//sur la partie droite de notre 
								//arbre

			nbStage = nbStage/2;	//On va descendre d'un etage donc on divise par
						//2 le nombre de feuilles du dernier etage
			
			iterator = iterator->right;						
		}else{
			nbStage = nbStage/2;
			iterator = iterator->left;
		}
		
	}while(iterator->left);		
	node->parent = iterator;
	iterator->left = node;
}


/**
 *Gaetan
 * @tree un arbre binaire complet dans lequel on souhaite ajouter un noeud
 * @data valeur de l'élément que l'on souhaite ranger dans l'arbre 
 * Rôle : 
 * Range un element dans un arbre en derniere position
 */
void CBTreeInsert(CBTree* tree, void* data) {
	TNode * newNode = newTNode(data);

	//1er cas d'arret : l'arbre est vide
	if(!tree->root){					// si l'arbre est vide car il n'a pas de racine 
		tree->root = newNode;				// la racine et le dernier élément prennent la valeur du noeud a insérer car il n'y a
		tree->last = newNode;				// qu\'un seul noeud à présent dans l'arbre (celui que l'on a ajouté) 
	//2e cas d'arret :  l'arbre n'est 
	//compose que d'un element
	}else if(tree->root == tree->last){ 			// sinon si l'arbre ne contient qu'un élément car sa racine est également son dernier élément
		tree->root->left = newNode;			// on ajoute le nouveau noeud a la suite de la racine c'est a dire le fils gauche de la racine
		newNode->parent = tree->root;

	}else if(isLeftChild(tree->last)){			// sinon si le dernier noeud  de l'arbre est un fils gauche 
		tree->last->parent->right = newNode;		// le nouveau noeud sera donc le fils droit partageant le même pere avec le dernier fils gauche 
		newNode->parent = tree->last->parent;

	}else if(!isNotSaturated(tree->numelm)){		// sinon si l'arbre est saturé
		TNode * iterator = tree->root;			// on utilise un itérateur qui prend la valeur de la racine
		while(iterator->left){				// tant que le noeud associé à l'itérateur a un fils gauche, l'itérateur
			iterator = iterator->left;		// prend la valeur de ce fils gauche
		}
		iterator->left = newNode;			// l'itérateur n'a plus de fils gauche et comme on sait que l'arbre est saturé, 
		newNode->parent = iterator;			// on insère le nouveau noeud au fils de l'itérateur qui devient son père

	}else{							// sinon on insère le nouveau noeud à la suite du dernier noeud de l'arbre
		insertAfterLast(tree, newNode);
	}

	tree->last = newNode;					// le dernier élément de l'arbre est donc le nouveau noeud que l'on y a ajouté
	tree->numelm += 1;					// on incrémente d'1 le nombre d'éléments de l'arbre
}

/*Fonction rajoutee
 *@param tree l'arbre dans lequel on travail
 *role
 *remove le last dans le cas ou le last est un fils gauche au "milieu" de l'arbre
 renvoie la node retiree
 */
TNode * removeLeftChild(CBTree* tree){
	int nbStage = countNbStage(tree->numelm); // Nombre d'etage dans l'arbre
	int indiceNextLast = pow(2,countNbStage(tree->numelm))-isNotSaturated(tree->numelm) - 1; // Indice du futur last
	int nbNodeLastStage = pow(2, countNbStage(tree->numelm)); // Nombre de node possible au dernier etage de notre arbre
	TNode * nodeRemoved = tree->last;
	TNode * iterator = tree->root;
	while(iterator->left){ // On fait une recherche dicotomique dans notre arbre pour chercher la position de notre futur last
		if(indiceNextLast <= nbNodeLastStage / 2){
			iterator = iterator->left;
		}
		else{
			iterator = iterator->right;
			indiceNextLast = indiceNextLast - (nbNodeLastStage/2);
		}
		nbNodeLastStage = nbNodeLastStage / 2;
	}
	tree->last = iterator;
	nodeRemoved->parent->left = NULL;
	nodeRemoved->parent = NULL;
	return nodeRemoved;

}


/*Arthur
 *Supprimer le last d'un arbre binaire complet
 *Renvoie le noeud supprimé
 */
void * CBTreeRemove(CBTree* tree) {
	assert(tree->last && tree->root);
	TNode * nodeRemoved;
	TNode * iterator;
	if(tree->root == tree->last){ // Si il y a qu'un seul element
		nodeRemoved = tree->root;
		tree->root = NULL;
		tree->last = NULL;
	}
	else if(!isLeftChild(tree->last)){ // Si le last est un fils droit
		nodeRemoved = tree->last;
		tree->last = nodeRemoved->parent->left;
		nodeRemoved->parent->right = NULL;
		nodeRemoved->parent = NULL;
	}
	else if(pow(2,countNbStage(tree->numelm))-isNotSaturated(tree->numelm) == 1){ // Si le last est tout a gauche de l'arbre
		nodeRemoved = tree->last;
		iterator = tree->root;
		while(iterator->right){// on va chercher la position de la node la plus a droite de l'arbre car ca sera notre futur last
			iterator = iterator->right;
		}
		tree->last = iterator;
		nodeRemoved->parent->left = NULL;
		nodeRemoved->parent = NULL;
	}
	else{
		nodeRemoved = removeLeftChild(tree);
	}
	tree->numelm -= 1;
	return nodeRemoved;
}

/*
*Swap la TNode child avec la TNode parent
*/
void CBTreeSwap(CBTree* tree, TNode* parent, TNode* child) {
	assert(parent != NULL && child != NULL && (child == parent->left || child == parent->right));
	TNode * childRight = child->right;
	TNode * childLeft = child->left;
	
	
	child->parent = parent->parent;
	if(parent->parent){
		if(parent->parent->left == parent){
			parent->parent->left = child;
		}else{
			parent->parent->right = child;
		}
	}else{
		tree->root = child;
	}	

	if(child == parent->left){
		child->right = parent->right;
		child->left = parent;
	}else{
		child->left = parent->left;
		child->right = parent;
	}
	
	parent->parent = child;
	parent->left = childLeft;
	parent->right = childRight;
	
	if(child->left == parent){
		if(child->right) child->right->parent = child;
	}else if(child->left){
		if(child->left) child->left->parent = child;
	}
	if(parent->right)
		parent->right->parent = parent;
	 if(parent->left){
		parent->left->parent = parent;
	}

	if(tree->last == child){
		tree->last = parent;
	}
}



/*
* Swap le root de l'arbre tree avec le last de l'arbre tree
*/
void CBTreeSwapRootLast(CBTree* tree) {
	TNode * copyRoot = tree->root;
	if(tree->last == tree->root){
		tree->root = tree->last;
		tree->last = copyRoot;
	}
	else{			
		tree->root->parent = tree->last->parent;
		if(tree->last->parent->left == tree->last){
			tree->last->parent->left = tree->root;
		}else{
			tree->last->parent->right = tree->root;
		}
		tree->last->left = tree->root->left;
		tree->last->left->parent = tree->last;
		if(tree->root->right){
			tree->last->right = tree->root->right;
			tree->last->right->parent = tree->last;
		}	
		tree->root->left = NULL;
		tree->root->right = NULL;
		tree->root = tree->last;
		tree->last = copyRoot;
		tree->root->parent = NULL;
	}	
}


