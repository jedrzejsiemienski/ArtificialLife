/*
 * Worm.cpp
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#include "Worm.h"

Worm::Worm(int type, int startX, int startY, int targetX, int targetY) {
	initPoint = new Point(startX, startY);
	endPoint = new Point(targetX, targetY);
	skeleton = new Skeleton(startX, startY);
	setBrainByType(type);
}

Worm::Worm(int type, string name) {
	initPoint = new Point(0, 0);
	endPoint = new Point(0, 0);
	setBrainByType(type);
	loadFromFile(name);
}

void Worm::setBrainByType(int type){
	switch(type){
		case 1:
			setBrain(new BrainOnePerceptron());
			break;
		case 2:
			setBrain(new BrainManyPerceptrons());
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
	delete endPoint;
}

void Worm::setBrain(BaseBrain* givenBrain){
	brain = givenBrain;
	brain->setInitPoint(initPoint->x, initPoint->y);
	brain->setEndPoint(endPoint->x, endPoint->y);
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

	delete result;
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
	return 0.0; //do napisania
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
	skeleton = new Skeleton(initPoint->x, initPoint->y);
}

void Worm::reset(){
	brain->reset();
	skeleton->reset();
}


