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
	createPopulation();
}

Environment::~Environment() {}

Worm * Environment::getBestWorm() {
	return bestWorm;
}

void Environment::print(){
	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		cout << (*currentWorm) << endl;
	}
}

float Environment::evolutionCycle(){
	mutate();
	cross();
	eliminate();
	return bestWorm->getCurrentDistanceToTarget();
}

void Environment::createPopulation(){
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






void Environment::mutate(){
	/*
	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		(*currentWorm)->mutate(mutationP, mutationF, mutationFt);
	}
	*/
}

void Environment::cross(){
	/*
	list<Worm*> newPopulation;
	Worm* mather;
	Worm* father;

	while(!population.empty()){
		currentWorm = population.begin();
	    advance(currentWorm, rand() % population.size());
	    mather = *currentWorm;
	    population.erase(currentWorm);

	    currentWorm = population.begin();
	    advance(currentWorm, rand() % population.size());
	    father = *currentWorm;
	    population.erase(currentWorm);

	    newPopulation.push_back(Worm::cross(mather, father));
	    newPopulation.push_back(Worm::cross(mather, father));
	    newPopulation.push_back(mather);
	    newPopulation.push_back(father);
	}

	population = newPopulation;
	*/
}

void Environment::eliminate(){
	/*
	unsigned int baseSize = population.size();
	unsigned int targetSize = baseSize / 2;

	list<Worm*>::iterator competitior1;
	list<Worm*>::iterator competitior2;

	Worm* winner;
	while(population.size() != targetSize){
		competitior1 = population.begin();
	    advance(competitior1, rand() % population.size());

	    competitior2 = population.begin();
	    advance(competitior2, rand() % population.size());

	    Worm* loser;
	    if(compare(*competitior1, *competitior2) == 1){
	    	winner = *competitior1;
	    	loser = *competitior2;
	    	if(bestWorm == loser){
	    		bestWorm = winner;
	    	}
	    	delete loser;
	    	population.erase(competitior2);
	    } else {
	    	winner = *competitior2;
	    	loser = *competitior1;
	    	if(bestWorm == loser){
	    		bestWorm = winner;
	    	}
	    	delete loser;
	    	population.erase(competitior1);
	    }

	    if(bestWorm != winner && compare(winner, bestWorm) == 1){
	    	bestWorm = winner;
	    }
	}
	*/
}


