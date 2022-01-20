#ifndef _ROAD_H_
#define _ROAD_H_

/** TYPE ABSTRAIT
 * Cette structure décrit une route
 * par les deux villes U et V qu'elle relie.
 */
struct road {
	struct town * U, * V; // indices of towns in graph->towns
	int km; // distance en kilomètres
};

// Créer une route qui relie les villes u et v données
struct road * createRoad(struct town * u, struct town * v, int dist);

// Libérer une route référencée par ptrR
void freeRoad(struct road * R);

// Consulter la ville U de la route R donnée
struct town * getURoad(struct road * R);

// Modifier la référence U
void setURoad(struct road * R, struct town * T);

// Consulter la ville V de la route R donnée
struct town * getVRoad(struct road * R);

// Modifier la référence V
void setVRoad(struct road * R, struct town * T);

// Consulter la distance de la route R donnée
int getKM(struct road * R);

// Modifier la distance
void setKM(struct road * R, int dist);

// Afficher le nom de deux villes que la route (R) connecte
void viewRoad(struct road * R);

#endif // _ROAD_H_