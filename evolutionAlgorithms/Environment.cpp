/*
 * Environment.cpp
 *
 *  Created on: 7 sty 2014
 *      Author: jedrek
 */

#include "Environment.h"

using namespace std;

Environment::Environment(Point start, Point target, int populationSize, float mutationP, float mutationF, float mutationFt, int givenMovementSteps) {
	this->start.x = start.x;
	this->start.y = start.y;
	this->target.x = target.x;
	this->target.y = target.y;

	movementSteps = givenMovementSteps;
	this->mutationP = mutationP;
	this->mutationF = mutationF;
	this->mutationFt = mutationFt;
	startPopulationSize = populationSize;
	createPopulation();
}

Environment::~Environment() {}

WormBase * Environment::getBestWorm() {
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
	return bestWorm->getDistanceToTarget();
}

void Environment::createPopulation(){
	for(int i = 0; i < startPopulationSize; i++){
		population.push_back(new WormBase(&start, &target));
	}
	bestWorm = *population.begin();
}

void Environment::mutate(){
	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		(*currentWorm)->mutate(mutationP, mutationF, mutationFt);
	}
}

void Environment::cross(){
	list<WormBase*> newPopulation;
	WormBase* mather;
	WormBase* father;

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
}

void Environment::eliminate(){
	unsigned int baseSize = population.size();
	unsigned int targetSize = baseSize / 2;

	list<WormBase*>::iterator competitior1;
	list<WormBase*>::iterator competitior2;

	WormBase* winner;
	while(population.size() != targetSize){
		competitior1 = population.begin();
	    advance(competitior1, rand() % population.size());

	    competitior2 = population.begin();
	    advance(competitior2, rand() % population.size());

	    WormBase* loser;
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

}

int Environment::compare(WormBase* w1, WormBase* w2) {
	float d1 = w1->getDistanceAfterNMoves(movementSteps, &target);
	float d2 = w2->getDistanceAfterNMoves(movementSteps, &target);

	//cout << d1 << " " << d2 << endl;

	if(d1 <= d2){
		return 1;
	} else {
		return 2;
	}

//	return 1;
	/*
	for(int i = 0; i < movementSteps; i++){
		w1->move();
		w2->move();
	}
	w1->reset();
	w2->reset();

	Point * p1 = w1->getPosition();
	Point * p2 = w2->getPosition();

	float d1 = sqrt(pow((p1->x - target.x),2) + pow((p1->y - target.y),2));
	float d2 = sqrt(pow((p2->x - target.x),2) + pow((p2->y - target.y),2));

	delete p1;
	delete p2;

	if(d1 <= d2){
		return 1;
	} else {
		return 2;
	}
	*/
}

void Environment::resetWorms(){
	for(currentWorm = population.begin(); currentWorm != population.end(); ++currentWorm){
		(*currentWorm)->reset();
	}
}
