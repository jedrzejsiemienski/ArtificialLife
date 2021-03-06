/*
 * BrainRandom.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "BrainRandom.h"

BrainRandom::BrainRandom() : BaseBrain(){}

BrainRandom::~BrainRandom() {}

int ** BrainRandom::stimulate(int b1, int b2, int a1, int a2, int a3){
	int ** result = new int*[dataCount];
	for(int i = 0; i < dataCount; i++){
		result[i] = new int[2];
		result[i][0] = rand() % 2;
		result[i][1] = rand() % 2;
	}
	return result;
}
