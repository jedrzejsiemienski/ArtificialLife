/*
 * Environment.h
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "Genotype.h"
#include "../worm/Worm.h"
#include "../utils/Point.h"
#include <math.h>
#include <stdlib.h>
#include <list>

class Environment {
public:
	Environment(Point, Point, int, int, float, float, int);
	virtual ~Environment();

	Worm * getBestWorm();
	Worm * epochs(int);
	float evolutionCycle();
	void clear();
	void print();

	int compare(Worm*, Worm*);

private:
	int movementSteps;
	unsigned int startPopulationSize;
	int type;
	float f;
	float cr;

	Point start;
	Point target;
	Worm * bestWorm;
	list<Worm*> population;
	list<Worm*> intermediatePopulation;

	void createBasePopulation();
	void createIntermediatePopulation();
	void eliminate();

	Worm* getWromFromPopulationAt(int);

};

#endif /* ENVIRONMENT_H_ */
