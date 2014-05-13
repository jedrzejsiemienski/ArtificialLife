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
			break;
		case 1:
			//this.brain = new BrainManyP();
		case 2:
		default:
			//this.brain = new BrainDummy();
			break;
	}
}

Worm::~Worm() {
	delete skeleton;
	delete brain;
}


void Worm::move(){

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
