/*
 * Worm.cpp
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#include "Worm.h"

Worm::Worm(int type, int startX, int startY, int targetX, int targetY, int givenMovementSteps, int initVal) {
	initPoint = new Point(startX, startY);
	endPoint = new Point(targetX, targetY);
	skeleton = new Skeleton(startX, startY);
	movementSteps = givenMovementSteps;
	setBrainByType(type, initVal);
}

Worm::Worm(int type, string name) {
	initPoint = new Point(0, 0);
	endPoint = new Point(0, 0);
	movementSteps = 0;
	setBrainByType(type);
	loadFromFile(name);
}

Worm::Worm(int type, int startX, int startY, int targetX, int targetY, Genotype* source, int givenMovementSteps){
	initPoint = new Point(startX, startY);
	endPoint = new Point(targetX, targetY);
	skeleton = new Skeleton(startX, startY);
	movementSteps = givenMovementSteps;
	setBrainByType(type);
	brain->setGenotype(source);
}

void Worm::setBrainByType(int type, int initVal){
	switch(type){
		case 1:
			setBrain(new BrainOnePerceptron(initVal));
			break;
		case 2:
			setBrain(new BrainManyPerceptrons(initVal));
			break;
		case 3:
			setBrain(new BrainDummy());
			break;
		case 4:
			setBrain(new BrainRandom());
			break;
		case 0:
		default:
			brain = 0; // add brain manually
			break;
	}
}

Worm::~Worm() {
	delete skeleton;
	delete brain;
	delete initPoint;
	delete endPoint;
}

void Worm::setBrain(BaseBrain* givenBrain){
	brain = givenBrain;
	brain->setInitPoint(initPoint->x, initPoint->y);
	brain->setEndPoint(endPoint->x, endPoint->y);
	brain->movementSteps = movementSteps;
}

BaseBrain* Worm::getBrain(){
	return brain;
}

void Worm::move(){
	int ** result = brain->stimulate(
		skeleton->getBeta1(),
		skeleton->getBeta2(),
		skeleton->getAlpha1(),
		skeleton->getAlpha2(),
		skeleton->getAlpha3()
	);

	int i = 0;
	if(result[i][0] == 1){
		if(result[i][1] == 1){
			skeleton->moveLeftJoint(true);
		} else {
			skeleton->moveLeftJoint(false);
		}
	}

	i++;
	if(result[i][0] == 1){
		if(result[i][1] == 1){
			skeleton->moveFirstJoint(true);
		} else {
			skeleton->moveFirstJoint(false);
		}
	}

	i++;
	if(result[i][0] == 1){
		if(result[i][1] == 1){
			skeleton->moveSecondJoint(true);
		} else {
			skeleton->moveSecondJoint(false);
		}
	}

	i++;
	if(result[i][0] == 1){
		if(result[i][1] == 1){
			skeleton->moveThirdJoint(true);
		} else {
			skeleton->moveThirdJoint(false);
		}
	}

	i++;
	if(result[i][0] == 1){
		if(result[i][1] == 1){
			skeleton->moveRightJoint(true);
		} else {
			skeleton->moveRightJoint(false);
		}
	}

	for(int j = 0; j < 5; j++){
		delete result[j];
	}
	delete[] result;
}

void Worm::draw(SDL_Surface* screen){
	skeleton->draw(screen);
}

Point * Worm::getPosition(){
	return skeleton->getPosition();
}

Point * Worm::getInitPoint(){
	return initPoint;
}

Point * Worm::getEndPoint(){
	return endPoint;
}

float Worm::getCurrentDistanceToTarget(){
	Point * p1 = getPosition();
	float currenDtistance = sqrt(pow((p1->x - endPoint->x),2) + pow((p1->y - endPoint->y),2));
	delete p1;
	return currenDtistance;
}

float Worm::getDistanceAfterNMoves(int n){
	for(int i = 0; i < n; i++){
		move();
	}
	float result = getCurrentDistanceToTarget();
	reset();
	return result;
}

float Worm::getMovementSteps(){
	return movementSteps;
}

void Worm::saveToFile(string name){
	brain->saveToFile(name);
}

void Worm::loadFromFile(string name){
	brain->loadFromFile(name);
	initPoint->x = brain->getInitPoint()->x;
	initPoint->y = brain->getInitPoint()->y;
	endPoint->x = brain->getEndPoint()->x;
	endPoint->y = brain->getEndPoint()->y;
	movementSteps = brain->movementSteps;
	skeleton = new Skeleton(initPoint->x, initPoint->y);
}

//TOFIX
void Worm::reset(){
	brain->reset();
	skeleton->reset();
}


