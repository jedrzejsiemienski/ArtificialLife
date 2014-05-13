/*
 * Worm.cpp
 *
 *  Created on: 13 maj 2014
 *      Author: jedrek
 */

#include "Worm.h"

Worm::Worm(int type, int startX, int startY, int targetX, int targetY) {
	endPoint = new Point(targetX, targetY);
	skeleton = new Skeleton(startX, startY);
	switch(type){
		case 0:
			//this.brain = new BrainOneP();
		case 1:
			//this.brain = new BrainManyP();
		case 2:
		default:
			brain = new BrainDummy();
			break;
	}
}

Worm::~Worm() {
	delete skeleton;
	delete brain;
	delete endPoint;
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
	if(result[i][1] == 1){
		if(result[i][1] == 1){
			skeleton->moveFirstJoint(true);
		} else {
			skeleton->moveFirstJoint(false);
		}
	}

	i++;
	if(result[i][1] == 1){
		if(result[i][1] == 1){
			skeleton->moveSecondJoint(true);
		} else {
			skeleton->moveSecondJoint(false);
		}
	}

	i++;
	if(result[i][1] == 1){
		if(result[i][1] == 1){
			skeleton->moveThirdJoint(true);
		} else {
			skeleton->moveThirdJoint(false);
		}
	}

	i++;
	if(result[i][1] == 1){
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
	return skeleton->getInitPoint();
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
