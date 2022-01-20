#ifndef _TOWN_H_
#define _TOWN_H_

#include "list.h"

#define INFTY INT_MAX

/** TYPE ABSTRAIT
 * Cette structure contient les champs suivants :
 *  (+) name : un nom de ville
 *  (+) alist : la liste d'adjance;
 *      liste des routes reliant cette ville à une autre ville.
 */
struct town {
	char * name; // e.g. L.A., N.Y., S.F.
	List * alist; // adjacency list which data are roads
	int dist; // distance actuelle ou finale
	struct town * pred; // prédécesseur

	/**
	 * Pointeur vers le nœud du tas qui contient la ville:
	 * (+) un entier (position au dictionnaire) pour un Tableau Dynamique
	 * (+) un LNode pour une Liste Ordonnée
	 * (+) un TNode pour un Arbre Binaire Complet
	 * Utiliser comme deuxième argument (position)
	 * dans la fonction HeapIncreasePriority
	 */
	void * ptr;
};

// Créer une ville avec un nom (name) donné
struct town * createTown(char * name);

// Libérer la chaîne de carcatère contenant le nom de la ville
// Libérer la liste d'adjacence mais pas les routes référencées
void freeTown(struct town * T);

// Obtenir le nom de la ville T
char * getTownName(struct town * T);

// Obtenir la liste d'adjacence de la ville T
List * getAList(struct town * T);

// Visualiser la ville T, i.e. son nom et ses routes
void viewTown(struct town * T);

// Afficher le nom de la ville T
void printTownName(struct town * T);

#endif // _TOWN_H_
