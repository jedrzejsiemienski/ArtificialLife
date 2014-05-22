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

vector<float> Environment::getResults(){
	return results;
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
	return bestWorm->getDistanceAfterNMoves(movementSteps);
}

void Environment::epochs(int n){
	for(int i = 0; i < n; i++){
		results.push_back(evolutionCycle());
	}
}

void Environment::createBasePopulation(){
	while(population.size() < startPopulationSize){
		population.push_back(new Worm(type, start.x, start.y, target.x, target.y, movementSteps));
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
Worm* Environment::getWromFromPopulationAt(int index){
	list<Worm*>::iterator worm = population.begin();
	for(int i = 0; i < index; i++){
		worm++;
	}
	return *worm;
}


void Environment::createIntermediatePopulation(){
	list<Worm*>::iterator currentWorm;
	int index1, index2, index3;

	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		Genotype* g1;
		Genotype* g2;
		Genotype* g3;
		Genotype* gBest;
		Genotype* mutated;
		Genotype* current;

		index1 = rand() % population.size();
		index2 = rand() % population.size();
		while(index1 == index2) index2 = rand() % population.size();
		index3 = rand() % population.size();
		while(index1 == index3 || index2 == index3) index3 = rand() % population.size();

		g1 = getWromFromPopulationAt(index1)->getBrain()->getGenotype();
		g2 = getWromFromPopulationAt(index2)->getBrain()->getGenotype();
		g3 = getWromFromPopulationAt(index3)->getBrain()->getGenotype();
		gBest = bestWorm->getBrain()->getGenotype();
		mutated = g1->mutateWith(f, g2, g3);
		//mutated = g1->mutateCurrentToBest(f, gBest, g2, g3);
		current = (*currentWorm)->getBrain()->getGenotype();

		intermediatePopulation.push_back(new Worm(
			type,
			(*currentWorm)->getInitPoint()->x,
			(*currentWorm)->getInitPoint()->y,
			(*currentWorm)->getEndPoint()->x,
			(*currentWorm)->getEndPoint()->y,
			current->crossWith(cr, mutated),
			movementSteps
		));

		delete g1;
		delete g2;
		delete g3;
		delete gBest;
		delete mutated;
		delete current;
	}

}

void Environment::clear(){
	while(intermediatePopulation.size() != 0){
		delete *intermediatePopulation.begin();
		intermediatePopulation.pop_front();
	}

	while(population.size() != 0){
		delete *population.begin();
		population.pop_front();
	}

	results.clear();
}

void Environment::eliminate(){
	list<Worm*>::iterator bp;
	list<Worm*>::iterator ip;

	Worm* winner;
	while(intermediatePopulation.size() != 0){
		Worm* loser;
		bp = population.begin();
		ip = intermediatePopulation.begin();

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

    	if(bestWorm == loser || (bestWorm != winner && compare(winner, bestWorm) == 1)){
    		bestWorm = winner;
    	}
    	delete loser;
	}
}


