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

