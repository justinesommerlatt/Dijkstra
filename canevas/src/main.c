#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include "dyntable.h"
#include "tree.h"
#include "list.h"
#include "heap.h"
#include "town.h"
#include "road.h"
#include "graph.h"
#include "test.h"

/**
 * Exemple d'une fonction qui affiche le contenu d'un HNode.
 * A modifier si besoin.
*/
void viewHNode(const HNode *node) {
	struct town * town = node->data;
	printf("(%d, %s)\n", node->value, getTownName(town));
}

/**
 * Ecrit dans le fichier outFileName la solution de l'algorithme de Dijkstra
 */
void writeSolution(graph G, char * sourceName, char * outFileName){
	FILE * fd;
	if ((fd = fopen(outFileName, "w")) == NULL) {
		fprintf(stderr, "Error while opening %s\n", outFileName);
		exit(EXIT_FAILURE);
	}
	fprintf(fd,"%d\n",G->numelm);
	fprintf(fd,"%s\n", sourceName);
	LNode * itown;
	for (itown = G->head; itown; itown = itown->suc) {
			if (strcmp(getTownName(itown->data), sourceName) != 0)
				fprintf(fd,"%s %d %s\n", getTownName((struct town *) itown->data),
												((struct town *) itown->data)->dist,
												getTownName(((struct town *) itown->data)->pred));
		}

	fclose(fd);
}


/**
 * Affichage de la solution de l'algorithme de Dijkstra.
 * Pour chaque ville du graphe G on doit déjà avoir défini
 * les valeurs dist et pred en exécutant l'algorithme de Dijkstra.
*/
void viewSolution(graph G, char * sourceName) {
	printf("Distances from %s\n", sourceName);
	LNode * itown;
	for (itown = G->head; itown; itown = itown->suc) {
		if (strcmp(getTownName(itown->data), sourceName) != 0)
			printf("%s : %d km (via %s)\n", getTownName((struct town *) itown->data),
											((struct town *) itown->data)->dist,
											getTownName(((struct town *) itown->data)->pred));
	}
}

/**
 * Algorithme de Dijkstra
 * inFileName : nom du fichier d'entrée
 * outFileName : nom du fichier de sortie
 * sourceName : nom de la ville de départ
 * heaptype : type du tas {0--tableaux dynamiques, 1--arbres binaires complets, 2--listes ordonnées}
 */
void Dijkstra(char * inFileName, char * outFileName, char * sourceName, int heaptype) {
	
	clock_t start, end;
	double cpu_time_used;
	graph G = readmap(inFileName);
	Heap * A;
	HNode * iterator;
	LNode * itown;
	LNode * iroad;
	LNode * firstTownNode = G->head;
	struct town * firstTown;
	struct town * t;
	struct road * r;
	DTable * dict;
	int numelm;
	int i;
	while(firstTownNode){ // Recherche de la ville source 
		
		if(!strcmp(((struct town*)firstTownNode->data)->name, sourceName)){
			break;
		}else{
			firstTownNode = firstTownNode->suc;
		}	
	}
	if(!firstTownNode){
		printf("Cette ville n'existe pas sur la carte\n");
	}else if(G->tail == G->head){
		printf("il n'y a qu'une seule ville sur la carte\n");
	}else{
		itown = G->head;
		while(itown){ // Initialisation de Dijkstra
			((struct town*)itown->data)->dist = 2000000000;
			((struct town*)itown->data)->pred = NULL;
			itown = itown->suc;
		}
		
		firstTown = (struct town *)firstTownNode->data;
		firstTown->dist = 0;
		
		start = clock();

		A = newHeap(heaptype);

		dict = (DTable*)A->dict;

		itown = G->head;
		
		i = 0;
		switch(heaptype){ // Choix du type d'implémentation
			case 0:
				while(itown){ // Tableau dynamique
					((struct town*)itown->data)->ptr =(int*) i;
					
					DTableInsert(dict, ((DTable*)A->heap)->used); 
					A->HeapInsert(A,((struct town*)itown->data)->dist, itown->data);
						
					((HNode*)((DTable*)A->heap)->T[(int)dict->T[i]])->ptr =(int*) i;
					i++;
					itown = itown->suc;

				}
				break;
			case 1:
				
				while(itown){ // Arbre
					t = (struct town *)itown->data;
					t->ptr = A->HeapInsert(A,((struct town*)itown->data)->dist, itown->data);
					itown = itown->suc;
				}
				numelm = ((CBTree*)A->heap)->numelm;
				break;
			case 2:
			
				while(itown){ // Liste
					t = (struct town *)itown->data;
					t->ptr = A->HeapInsert(A,((struct town*)itown->data)->dist, itown->data);
					itown = itown->suc;
				}
				numelm = ((CBTree*)A->heap)->numelm;
				break;
		}
		iterator = A->HeapExtractMin(A); // Extraction de la ville source
		if(heaptype){ // Arbre ou liste
			while(((CBTree*)A->heap)->numelm){ 
				t = (struct town*)iterator->data;
				iroad = (LNode*)t->alist->head;
				while(iroad){ // Parcours toutes les routes pour calculer la distance dist
					r = (struct road*)iroad->data;
					if(t == getURoad(r)){ // si la ville recherchée est dans V
						if(getVRoad(r)->dist > getKM(r) + t->dist && getVRoad(r) != firstTown){ // Calcule de la distance et mise à jour si distance infèrieure  
							
							getVRoad(r)->dist = getKM(r) + t->dist;
							
							getVRoad(r)->pred = t;	
							
							A->HeapIncreasePriority(A, getVRoad(r)->ptr, getVRoad(r)->dist); 
							
						}
					}else{ // Ville dans U
						if(getURoad(r)->dist > getKM(r) + t->dist && getURoad(r) != firstTown){ // Calcule de la distance et mise à jour si distance infèrieure  
							
							getURoad(r)->dist = getKM(r) + t->dist;	
							
							getURoad(r)->pred = t;	
							A->HeapIncreasePriority(A, getURoad(r)->ptr, getURoad(r)->dist);
							
						}
					}
						
					iroad = iroad->suc;
				}
				
				iterator = A->HeapExtractMin(A);
				
			}
		}else{ //Tableau Dynamique
			
			while(((DTable*)A->heap)->used){
				t = (struct town*)iterator->data;
				iroad = (LNode*)t->alist->head;
				while(iroad){// Parcours toutes les routes pour calculer la distance dist
					r = (struct road*)iroad->data;
					if(t == getURoad(r)){// si la ville recherchée est dans V
						if(getVRoad(r)->dist > getKM(r) + t->dist && getVRoad(r) != firstTown){ // Calcule de la distance et mise à jour si distance infèrieure  
							getVRoad(r)->dist = getKM(r) + t->dist;
							
							getVRoad(r)->pred = t;

							A->HeapIncreasePriority(A, getVRoad(r)->ptr, getVRoad(r)->dist); 
							
						}
					}else{// Ville dans U

						if(getURoad(r)->dist > getKM(r) + t->dist && getURoad(r) != firstTown){ // Calcule de la distance et mise à jour si distance infèrieure  
							
							
							getURoad(r)->dist = getKM(r) + t->dist;	

							getURoad(r)->pred = t;

							A->HeapIncreasePriority(A, getURoad(r)->ptr, getURoad(r)->dist);
							
						}
					}
						
					iroad = iroad->suc;

				}
				
				iterator = A->HeapExtractMin(A);
				
			}
		}
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		printf("Dijkstra time = %lf\n", cpu_time_used);
		writeSolution(G, sourceName, outFileName);
		
		viewSolution(G, sourceName);
		
	}
}

