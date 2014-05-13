/*
 * Skeleton.cpp
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#include "Skeleton.h"

using namespace std;

Skeleton::Skeleton(float startX, float startY, float targetX, float targetY) {
	initPoint = new Point(startX, startY);
	endPoint = new Point(targetX, targetY);

	distance = -1;
	jointsCount = 3;
	joints = new Joint*[jointsCount];

	bool positive;
	for(int i=0; i < jointsCount; i++){
		positive = i%2 == 0;
		joints[i] = new Joint(initPoint->x, initPoint->y, positive);
		if(i > 0){
			joints[i-1]->setRight(joints[i]);
			joints[i]->setLeft(joints[i-1]);
		}
	}
}

Skeleton::~Skeleton() {
	for(int i = 0; i < jointsCount; i++){
		delete joints[i];
	}
	delete[] joints;
	delete initPoint;
	delete endPoint;
}

Point * Skeleton::getEndPoint(){
	return endPoint;
}

Point * Skeleton::getInitPoint(){
	return initPoint;
}

Point * Skeleton::getPosition(){
	Point * c = new Point();
	c->x = joints[0]->a.x;
	c->y = joints[0]->a.y;
	return c;
}

void Skeleton::reset(){
	joints[0]->reset(false);
}

void Skeleton::draw(SDL_Surface* screen){
	for(int i=0; i < jointsCount; i++){
		joints[i]->draw(screen);
	}
}

void Skeleton::moveFirstJoint(bool increase){
	moveCenterJoint(increase, 0);
}

void Skeleton::moveSecondJoint(bool increase){
	moveCenterJoint(increase, 1);
}
void Skeleton::moveThirdJoint(bool increase){
	moveCenterJoint(increase, 2);
}

void Skeleton::moveCenterJoint(bool increase, int i){
	if(increase){
		joints[i]->increaseAlpha();
	} else {
		joints[i]->decreaseAlpha();
	}
}

void Skeleton::moveLeftJoint(bool increase){
	if(increase){
		joints[0]->increaseBetaLeft();
	} else {
		joints[0]->decreaseBetaLeft();
	}
}

void Skeleton::moveRightJoint(bool increase){
	if(increase){
		joints[jointsCount-1]->increaseBetaRight();
	} else {
		joints[jointsCount-1]->decreaseBetaRight();
	}
}

float Skeleton::getCurrentDistanceToTarget(Point * target){
	Point * p1 = getPosition();
	float currenDtistance = sqrt(pow((p1->x - target->x),2) + pow((p1->y - target->y),2));
	delete p1;
	return currenDtistance;
}

int Skeleton::normalizeAlpha(float a, bool positive){
	float b;
	if(a > 180){
		b = a - 180;
	} else {
		b = a;
	}

	if(!positive){
		b = b - 60;
	}
	b = b - 20;
	return b;
}

int Skeleton::normalizeBeta(float a){
	return a + 90;
}
