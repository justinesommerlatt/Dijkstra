#ifndef _DYNTABLE_
#define _DYNTABLE_
/**
 * @brief
 * Tableau Dynamique
 */


/**
 * Le tableau dynamique est une structure contenant
 * (+) Un tableau (T) de pointeurs vers de données de type void,
 * (+) La taille (size) du tableau,
 * (+) Le nombre de cases actuellement utilisées
 */
typedef struct DynamicTable {
	void **T;
	int size;
	int used;
} DTable;

void testStaticSUDyntable(DTable * dtab);

/**
 * @brief
 * Construire un tableau dynamique
 */
DTable * newDTable();

/**
 * @brief
 * Afficher les éléments du tableau dynamique dtab.
 * Chaque élément est affiché grace au pointeur de fonction ptrF.
 */
void viewDTable(const DTable * dtab, void (*ptrf)(const void*));

/**
 * @brief
 * Ajouter dans le tableau dynamique dtab un élément de donnée data.
 */
void DTableInsert(DTable * dtab, void * data);

/**
 * @brief
 * Supprimer l'élément dans la position used-1 (dernier élément)
 * du tableau dynamique dtab.
 */
void * DTableRemove(DTable * dtab);

/**
 * @brief
 * Permuter la donnée des positions pos1 et pos2 dans le tableau dynamique dtab.
 */
void DTableSwap(DTable * dtab, int pos1, int pos2);

#endif // _DYNTABLE_
