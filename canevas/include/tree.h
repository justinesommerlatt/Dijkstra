#ifndef _TREE_
#define _TREE_
/**
 * @brief
 * Arbre binaire complet générique
 */

/**
 * @brief
 * Un élément d'un arbre binaire contient
 * (+) Une donnée (data)
 * (+) Une référence (left) au fils gauche
 * (+) Une référence (right) au fils droit
 * (+) Une référence (parent) au père
 */
typedef struct TreeNode {
	void * data;
	struct TreeNode * left;
	struct TreeNode * right;
	struct TreeNode * parent;
} TNode;

/**
 * @brief
 * Construire et initialiser un nouveau noeud d'un arbre binaire.
 * Renvoie le nouveau noeud créé.
 */
TNode * newTNode(void *data);

/**
 * L'arbre binaire complet est une structure contenant
 * (+) Une référence (root) sur sa racine,
 * (+) Une référence (last) sur son élement ajouté en dernier,
 * (+) Le nombre d'éléments
 */
typedef struct CompleteBinaryTree {
	TNode * root;
	TNode * last;
	int numelm;
} CBTree;

/**
 * @brief
 * Construire un arbre vide
 */
CBTree * newCBTree();

/**
 * @brief
 * Afficher les éléments de l'arbre.
 * Chaque élément est affiché grace au pointeur de fonction ptrF.
 * L'attribut order spécifie l'ordre d'affichage :
 * (+) 0 = ordre préfixe
 * (+) 1 = ordre postfixe
 * (+) 2 = ordre infixe
 */
void viewCBTree(const CBTree* tree, void (*ptrF)(const void*), int order);

/**
 *Gaetan
 *Fonction rajoutee
 *Renvoie true si la node est un fils gauche
 *sinon renvoie false
 *NE PAS UTILISER SUR UN ARBRE A UN ELEMENT
 *OU VIDE
 */
int isLeftChild(TNode * child);


/**
 * Gaetan
 * Fonction rajoutee
 * @param numelm Le nombre d'element d'un arbre
 * Renvoie vrai si l'arbre est saturee, sinon renvoie faux
 */
int isNotSaturated(int numelm);

/**
 * Gaetan
 * Fonction rajoutee
 * @param numelm Le nombre d'element d'un arbre
 * Renvoie le nombre d'etage d'un arbre
 */
int countNbStage(int numelm);

/**
 * Gaetan
 * Fonction rajoutee
 * @param tree un arbre ou l'on doit rajouter un feuille
 * mais garder le caractere complet
 * @param node la node a ajouter a l'arbre
 * ajoute la node a la fin de l'arbre et conserve son
 * caractere complet
 */
void insertAfterLast(CBTree * tree, TNode * node);

/**
 * @brief
 * Ajouter dans l'arbre binaire complet tree un élément de donnée data.
 */
void CBTreeInsert(CBTree* tree, void* data);


/**
 * @brief
 * Supprimer l'élément indiqué par le pointeur last de l'arbre binaire complet tree.
 * Renvoie la donnée du nœud supprimé.
 */
void * CBTreeRemove(CBTree* tree);

/**
 * @brief
 * Permuter les positions des nœuds parent et child dans l'arbre tree.
 */
void CBTreeSwap(CBTree* tree, TNode* parent, TNode* child);

/*
 * Fonction rajoutee
 * @param tree arbre ou l'on remove
 * role 
 * remove le last qui est tout a gauche de notre arbre
 */
TNode * removeLeftChild(CBTree* tree);

/**
 * @brief
 * Permuter les nœuds root et last de l'arbre tree.
 */
void CBTreeSwapRootLast(CBTree* tree);

#endif // _TREE_
