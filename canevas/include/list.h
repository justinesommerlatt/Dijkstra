#ifndef _LIST_
#define _LIST_
/**
 * @brief
 * Liste générique homogène doublement chaînée
 */

/**
 * @brief
 * Un élément de liste contient
 * (+) Une donnée (data)
 * (+) Une référence (suc) à l'élément suivant
 * (+) Une référence (pred) à l'élément précédent
 */
typedef struct ListNode {
	void * data;
	struct ListNode * suc, * pred;
} LNode;

/**
 * @brief
 * La liste est une structure contenant
 * (+) Une référence (head) sur son premier élément,
 * (+) Une référence (tail) sur son dernier élement et
 * (+) Le nombre d'éléments
 */
typedef struct List {
	LNode * head, * tail;
	int numelm;
} List;

/**
 * @brief
 * Construire une liste vide
 */
List * newList ();

/**
 * @brief
 * Deux possibilités de supprimer la liste L :
 * (+) Si le pointeur de fonction (ptrF) est indéfini (NULL)
 *     Alors les données (data) référencées par les élements
 *     de la liste L ne sont pas supprimées ;
 * (+) Si le pointeur de fonction (ptrF) est défini
 *     Alors ce pointeur de fonction (ptrF) référence la fonction
 *     devant servir à supprimer les données (data) référencées par
 *     les éléments de la liste L.
 */
void deleteList(List * L, void (*ptrF)());

/**
 * @brief
 * Afficher les éléments de la liste.
 * Chaque élément est affiché grâce au pointeur de fonction ptrF
 */
void viewList(const List * L, void (*ptrF) ());

/**
 * @brief
 * Ajouter en tête de la liste L un élément de donnée data
 */
void listInsertFirst(List * L, void * data);

/**
 * @brief
 * Ajouter à la fin de la liste L un élément de donnée data
 */
void listInsertLast(List * L, void * data);

/**
 * @brief
 * Insérer un élément de liste de donnée data dans la liste L
 * après le pointeur d'élément ptrelm
 * 
 * Note.
 *    le pointeur d'élément ptrelm désigne obligatoirement
 *    un élément de la liste L.
 */
void listInsertAfter(List * L, void * data, LNode * ptrelm);

/**
 * @brief
 * Supprimer le premier élément de liste L.
 * Assurez vous que la liste n'est pas vide.
 */
LNode* listRemoveFirst(List * L);

/**
 * @brief
 * Supprimer le premier élément de liste L
 * Assurez vous que la liste n'est pas vide.
 */
LNode* listRemoveLast(List * L);

/**
 * @brief
 * Supprimer l'élément pointé par node de la liste L.
 * L'élément est supposé appartenir effectivement à la liste.
 */
LNode* listRemoveNode(List * L, LNode * node);

/**
 * @brief
 * Permuter les positions des nœuds left et right dans la liste L.
 */
void listSwap(List * L, LNode * left, LNode *right);

#endif // _LIST_
