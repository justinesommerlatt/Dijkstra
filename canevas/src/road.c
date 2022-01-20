#include <stdlib.h>
#include <stdio.h>
#include "road.h"
#include "town.h"

struct road * createRoad(struct town * U, struct town * V, int dist) {
	struct road * R = calloc(1, sizeof(struct road));

	R->U = U;
	R->V = V;
	R->km = dist;

	return R;
}

void freeRoad(struct road * R) {
	free(R);
}

struct town * getURoad(struct road * R) {
	return R->U;
}

void setURoad(struct road * R, struct town * T) {
	R->U = T;
}

struct town * getVRoad(struct road * R) {
	return R->V;
}

void setVRoad(struct road * R, struct town * T) {
	R->V = T;
}

int getKM(struct road * R) {
	return R->km;
}

void setKM(struct road * R, int dist) {
	R->km = dist;
}

void viewRoad(struct road * R) {
	printTownName(R->U);
	printTownName(R->V);
	printf("%d km\n", R->km);
}