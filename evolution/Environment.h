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
#include <list>

class Environment {
public:
	Environment(Point, Point, int, int, float, float, int);
	virtual ~Environment();

	Worm * getBestWorm();

	float evolutionCycle();

	void print();

private:
	int movementSteps;
	int startPopulationSize;
	int type;
	float f;
	float cr;

	Point start;
	Point target;
	Worm * bestWorm;
	list<Worm*> population;
	list<Worm*>::iterator currentWorm;

	void createPopulation();
	void mutate();
	void cross();
	void eliminate();
	void resetWorms();

	int compare(Worm*, Worm*);
};

#endif /* ENVIRONMENT_H_ */
