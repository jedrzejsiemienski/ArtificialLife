/*
 * Environment.h
 *
 *  Created on: 7 sty 2014
 *      Author: jedrek
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "../worms/Worm.h"
#include "../utils/Point.h"
#include <math.h>
#include <list>

using namespace std;

class Environment {
public:
	Environment(Point, Point, int, float, float, float, int);
	virtual ~Environment();

	Worm * getBestWorm();

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

