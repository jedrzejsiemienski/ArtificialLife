/*
 * BrainDummy.cpp
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#include "BrainDummy.h"

BrainDummy::BrainDummy() : BaseBrain() {}

BrainDummy::~BrainDummy() {}

int ** BrainDummy::stimulate(int b1, int b2, int a1, int a2, int a3){
	int ** result = new int*[dataCount];
	for(int i = 0; i < dataCount; i++){
		result[i] = new int[2];
		result[i][0] = 1;
		result[i][1] = 0;
	}
	return result;
}
