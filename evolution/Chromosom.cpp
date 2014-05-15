/*
 * Chromosom.cpp
 *
 *  Created on: 28 gru 2013
 *      Author: jedrek
 */

#include "Chromosom.h"

using namespace std;

Chromosom::~Chromosom() {
	delete[] pairs;
	delete[] floats;
}

Chromosom::Chromosom(){
	pairsCount = 0;
	floatsCount = 0;
	pairs = 0;
	floats = 0;
}

Chromosom::Chromosom(int givenPairsCount, int givenFloatsCount, Pair* givenPairs, float* givenFloats) {
	pairsCount = givenPairsCount;
	pairs = givenPairs;
	floatsCount = givenFloatsCount;
	floats = givenFloats;
}

string Chromosom::toString(){
	string result = "";

	for(int i = 0; i < pairsCount; i++){
		ostringstream ss;
		ss << pairs[i].t << " " << pairs[i].w << "\n";
		result.append(ss.str());
	}

	for(int i = 0; i < floatsCount; i++){
		ostringstream ss;
		ss << floats[i] << "\n";
		result.append(ss.str());
	}

	return result;
}

void Chromosom::substract(Chromosom* x){
	for(int i = 0; i < pairsCount; i++){
		pairs[i].t -= x->pairs[i].t;
		pairs[i].w -= x->pairs[i].w;
	}

	for(int i = 0; i < floatsCount; i++){
		floats[i] -= x->floats[i];
	}
}

void Chromosom::add(Chromosom* x){
	for(int i = 0; i < pairsCount; i++){
		pairs[i].t += x->pairs[i].t;
		pairs[i].w += x->pairs[i].w;
	}

	for(int i = 0; i < floatsCount; i++){
		floats[i] += x->floats[i];
	}
}

void Chromosom::multiply(float a){
	for(int i = 0; i < pairsCount; i++){
		pairs[i].t *= a;
		pairs[i].w *= a;
	}

	for(int i = 0; i < floatsCount; i++){
		floats[i] *= a;
	}

}

