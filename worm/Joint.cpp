/*
 * Joint.cpp
 *
 *  Created on: 29 gru 2013
 *      Author: jedrek
 */

#include "Joint.h"

using namespace std;

Joint::Joint(int x, int y, bool positive) {
	this->positive = positive;
	startX = x;
	startY = y;

	reset(true);

	d = 30.0;

	leftJoint = 0;
	rightJoint = 0;

	recalculate(true);
}

void Joint::reset(bool first){
	resetAngles();

	a.x = startX;
	a.y = startY;

	if(!first){
		recalculate(true);
		propagateRight(true);
	}
}

void Joint::resetAngles(){
	if(positive){
		alpha = 60;
	} else {
		alpha = 300;
	}
	beta = 0;
}

void Joint::setLeft(Joint* j){
	leftJoint = j;
}

void Joint::setRight(Joint* j){
	rightJoint = j;
	propagateRight();
}

void Joint::setAB(Point a, Point b, bool resetAngles){

	if(resetAngles){
		this->resetAngles();
	}

	this->a.x = a.x;
	this->a.y = a.y;
	this->b.x = b.x;
	this->b.y = b.y;

	recalculateBeta(true);
	propagateRight(resetAngles);
}

void Joint::setCB(Point c, Point b){
	this->c.x = c.x;
	this->c.y = c.y;
	this->b.x = b.x;
	this->b.y = b.y;

	recalculateBeta(false);
	propagateLeft();
}

void Joint::propagate(){
	propagateRight();
	propagateLeft();
}

void Joint::propagateRight(bool resetAngles){
	if(rightJoint != 0){
		rightJoint->setAB(b, c, resetAngles);
	}
}

void Joint::propagateLeft(){
	if(leftJoint != 0){
		leftJoint->setCB(b, a);
	}
}


void Joint::recalculate(bool left){
	//if left a point is steady, if not c point is steady
	float g = 2 * d * sin((alpha/2.0)*PI/180);
	float omega = 90 - alpha/2 - beta;
	float dx = g * cos(beta*PI/180);
	float dy = g * sin(beta*PI/180);

	if(left){
		c.x = a.x + dx;
		c.y = a.y + dy;
	} else {
		a.x = c.x - dx;
		a.y = c.y - dy;
	}

	dx = d * cos(omega*PI/180);
	dy = d * sin(omega*PI/180);
	b.x = a.x + dx;
	b.y = a.y - dy;

	recalculateBeta(left);
}

void Joint::recalculateBeta(bool left) {

	Point p;
	if(left){
		p.x = a.x;
		p.y = a.y;
	} else {
		p.x = c.x;
		p.y = c.y;
	}

	float g = 2 * d * sin((alpha/2.0)*PI/180);

	AA = (b.x - p.x) / (p.y - b.y);
	BB = (p.x*p.x - b.x*b.x + p.y*p.y - b.y*b.y + d*d - g*g) / (2 * (p.y - b.y));

	AAA = 1 + AA*AA;
	BBB = 2*(AA*BB - b.x - AA*b.y);
	CCC = b.x*b.x + BB*BB - 2*BB*b.y + b.y*b.y - d*d;

	float delta = BBB*BBB - 4*AAA*CCC;

	min = - BBB / (2*AAA);

	float hx = min;
	float hy = AA*min + BB;
	h = g * sin((90 - alpha/2)*PI/180);
	float Ac = 1;
	float Bc = - 2 * hx;
	float Cc = hx * hx  - (h*h)/(1 + AA*AA);
	delta = Bc*Bc - 4*Ac*Cc;

	if(delta >= 0){
		float x1 = (- Bc - sqrt(delta)) / 2*Ac;
		float x2 = (- Bc + sqrt(delta)) / 2*Ac;

		float y1 = AA * x1 + BB;
		float y2 = AA * x2 + BB;

		Point * referencePoint;
		if(left){
			referencePoint = &c;
		} else {
			referencePoint = &a;
		}

		float d1 = (referencePoint->x - x1)*(referencePoint->x - x1) + (referencePoint->y - y1)*(referencePoint->y - y1);
		float d2 = (referencePoint->x - x2)*(referencePoint->x - x2) + (referencePoint->y - y2)*(referencePoint->y - y2);

		if(d1 < d2){
			referencePoint->x = x1;
			referencePoint->y = y1;
		} else {
			referencePoint->x = x2;
			referencePoint->y = y2;
		}

	}
}

Joint::~Joint() {
	leftJoint = 0;
	rightJoint = 0;
}

bool Joint::canIncreaseAlpha(){
	//if((positive && alpha < 80) || (!positive && alpha < 320)){
	if((positive && alpha < 100) || (!positive && alpha < 340)){
		return true;
	} else {
		return false;
	}
}

bool Joint::canDecreaseAlpha(){
	//if((positive && alpha > 40) || (!positive && alpha > 280)){
	if((positive && alpha > 20) || (!positive && alpha > 260)){
		return true;
	} else {
		return false;
	}
}

bool Joint::canIncreaseBeta(){
	if(beta < 40){
		return true;
	} else {
		return false;
	}
}

bool Joint::canDecreaseBeta(){
	if(beta > -40){
		return true;
	} else {
		return false;
	}
}

void Joint::increaseAlpha(){
	float step = 1;
	if(positive){
		if(canIncreaseAlpha()){
			alpha += step;
			recalculate(true);
			propagate();
		}
	} else {
		if(canDecreaseAlpha()){
			alpha = alpha - step;
			recalculate(true);
			propagate();
		}
	}
}

void Joint::decreaseAlpha(){
	float step = 1;
	if(!positive){
		if(canIncreaseAlpha()){
			alpha += step;
			recalculate(false);
			propagate();
		}
	} else {
		if(canDecreaseAlpha()){
			alpha -= step;
			recalculate(false);
			propagate();
		}
	}
}

void Joint::increaseBetaLeft(){
	float step = 0.1;
	if(canIncreaseBeta()){
		beta += step;
		recalculate(true);
		propagate();
	}
}

void Joint::decreaseBetaLeft(){
	float step = 0.1;
	if(canDecreaseBeta()){
		beta -= step;
		recalculate(true);
		propagate();
	}
}

void Joint::increaseBetaRight(){
	float step = 0.1;
	if(canDecreaseBeta()){
		beta -= step;
		recalculate(false);
		propagate();
	}
}

void Joint::decreaseBetaRight(){
	float step = 0.1;
	if(canIncreaseBeta()){
		beta += step;
		recalculate(false);
		propagate();
	}
}

void Joint::setStartPoint(int x, int y){
	startX = x;
	startY = y;
}

void Joint::draw(SDL_Surface* screen){
    lineRGBA(screen, a.x, a.y, b.x, b.y, 255, 0, 0, 255);
    lineRGBA(screen, b.x, b.y, c.x, c.y, 255, 0, 0, 255);
    //lineRGBA(screen, a.x, a.y, c.x, c.y, 0, 0, 255, 255);
    //filledCircleColor(screen, c.x, c.y, 2, 0x3300ff);

    SDL_Flip(screen);
}

void Joint::print() {
	cout << "Jestem przegubem pod adresem " << this << endl;
	cout << "a = (" << a.x << ", " << a.y << ")" << endl;
	cout << "b = (" << b.x << ", " << b.y << ")" << endl;
	cout << "c = (" << c.x << ", " << c.y << ")" << endl;
}
