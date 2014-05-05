/*
 * Chromosom.h
 *
 *  Created on: 28 gru 2013
 *      Author: jedrek
 */

#ifndef CHROMOSOM_H_
#define CHROMOSOM_H_

#include <iostream>
#include <conio.h>
#include <sstream>

using namespace std;

struct Pair{
	float w;
	float t;
};

class Chromosom {
public:
	Chromosom();
	Chromosom(int, int, Pair*, float*);
	virtual ~Chromosom();

	int pairsCount;
	int floatsCount;

	Pair * pairs;
	float * floats;

	string toString();
};

#endif /* CHROMOSOM_H_ */
