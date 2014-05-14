/*
 * Environment.cpp
 *
 *  Created on: 14 maj 2014
 *      Author: jedrek
 */

#include "Environment.h"

Environment::Environment(Point start, Point target, int type, int populationSize, float f, float cr, int movementSteps) {
	this->start.x = start.x;
	this->start.y = start.y;
	this->target.x = target.x;
	this->target.y = target.y;

	this->type = type;
	this->movementSteps = movementSteps;
	this->f = f;
	this->cr = cr;
	startPopulationSize = populationSize;
	createBasePopulation();
}

Environment::~Environment() {}

Worm * Environment::getBestWorm() {
	return bestWorm;
}

void Environment::print(){
	list<Worm*>::iterator currentWorm;
	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		cout << (*currentWorm) << endl;
	}
}

float Environment::evolutionCycle(){
	createIntermediatePopulation();
	eliminate();
	return bestWorm->getCurrentDistanceToTarget();
}

void Environment::createBasePopulation(){
	for(int i = 0; i < startPopulationSize; i++){
		population.push_back(new Worm(type, start.x, start.y, target.x, target.y));
	}
	bestWorm = *population.begin();
}

int Environment::compare(Worm* w1, Worm* w2) {
	float d1 = w1->getDistanceAfterNMoves(movementSteps);
	float d2 = w2->getDistanceAfterNMoves(movementSteps);

	if(d1 <= d2){
		return 1;
	} else {
		return 2;
	}
}

//TOFIX
Worm* Environment::randomWorm(){
	return bestWorm;
}


void Environment::createIntermediatePopulation(){
	Genotype* g1;
	Genotype* g2;
	Genotype* g3;
	Genotype* current;
	Genotype* result;
	list<Worm*>::iterator currentWorm;

	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		g1 = randomWorm()->getBrain()->getGenotype();
		g2 = randomWorm()->getBrain()->getGenotype();
		while(g1 == g2) g2 = randomWorm()->getBrain()->getGenotype();
		g3 = randomWorm()->getBrain()->getGenotype();
		while(g1 == g3 || g2 == g3) g3 = randomWorm()->getBrain()->getGenotype();

		current = (*currentWorm)->getBrain()->getGenotype();
		result = current->crossWith(cr, g1->mutateWith(f, g2, g3));

		intermediatePopulation.push_back(new Worm(type, result));
	}

}

void Environment::eliminate(){
	list<Worm*>::iterator bp = population.begin();
	list<Worm*>::iterator ip = intermediatePopulation.begin();

	Worm* winner;
	while(intermediatePopulation.size() != 0){
		Worm* loser;
	    if(compare(*bp, *ip) == 1){
	    	winner = *bp;
	    	loser = *ip;
	    } else {
	    	winner = *ip;
	    	loser = *bp;
	    }

	    population.push_back(winner);

	    population.pop_front();
    	intermediatePopulation.pop_front();

	    if(bestWorm != winner && compare(winner, bestWorm) == 1){
	    	bestWorm = winner;
	    }

	    delete loser;
	}
}


