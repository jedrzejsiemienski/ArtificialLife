/*
 * Skeleton.h
 *
 *  Created on: 6 sty 2014
 *      Author: jedrek
 */

#ifndef SKELETON_H_
#define SKELETON_H_

#include "Joint.h"
#include "../utils/Point.h"
#include "SDL.h"
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

class Skeleton {
public:
	Skeleton(float, float, float, float);
	virtual ~Skeleton();

	void draw(SDL_Surface*);
	void reset();

	void moveLeftJoint(bool);   //beta, first joint
	void moveRightJoint(bool);  //beta, third joint
	void moveFirstJoint(bool);  //alpha, first joint
	void moveSecondJoint(bool); //alpha, second joint
	void moveThirdJoint(bool);  //alpha, third joint

	Point * getPosition();
	Point * getInitPoint();
	Point * getEndPoint();

	float getCurrentDistanceToTarget(Point *);

private:
	Point * initPoint;
	Point * endPoint;

	float distance;
	int jointsCount;
	Joint** joints;

	void moveCenterJoint(bool, int);
	int normalizeAlpha(float, bool);
	int normalizeBeta(float);
};

#endif /* SKELETON_H_ */
