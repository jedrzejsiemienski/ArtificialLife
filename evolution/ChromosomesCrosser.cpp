/*
 * ChromosomesCrosser.cpp
 *
 *  Created on: 28 gru 2013
 *      Author: jedrek
 */

#include "ChromosomesCrosser.h"

void ChromosomesCrosser::mutate(Chromosom * c, float f, float ft){
	//inaczaj traktujemy t inaczej cala reszte
	for(int i = 0; i < c->pairsCount; i++){
		c->pairs[i].w *= 1 + randomNumber() * f;
		c->pairs[i].t *= 1 + randomNumber() * ft;
	}

	for(int i = 0; i < c->floatsCount; i++){
		c->floats[i] *= 1 + randomNumber() * f;
	}
}

//random number from range -1, 1
float ChromosomesCrosser::randomNumber() {
	float base = 1000.0;

	float number = (float)(rand() % ((int)base * 2));
	return (number - base) / base;
}

Chromosom * ChromosomesCrosser::cross(Chromosom * c1, Chromosom * c2, crossingTypes type = crossingTypes(MULTI_POINT), double param = 1) {
	Chromosom * result;

	if(!assertEqualStructure(c1, c2))
		return 0;

	switch(type){
		case crossingTypes(MULTI_POINT):
			result = multiPointCrossing(c1, c2, param);
			break;
		case crossingTypes(HOMOGENEOUS):
			result = homogeneousCrossing(c1, c2, param);
			break;
	};

	return result;
}

bool ChromosomesCrosser::assertEqualStructure(Chromosom * c1, Chromosom * c2){
	return true;
}

//zakladamy ze c1 i c2 maja taka sama strukture
Chromosom * ChromosomesCrosser::multiPointCrossing(Chromosom * c1, Chromosom * c2, double points){
	// krzyzowanie wielo punkowte, parametrem jest ilosc punktow krzyzowania (liczba naturalna)
	// dopuszczamy maksymalnie 2 punktowa bo wiecej raczej nei ma sensu, jak cos to sie bedziemy potem martwic
	Chromosom * result = new Chromosom();
	result->pairsCount = c1->pairsCount;
	result->floatsCount = c1->floatsCount;
	result->pairs = new Pair[result->pairsCount];
	result->floats = new float[result->floatsCount];

	//losujemy punkty krzyzowania
	int length = c1->pairsCount + c1->floatsCount;
	int a = rand() % length;

	if(points == 1){
		for(int i = 0; i < result->pairsCount; i++){
			if(i < a){
				result->pairs[i] = c1->pairs[i];
			} else {
				result->pairs[i] = c2->pairs[i];
			}
		}

		if(a < c1->pairsCount)
			a -= c1->pairsCount;

		for(int i = 0; i < result->floatsCount; i++){
			if(i < a){
				result->floats[i] = c1->floats[i];
			} else {
				result->floats[i] = c2->floats[i];
			}
		}

	}

	/*
	 *  2 stopniowe do dopisania potem
	 */

	/*
	else {
		int b = rand() % length;
		if(b > a){
			int tmp = a;
			a = b;
			b = tmp;
		}
	}
	*/

	return result;
}


Chromosom * ChromosomesCrosser::homogeneousCrossing(Chromosom * c1, Chromosom * c2, double p){
	// krzyzowanie jednorodne, parametrem ejst prawdopodobienstwo wymiany genu podczas iterowania
	Chromosom * result = new Chromosom();
	result->pairsCount = c1->pairsCount;
	result->floatsCount = c1->floatsCount;
	result->pairs = new Pair[result->pairsCount];
	result->floats = new float[result->floatsCount];

	float random;
	float base = 1000.0;
	for(int i = 0; i < result->pairsCount; i++){
		random = (float)(rand() % (int)base) / base;
		if(random < p){
			result->pairs[i] = c1->pairs[i];
		} else {
			result->pairs[i] = c2->pairs[i];
		}
	}

	for(int i = 0; i < result->floatsCount; i++){
		random = (float)(rand() % (int)base) / base;
		if(random < p){
			result->floats[i] = c1->floats[i];
		} else {
			result->floats[i] = c2->floats[i];
		}
	}

	return result;
}
