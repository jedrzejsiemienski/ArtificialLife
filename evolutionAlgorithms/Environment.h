/*
 * Environment.h
 *
 *  Created on: 7 sty 2014
 *      Author: jedrek
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "../worms/WormBase.h"
#include "../utils/Point.h"
#include <math.h>
#include <list>

using namespace std;

class Environment {
public:
	Environment(Point, Point, int, float, float, float, int);
	virtual ~Environment();

	WormBase * getBestWorm();

	float evolutionCycle();

	void print();

private:
	int movementSteps;
	int startPopulationSize;
	float mutationP;
	float mutationF;
	float mutationFt;

	Point start;
	Point target;
	WormBase * bestWorm;
	list<WormBase*> population;
	list<WormBase*>::iterator currentWorm;


	void createPopulation();
	void mutate();
	void cross();
	void eliminate();
	void resetWorms();

	int compare(WormBase*, WormBase*);

};

#endif /* ENVIRONMENT_H_ */

