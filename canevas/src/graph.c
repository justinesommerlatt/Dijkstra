#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"
#include "graph.h"
#include "road.h"
#include "town.h"

static void insert_ordered(List * L, void * data, struct town * departure) {
	if (L->head == NULL) {
		listInsertFirst(L, data);
	} else {
		LNode * iterator = L->head;

		if (departure == NULL) { // C'est la liste des villes

			char * Tname = getTownName(data);

			while (iterator && strcmp(Tname, getTownName(iterator->data)) > 0)
				iterator = iterator->suc;
		} else { // C'est une liste d'ajacence, une liste de routes
			struct town * u = getURoad(data);
			struct town * v = getVRoad(data);
			struct town * cur = (departure == u) ? v : u;

			while (iterator) {
				u = getURoad(iterator->data);
				v = getVRoad(iterator->data);
				struct town * next = (departure == u) ? v : u;

				if (strcmp(getTownName(cur), getTownName(next)) < 0)
					break;
				iterator = iterator->suc;
			}
		}

		if (iterator == NULL) // Ajout en queue
			listInsertAfter(L, data, L->tail);
		else if (iterator == L->head) // Ajout en Tête
			listInsertFirst(L, data);
		else
			listInsertAfter(L, data, iterator->pred);
	}
}

graph readmap(char * filename) {
	FILE * fd;
	if ((fd = fopen(filename, "rt")) == NULL) {
		fprintf(stderr, "Error while opening %s\n", filename);
		exit(EXIT_FAILURE);
	}

	int nb;

	// Construction de la liste des villes
	//  qui sont les sommets du graphe
	graph G = newList(); 

	fscanf(fd, " %d", &nb);
	for (int i = 0; i < nb; i++) {
		char txtbuf[BUFSIZ];
		int buflen;

		fscanf(fd, " %s", txtbuf);
		buflen = strlen(txtbuf) + 1;
		char * name = calloc(buflen, sizeof(char));
		strcpy(name, txtbuf);

		struct town * T = createTown(name);

		insert_ordered(G, T, NULL);
	}

	// Construction de la liste des routes
	//  dont les villes sont des références
	//  aux villes enregistrées auparavant
	// Les routes sont les arêtes du graphe
	List * edges = newList();

	fscanf(fd, " %d", &nb);
	for (int i = 0; i < nb; i++) {
		char T1[20], T2[20];
		int dist;
		fscanf(fd, " ( %s , %s , %d )", T1, T2 , &dist);

		LNode * iterator = G->head;
		while (iterator && strcmp(T1, getTownName(iterator->data)) != 0)
			iterator = iterator->suc;
		if (iterator == NULL)
			exit(EXIT_FAILURE);

		struct town * u = iterator->data;

		iterator = G->head;
		while (iterator && strcmp(T2, getTownName(iterator->data)) != 0)
			iterator = iterator->suc;
		if (iterator == NULL)
			exit(EXIT_FAILURE);

		struct town * v = iterator->data;

		struct road * R = createRoad(u, v, dist);

		listInsertFirst(edges, R); // un simple ajout en tête
	}

	// Construction des listes d'adjacences
	//  en parcourant la liste de routes
	for (LNode * roads = edges->head; roads; roads = roads->suc) {
		struct town * u = getURoad(roads->data);
		struct town * v = getVRoad(roads->data);

		if (u == NULL || v == NULL)
			exit(EXIT_FAILURE);

		insert_ordered(u->alist, roads->data, u); // insertion ordonnée de ville de départ u
		insert_ordered(v->alist, roads->data, v); // insertion ordonnée de ville de départ v
	}

	// Libérer la liste des arêtes mais pas les routes
	deleteList(edges, NULL);

	fclose(fd);
	return G;
}
  
void viewmap(graph G) {
	printf("\t\t+++++%d Towns+++++\n", G->numelm);
	for (LNode * towns = G->head; towns; towns = towns->suc) {
		printf("\t%s connected to:\n", getTownName(towns->data));
		for (LNode * roads = getAList(towns->data)->head; roads; roads = roads->suc) {
			struct town * u = getURoad(roads->data);
			struct town * v = getVRoad(roads->data);
			int dist = getKM(roads->data);
			struct town * next = (u == towns->data) ? v : u;
			printf("\t\t%s, %d km\n", getTownName(next), dist);
		}
	}
}

void freeGraph(graph G) {
	LNode * iterator = G->head;

	while (iterator) {
		struct town * T = iterator->data;
		LNode * alist = T->alist->head;

		free(T->name); // Libérer le nom
		while (alist) { // Libérer la liste d'adjacence
			struct road * R = alist->data;
			struct town * U = getURoad(R);
			struct town * V = getVRoad(R);

			// Déréférencer la ville T dans la route R
			if (!strcmp(getTownName(U), getTownName(T)))
				setURoad(R, NULL);
			else
				setVRoad(R, NULL);
			U = getURoad(R);
			V = getVRoad(R);
			// Si les deux villes sont déréférencées
			// Alors libérer la route R
			if (!U && !V)
				freeRoad(R);
			LNode * cur = alist;

			alist = alist->suc;
			free(cur);
		}
		LNode * cur = iterator;

		free(T);
		iterator = iterator->suc;
		free(cur);
	}
	free(G);
}
