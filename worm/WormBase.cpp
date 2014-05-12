/*
 * WormBase.cpp
 */

#include "WormBase.h"

using namespace std;

WormBase::WormBase(Point * initPoint, Point * endPoint) {
	/*
	this->initPoint = new Point(initPoint->x, initPoint->y);
	this->endPoint = new Point(endPoint->x, endPoint->y);

	distance = -1;
	lastLinkMoved = 0;
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
	*/
}

WormBase::~WormBase() {
	/*
	for(int i = 0; i < jointsCount; i++){
		delete joints[i];
	}
	delete[] joints;
	delete initPoint;
	*/
}

/*
Point * WormBase::getEndPoint(){
	return endPoint;
}

Point * WormBase::getInitPoint(){
	return initPoint;
}

Point * WormBase::getPosition(){
	Point * c = new Point();
	c->x = joints[0]->a.x;
	c->y = joints[0]->a.y;
	return c;
}

void WormBase::draw(SDL_Surface* screen){
	for(int i=0; i < jointsCount; i++){
		joints[i]->draw(screen);
	}
}

void WormBase::moveCenterJoint(int i){
	int x, y, z;
	x = 0;
	y = normalizeAlpha(joints[i]->alpha, joints[i]->positive);
	z = 0;

	if(i > 0){
		x = normalizeAlpha(joints[i-1]->alpha, joints[i-1]->positive);
		z = normalizeAlpha(joints[i-1]->alpha, joints[i-1]->positive);
	}

	if(i < jointsCount - 1){
		z = normalizeAlpha(joints[i+1]->alpha, joints[i+1]->positive);
		x = normalizeAlpha(joints[i+1]->alpha, joints[i+1]->positive);
	}

	if(i == 0 || i == jointsCount - 1){
		x = normalizeBeta(joints[0]->beta);
		z = normalizeBeta(joints[jointsCount-1]->beta);
	}


	int * result = stimulatePerceptron(i, x, y, z);
	if(result[0] == 1){
		if(result[1] == 1){
			joints[i]->increaseAlpha();
		} else {
			joints[i]->decreaseAlpha();
		}
	}

	delete[] result;

	/*
	if(result[0] == 1 && result[1] == 0){
		joints[i]->increaseAlpha();
	} else if(result[0] == 0 && result[1] == 1){
		joints[i]->decreaseAlpha();
	}
	*//*
}

void WormBase::moveLeftJoint(){
	int x, y, z;
	x = normalizeBeta(joints[0]->beta);
	y = normalizeAlpha(joints[0]->alpha, joints[0]->positive);
	z = normalizeBeta(joints[jointsCount-1]->beta);
	int * result = stimulatePerceptron(jointsCount, x, y, z);
	//cout << "x - " << x << ", y - " << y << ", z - " << z << endl;
	if(result[0] == 1){
		if(result[1] == 1){
			joints[0]->increaseBetaLeft();
		} else {
			joints[0]->decreaseBetaLeft();
		}
	}
	delete[] result;
}

void WormBase::moveRightJoint(){
	int x, y, z;
	x = normalizeBeta(joints[jointsCount-1]->beta);
	y = normalizeAlpha(joints[jointsCount-1]->alpha, joints[jointsCount-1]->positive);
	z = normalizeBeta(joints[0]->beta);
	int * result = stimulatePerceptron(jointsCount + 1, x, y, z);
	//cout << "x - " << x << ", y - " << y << ", z - " << z << endl;
	if(result[0] == 1){
		if(result[1] == 1){
			joints[jointsCount-1]->increaseBetaRight();
		} else {
			joints[jointsCount-1]->decreaseBetaRight();
		}
	}
	delete[] result;
}

float WormBase::getDistanceToTarget(){
	return distance;
}

float WormBase::getDistanceAfterNMoves(int movesCount, Point * target, bool verbose){
	if(distance == -1.0){
		for(int i = 0; i < movesCount; i++){
			move();
			if(verbose){
				cout << getCurrentDistance(target) << endl;
			}
		}
		distance = getCurrentDistance(target);
		reset();
	}
	return distance;
}

float WormBase::getCurrentDistance(Point * target){
	Point * p1 = getPosition();
	float currenDtistance = sqrt(pow((p1->x - target->x),2) + pow((p1->y - target->y),2));
	//cout << p1->x << " " << p1->y << " - " << target->x << " " << target->y << " : " << currenDtistance << endl;
	delete p1;
	return currenDtistance;
}

void WormBase::move(){
	//cout << "move" << endl;

	if(lastLinkMoved < jointsCount){
		moveCenterJoint(lastLinkMoved);
	}

	if(lastLinkMoved == jointsCount){
		moveLeftJoint();
	}

	if(lastLinkMoved == jointsCount + 1){
		moveRightJoint();
	}

	lastLinkMoved++;
	if(lastLinkMoved == jointsCount + 2){
		lastLinkMoved = 0;
	}

	//cout << getPosition().x << " - " << getPosition().y << endl;
}

int WormBase::normalizeAlpha(float a, bool positive){
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

	//cout << "alfa " << b << endl;
	return b;
}

int WormBase::normalizeBeta(float a){
	return a + 90;
}

bool WormBase::tossACoin(){
	if(rand() % 2 == 0){
		return true;
	} else {
		return false;
	}
}
*/
