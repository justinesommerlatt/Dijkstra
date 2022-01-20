#ifndef _TEST_H_
#define _TEST_H_
#include "tree.h"
#include "heap.h"
void test_list();


/*
	printf("==================\n");
	viewCBTree(tree, &viewHNodeT, 0);	
	TNode * CopieLast;
	TNode * iterator = tree->root;
	//Nombre d'étage de l'arbre
        int nbStage = countNbStage(tree->numelm);
        //Nombre de noeud maximum possible sur le dernier étage
        int nbNodeSaturated = pow(2,nbStage);
        //Nombre de noeud manquant pour que l'arbre soit saturé
        int nbNodeLastStage = isNotSaturated(tree->numelm);
        //Indice du prochain last apres supression de l'actuel
        int indiceNextLast = nbNodeSaturated - nbNodeLastStage - 1;
         //Recherche dicotomique du futur last

	printf("cbtree remove\n");
        if(!tree->root){// Si l'arbre est vide
                return NULL;
        }
        CopieLast = tree->last;
	printf("POULETTTTTTTTTTTTTTTTTT\n");
	viewHNodeT((HNode*)CopieLast->data);
        if(tree->root == tree->last){// Si l'arbre n'a qu'un élément
                tree->last = NULL;
                tree->root = NULL;
        }
        else{// Sinon

                if(!isLeftChild(tree->last)){// Si le last est un fils droit
        		printf("LAST FILS DROIT\n================================");

	viewHNodeT((HNode*)tree->last->parent->left->data);
			tree->last = tree->last->parent->left;
	viewHNodeT((HNode*)tree->last->parent->right->parent->data);
                        tree->last->parent->right = NULL;
	//viewHNodeT((HNode*)CopieLast->data);
			CopieLast->parent = NULL;
                }else if(nbNodeSaturated - nbNodeLastStage == 1){ // Si le last est tout a gauche
			tree->last->parent->left = NULL;
			tree->last->parent = NULL;
			while(iterator->right){
				iterator = iterator->right;
			}
			tree->last = iterator;
		
		}else if(isLeftChild(tree->last)){// Si le last est un fils gauche
			printf("avant do\n");
			printf("ON EST PASSE ICI 1*\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                        do{
				printf("==================\n");
			//	printf("%s\n",getTownName(((struct town*)((HNode*)iterator->data)->data)));
				printf("la\n");

                                //On regarde si il se trouve dans la "partie gauche"
                                if(indiceNextLast <= nbNodeSaturated/2){
                                        //On descend d'un étage
                                        iterator = iterator->left;
                                        //Maj nb noeud max sur cet etage
                                        nbNodeSaturated /= 2;

                                }
                                //Sinon il se trouve dans la "partie droite"
                                else{
                                        //On descend d'un étage
                                        iterator = iterator->right;
                                        //Maj nb noeud max sur cet etage
                                        nbNodeSaturated /= 2;
                                        //Maj de l'indice du futur last
                                        indiceNextLast = indiceNextLast - nbNodeSaturated;

                                }
                        }while(iterator->left);
                        //Suppresion du last dans l'arbre
                        tree->last->parent->left = NULL;
                        //Mise à jour du last dans l'arbre
                        tree->last = iterator;
			CopieLast->parent = NULL;
                }        
        }
	tree->numelm --;
        return CopieLast;
}
*/
void viewHNodeT(const void *node);

void printIntHNode(const void * data);

void printIntDict(const void * data);

#endif // _TEST_H_
